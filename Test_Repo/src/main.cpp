// 4-Wire PWM Fan Control
// Simple PWM control of fan with Arduino Mini Pro (5V)
// Fan Wiring
// Pin 1 -> 0VDC
// Pin 2 -> +12VDC
// Pin 3 -> Tach signal
// Pin 4 -> PWM Control (25kHz)

// Arduino Mini Wiring
// Pin 3 -> PWM Control

#include <Arduino.h>

int16_t PWMPin = 3;

void setup() {
  pinMode(PWMPin, OUTPUT);           // this is the PWM signal to the fan
  pwm25kHzBegin();                   // set up registers for 25kHz PWM control
  pwmDuty(0);                        // fan is off to start
}

void loop() {
  // Test code
  pmwDuty(0);                         // 0% 
  delay(5000);                        // wait
  pwmDuty(19);                        // 25% (range = 0-79 = 1.25-100%)
  delay(5000);                        // wait, then speed up
  pwmDuty(39);                        // 50% (range = 0-79 = 1.25-100%)
  delay (5000);                       // wait
  pwmDuty(59);                        // 75% (range = 0-79 = 1.25-100%)
  delay (5000);                       // wait
  pwmDuty(79);                        // 100% (range = 0-79 = 1.25-100%)
  delay (5000);                       // wait
}

void pwm25kHzBegin() {
  TCCR2A = 0;                                             // TC2 Control Register A
  TCCR2B = 0;                                             // TC2 Control Register B
  TIMSK2 = 0;                                             // TC2 Interrupt Mask Register
  TIFR2 = 0;                                              // TC2 Interrupt Flag Register
  TCCR2A |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);  // OC2B cleared/set on match when up/down counting, fast PWM
  TCCR2B |= (1 << WGM22) | (1 << CS21);                   // prescaler 8
  OCR2A = 79;                                             // TOP overflow value (Hz)
  OCR2B = 0;
}

void pwmDuty(byte ocrb) {
  OCR2B = ocrb;                                           // PWM Width (duty)
