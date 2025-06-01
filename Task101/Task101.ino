const int sensorPin = A0;
const int pumpPin = 8;
const int threshold = 650; // Adjust based on testing

void setup() {
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, HIGH); // Transistor OFF
  Serial.begin(9600);
}

void loop() {
  int moisture = analogRead(sensorPin);
  Serial.print("Moisture: ");
  Serial.println(moisture);

  if (moisture > threshold) {
    digitalWrite(pumpPin, LOW); // Transistor ON → Pump ON
    Serial.println("Pump ON");
  } else {
    digitalWrite(pumpPin, HIGH); // Transistor OFF → Pump OFF
    Serial.println("Pump OFF");
  }

  delay(2000);
}

