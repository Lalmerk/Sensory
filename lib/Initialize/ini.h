#pragma once

#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"
#include <Wire.h>

int startPOST(DHT *sensor, LiquidCrystal_I2C *screen) 
{ //we use -> arrow because we used a pointer as parameter
    
  int errorTotal = 0;//tracks the error and returns it all at once for debugging efficiency instead of returning error 1 by 1
  
  sensor->begin();
  delay(2000);
  
    
    float temp = sensor->readTemperature();

   
    
  if(isnan(temp))
  {
    errorTotal += 1; 
  }
  
  Wire.beginTransmission(0x27);
  if(Wire.endTransmission() != 0)
  {
    errorTotal += 2;
  }
  else
  {
    screen->init();
    screen->backlight();
    screen->setCursor(0, 0);
    screen->print("System Check");
    screen->setCursor(0,1);
    screen->print("Success!!");
    
    delay(2000);
  }

  return errorTotal;

}

