const unsigned char rowNum =5;
const unsigned char colNum =8;
unsigned int arrayFullDataCurrent =0;
unsigned char rows[rowNum]= {2,3,4,5,6};
unsigned char colums[colNum]={7,8,9,10,11,12,13,A0};
unsigned long timeMillisGet =0;
unsigned char r = 0;
unsigned char c = 0;
unsigned int arrayRunTimeCurrent =0;
unsigned char arrayRunTimeLoopCurrent = 0;
unsigned char arrayRunTimeLoopMax = 0;
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
  MOVEIN,
  RUN_CHANGE,
  CLOCKLEFT, 
  CLOCKRIGHT,
  NUM_EFFECT
};
char arrayRunTime[NUM_EFFECT][NUM_RUN_TIME]=
{
  {0,2,3},// IndexStart, NumberItem, LoopTime
  {2,5,4}, 
  {7,6,5},
  {13,8,10},
  {21,8,10},
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
    if((unsigned long)(millis() - timeMillisGet) > 100 )
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
   runLed();
}
