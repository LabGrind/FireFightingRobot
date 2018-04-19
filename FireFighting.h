#include "Arduino.h"
#include "Servo.h"

class FireFighting
{
	public:
		void firefightingSetup(int pPin, int fPin, int sPin);
    bool fireScan();
		void activateFan();
    void fireFight();
	
	private:
    int fanPin;
    int servoPin;

    float reading;

    bool fireStarted = false;
    bool fireDetected = false;
    int fireStart = 0;
    int fireEnd = 0;



    bool fireFound = false;
    bool fireExists = false;
    int pin;
    float voltage;
    Servo servo;
	  //Light reading variables
	  int lightfilterArray[15] = {90,90,90,90,90,90,90,90,90,90,90,90,90,90,90};
    int i = 0;
		int lightfilterIndex = 0;
		int maxLightReading = 0;
		int maxLightPos = 0;
    int fireCount = 2;
		//Boolean variable to prevent the code from running multiple different times
		bool oneRound = false;
};
