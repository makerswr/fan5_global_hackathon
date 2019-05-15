// 선언파트
#include <Nextion.h>  
#include <Servo.h>
Servo myservo;
static int cnt = 0;/nextion <-> arduino serial test
NexButton p0 = NexButton(1, 1, "p0");  // page Button added
NexTouch *nex_listen_list[] = 
{
  &p0,  
  NULL
};  

// 함수파트
void p0PushCallback(void *ptr)  // Press event for button b1
{
  digitalWrite(10,LOW); // LovEarth Servo
  digitalWrite(11,LOW); // Animal, Trashbin
  digitalWrite(13,LOW); // LED Test
  delay(5500);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(13,HIGH);
} 
void p0PopCallback(void *ptr)  // Release event for page p0 (but no release event given from nexiton
{
  
}  

//셋업파트
void setup() { 
  myservo.attach(9); //servo attach 
  Serial.begin(9600);  // Start serial comunication at baud=9600
  // I am going to change the Serial baud to a faster rate.
  // The reason is that the slider have a glitch when we try to read it's value.
  // One way to solve it was to increase the speed of the serial port.
  delay(500);  // This dalay is just in case the nextion display didn't start yet, to be sure it will receive the following command.
  Serial.print("baud=115200");  // Set new baud rate of nextion to 115200, but it's temporal. Next time nextion is power on,
                                // it will restore to default baud of 9600.
                                // To take effect, make sure to reboot the arduino (reseting arduino is not enough).
                                // If you want to change the default baud, send the command as "bauds=115200", instead of "baud=115200".
                                // If you change the default baud, everytime the nextion is power ON is going to have that baud rate, and
                                // would not be necessery to set the baud on the setup anymore.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to nextion.
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.end();  // End the serial comunication of baud=9600
  Serial.begin(115200);  // Start serial comunication at baud=115200
  
  p0.attachPush(p0PushCallback);  // Button press
  p0.attachPop(p0PopCallback);  // Button release
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}
//루프 파트
void loop() { 
  nexLoop(nex_listen_list);  // Check for any touch event
} 
