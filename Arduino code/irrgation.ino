
#include <Wire.h>
#include <Rtc_Pcf8563.h>
#include <EEPROM.h>


Rtc_Pcf8563 rtc;
int irr_hour=0;
int irr_day=0;
int irr_min=0;
int day_of_irr=0;
int value=0;
int in1 =7;
int in2=8;

void setup()
{
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
//-------***this section of the cod use only once to make the calibration***--------------------------------------//
/*
 //clear out the registers
  rtc.initClock();
  //set a time to start with.
  //day, weekday, month, century(1=1900, 0=2000), year(0-99)
  rtc.setDate(30, 6, 10, 0, 24);
  //hr, min, sec
  rtc.setTime(1, 34, 0);


  EEPROM.update(0, 30);
  //both format functions call the internal getTime() so that the 
  //formatted strings are at the current time/date.
  */
//-------***this section of the cod use only once to make the calibration***--------------------------------------//

}

void loop()
{

irr_hour=rtc.getHour();
irr_day=rtc.getDay();
irr_min=rtc.getMinute();
day_of_irr = EEPROM.read(0);


if(irr_day==day_of_irr){
  if(irr_hour==1&&irr_min>=30&&irr_min<=35){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
        Serial.print("----------------:\n");
        Serial.println("---- Irrigation Active ----\n");
        Serial.print("----------------:\n");


  }else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }

  if(irr_hour==2){
    if(rtc.getMonth()==1||rtc.getMonth()==3||rtc.getMonth()==5||rtc.getMonth()==7||rtc.getMonth()==8||rtc.getMonth()==10||rtc.getMonth()==12){
      if(irr_day>=29){
        value=3-(31-irr_day);
        EEPROM.update(0, value);

      }
      else {
        value=irr_day+3;
        EEPROM.update(0, value);
      }

    }
    if(rtc.getMonth()==11||rtc.getMonth()==9||rtc.getMonth()==6||rtc.getMonth()==4){
      if(irr_day>=28){
        value=3-(30-irr_day);
        EEPROM.update(0, value);
      }
      else {
        value=irr_day+3;
        EEPROM.update(0, value);
      }
      }

    
    if(rtc.getMonth()==2){
      if(irr_day>=27){
        value=3-(29-irr_day);
        EEPROM.update(0, value);
      }
      else {
        value=irr_day+3;
        EEPROM.update(0, value);
      }

    }
  }
}


}
