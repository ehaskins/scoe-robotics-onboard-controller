#include <XBee.h>
//
//
unsigned long timer1;
unsigned long timer2;

//Fields to remember the most recent packet.
int SerialData = 0;
int MotorSpeed2 = 0;
int MotorSpeed3 = 0;
int MotorSpeed4 = 0;
int MotorSpeed5 = 0;
int Motor2Direction = 0;
int Motor3Direction = 0;
int Motor4Direction = 0; 
int Motor5Direction = 0;
int intakePower = 0;
int intakeDirection = 0;
int feedPower = 0;
int shooterSpeed = 0;
int kill = 0;


//Remembers which LED to ignite for our (totally pointless but cool) bar of lights
int LEDcounter = 1;

//Pin Definitions go here
const int MOTOR2 = 2;
const int MOTOR3 = 3;
const int MOTOR4 = 4;
const int MOTOR5 = 5;
const int MOTOR2DIRECTION = 22;
const int MOTOR3DIRECTION = 24;
const int MOTOR4DIRECTION = 26;
const int MOTOR5DIRECTION = 28;
const int INTAKEPOWER = 23;
const int INTAKEDIR = 25;
const int FEEDPOWER = 27;
const int SHOOTERSPEED = 29;

//PIN LEDS IN WHITE, GREEN, WHITE, GREEN, ... WHITE
/* 30= WHITE
 31= GREEN
 32= WHITE
 33= GREEN
 34= WHITE
 35= GREEN
 36= WHITE
 37= GREEN
 39= WHITE
 
 */



XBee xbee;
XBeeResponse response = XBeeResponse();
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();
uint8_t inData[14];

uint8_t option = 0;
uint8_t data = 0;

void setup() {
  //Include PINMODES Here
  pinMode(MOTOR2,OUTPUT);  
  pinMode(MOTOR3,OUTPUT);
  pinMode(MOTOR4,OUTPUT);
  pinMode(MOTOR5,OUTPUT);
  pinMode(MOTOR2DIRECTION,OUTPUT);
  pinMode(MOTOR3DIRECTION,OUTPUT);
  pinMode(MOTOR4DIRECTION,OUTPUT);
  pinMode(MOTOR5DIRECTION,OUTPUT);
  pinMode(SHOOTERSPEED,OUTPUT);
  pinMode(INTAKEPOWER,OUTPUT);
  pinMode(FEEDPOWER, OUTPUT);
  Serial.begin(57600);
  Serial.println("Begin");
  timer1 = millis();
  // start serial
  xbee.begin(57600);
}

// continuously reads packets, looking for RX16 or RX64
void loop() {
  timer2 = millis();
  if((timer2 - timer1)>1000){
    kill = 1;

    //  digitalWrite(LEDcounter+29, HIGH);
    //  if(LEDcounter = 1){
    //    digitalWrite(LEDcounter+(29+8), LOW);
    //  }else{
    //    digitalWrite(LEDcounter+(29-1), LOW);
    //  }
    //  
    //  if(LEDcounter=9){
    //    LEDcounter=1;
    //  }else{
    //    LEDcounter++;
    //  }    

    xbee.readPacket();

    if (xbee.getResponse().isAvailable()) {
      // got something

      if (xbee.getResponse().getApiId() == RX_16_RESPONSE || xbee.getResponse().getApiId() == RX_64_RESPONSE) {
        // got a rx packet
        //Serial.println("Got an RX packet");

        if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
          xbee.getResponse().getRx16Response(rx16);
          option = rx16.getOption();
          data = rx16.getData(0);
          memcpy(inData,rx16.getData(),sizeof(uint8_t)*13);

          for(int i=0; i<rx16.getDataLength(); i++) {
            Serial.println((int)(rx16.getData(i)));
          }
          //Serial.println();
        } 
        else {

          xbee.getResponse().getRx64Response(rx64);
          option = rx64.getOption();
          data = rx64.getData(0);
          memcpy(inData,rx64.getData(),sizeof(uint8_t)*13);
          for(int i=0; i<rx64.getDataLength(); i++) {
            Serial.println((int)(rx64.getData(i)));
          }
          //Serial.println();
        }
      }
    }  

    for(int i=0; i<14; i++){   
      if(inData[i]==11 && i!=0){
        break;
      }
      else if(i == 1){
        MotorSpeed2=(int)inData[1];
      }
      else if(i == 2){  
        MotorSpeed3=(int)inData[2];
      }
      else if(i == 3){  
        MotorSpeed4=(int)inData[3];
      }
      else if(i == 4){  
        MotorSpeed5=(int)inData[4];
      }
      else if(i == 5){    
        Motor2Direction=(int)inData[5];
      }
      else if(i == 6){    
        Motor3Direction=(int)inData[6];
      }
      else if(i == 7){    
        Motor4Direction=(int)inData[7];
      }
      else if(i == 8){    
        Motor5Direction=(int)inData[8];
      }
      else if(i == 9){    
        intakePower=(int)inData[9];
      }
      else if(i == 10){    
        intakeDirection=(int)inData[10];
      }
      else if(i == 11){    
        feedPower=(int)inData[11];
      }
      else if(i == 12){    
        shooterSpeed=(int)inData[12];
      }
      else if(i == 13){    
        kill=(int)inData[12];
      }
    } 
    run();

  }
}
void run (){
  Serial.println("Assigning Motor Values.");

  if(kill!=1){
    analogWrite(MOTOR2, MotorSpeed2);//Serial.println(MotorSpeed1);  
    analogWrite(MOTOR3, MotorSpeed3);//Serial.println(MotorSpeed2); 
    analogWrite(MOTOR4, MotorSpeed4);//Serial.println(MotorSpeed3); 
    analogWrite(MOTOR5, MotorSpeed5);//Serial.println(MotorSpeed4); 

    digitalWrite(MOTOR2DIRECTION, Motor2Direction);
    digitalWrite(MOTOR3DIRECTION, Motor3Direction);
    digitalWrite(MOTOR4DIRECTION, Motor4Direction);
    digitalWrite(MOTOR5DIRECTION, Motor5Direction);
    digitalWrite(SHOOTERSPEED, shooterSpeed);
    digitalWrite(INTAKEPOWER, intakePower);
    digitalWrite(INTAKEDIR, intakeDirection);
    digitalWrite(FEEDPOWER, feedPower);
  }
}



