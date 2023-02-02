
const int relay = 2;
String receive;
unsigned long valid[] = {
552797,
501486,
576110,
575760,
555122,
501486,
502597,
503475,
589592,
532925,
501139,
508391,
575697,
577514,
599053,
525788,
557122,
531034,
557122,
524186,
549111,
557232,
559082,
559263,
531110,
576390,
590784,
536178,
574586,
544576,
593180,
545589,
591269,
498790,
549502,
590871,
545243,
250089,
532731,
524318,
552797,
536486,
547871,
561379,
531013,
531335,
548831,
498804,
532865,
532362,
546669,
589858,
545136,
557993,
593340,
590087,
544745,
552890,
587330,
532770,
370376,
531303};
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
