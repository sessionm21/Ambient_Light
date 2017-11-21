#include <Adafruit_NeoPixel.h>

#define PIN D6
#define NUM_LEDS 70
#define WIDTH 10
#define LEDS_ON NUM_LEDS/WIDTH


//int color_array[NUM_LEDS];
char buffer[10];
char temp;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
  Serial.begin(9600);
  strip.begin();
  blue();
  //fade_to(200,0,0);
}
void loop()
{
  Serial.printf("w");
  delay(500);
  if(Serial.available())
    {
      switch(Serial.read())
        {
        case '0':
          red();
          break;
        case '1':
          blue();
          break;
        case '2':
          green();
          break;
        case '3':
          rainbow();
          break;
        case '4':
          input_mode();
          break;
        }
    }
}
void input_mode()
{
  int r,g,b;
  r = get_number();
  g = get_number();
  b = get_number();
  fade_to(r,g,b);
}
int get_number()
{
  int i = 0;
  while(1)
    {
      if(Serial.available())
        {
          buffer[i] = Serial.read();
          if(buffer[i] == '^')
            {
              break;
            }
          i++;
        }
    }
  buffer[i] = '\0';
  return atoi(buffer);
}
inline void fade_to(int r, int g, int b)
{
  int n;
  for(n = 255; n>=50; n--)
    {
      strip.setBrightness(n);
      strip.show();
      delay(10);
    }
  for(int i = 0; i< NUM_LEDS; i++)
    {
      strip.setPixelColor(i, r, g, b);
    }
  strip.setBrightness(n);
  for(int i = 10; i<255; i++)
    {
      strip.setBrightness(i);
      strip.show();
      delay(10);
    }
}
void red()
{
  for(int i = 0; i< NUM_LEDS; i++)
    {
      strip.setPixelColor(i, 255, 0, 0);
      strip.show();
      delay(10);
    }
}
void green()
{
  for(int i = 0; i< NUM_LEDS; i++)
    {
      strip.setPixelColor(i, 255, 0, 0);
      strip.show();
      delay(10);
    }
}
void blue()
{
  for(int i = 0; i< NUM_LEDS; i++)
    {
      strip.setPixelColor(i, 0, 0, 255);
      strip.show();
      delay(5);
    }
}
void rainbow()
{
  for(int i = 0 ; i < NUM_LEDS; i++)
    {
      strip.setPixelColor(i, 127*sin(i+0)     + 128, 127*sin(i+2)    +128, 127*sin(i+4)    +128);
      //  spec(0, 127*sin(i+0)     + 128, 127*sin(i+2)    +128, 127*sin(i+4)    +128);
      strip.show();
      delay(10);
    }
}
void spec(int start, int r, int g, int b)
{
  for(int i = start ; i < NUM_LEDS; i+=WIDTH)
    {
      strip.setPixelColor(i, r, g, b);
    }
  strip.show();
}
