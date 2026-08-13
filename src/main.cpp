#include <Arduino.h>
#include <WiFi.h>
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
ledcAttachPin(ENB,PWM_CH_B); 


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
server.on("/S",HTTP_GET,[](){stopMotor(); server.send(200,"text/plain","Stop");});


server.on("/speed",HTTP_GET,[](){
  if(server.hasArg("v")){
    speedValue=server.arg("v").toInt(); //string to int
    speedValue=constrain(speedValue,0,255); //clamping value form 0 tp 225
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

void handleRoot(){
  String html =R"rawliteral(
  <!DOCTYPE html><html>
    <head>
      <title>NRXN CAR</title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <style>
      body{ text-align: center; font-family:sans-serif;}
      button{
      width: 100px; height:40px;
      font-size:16px; margin:10px;
      }
      input[type=range]{widht:80%}
      </style>
      <script>
        function sendCommand(cmd){
        fetch("/"+cmd);
        }
        //for the javascript fxn i.e button functionality 
        function setupButton(id,command){
        const btn =document.getElementById(id);
        btn.addEventListener('mousedown',()=> sendCommand(command));
        btn.addEventListener('mouseup', () => sendCommand('S'));
          btn.addEventListener('touchstart', (e) => { e.preventDefault(); sendCommand(command); });
          btn.addEventListener('touchend', (e) => { e.preventDefault(); sendCommand('S'); });
        }
        function setSpeed(val) {
          fetch("/speed?v=" + val);
          document.getElementById("speedLabel").innerText = val;
        }
        window.onload = () => {
          setupButton("forward", "F");
          setupButton("backward", "B");
          setupButton("left", "L");
          setupButton("right", "R");
        };
      </script>
    </head>
    <body>
      <h2 style="text-align: center; font-weight:500; text-transform:uppercase">NRXN WEB CONTROLLED CAR</h2>
      <div>
        <button id="forward">Forward (F)</button><br>
        <button id="left">Left(L)</button>
        <button id="right">Right(R)</button><br>
        <button id="backward">Backward(B)</button>
      </div>
      <p>Speed: <span id="speedLabel">200</span></p>
        <input type="range" min="0" max="255" value="200" oninput="setSpeed(this.value)">
      </div>
    </body>
    </html>
        })rawliteral";
        server.send(200,"text/html", html);
}
void forward(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void backward(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
//motor A moves forward and B backward leading to left 
void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);    
}
void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

