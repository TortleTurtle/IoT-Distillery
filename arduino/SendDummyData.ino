unsigned long startMillis;
unsigned long currentMillis;
const unsigned long interval = 10000; //10 seconds

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  currentMillis = millis();
  if (currentMillis - startMillis >= interval) {
    Serial.print("[64.2]");
    startMillis = currentMillis;
  }
  
  // put your main code here, to run repeatedly:
  Serial.print("<1, 62.5>");
}
