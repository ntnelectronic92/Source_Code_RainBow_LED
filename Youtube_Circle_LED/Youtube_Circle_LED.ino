#include <Adafruit_NeoPixel.h>
#define PINLED 2
int analogPin = A1;
#define NumberLED 60
#define delayNumberStep 100
#define delayNumber 100
#define ColorNumber 4
#define CircleLedNumber 4
#define _Red   255, 0, 0
#define _Green 0, 255, 0
#define _Blue  0, 0, 255
#define _Pink  255, 26, 179
#define _Start_First_Circle 0
#define _Length_First_Circle 24
#define _Start_Second_Circle (_Start_First_Circle + _Length_First_Circle)
#define _Length_Second_Circle 16
#define _Start_Third_Circle (_Start_Second_Circle + _Length_Second_Circle)
#define _Length_Third_Circle 12
#define _Start_Four_Circle (_Start_Third_Circle + _Length_Third_Circle)
#define _Length_Four_Circle 8

uint8_t colorArray[4][3]={{_Red},{_Green},{_Blue},{_Pink}};
enum{
_rainBow,
_rainBowCycle,
_theaterChase,
_theaterChase_rainBow,
_colorWipe,
_colorMoveIn,
_colorMoveOut,
_numberEffect,
}EffectLED;
// Declare
  uint8_t effectLED = _colorMoveOut;
  uint16_t valueAnalog =0;
  uint16_t valueDelay =0;
  unsigned long previousMillis = 0; 
  unsigned long currentMillis = 0;
//
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NumberLED, PINLED, NEO_GRB + NEO_KHZ800);
void setup() {
  Serial.begin(9600);           //  setup serial
  pinMode(PINLED, OUTPUT);
  strip.begin();
  strip.setBrightness(100);
  strip.show(); 

}
void Handle_Effect(void)
{
  effectLED++;
  if(effectLED>= _numberEffect)
  {
   effectLED =_rainBow;
  }
  for (uint16_t i=0; i < strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, 0);//turn every third pixel off
  } 
  strip.show(); 
}
uint16_t ReturnDelayBaseAnalog(uint8_t inputAnalogPin)
{
     valueAnalog = analogRead(inputAnalogPin);  // read the input pin
     valueAnalog = constrain(valueAnalog,0,800); 
     valueDelay = map(valueAnalog, 0, 800, 0,500);
     //Serial.println(valueDelay);          // debug value
     return valueDelay;
}
void loop() {
  currentMillis = millis();
  if(effectLED == _rainBow)
  {
    rainbow( ReturnDelayBaseAnalog(analogPin)/50);
  }
  else if(effectLED == _rainBowCycle)
  {
   rainbowCycle( ReturnDelayBaseAnalog(analogPin)/50);
  }
  else if(effectLED == _theaterChase)
  {
    theaterChase(ReturnDelayBaseAnalog(analogPin));
  }
    else if(effectLED == _theaterChase_rainBow)
  {
    theaterChaseRainbow(ReturnDelayBaseAnalog(analogPin));
  }
  else if(effectLED == _colorWipe)
  {
    colorWipe(ReturnDelayBaseAnalog(analogPin));
  }
  else if(effectLED == _colorMoveIn)
  {
     colorMoveIn(ReturnDelayBaseAnalog(analogPin));
  }
  else if(effectLED == _colorMoveOut)
  {
    colorMoveOut(ReturnDelayBaseAnalog(analogPin));
  }
}
uint32_t getColor(uint8_t indexColor)
{
  return strip.Color( colorArray[indexColor][0],colorArray[indexColor][1],colorArray[indexColor][2]);
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbow(uint16_t wait) {
  uint16_t i;
  uint16_t static j = 0;
  if(effectLED != _rainBow)
  {
    return; 
  }
  if (currentMillis - previousMillis >= wait) 
  {
    previousMillis = currentMillis;
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    j++;
    if(j >=256)
    {
     j = 0;
     Handle_Effect();
    }
  }
}

void rainbowCycle(uint16_t wait) {
  uint16_t i;
  uint16_t static j = 0;
  if(effectLED != _rainBowCycle)
  {
    return; 
  }
  if (currentMillis - previousMillis >= wait) 
  {
    previousMillis = currentMillis;
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    j++;
    if(j >=256*5)// 5 cycles of all colors on wheel
    {
     j = 0;
     Handle_Effect();
    }
  }
}

void theaterChase(uint16_t wait) {
    uint16_t i;
    uint16_t static j = 0;
    uint8_t static q = 0;
    uint32_t static colorChange = 0;
    colorChange =getColor(j/10);
    if(effectLED != _theaterChase)
    {
      return; 
    }
    if (currentMillis - previousMillis >= wait) 
    {
      previousMillis = currentMillis; 
      if(q > 0)
      {
          for (uint16_t i=0; i < strip.numPixels(); i=i+3) 
          {
              strip.setPixelColor(i+(q -1), 0);//turn every third pixel off
          }
      }
      else
      {
          for (uint16_t i=0; i < strip.numPixels(); i=i+3) 
          {
              strip.setPixelColor(i+2, 0);//turn every third pixel off
          }  
      } 
      for ( i=0; i < strip.numPixels(); i=i+3) 
      {
        strip.setPixelColor(i+q, colorChange);//turn every third pixel on
      }
      strip.show();
      q++;
      if(q>=3)
      {
        q =0;
        j++;
        if(j >=10*ColorNumber)//do 10 cycles of chasing
        {
          j = 0;
          q = 0;
           Handle_Effect();
        }
      }
    }
}

void theaterChaseRainbow(uint16_t wait) {
    uint16_t i;
    uint16_t static j = 0;
    uint8_t static q = 0;
    if(effectLED != _theaterChase_rainBow)
    {
      return; 
    }
    if (currentMillis - previousMillis >= wait) 
    {
      previousMillis = currentMillis; 
      if(q > 0)
      {
          for (uint16_t i=0; i < strip.numPixels(); i=i+3) 
          {
              strip.setPixelColor(i+(q -1), 0);//turn every third pixel off
          }
      }
      else
      {
          for (uint16_t i=0; i < strip.numPixels(); i=i+3) 
          {
              strip.setPixelColor(i+2, 0);//turn every third pixel off
          }  
      } 
      for ( i=0; i < strip.numPixels(); i=i+3) 
      {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));//turn every third pixel on
      }
      strip.show();
      q++;
      if(q>=3)
      {
        q =0;
        j++;
        if(j >=50)//do 50 cycles of chasing
        {
          j = 0;
          q = 0;
           Handle_Effect();
        }
      }
    }
}
// Fill the dots one after the other with a color
void colorWipe( uint16_t wait) {
 int8_t static i,j = 0;
 uint32_t static colorChange = 0;
 colorChange =getColor(j%ColorNumber);
  if(effectLED != _colorWipe)
  {
    return; 
  }
 if (currentMillis - previousMillis >= wait) 
  {
    previousMillis = currentMillis;
    strip.setPixelColor(i, colorChange);
    strip.show();
    i++;
    if(i>= strip.numPixels())
    {
       i= 0; 
       j++;
       if(j>=ColorNumber)
       {
         j= 0;
         Handle_Effect();
       }
    }
  }
}
void _colorInRange(uint16_t start, uint16_t length,uint16_t wait)
{
  int8_t static i,j = 0;
  uint32_t static colorChange = 0;
  colorChange =getColor(j%ColorNumber);
     for(i=0; i<strip.numPixels(); i++) 
     {
        if(i>=start && i<(start + length)) 
        {
          strip.setPixelColor(i, colorChange);
        }
        else
        {
          strip.setPixelColor(i, 0);
        }
     }
     strip.show();
     j++;
     if(j>=ColorNumber)
     {
       j= 0;
     }
}
void colorMoveIn( uint16_t wait) 
{
  int8_t static i,j = 0;
  if(effectLED != _colorMoveIn)
  {
    return; 
  }
  if (currentMillis - previousMillis >= wait) 
  {
     previousMillis = currentMillis;
     if(i% CircleLedNumber == 0)
     {
      _colorInRange(_Start_First_Circle,_Length_First_Circle,wait);
     }
     else if (i% CircleLedNumber == 1)
     {
      _colorInRange(_Start_Second_Circle,_Length_Second_Circle,wait);
     }
     else if(i% CircleLedNumber == 2)
     {
       _colorInRange(_Start_Third_Circle,_Length_Third_Circle,wait);
     }
     else if(i% CircleLedNumber == 3)
     {
       _colorInRange(_Start_Four_Circle,_Length_Four_Circle,wait);
     }
     i++;
     if(i>= CircleLedNumber)
     {
       i=0; 
       j++;
       if(j>10)
       {
         Handle_Effect();
         j = 0;
       }
     }

  }
}

void colorMoveOut(uint16_t wait) 
{
  int8_t static i,j = 0;
  if(effectLED != _colorMoveOut)
  {
    return; 
  }
  if (currentMillis - previousMillis >= wait) 
  {
     previousMillis = currentMillis;
     if(i% CircleLedNumber == 3)
     {
      _colorInRange(_Start_First_Circle,_Length_First_Circle,wait);
     }
     else if (i% CircleLedNumber == 2)
     {
      _colorInRange(_Start_Second_Circle,_Length_Second_Circle,wait);
     }
     else if(i% CircleLedNumber == 1)
     {
       _colorInRange(_Start_Third_Circle,_Length_Third_Circle,wait);
     }
     else if(i% CircleLedNumber == 0)
     {
       _colorInRange(_Start_Four_Circle,_Length_Four_Circle,wait);
     }
     i++;
     if(i>= CircleLedNumber)
     {
       i =0; 
       j++;
       if(j>10)
       {
         Handle_Effect();
         j = 0;
       }
     }
  }
}
