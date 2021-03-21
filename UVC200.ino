
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>      
             
 
#define FIREBASE_HOST "uvc200-88612-default-rtdb.firebaseio.com"      
#define FIREBASE_AUTH "RwxrQAFPLmyti8GUOFwXvfFxemqwAJHLWkH7tRVM"            
#define WIFI_SSID "Varnit"                                  
#define WIFI_PASSWORD "Primus2147"            


#include <Adafruit_GFX.h>        //OLED libraries
#include <Adafruit_SSD1306.h>
#include <Wire.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declaring the display name (display)

 int t=200;



/////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(9600);
   
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Start the OLED display
  display.display();
  delay(1000);
               
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());                               //prints local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                 // connect to the firebase
  
 
}
 
void loop() 
{
   


 delay(1000);
////////////////////////////////////////////////////////////////////////////////////////////////
  Firebase.setInt("/timer/Time_left", t);            
 //////////////////////////////////////////////////////////////////////////////////////////////////////
t--;
display.clearDisplay();  
  display.setTextSize(1);                                   //Near it display the average BPM you can display the BPM if you want
    display.setTextColor(WHITE); 
    display.setCursor(0,10);                
    display.println("Time left:");             
    display.setCursor(60,10);                
    display.println(t); 
 display.display();

  
if (t==0)
{
t=0;
 Firebase.setInt("/timer", t); 
   String done =String("Inprogress");                  

  Firebase.pushString("/timer/Status", done);

 display.clearDisplay();
  draw_circle();
   delay(500);
  draw_rectangle();
   delay(500);
  draw_triangle();
    delay(500);
  display.display();   

  
display.clearDisplay();
display.setTextSize(2);                                   //Near it display the average BPM you can display the BPM if you want
    display.setTextColor(WHITE); 
    display.setCursor(0,0);                
    display.println("Sanitized! Open it");
 display.display();  
delay(60000);
}
 

    if (Firebase.failed()) 
    {
 
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error()); 
      return;
  }
}

void draw_circle(){
  display.clearDisplay();
  display.drawCircle(display.width()/2, display.height()/2, 8, WHITE); //(Center x position, Center y position, radius, color)
  display.display();
}

//The function below clears the whole screen and draw a rectangle
void draw_rectangle(){
  display.clearDisplay();
  display.drawRect(0, 0, display.width()/2, display.height()/2, WHITE); //(Rectangle top left point x position, y position, Rectangle bottom right x position, y position, color)
  display.display();
}

//The function below clears the whole screen and draw a triangle
void draw_triangle(){
  display.clearDisplay();
  display.drawTriangle(10, 28, 64, 5, 110, 28, WHITE); //(x1,y1,x2,y2,x3,y3, color) three points of the triangle
  display.display();
}

/*
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>      
             
 
#define FIREBASE_HOST "uvc200-88612-default-rtdb.firebaseio.com"      
#define FIREBASE_AUTH "RwxrQAFPLmyti8GUOFwXvfFxemqwAJHLWkH7tRVM"            
#define WIFI_SSID "Varnit"                                  
#define WIFI_PASSWORD "Primus2147"            

 int t=20;
/////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(9600);
                                              //reads dht sensor data 
               
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());                               //prints local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                 // connect to the firebase
  
 
}
 
void loop() 
{
   


 delay(1000);
////////////////////////////////////////////////////////////////////////////////////////////////
  Firebase.setInt("/timer/Time_left", t);            
 //////////////////////////////////////////////////////////////////////////////////////////////////////
t--;
  
if (t==0)
{
t=0;
 Firebase.setInt("/timer", t); 
   String done =String("Sanitized, Open the Lid");                  

  Firebase.pushString("/timer/Time_left", done);
delay(60000);
}
 

    if (Firebase.failed()) 
    {
 
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error()); 
      return;
  }
}
*/
 
