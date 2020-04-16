//A project of Corona Live stats using GET command and esp8266 module from https://www.iedcr.gov.bd/
/*
 * 
 * |||||||||||||||||Components||||||||||||||||||||
 * ||                                           ||
 * ||1.ESP8266(NODEMCU);                        ||
 * ||2.LCD 16X2                                 ||
 * ||3.Breadboard;                              ||
 * ||4.Some Jumper Wires;                       ||              
 * ||5.10K Variable Resistor                    ||
 * ||                                           ||
 * |||||||||||||||||||||||||||||||||||||||||||||||
 *    
 * 
 * |||||||||||||||||||||||Pinout|||||||||||||||||||||
 * ||                                              ||
 * ||LCD(16X2)               TO         NODEMCU    ||
 * ||                                              ||
 * ||VSS                     =           GND;      ||
 * ||VDD                     =           VIN;      ||
 * ||RS                      =           D0;       ||     
 * ||RW                      =           GND;      ||
 * ||E                       =           D1;       ||
 * ||D4                      =           D2;       ||
 * ||D5                      =           D3;       ||
 * ||D6                      =           D4;       ||
 * ||D7                      =           D5;       ||
 * ||A                       =           VIN;      ||
 * ||K                       =           GND;      ||
 * ||                                              ||
 * ||Others;                                       ||||||||||||||||||||||||||||||||||||||||||||||||||||                 
 * ||                                                                                                ||
 * ||10K Variable Resistor(Left pin)             =           VIN/GND[Nodemcu](as your wish);         ||
 * ||10K Variable Resistor(Middle pin)           =           V0[LCD];                                ||                                 
 * ||10K Variable Resistor(Right pin)            =           VIN/GND[nodemcu](as your wish);         ||               
 * ||                                                                                                ||
 * ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
 * 
 * 
 * 
 * Github Repo Link: https://github.com/pollob1563/Corona-Updater/    
 *
 * Schematic Circuit Diagram: https://easyeda.com/prosenjit.pollob/nodemcu-with-lcd
 * 
 */
// include the library code:
#include <ESP8266WiFi.h>                 // initialize the library by associating any needed ESP8266(NODEMCU) interface pin
#include <LiquidCrystal.h>              // initialize the library by associating any needed LCD Module interface pin



      /**//**//**//**//**//**//**//**//**//**//*Fill Up Your Credential/**//**//**//**//**//**//**//**//**//**//***//**//***/
     /**/                                                                                                                /**/
    /**/               const char* ssid = "TP-Link_5EEC";        // Your WiFi SSID name                                 /**/
   /**/                const char* password = "76278860" ;      // Your WiFi password                                  /**/
  /**/                 const char* host="api.thingspeak.com";  // Connecting To the Website where you store your data /**/
 /**/                                                                                                                /**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/


const int rs = D0, en = D1, d4 = D2, d5 = D3, d6 = D4, d7 = D5; //decleared those variable for connect LCD to nodemcu

int n = 1;   //For Caution                         

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                   //trying to connect LCD to Nodemcu 

void setup() {

  delay(5000);

  lcd.begin(16,2); //LCD

  lcd.clear();
  
 

  Serial.begin(115200); // Baud rate of Serial Monitor

  lcd.setCursor(0,0);
  lcd.print("WiFi:"); //Print WiFi Name at LCD display
  lcd.print(ssid);

  Serial.print("WiFi: ");  //Print WiFi Name at Serial Monitor
  Serial.println(ssid);
  
  delay (2000);

  WiFi.begin(ssid,password); //Connecting to WiFi
  lcd.clear();
  

  lcd.setCursor(0,0);
  lcd.print("WiFi Connecting");
  Serial.println("WiFi Connecting"); //Print WiFi Status at Serial Monitor
  delay(8000);                       //Waitng For Connecting
  lcd.clear();

  

  while( WiFi.status() != WL_CONNECTED ){
     
      lcd.setCursor(0,0);
      lcd.print("NOT CONNECTED");  //Print WiFi Status at LCD display (Confarmation Messege)
      
      Serial.println("WiFi NOT CONNECTED");  //Print WiFi Status at Serial Monitor(Confarmation Messege)
      Serial.println();
      delay(500);
      Serial.println("Wait a few Seconds or check your WiFi SSID and Password(In Credential Section)"); //If WiFi Not CONNECTED then the instruction print at Serial Monitor 
      delay(1000);
      lcd.clear();      
  }

  
  
  lcd.clear();
  lcd.setCursor(0,0);
  
  lcd.print("WiFi Connected!"); //Print WiFi Status at LCD Display(Confarmation Messege)
  Serial.println("Wifi Connected!"); //Print WiFi Status at Serial Monitor(Confarmation Messege)
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP() ); //Print Gateway IP at LCD Display
  delay(100);
  Serial.print("Default Gateway: ");//Gateway IP
  Serial.println(WiFi.localIP() );//Print Gateway IP at Serial Monitor

  delay(2000);
  
  lcd.clear();
  
  WiFiClient client,client1,client2; //Declear the variable for WiFiClient
  
  const int httpPort=80;            //HTTPPORT Status 
  
  if((!client.connect(host,httpPort))||(!client1.connect(host,httpPort))||(!client2.connect(host,httpPort))){
   Serial.println("Connection Failed!");
   lcd.setCursor(0,0);
   lcd.print("Connection ");
   lcd.setCursor(0,1);
   lcd.print("         Failed!");
   delay(1500);

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Connection ");
   lcd.setCursor(0,1);
   lcd.print("         Failed!");
   delay(1500);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("ERROR: ");
   lcd.setCursor(0,1);
   lcd.print("      0x80070035");
   
    
  }
  else {
    Serial.println("Connecting To: IEDCR");

   lcd.setCursor(0,0);
   lcd.print("Connecting To: ");
   delay(1000);
   lcd.setCursor(0,1);
   lcd.print("iedcr.gov.bd");
   delay(2000);
    
  }
  
  Serial.println("==========================================================================================================================================================================");//endline sign

  delay(100);
}

void loop() {

  lcd.clear();
  Serial.print("Connecting to ");
  Serial.println(host);
  
  WiFiClient client,client1,client2;
  const int httpPort=80;
  
  if((!client.connect(host,httpPort))||(!client1.connect(host,httpPort))||(!client2.connect(host,httpPort))){
   Serial.println();
   Serial.println("Connection Failed!");
   Serial.println("ERROR: 0x80070035");
   Serial.println();
   
   lcd.setCursor(0,0);
   lcd.print("Connection ");
   lcd.setCursor(0,1);
   lcd.print("         Failed!");
   delay(1500);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("ERROR: ");
   lcd.setCursor(0,1);
   lcd.print("      0x80070035");
   delay(2500);
  }
  
  lcd.setCursor(0,0);
  lcd.print("COVID-19 Live");
  lcd.setCursor(11,1);
  lcd.print("Stats");
  
  String cases ="https://api.thingspeak.com/apps/thinghttp/send_request?api_key=0WYQ4B80AG8BZ6BD";  //Total Cases
  
  Serial.println(cases);
  client.print(String("GET ")+ cases + " HTTP/1.0\r\n"+
               "Host: "+ host +  "\r\n" +
               "Connection: close\r\n\r\n");
  
               
  client.flush();             
  delay(500); 
  
  String recovered ="https://api.thingspeak.com/apps/thinghttp/send_request?api_key=ZX7A6PQ6HZFA09XR"; // Total Recovered 
  Serial.println(recovered);
  client1.print(String("GET ")+ recovered + " HTTP/1.0\r\n"+
               "Host: "+ host +  "\r\n" +
               "Connection: close\r\n\r\n");
  
               
  client1.flush();             
  delay(500); 
  
  
  String death ="https://api.thingspeak.com/apps/thinghttp/send_request?api_key=MK37Y3T4BVTZ4P4S"; //Total Death
  Serial.println(death);
  client2.print(String("GET ")+ death + " HTTP/1.0\r\n"+
               "Host: "+ host +  "\r\n" +
               "Connection: close\r\n\r\n");
  
               
  client2.flush();             
  delay(500); 

  Serial.println();
  Serial.println("Country: BANGLADESH");
  Serial.println();

  delay(1500);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.print(">>>>Country>>>>");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("   BANGLADESH   ");
  delay(1000);
  
  
  while(client.available()){
  String line=client.readStringUntil('\r');
  if((line.substring(1,2)=="1")||(line.substring(1,2)=="2")||(line.substring(1,2)=="3")||(line.substring(1,2)=="4")||(line.substring(1,2)=="5")||(line.substring(1,2)=="6")||(line.substring(1,2)=="7")||(line.substring(1,2)=="8")||(line.substring(1,2)=="9"))
  {
     Serial.println();
     Serial.print("Total Cases:     ");
     Serial.println(line.substring(1,13));
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("T.Cases: ");
     lcd.print(line.substring(1,13));
     delay(1000);
     
     lcd.setCursor(0,1);
     lcd.print("Source: IEDCR"); 
     delay(6000);
     break;
  
  }
  
  else if (n==18) {
     Serial.println();
     Serial.println("Data Not Found");
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Error: 503");
     delay(500);
     
     lcd.setCursor(0,1);
     lcd.print("................"); 
     delay(2000);
     break;
  }

  n++;
  
  Serial.print(".");
  
  
  }

  Serial.println();
  Serial.println();

  n = 1;

  while(client1.available()){
  String line1=client1.readStringUntil('\r');

  if((line1.substring(1,2)=="1")||(line1.substring(1,2)=="2")||(line1.substring(1,2)=="3")||(line1.substring(1,2)=="4")||(line1.substring(1,2)=="5")||(line1.substring(1,2)=="6")||(line1.substring(1,2)=="7")||(line1.substring(1,2)=="8")||(line1.substring(1,2)=="9"))
  {
     Serial.println();
     Serial.print("Total Recovered: ");
     Serial.println(line1.substring(1,13));

     lcd.setCursor(0,0);
     lcd.print(">>>>>>>>>>>>>>>>");
     delay(1000);
     lcd.setCursor(0,0);
     lcd.print("                ");
     lcd.setCursor(0,0);
     lcd.print("Recovered: ");
     lcd.print(line1.substring(1,13));
     
     delay(6000);  
      break;
  
  }

  else if (n==18) {
     Serial.println();
     Serial.println("Data Not Found");
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Error: 503");
     delay(500);
     
     lcd.setCursor(0,1);
     lcd.print("................"); 
     delay(2000);
     break;
  }

  n++;
  
  Serial.print(".");
  
  }

  Serial.println();
  Serial.println();

  n = 1;
    
  while(client2.available()){
  String line2=client2.readStringUntil('\r');
  if((line2.substring(1,2)=="1")||(line2.substring(1,2)=="2")||(line2.substring(1,2)=="3")||(line2.substring(1,2)=="4")||(line2.substring(1,2)=="5")||(line2.substring(1,2)=="6")||(line2.substring(1,2)=="7")||(line2.substring(1,2)=="8")||(line2.substring(1,2)=="9"))
  {
     Serial.println();
     Serial.print("Total death:  ");
     Serial.println(line2.substring(1,13));
     
     lcd.setCursor(0,0);
     lcd.print(">>>>>>>>>>>>>>>>");
     delay(1000);
     lcd.setCursor(0,0);
     lcd.print("                ");
     lcd.setCursor(0,0);
     lcd.print("T.Death: ");
     lcd.print(line2.substring(1,13));
     
     delay(6000);
     break;
  
  }
  else if (n==18) {
       Serial.println();
       Serial.println("Data Not Found");
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Error: 503");
       delay(500);
       
       lcd.setCursor(0,1);
       lcd.print("................"); 
       delay(2000);
       break;
    }
  
    n++;
    
    Serial.print(".");
  }

  Serial.println();
  Serial.println();

  n = 1;
  
  lcd.setCursor(0,0);
  lcd.print(">>>>>>>>>>>>>>>>");
  lcd.setCursor(0,1);
  lcd.print("<<<<<<<<<<<<<<<<<");

  Serial.println("</></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></>"); //endline sign
  Serial.println();
  
}
