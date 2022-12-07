
const int relay = 2;
String receive;
unsigned long valid[] = {
531303,
532770,
502597,
530497,
531639,
544576,
562141,
565778,
536178,
524204,
545589,
587330,
559263,
524186,
559082,
557755,
575716,
546669,
557993,
547491,
561379,
528891,
545243,
525734,
527099,
590871,
577514,
525154,
533378,
531110,
531335,
548877,
498804,
524318,
549111,
547871};
int max = sizeof(valid) / sizeof(unsigned long);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
}



bool validateInput(String hex) {
  char * pEnd;
  unsigned long num = strtol (hex.substring(6, 12).c_str(), &pEnd, 16);
  Serial.println(num);
  unsigned long mask = 0b000111111111111111111110;
  num = (num & mask) >> 1;
  Serial.println(num);
  for (int i = 0; i < max; i++) {
    if (valid[i] == num) {
      Serial.println("Valid code!");
      return true;
    }
  }
  Serial.println("Not valid code");
  return false;

  
}
void loop() {
  
  if(Serial.available() > 0) {
    receive = Serial.readString();
    Serial.println(receive);
    if (validateInput(receive)) {
      digitalWrite(relay, HIGH);
      delay(100);
      digitalWrite(relay, LOW);
    }
    delay(100);
  }
  
  delay(100);
}
