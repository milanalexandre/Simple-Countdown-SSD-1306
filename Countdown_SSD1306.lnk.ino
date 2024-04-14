/*-------------------------------------------
 * Countdown with SSD1306
 * Credits: Diogo Vilhena
 * https://github.com/VilhenaChen
 *-------------------------------------------
 */
 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Variables declaration Hour(hours) minutete(minute) Second(sec)
int hours = 53;
int minute = 57;
int sec = 59;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int next_update; //save time for next display update 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x64
  display.fillScreen(0);
  display.display();
  next_update = millis();
}

void print_digits(int time_to_print)
{
  //This if(variable < 10) ensures that if the number is below 2 digits, it will remain centered otherwise justs prints the variable
  if (time_to_print < 10)
  {
    display.print("0" + String(time_to_print));
  }
  else
  {
    display.print(time_to_print);
  }
}

#define TextSize 3
#define Text_X_countdown 0 //setCursor(x) //Change to your needs
#define Text_Y_countdown 27 //setCursor(y) //Change to your needs


void print_countdown()
{
  display.clearDisplay(); // Used to clear the display
  //Text stuff, Size and Color
  display.setTextSize(TextSize);
  display.setTextColor(WHITE);
  
  // set text size
  int16_t x1, y1;
  uint16_t w, h; // text size
  display.getTextBounds("0", 0, 0, &x1, &y1, &w, &h);
  uint16_t cursor = Text_X_countdown;
  display.setCursor(cursor, Text_Y_countdown);

  // hours
   print_digits(hours);
  cursor = cursor + w + ((2 * w) / 3);
  display.setCursor(cursor, Text_Y_countdown);

  // split
  display.print(":");
  cursor = cursor + ((2 * w) / 3);
  display.setCursor(cursor, Text_Y_countdown);

  // hours
  print_digits(minute);
  cursor = cursor + w + ((2 * w) / 3);
  display.setCursor(cursor, Text_Y_countdown);

  // split
  display.print(":");
  cursor = cursor + ((2 * w) / 3);
  display.setCursor(cursor, Text_Y_countdown);

  // sec
  print_digits(sec);

  display.display(); // Display the corrent countdown
}

void remove_1sec_countdown()
{
  //The maths behinf this, if sec==0 then minute=minute-1 and if minute==0 then hours=hours-1, just the basics of a clock
  sec = sec - 1;
  if (sec == -1)
  {
    sec = 59;
    minute = minute - 1;
  }
  if (minute == -1)
  {
    minute = 59;
    hours = hours - 1;
  }
}

void loop()
{
  
  if (sec == 0 && minute == 0 && hours == 0){
    while (true)
    {
    }
  }
  if (next_update < millis()){
    next_update += 1000;
    remove_1sec_countdown();
    print_countdown();
  }
}