#include <Arduino.h>
#include <Wifi.h>
#include <WebServer.h>

//defining the motor pins that i connected
#define ENA 13
#define IN1 12
#define IN2 14
#define ENB 15
#define IN3 27
#define IN4 26

const uint8_t PWM_CH_A =0;
const uint8_t PWM_CH_B =1;
const uint16_t PWM_FREQ =1000; //speed 
const uint8_t PWM_RES =8;

int speedValue = 200; //inital speed that willbe made to control

//wifi initialization
const char* ssid="Niranjan_Car";
const char* password="12345678";
WebServer server(80);

//function prototype definationa
void stopMotor();
void forward();
void backward();
void left();
void right();
void handleRoot();

//starting serial to begin communication
void setup(){
Serial.begin(115200);
//defining pin mode
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);

//for speeed setup for signal to motor driver form the esp
ledcSetup(PWM_CH_A,PWM_FREQ,PWM_RES);
ledcAttachPin(ENA,PWM_CH_A); 
ledcSetup(PWM_CH_B,PWM_FREQ,PWM_RES);
ledcAttachPin(ENB,PWM_CH_A); 


//creating own access point 
WiFi.softAP(ssid,password);
Serial.print("IP Address");
Serial.println(WiFi.softAPIP());

//html and api fxn this 
server.on("/", handleRoot);
server.on("/F",HTTP_GET,[](){forward(); server.send(200,"text/plain","Forward");});
server.on("/B",HTTP_GET,[](){backward(); server.send(200,"text/plain","Backward");});
server.on("/L",HTTP_GET,[](){left(); server.send(200,"text/plain","Left");});
server.on("/R",HTTP_GET,[](){right(); server.send(200,"text/plain","Right");});
server.on("/R",HTTP_GET,[](){stopMotor(); server.send(200,"text/plain","Stop");});


server.on("/speed",HTTP_GET,[](){
  if(server.hasArg("v")){
    speedValue=server.arg("v").toInt(); //string to int
    speedValue=constrain(speedValue,0,225); //clamping value form 0 tp 225
    ledcWrite(PWM_CH_A,speedValue);
    ledcWrite(PWM_CH_B,speedValue);
  }
  server.send(200,"text/plain","Speed set");
});
server.begin();
Serial.println("RObo car is ready bruhhhhhh");
}
//fro response fo the http 
void loop() {
  server.handleClient();
}





