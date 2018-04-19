#include "FireFighting.h"
#include "Servo.h"

//Setting up the analog input
void FireFighting::firefightingSetup (int pPin, int fPin, int sPin)
{
  this->pin = pPin;
  fanPin = fPin;
  servoPin = sPin;
 
  pinMode(fanPin, OUTPUT);
  pinMode(pin, INPUT);
  Serial.begin(115200);
  servo.attach(sPin);
  servo.write(90);
}

bool FireFighting::fireScan(){
  Serial.println("Scanning");
  //Bring the servo to the zero position before it starts reading anything
  servo.write(0);
  delay(100);

  //Sweep Through 
  for (int i=15; i<165; i++) {
    servo.write(i);
    float firstReading, reading;
    
    for(int j = 0; j < 5; j++){
      firstReading += analogRead(pin);
    }
  
    reading = firstReading/5;
    firstReading = 0;
    //Serial.println(reading);

    //Logging down the first position of the fire
    if((reading > 700) && (fireStarted == false))
    {
      fireStart = i;
      //this variable is used as the primary variable that indicates the presence of a fire
      fireStarted = true;
    }
      
    if((fireStarted == true) && (reading < 700) && (fireDetected == false))
    {
      fireEnd = i;
      fireDetected = true;    
    }
/*
    Serial.println("fireStart: ");
    Serial.println(fireStart);
    Serial.println("fireEnd: ");
    Serial.println(fireEnd);*/
    delay(20);
  } 

  fireStarted = false;
  
  if(fireDetected == true){
    //Serial.println("Fire Detected");
    fireDetected = false;
    return true;
  } else {
    servo.write(90);
    Serial.println("Error");
    return false;
  }
}

void FireFighting::activateFan()
{
  Serial.println("Firefighting activated");
  servo.write(fireStart);

  delay(200);
  int pointRead = analogRead(pin);
  while(pointRead > 200)
  {
    digitalWrite(fanPin,HIGH);   
    Serial.println("FightingFire");
    for(int i = fireStart; i < fireEnd; i++){
      servo.write(i);
      delay(50);
    }
    for(int i = fireEnd; i >= fireStart; i--){
      servo.write(i);
      delay(50);
    }
    pointRead = analogRead(pin);
  }  
  digitalWrite(fanPin,LOW);
}

void FireFighting::fireFight()
{
  bool fireStat = fireScan();
  while(fireStat == true){
    activateFan();
    delay(200);
    fireStat = fireScan();
  }
  servo.write(90);
}

/*
void FireFighting::firefight()
{
 
 if(oneRound == false){
  //For angle of 0 to 180, the servo will sweep through, read from the phototransistor and compare whether the reading is larger than the current stored value for
  //the largest light reading and also its corresponding position (this will not change if it is smaller or equal to)
  for (int i=0; i<=180; i++) {
    //Move to the current positon of i
    servo.write(i);
    float voltage = analogRead(pin);
    //To prevent the robot stopping at a "trash position" it will only register a position IF the raw reading is above 700 (which is the value obtained when the phototransistor is directly in front of the fire)
    if(voltage > 700){   
      if(lightfilterIndex < 10){
        lightfilterArray[lightfilterIndex] = i;
      }
      lightfilterIndex++;
      fireFound = true;
      fireExists = true;
    }
    delay(15);
    }

  //Move the servo to the position of the maximum light reading
  if(fireFound == true){
    servo.write(lightfilterArray[8]);
    delay(200);
  } else {
    servo.write(90);
  }

  if(fireExists == true){
    while(fireExists == true){
      digitalWrite(fanPin,HIGH);
      int fire = analogRead(pin);
      if(fire < 80){
        fireExists = false;
      }
      delay(100);
    }
  } else if(fireExists == false){
    digitalWrite(fanPin,LOW);
  }
} 
}
*/
