

int DATA               = 3;
int DATA_OUTPUT_ENABLE = 4;
int LATCH              = 5;
int CLOCK              = 6;
int RESET              = 7;

const int button1Pin = 2;  // pushbutton pin


// || 4=Blue || 3=Yellow || 2=Red || 1=Green || 6=Purple || 5=Cyan || 0=Off || 

byte Screen[8][8] = {{4,4,4,4,4,4,4,4},
                     {4,4,4,4,4,4,4,4},
                     {4,2,2,4,2,2,4,4},
                     {2,4,4,2,4,4,2,4},
                     {2,4,4,4,4,4,2,4},
                     {4,2,4,4,4,2,4,4},
                     {4,4,2,4,2,4,4,4},
                     {4,4,4,2,4,4,4,4}};

byte HappyFace[8][8] = {{0,0,3,3,3,3,0,0},
                        {0,3,3,3,3,3,3,0},
                        {3,3,4,3,3,4,3,3},
                        {3,3,3,3,3,3,3,3},
                        {3,3,3,3,3,3,3,3},
                        {3,3,2,3,3,2,3,3},
                        {0,3,3,2,2,3,3,0},
                        {0,0,3,3,3,3,0,0}}; 

byte BlueBall[8][8] = {{0,0,0,4,4,0,0,0},
                       {0,0,4,5,5,4,0,0},
                       {0,4,5,7,7,5,4,0},
                       {4,5,7,7,7,7,5,4},
                       {4,5,7,7,7,7,5,4},
                       {0,4,5,7,7,5,4,0},
                       {0,0,4,5,5,4,0,0},
                       {0,0,0,4,4,0,0,0}};

byte Picture[8][8] = {{1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,1},
                      {1,2,2,1,1,1,2,2},
                      {1,2,2,2,1,2,2,2},
                      {1,2,2,2,2,2,2,2},
                      {1,1,2,2,2,2,2,1},
                      {1,1,1,2,2,2,1,1},
                      {1,1,1,1,2,1,1,1}};



byte Circle1[8][8] = {{2,2,2,2,2,2,2,2},
                      {2,2,2,2,2,2,2,2},
                      {2,2,2,2,2,2,2,2},
                      {2,2,2,1,1,2,2,2},
                      {2,2,2,1,1,2,2,2},
                      {2,2,2,2,2,2,2,2},
                      {2,2,2,2,2,2,2,2},
                      {2,2,2,2,2,2,2,2}};



byte Circle2[8][8] = {{2,2,2,2,2,2,2,2},
                      {2,2,2,2,2,2,2,2},
                      {2,2,2,1,1,2,2,2},
                      {2,2,1,2,2,1,2,2},
                      {2,2,1,2,2,1,2,2},
                      {2,2,2,1,1,2,2,2},
                      {2,2,2,2,2,2,2,2},
                      {2,2,2,2,2,2,2,2}};


byte Circle3[8][8] = {{2,2,2,2,2,2,2,2},
                      {2,2,2,1,1,2,2,2},
                      {2,2,1,2,2,1,2,2},
                      {2,1,2,2,2,2,1,2},
                      {2,1,2,2,2,2,1,2},
                      {2,2,1,2,2,1,2,2},
                      {2,2,2,1,1,2,2,2},
                      {2,2,2,2,2,2,2,2}};

byte Circle4[8][8] = {{2,2,2,1,1,2,2,2},
                      {2,2,1,2,2,1,2,2},
                      {2,1,2,2,2,2,1,2},
                      {1,2,2,2,2,2,2,1},
                      {1,2,2,2,2,2,2,1},
                      {2,1,2,2,2,2,1,2},
                      {2,2,1,2,2,1,2,2},
                      {2,2,2,1,1,2,2,2}};



unsigned long LastStateChangeTime;
unsigned long StateWaitTime;
int State;

void sendBit(uint8_t aData)
{
  digitalWrite(DATA,  aData);  
  digitalWrite(CLOCK, HIGH);
  digitalWrite(CLOCK, LOW);
  digitalWrite(DATA,  LOW);  
}

void sendDataFromArray()
{
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    //Set Anode Line
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      if (lineIndex == rowIndex)
      {
        sendBit(HIGH);
      }
      else
      {
        sendBit(LOW);
      }
    }

    //Set Green Row
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      if ((Screen[lineIndex][rowIndex] & 1) == 0)
      {
        sendBit(HIGH);
      }
      else
      {
        sendBit(LOW);
      }
    }

    //Set Red Row
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      if ((Screen[lineIndex][rowIndex] & 2) == 0)
      {
        sendBit(HIGH);
      }
      else
      {
        sendBit(LOW);
      }
    }

    //Set Blue Row
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      if ((Screen[lineIndex][rowIndex] & 4) == 0)
      {
        sendBit(HIGH);
      }
      else
      {
        sendBit(LOW);
      }
    }

    //Send data to output
    digitalWrite(LATCH, HIGH);
    digitalWrite(LATCH, LOW);
  }
}

void Clear()
{  
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = 0;
    }
  }
}

void ShowHappyFace()
{  
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = HappyFace[lineIndex][rowIndex];
    }
  }
}

void ShowPicture()
{  
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = Picture[lineIndex][rowIndex];
    }
  }
}

void ShowRainBow()
{  
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    Screen[lineIndex][0] = 7;
    Screen[lineIndex][1] = 7;
    Screen[lineIndex][2] = 7;
    Screen[lineIndex][3] = 7;
    Screen[lineIndex][4] = 7;
    Screen[lineIndex][5] = 7;
    Screen[lineIndex][6] = 7;
    Screen[lineIndex][7] = 7;
  }
}



void ShowCircle1(){  
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = Circle1[lineIndex][rowIndex];
    }
  }
}

void ShowCircle2(){
    
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = Circle2[lineIndex][rowIndex];
    }
  }
}

void ShowCircle3(){
    
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = Circle3[lineIndex][rowIndex];
    }
  }
}

void ShowCircle4(){
    
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = Circle4[lineIndex][rowIndex];
    }
  }
}



void ShowFartyFace()
{  
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = HappyFace[lineIndex][rowIndex];
    }
  }
}

void ScrollUp(byte NewLine[])
{
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 7; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = Screen[lineIndex+1][rowIndex];
    }
  }

  for(rowIndex = 0; rowIndex < 8; rowIndex++)
  {
    Screen[7][rowIndex] = NewLine[rowIndex];
  }
}


void ScrollSide(byte NewLine[])
{
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 7; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = Screen[lineIndex][rowIndex+1];
    }
  }

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
   // Screen[7][rowIndex] = NewLine[rowIndex];
    Screen[lineIndex][7] = NewLine[rowIndex];
    
  }
}


void UpdateState()
{
  State++;
  if (State == 19)
  {
    State = 0;
  }

  LastStateChangeTime = millis();
  switch (State)
  {
//     case 0:
//       Screen([8]);
//       StateWaitTime = 2000;
//       break;
//     case 1:
//       Clear();
//       StateWaitTime = 250;
//       break;
//     case 2:
//       Clear();
//       StateWaitTime = 2000;
//       break;
     case 3:
       ScrollUp(Picture[1]);
       StateWaitTime = 250;
       break;
     case 4:
       ScrollUp(Picture[2]);
       StateWaitTime = 250;
       break;
     case 5:
       ScrollUp(Picture[3]);
       StateWaitTime = 250;
       break;   
     case 6:
       ScrollUp(Picture[4]);
       StateWaitTime = 250;
       break;
     case 7:
       ScrollUp(Picture[5]);
       StateWaitTime = 250;
       break;
     case 8:
       ScrollUp(Picture[6]);
       StateWaitTime = 250;
       break;
     case 9:
       ScrollUp(Picture[7]);
       StateWaitTime = 250;
       break; 
       
  }
}





//Side Scroll

void UpdateState2()
{
  State++;
  if (State == 19)
  {
    State = 0;
  }

  LastStateChangeTime = millis();
  switch (State)
  {
//     case 0:
//       Screen([8]);
//       StateWaitTime = 2000;
//       break;
//     case 1:
//       Clear();
//       StateWaitTime = 250;
//       break;
//     case 2:
//       Clear();
//       StateWaitTime = 2000;
//       break;
     case 3:
       ScrollSide(Picture[1]);
       StateWaitTime = 250;
       break;
     case 4:
       ScrollSide(Picture[2]);
       StateWaitTime = 250;
       break;
     case 5:
       ScrollSide(Picture[3]);
       StateWaitTime = 250;
       break;   
     case 6:
       ScrollSide(Picture[4]);
       StateWaitTime = 250;
       break;
     case 7:
       ScrollSide(Picture[5]);
       StateWaitTime = 250;
       break;
     case 8:
       ScrollSide(Picture[6]);
       StateWaitTime = 250;
       break;
     case 9:
       ScrollSide(Picture[7]);
       StateWaitTime = 250;
       break; 
       
  }
}

//Blinking State

void BlinkingState()
{
  State++;
  if (State == 4)
  {
    State = 0;
  }

  LastStateChangeTime = millis();
  switch (State)
  {

    case 1:
       ShowPicture();
       StateWaitTime = 100;
       break;
     case 2:
       Clear();
       StateWaitTime = 100;
       break;
       
//     case 3:
//       ShowPicture();
//       StateWaitTime = 500;
//       break;
//       
//     case 4:
//       Clear();
//       StateWaitTime = 500;
//       break;   
       

  }
}


//Animates the Circle Animation
void AnimateCircle()
{
  State++;
  if (State == 5)
  {
    State = 0;
  }

  LastStateChangeTime = millis();
  switch (State)
  {

     case 1:
       ShowCircle1();
       StateWaitTime = 60;
       break;
     case 2:
       ShowCircle2();
       StateWaitTime = 60;
       break;
     case 3:
       ShowCircle3();
       StateWaitTime = 60;
       break;
     case 4:
       ShowCircle4();
       StateWaitTime = 60;
       break;   

  }
}



void setup() 
{

  Serial.begin(9600);
  pinMode(DATA, OUTPUT);
  pinMode(DATA_OUTPUT_ENABLE, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(RESET, OUTPUT);

  pinMode(button1Pin, INPUT);
  
  digitalWrite(DATA_OUTPUT_ENABLE, LOW);
  digitalWrite(RESET, HIGH); 
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, LOW);
  digitalWrite(DATA, LOW);
  
  ShowPicture();
  State = 0;
  StateWaitTime = 50;
  LastStateChangeTime = millis();
}



void loop() {
  

  int  button1State = digitalRead(button1Pin);

  if(button1State == LOW){
    ShowHappyFace();
  }


  
  if ((StateWaitTime > 0) &&
      (LastStateChangeTime + StateWaitTime < millis()))
  {

    
//Serial.print("Loop");
 UpdateState2();
 //BlinkingState();
// ShowPicture();

// AnimateCircle();

 //ShowCircle2();
   
  }  
  
  sendDataFromArray();
}
