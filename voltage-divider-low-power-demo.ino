#include <JeeLib.h>

#define VOLTAGE_READ_PIN A3
#define VOLTAGE_ENABLE_PIN 8

static float volt_r1 = 56100.0;
static float volt_r2 = 10000.0;
static float voltage = 3.3;
byte ADCSRA_status;

ISR(WDT_vect) { Sleepy::watchdogEvent(); }

void setup() {
  Serial.begin(9600);


  pinMode(VOLTAGE_READ_PIN, INPUT);
  pinMode(VOLTAGE_ENABLE_PIN, OUTPUT);
  digitalWrite(VOLTAGE_ENABLE_PIN, LOW);

  ADCSRA_status = ADCSRA;
  ADCSRA &= ~(1 << 7);

}


void loop() {
  ADCSRA = ADCSRA_status;
  digitalWrite(VOLTAGE_ENABLE_PIN, HIGH);
  float val = analogRead(VOLTAGE_READ_PIN);
  digitalWrite(VOLTAGE_ENABLE_PIN, LOW);
  ADCSRA &= ~(1 << 7);

  Serial.print("IN: ");
  Serial.println( (val * voltage) / 1024.0);

  float vin = ((val * voltage) / 1024.0) / (volt_r2 / ( volt_r1 + volt_r2));
  Serial.println(vin);
  Serial.flush();



  Sleepy::loseSomeTime(9000);
}
