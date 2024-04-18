// C++ code
int pins[] = {11, 12, 13};
int numPins = 3;
const int LED=13;
const int BOTON=7;

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(LED, OUTPUT); // LED ROJO (13)
  pinMode(BOTON, OUTPUT);

}

void loop(){  
  for (int i = 0; i < numPins; i++) {
    for (int j = 0; j < numPins; j++){
       while(digitalRead(BOTON)==HIGH){
        	digitalWrite(LED,HIGH);
            digitalWrite(12,LOW);
            digitalWrite(11,LOW);
    	};
          digitalWrite(pins[j], (i == j) ? HIGH : LOW);
  	}
    	delay(1500);	
  }
}
