#define LED_PIN 13
#define LDR_PIN A0

int encender = 0;
int valorLDR = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    encender = Serial.parseInt();
  }

  valorLDR = analogRead(LDR_PIN);

  if (encender == 1) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  Serial.println(valorLDR);

  delay(500);
}
