
const int relay = 2;
String receive;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
}

void loop() {
  
  if(Serial.available() > 0) {
    receive = Serial.readString();
    Serial.println(receive);
    /*
    digitalWrite(tx, HIGH);
    delay(100);
    digitalWrite(tx, LOW);
    */
  }
  
  delay(100);
}
