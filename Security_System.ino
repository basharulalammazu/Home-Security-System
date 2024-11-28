#include <SoftwareSerial.h>

//phone number must be with country code
//NOTE: Must be your personal phone number here
//this is not gsm module phone number
const String PHONE = "ENTER_YOUR_PHONE_NUMBER";

//SIM800L Module pin
#define rxPin 4
#define txPin 5
SoftwareSerial sim800L(rxPin,txPin);

#define LASER_RECEIVER_PIN 9
#define LASER_TRANSMIT_PIN 8
//fire_flag = 0 means tripwire detected
boolean laser_flag = 0;

//int Laser = 8;
//int Ldr = 9;
#define BUZZER_PIN 11
//int buzzer = 11;
int led1 = 2;
int led2 = 3;

void setup() 
{    
    //Begin serial communication: Arduino IDE (Serial Monitor)
    Serial.begin(115200);
    //----------------------------------------------------------------
    //Begin serial communication: SIM800L
    sim800L.begin(9600);
    //----------------------------------------------------------------
    pinMode(LASER_RECEIVER_PIN,INPUT);
    pinMode(LASER_TRANSMIT_PIN,OUTPUT);
    //by default the LASER Transmitter is ON
    digitalWrite(LASER_TRANSMIT_PIN,HIGH);
    //----------------------------------------------------------------
    pinMode(BUZZER_PIN, OUTPUT);
    //by default the BUZZER is OFF
    digitalWrite(BUZZER_PIN,LOW);
    //----------------------------------------------------------------
    //pinMode(Laser,OUTPUT);
    //pinMode(Ldr,INPUT);
    //pinMode(buzzer,OUTPUT);
    pinMode(led1,OUTPUT);
    pinMode(led2,OUTPUT);

    Serial.println("Initializing...");

    //Once the handshake test is successful, it will back to OK
    sim800L.println("AT");
    delay(1000);
    sim800L.println("AT+CMGF=1");
    delay(1000);
    //----------------------------------------------------------------
}

 void loop()
{ 
    while(sim800L.available())
    {
        Serial.println(sim800L.readString());
    }

    int laser_value = digitalRead(LASER_RECEIVER_PIN);

    if(laser_value == LOW) 
    {
        digitalWrite(BUZZER_PIN,HIGH);
        if(laser_flag == 0) 
        {
            Serial.println("Laser Tripwire Detected.");
            laser_flag == 1;
            make_call();
        }
        digitalWrite(2,LOW);
        digitalWrite(3,HIGH);
        //----------------------------------------------------------------
    }

    else 
    {
        //Serial.println("Laser Tripwire !Detected.");
        digitalWrite(BUZZER_PIN,LOW);
        laser_flag = 0;
        digitalWrite(2,HIGH);
        digitalWrite(3,LOW);
    }
}

void make_call()
{
    Serial.println("calling....");
    sim800L.println("ATD"+PHONE+";");
    delay(20000); //20 sec delay
    sim800L.println("ATH");
    delay(1000); //1 sec delay
}
