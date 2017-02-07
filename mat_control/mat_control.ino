int timer = 0;  //After a trigger, how long until it goes dim

int Pulse = 0;
int PulseD = 1;

int leftSide = 3;
int rightSide = 5;

int lightSensor = A5;    //  Pin the light sensor is on
int pressure = A4;  //Pad pressure
int lightLevel = 0;

void setup() {

  //Serial.begin(9600);
  analogReference(DEFAULT);
  pinMode(leftSide, OUTPUT);
  pinMode(rightSide, OUTPUT); 
  pinMode(13, OUTPUT);
  digitalWrite(13, 1);  //Ready light
}

void loop() {

  lightLevel = analogRead(lightSensor);    

  //Serial.println(analogRead(pressure));

  if (analogRead(pressure) < 800) {  //Someone standing there?

    if (lightLevel > 600) {  //Is it dark in the room?
    
      timer = 1000;  //Keep light on until they step off
    
      if (PulseD == 1 ) {
        Pulse += 1;
        if (Pulse > 254) { 
          PulseD = 0;
        }      
      }  

      if (PulseD == 0 ) {      
        Pulse -= 1;        
        if (Pulse == 64) {  //Never goes fully dim
          PulseD = 1;
        }      
      } 
    }    
  }
  
  if (timer) {
    timer -= 1;    
  }
  
  if (timer == 0) {
    Pulse = 0;
    PulseD = 1;
  }
  
  if (timer > 0 and timer < 512) {
    Pulse -= 0.5;
    
    if (Pulse < 0) {
      Pulse = 0;
      PulseD = 1;
    }
  }
  
  analogWrite(leftSide, Pulse);
  analogWrite(rightSide, Pulse);  

  delay(10);  
  
}
