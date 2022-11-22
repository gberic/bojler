#include <DallasTemperature.h>
#include <RTClib.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <OneWire.h>


// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
//kkkkkk
RTC_DS1307 RTC;
int bojler = 0;
int jeftina = 0;
void setup() {
  pinMode(13, OUTPUT);          // sets the digital pin 13 as output
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);




  // display a line of text
//  display.setTextSize(4);
//  display.setTextColor(WHITE);
//  display.setCursor(1,30);
//  display.print("12:34");

  // update display with all of the above graphics
 // display.display();
  Serial.begin(9600);
    Wire.begin();
    RTC.begin();
     Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
  // Check to see if the RTC is keeping time.  If it is, load the time from your computer.
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // This will reflect the time that your sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
//   RTC.adjust(DateTime(__DATE__, __TIME__)); //raskomentiraj ovu liniju ya podesavanje tekuceh=g vremena
}



void loop () {
    DateTime now = RTC.now();

//    Serial.print(' ');
//    Serial.print(now.hour(), DEC);
//    Serial.print(':');
//    Serial.print(now.minute(), DEC);
//    Serial.print(':');
//    Serial.print(now.second(), DEC);
//    Serial.println();
    delay(1000);


if(now.hour()>22 || now.hour()<7)
    {jeftina =1;}
    else {jeftina =0;}

if(now.hour()>2 && now.hour()<7)
    {bojler =1;}
    else {bojler =0;}

      // display a line of text
      display.clearDisplay();
// display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(35,5);
 display.print(now.day(), DEC);
display.print('/');
display.print(now.month(), DEC);
display.print('/');
display.print(now.year(), DEC);
//  display.print("22.01.2018. utorak");


// display a line of text
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(2,15);

if (jeftina == 1){display.print("NT +");}
else {display.print("VT +");}
display.print(sensors.getTempCByIndex(0));




  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(5,35);
   if(now.hour()<10){display.print(" ");}

  display.print(now.hour(), DEC);
   display.print(':');

  if(now.minute()<10){display.print("0");}

    display.print(now.minute(), DEC);


  // update display with all of the above graphics

 display.display();

if (bojler ==1 && sensors.getTempCByIndex(0)< 40){digitalWrite(13, HIGH);}
if (bojler ==0 || sensors.getTempCByIndex(0)> 58){digitalWrite(13, LOW);}
else {digitalWrite(13, LOW);}

//  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
//  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
//  Serial.print("Temperature for the device 1 (index 0) is: ");
//  Serial.println(sensors.getTempCByIndex(0));
}
