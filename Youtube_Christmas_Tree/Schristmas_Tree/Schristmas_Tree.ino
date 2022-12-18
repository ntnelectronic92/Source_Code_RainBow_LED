const unsigned char rowNum =5;
const unsigned char colNum =8;
int analogPin = A1;
uint16_t arrayFullDataCurrent =0;
unsigned char rows[rowNum]= {2,3,4,5,6};
unsigned char colums[colNum]={7,8,9,10,11,12,13,A0};
unsigned long timeMillisGet =0;
unsigned char r = 0;
unsigned char c = 0;
uint16_t arrayRunTimeCurrent =0;
unsigned char arrayRunTimeLoopCurrent = 0;
unsigned char arrayRunTimeLoopMax = 0;
uint16_t valueDelay =0;
uint16_t valueAnalog =0;
enum// RUNTIME
{
INDEXSTART,
NUMBERITEM,
LOOPTIME, 
NUM_RUN_TIME
};
enum //EFFECT
{
  BLINK_CENTER,
  MOVE_UP,
  RUN_CHANGE,
  CLOCKLEFT, 
  CLOCKRIGHT,
  CLOCKLEFT_FILL, 
  ROLLING,
  MOVEDOWN,
  FILL_UP,
  FILL_DOWN,
  SWAP_COL,
  NUM_EFFECT
};
char arrayRunTime[NUM_EFFECT][NUM_RUN_TIME]=
{
  {0,2,3},// IndexStart, NumberItem, LoopTime
  {2,5,10}, 
  {7,6,10},
  {13,8,10},
  {21,8,10},
  {29,16,10},
  {45,41,10},
  {86,5,10},
  {91,5,10},
  {96,5,10},
  {101,2,40},
};

char  arrayFullData[][rowNum]={
{0x00,0x00,0x00,0x00,0xFF},// 0 
{0x00,0x00,0x00,0x00,0x00},

{0xFF,0x00,0x00,0x00,0x00},//5
{0x00,0xFF,0x00,0x00,0x00},
{0x00,0x00,0xFF,0x00,0x00},
{0x00,0x00,0x00,0xFF,0x00},
{0x00,0x00,0x00,0x00,0xFF},

{0xFF,0x00,0xFF,0x00,0xFF},//6
{0x00,0xFF,0x00,0xFF,0x00},
{0xFF,0x00,0xFF,0x00,0xFF},
{0x00,0xFF,0x00,0xFF,0x00},
{0xFF,0x00,0xFF,0x00,0xFF},
{0x00,0xFF,0x00,0xFF,0x00},

{0x01,0x01,0x01,0x01,0xFF}, //8
{0x02,0x02,0x02,0x02,0xFF},
{0x04,0x04,0x04,0x04,0xFF},
{0x08,0x08,0x08,0x08,0xFF},
{0x10,0x10,0x10,0x10,0xFF},
{0x20,0x20,0x20,0x20,0xFF},
{0x40,0x40,0x40,0x40,0xFF},
{0x80,0x80,0x80,0x80,0xFF},

{0x80,0x80,0x80,0x80,0xFF},//8
{0x40,0x40,0x40,0x40,0xFF},
{0x20,0x20,0x20,0x20,0xFF},
{0x10,0x10,0x10,0x10,0xFF},
{0x08,0x08,0x08,0x08,0xFF},
{0x04,0x04,0x04,0x04,0xFF},
{0x02,0x02,0x02,0x02,0xFF},
{0x01,0x01,0x01,0x01,0xFF}, 

{0x01,0x01,0x01,0x01,0xFF},//16
{0x03,0x03,0x03,0x03,0xFF},
{0x07,0x07,0x07,0x07,0xFF},
{0x0F,0x0F,0x0F,0x0F,0xFF}, 
{0x1F,0x1F,0x1F,0x1F,0xFF},
{0x3F,0x3F,0x3F,0x3F,0xFF},
{0x7F,0x7F,0x7F,0x7F,0xFF},
{0xFF,0xFF,0xFF,0xFF,0xFF},
{0xFE,0xFE,0xFE,0xFE,0xFF},
{0xFC,0xFC,0xFC,0xFC,0xFF},
{0xF8,0xF8,0xF8,0xF8,0xFF},
{0xF0,0xF0,0xF0,0xF0,0xFF},
{0xE0,0xE0,0xE0,0xE0,0xFF}, 
{0xC0,0xC0,0xC0,0xC0,0xFF},
{0x80,0x80,0x80,0x80,0xFF},
{0x00,0x00,0x00,0x00,0xFF},

{0x00,0x00,0x00,0x00,0x00},//9
{0x01,0x00,0x00,0x00,0x00},
{0x03,0x00,0x00,0x00,0x00},
{0x07,0x00,0x00,0x00,0x00},
{0x0f,0x00,0x00,0x00,0x00},
{0x1f,0x00,0x00,0x00,0x00},
{0x3f,0x00,0x00,0x00,0x00},
{0x7f,0x00,0x00,0x00,0x00},
{0xff,0x00,0x00,0x00,0x00},

{0xff,0x01,0x00,0x00,0x00},//8
{0xff,0x03,0x00,0x00,0x00},
{0xff,0x07,0x00,0x00,0x00},
{0xff,0x0f,0x00,0x00,0x00},
{0xff,0x1f,0x00,0x00,0x00},
{0xff,0x3f,0x00,0x00,0x00},
{0xff,0x7f,0x00,0x00,0x00},
{0xff,0xff,0x00,0x00,0x00},

{0xff,0xff,0x01,0x00,0x00},//8
{0xff,0xff,0x03,0x00,0x00},
{0xff,0xff,0x07,0x00,0x00},
{0xff,0xff,0x0f,0x00,0x00},
{0xff,0xff,0x1f,0x00,0x00},
{0xff,0xff,0x3f,0x00,0x00},
{0xff,0xff,0x7f,0x00,0x00},
{0xff,0xff,0xff,0x00,0x00},

{0xff,0xff,0xff,0x01,0x00},//8
{0xff,0xff,0xff,0x03,0x00},
{0xff,0xff,0xff,0x07,0x00},
{0xff,0xff,0xff,0x0f,0x00},
{0xff,0xff,0xff,0x1f,0x00},
{0xff,0xff,0xff,0x3f,0x00},
{0xff,0xff,0xff,0x7f,0x00},
{0xff,0xff,0xff,0xff,0x00},

{0xff,0xff,0xff,0xff,0x01},//8
{0xff,0xff,0xff,0xff,0x03},
{0xff,0xff,0xff,0xff,0x07},
{0xff,0xff,0xff,0xff,0x0f},
{0xff,0xff,0xff,0xff,0x1f},
{0xff,0xff,0xff,0xff,0x3f},
{0xff,0xff,0xff,0xff,0x7f},
{0xff,0xff,0xff,0xff,0xff},

{0x00,0x00,0x00,0x00,0xFF},//5
{0x00,0x00,0x00,0xFF,0x00},
{0x00,0x00,0xFF,0x00,0x00},
{0x00,0xFF,0x00,0x00,0x00},
{0xFF,0x00,0x00,0x00,0x00},

{0xFF,0x00,0x00,0x00,0x00},//5
{0xFF,0xFF,0x00,0x00,0x00},
{0xFF,0xFF,0xFF,0x00,0x00},
{0xFF,0xFF,0xFF,0xFF,0x00},
{0xFF,0xFF,0xFF,0xFF,0xFF},

{0x00,0x00,0x00,0x00,0xFF},//4
{0x00,0x00,0x00,0xFF,0xFF},
{0x00,0x00,0xFF,0xFF,0xFF},
{0x00,0xFF,0xFF,0xFF,0xFF},
{0xFF,0xFF,0xFF,0xFF,0xFF},

{0xAA,0xAA,0xAA,0xAA,0xFF},//2
{0x55,0x55,0x55,0x55,0xFF},

};
void initialIO()
{
  for(char i =0;i< rowNum; i++)
  {
   pinMode(rows[i],OUTPUT);  
  }  
  for(char i =0;i< colNum; i++)
  {
   pinMode(colums[i],OUTPUT);  
  } 
}
void setByteRow(char input)
{
  for(int i = 0;i<rowNum;i++)
  {
    digitalWrite(rows[i],((input>> i) & 0x01));
  }  
}
void setByteColum(char input)
{
  for(int i = 0;i<colNum;i++)
  {
     digitalWrite( colums[i] ,((input>> i) & 0x01));
  }  
}
void displayOneLoop()
{
   setByteRow(0xFF);
   setByteColum(arrayFullData[arrayFullDataCurrent][r]) ; 
   setByteRow(~(0x01 <<r));
   delay(1);
   r++;
   if(r >= rowNum)
   {
     r = 0;  
   }
}
uint16_t ReturnDelayBaseAnalog(uint8_t inputAnalogPin)
{
     valueAnalog = analogRead(inputAnalogPin);  // read the input pin
     valueAnalog = constrain(valueAnalog,0,800); 
     valueDelay = map(valueAnalog, 0, 800, 0,500);
     //Serial.println(valueDelay);          // debug value
     return valueDelay;
}
void setup() {
  initialIO();
  //initialRunTime();
  //Serial.begin(9600);
  //Serial.println(arrayRunTimeNumTotal);
}
//char buff[50];
void runLed()
{
    //sprintf(buff, "arrayRunTimeLoop value is %d ", arrayRunTimeLoop);
   // Serial.println(buff);
    // sprintf(buff, "arrayNumCurrent value is %d ", arrayNumCurrent);
    //Serial.println(buff);
    if((unsigned long)(millis() - timeMillisGet) > valueDelay )
    {
      arrayFullDataCurrent++;
      if(arrayFullDataCurrent >= (arrayRunTime[arrayRunTimeCurrent][INDEXSTART] + arrayRunTime[arrayRunTimeCurrent][NUMBERITEM]))
      {
        arrayRunTimeLoopCurrent++;
        if(arrayRunTimeLoopCurrent >= arrayRunTime[arrayRunTimeCurrent][LOOPTIME])
        {
          arrayRunTimeLoopCurrent = 0;
          arrayRunTimeCurrent++;
          if(arrayRunTimeCurrent >= NUM_EFFECT)
          {
            arrayRunTimeCurrent = 0;
          }
        }
        arrayFullDataCurrent = arrayRunTime[arrayRunTimeCurrent][INDEXSTART];
      }
      timeMillisGet = millis();
    }
    else
    {
       displayOneLoop();
    }
}

void loop() 
{
   ReturnDelayBaseAnalog(analogPin);
   runLed();
}
