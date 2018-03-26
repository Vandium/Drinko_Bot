#include <Adafruit_NeoPixel.h>


#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      24

#define E1_STEP_PIN        36
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30

#define SDPOWER            -1
#define SDSS               53
#define LED_PIN            13



#define HEATER_1_PIN        7
#define HEATER_2_PIN       -1

#define TEMP_0_PIN         13   // ANALOG NUMBERING
#define TEMP_1_PIN         15   // ANALOG NUMBERING
#define TEMP_2_PIN         -1   // ANALOG NUMBERING
#define TEMP_BED_PIN       14   // ANALOG NUMBERING


#define BEEPER_PIN 37
#define HEATER_BED_PIN    8    // BED
//****************************************** END OF MKS BASE MARLIN PIN DEFINITIONS ************************************

//WS2812 LED ring for camera lighting
#define CAM_LED A11
#define CAM_LED_NUM 24
Adafruit_NeoPixel CamLight = Adafruit_NeoPixel(CAM_LED_NUM, CAM_LED, NEO_GRB + NEO_KHZ800);


//Serial command data
String Stream = ""; // serial buffer
String Descriptor = "";
String X_MOVE = "";
String Y_MOVE = "";
int x = 0;
int y = 0;



void setup() {
Serial.begin(115200);
CamLight.begin();
Serial.println("Running.........");
setAllColor(); // turns on Cam Light Ring


// X axis stepper driver pins
pinMode(X_STEP_PIN,OUTPUT);  
pinMode(X_DIR_PIN,OUTPUT);      
pinMode(X_ENABLE_PIN,OUTPUT);   
pinMode(X_MIN_PIN,INPUT);        
pinMode(X_MAX_PIN,INPUT);

// Y axis stepper driver pins
pinMode(Y_STEP_PIN,OUTPUT);      
pinMode(Y_DIR_PIN,OUTPUT);      
pinMode(Y_ENABLE_PIN,OUTPUT);      
pinMode(Y_MIN_PIN,INPUT);         
pinMode(Y_MAX_PIN,INPUT);          


//Z axis stepper driver pins
pinMode(Z_STEP_PIN,OUTPUT);         
pinMode(Z_DIR_PIN,OUTPUT);          
pinMode(Z_ENABLE_PIN,OUTPUT);      
pinMode(Z_MIN_PIN,INPUT);          
pinMode(Z_MAX_PIN,INPUT);          


//E0 axis stepper driver pins
pinMode(E0_STEP_PIN,OUTPUT);        
pinMode(E0_DIR_PIN,OUTPUT);         
pinMode(E0_ENABLE_PIN,OUTPUT);      


//E1 axis stepper driver pins
pinMode(E1_STEP_PIN,OUTPUT);       
pinMode(E1_DIR_PIN,OUTPUT);        
pinMode(E1_ENABLE_PIN,OUTPUT);      

//low enables stepper
digitalWrite(X_ENABLE_PIN,HIGH);
digitalWrite(Y_ENABLE_PIN,HIGH);
digitalWrite(Z_ENABLE_PIN,HIGH);
digitalWrite(E0_ENABLE_PIN,HIGH);
digitalWrite(E1_ENABLE_PIN,HIGH);
}

void loop() {

checkSerial(); // in the future this should return a boolean or maybe the interperatation of the G code

if(x != 0 && y != 0){
    moveTo(x,y);
}



if(x != 0){
    moveTo(x,0);

}

if(y  != 0){
    moveTo(0,y);
}


  


}




