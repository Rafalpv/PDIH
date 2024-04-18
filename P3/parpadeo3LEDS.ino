int pins[] = {11, 12, 13};
int numPins = 3;

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

}

void loop()
{
  for (int i = 0; i < numPins; i++) {
    for (int j = 0; j < numPins; j++) {
      digitalWrite(pins[j], (i == j) ? HIGH : LOW);
    }
    delay(1500);
  }  
}
