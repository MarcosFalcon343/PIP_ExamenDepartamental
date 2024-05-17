#include <DHT.h>

#define DHTPIN 2      // Pin donde está conectado el DHT11
#define DHTTYPE DHT11 // Tipo de sensor DHT11
#define MOTOR_DHT_PIN 8  // Pin del motor controlado por el DHT11
#define MOTOR_LDR_PIN 9  // Pin del motor controlado por el LDR
#define LDR_PIN A0       // Pin analógico donde está conectado el LDR

DHT dht(DHTPIN, DHTTYPE);

int motorDHTState = 0;
int motorLDRState = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(MOTOR_DHT_PIN, OUTPUT);
  pinMode(MOTOR_LDR_PIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String datosRecibidos = Serial.readStringUntil('\n');
    int separadorIndex = datosRecibidos.indexOf('%');
    
    if (separadorIndex != -1) {
      motorDHTState = datosRecibidos.substring(0, separadorIndex).toInt();
      motorLDRState = datosRecibidos.substring(separadorIndex + 1).toInt();
    }
  }

  // Controlar el motor basado en el estado recibido
  digitalWrite(MOTOR_DHT_PIN, motorDHTState == 1 ? HIGH : LOW);
  digitalWrite(MOTOR_LDR_PIN, motorLDRState == 1 ? HIGH : LOW);

  // Leer y enviar los valores actuales de temperatura y luz
  float temperature = dht.readTemperature();
  int ldrValue = analogRead(LDR_PIN);
  Serial.print(temperature);
  Serial.print('%');
  Serial.println(ldrValue);

  delay(1000); // Esperar un segundo antes de la próxima lectura y envío
}
