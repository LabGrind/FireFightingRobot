#include "FireFighting.h"
#define pin A12
FireFighting fireFightingSystem;

enum state {
  firefighting,
  everythingelse
};
state currentState = firefighting;

void setup() {
  fireFightingSystem.firefightingSetup(pin, 45, 3);

}

void loop() {
  
  switch (currentState) {
    case (firefighting):
       fireFightingSystem.fireFight();
       currentState = everythingelse;
       break;
    case (everythingelse):
      break;
    
  }

}
