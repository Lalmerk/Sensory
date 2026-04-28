#include <Arduino.h>
#include <ini.h>
#include <HI_calculation.h>
#include <warning.h>




#define red_LED 2
#define blue_LED 4
#define green_LED 7 //LEDS
#define buzzer 13  //buzzer


#define DHTPIN 5     // The digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // The specific model of your sensor change to DHT22 or DHT11 depending on the model


DHT sensor(DHTPIN, DHTTYPE); //DHT object
LiquidCrystal_I2C screen(0x27, 16, 2);

void setup() 
{
  
  int POST_Status;

  pinMode(red_LED, OUTPUT);  
  pinMode(blue_LED, OUTPUT); 
  pinMode(green_LED, OUTPUT); 
  pinMode(buzzer, OUTPUT); 

  Serial.begin(9600);
  Serial.println("System Initializing");

  POST_Status = startPOST(&sensor,&screen);

  switch (POST_Status)
  {
    case 0: //Everything works 
      
      screen.clear();
      screen.setCursor(0,0);
      screen.print("Welcome!");

      digitalWrite(green_LED, HIGH);

      tone(buzzer, NOTE_C4, 150);
      delay(buzzer);
      tone(buzzer, NOTE_E4, 150);

      delay(200);

      tone(buzzer, NOTE_G4, 150);
      delay(buzzer);
      tone(buzzer, NOTE_C5, 300); 
      delay(300);

      screen.clear();
      digitalWrite(green_LED, LOW);
      break;
    
    case 1: // DHT sensor offline
     
      for (int i = 0; i < 3; i++) //beeps and blinks 3 times
        {
          
          screen.clear();
          screen.setCursor(0, 0);
          screen.print("DHT Offline");

          digitalWrite(red_LED, HIGH);
          tone(buzzer, NOTE_A4);

          delay(500);

          
          digitalWrite(red_LED, LOW);
          noTone(buzzer);     
          delay(500);
        }
        while (1) //traps the program to debug state until user restarts or turn off the device
        {
          digitalWrite(red_LED, HIGH);
          delay(500);
          digitalWrite(red_LED, LOW);
          delay(500);
        }
      
      break;

    case 2: //screen is not available check connection

      for (int i = 0; i < 3; i++) //beeps and blinks 3 times
        {
          

          digitalWrite(blue_LED, HIGH);
          tone(buzzer, NOTE_B0);

          delay(500);

          
          digitalWrite(blue_LED, LOW);
          noTone(buzzer);     
          delay(500);
        }
        while (1) //traps the program to debug state until user restarts or turn off the device
        {
          digitalWrite(blue_LED, HIGH);
          delay(500);
          digitalWrite(blue_LED, LOW);
          delay(500);
        }

      break;
    
    case 3: //DHT sensor and Screen not available

        for (int i = 0; i < 3; i++) //beeps and blinks 3 times
        {
          
          

          digitalWrite(red_LED, HIGH);
          digitalWrite(blue_LED, HIGH);
          tone(buzzer, NOTE_A4);
          tone(buzzer, NOTE_B0);

          delay(500);

          
          digitalWrite(red_LED, LOW);
          digitalWrite(blue_LED, LOW);
          noTone(buzzer);     
          delay(500);
        }
        while (1) //traps the program to debug state until user restarts or turn off the device
        {
          digitalWrite(red_LED, HIGH);
          digitalWrite(blue_LED, HIGH);
          delay(500);
          digitalWrite(red_LED, LOW);
          digitalWrite(blue_LED, LOW);
          delay(500);
        }

      break;

    default: //check all peripherals if functioning 
        digitalWrite(green_LED, HIGH);
        digitalWrite(red_LED, HIGH);
        digitalWrite(blue_LED, HIGH);

        delay(3000);

        digitalWrite(green_LED, HIGH);
        digitalWrite(red_LED, LOW);
        digitalWrite(blue_LED, LOW);

      break;
  }
  
  


}

void loop() 
{
 
  float tempC = sensor.readTemperature();
  float humidity = sensor.readHumidity();
  float tempF = convertToFahrenheit(tempC);
  float HI; //Heat Index is in Celsius
  if (isnan(tempC) || isnan(humidity)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    
    screen.clear();
    screen.setCursor(0,0);
    screen.print("DHT Sensor FAIL");

    digitalWrite(red_LED, HIGH);
    tone(buzzer, NOTE_A4);
    delay(5000);

    noTone(buzzer);
    digitalWrite(red_LED, LOW);
    


    return; // Skip the rest of the loop if there's an error
  }

  if (tempF >= 80.0) 
  {
   
    HI = SteadmanFormula(tempF, humidity);
    Serial.print("Heat Index: ");
    Serial.println(HI);

    switch (Warning(HI))
    {
      case 0:
          // Everything is fine
          screen.clear();
          screen.setCursor(0, 0);
          screen.print("Status: Normal  ");
          delay(5000);
          screen.clear();
          break;

        case 1:
          // 27-32 Caution
          screen.clear();
          screen.setCursor(0, 0);
          screen.print("Status: Caution ");
          delay(5000);
          screen.clear();

          break;
        
        case 2:
          // 33-41 
          screen.setCursor(0, 0);
          screen.print("EXTREME CAUTION ");
          delay(5000);
          screen.clear();
          break;

        case 3:
          // 42-51  Danger
          screen.setCursor(0, 0);
          screen.print("STATUS: DANGER! ");
          delay(5000);
          screen.clear();
          break;

        case 4:
            // 52+ 
            screen.setCursor(0, 0);
            screen.print("EXTREME DANGER!!");
            delay(5000);
          screen.clear();
          
            break;

        default:
            screen.clear();
            screen.setCursor(0, 0);
            screen.print("Check Sensor... ");
            delay(5000);
            screen.clear();
            break;
    }
    

  } 
  else 
  {
      
    Serial.print("Temperature is below threshold. Current Temp: ");
    Serial.println(tempC);

    screen.clear();
    screen.setCursor(0,0);
    screen.print("Air Temp: ");
    screen.print(tempC);
    screen.print(char(223)); 
    screen.print("C");

    digitalWrite(blue_LED, HIGH);
    delay(5000);
    screen.clear();
    digitalWrite(blue_LED, LOW);
  }

 

   



}