#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// set pin numbers

const int GreentouchPin = 15;
const int GreenledPin = 16;
const int YellowtouchPin = 32;
const int YellowledPin = 19;
const int RedtouchPin = 33;
const int RedledPin = 18;

char ssid[] = "iPhone7";      // my hotspot name
char password[] = "12345677"; // my hotspot password

String key = "fAbTjvDGXQXK9U_bZzDdi"; //webhooks key
String event_name = "com3505_2021";   //webhooks event name
//values that you want to send when the event is triggered
String value1 = "button";               
String value2 = "was";                
String value3 = "touched";                

//threshold value
const int threshold = 20;
// variable for storing the touch pin value
int NotificationtouchValue;
int greentouchValue;
int yellowtouchValue;
int redtouchValue;

void setup()
{
        Serial.begin(115200);
        pinMode(14, INPUT_PULLUP);
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        delay(1000); // give me time to bring up serial monitor

        // Attempt to connect to Wifi network:

        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED)
        {
                delay(500);
        }
        // initialize the LED pin as an output:
        pinMode(GreenledPin, OUTPUT);
        pinMode(YellowledPin, OUTPUT);
        pinMode(RedledPin, OUTPUT);
}
void loop()
{
        // read the state of the pushbutton value:
        greentouchValue = touchRead(GreentouchPin);
        Serial.print(greentouchValue);
        yellowtouchValue = touchRead(YellowtouchPin);
        Serial.print(yellowtouchValue);
        redtouchValue = touchRead(RedtouchPin);
        Serial.print(redtouchValue);
      
        Serial.print(" ");
        NotificationtouchValue = digitalRead(14);
        Serial.print(NotificationtouchValue);
     

        // check if the touchValue is below the threshold
        // if it is, set ledPin to HIGH
        if (yellowtouchValue < threshold)
        {
                // turn LED on
                digitalWrite(YellowledPin, HIGH);
                delay(100); // wait for a second
                digitalWrite(YellowledPin, LOW);

                Serial.println(" Yellow LED on");
        }
        else
        {
                digitalWrite(YellowledPin, LOW);
                Serial.println(" Yellow LED off");
        }
        
        // check if the touchValue is below the threshold
        // if it is, set ledPin to HIGH
        if (greentouchValue < threshold)
        {
                digitalWrite(GreenledPin, HIGH);
                delay(800); // wait for a second
                digitalWrite(GreenledPin, LOW);

                Serial.println(" Green LED on");
        }
        else
        {
                digitalWrite(GreenledPin, LOW);
                Serial.println(" Green LED off");
        }
        
        // check if the touchValue is below the threshold
        // if it is, set ledPin to HIGH
        if (redtouchValue < threshold)
        {
                digitalWrite(RedledPin, HIGH);
                Serial.println("Red LED on");
        }
        else
        {
                // turn LED off
                digitalWrite(RedledPin, LOW);
                Serial.println(" Red LED off");
        }

        // check if the touchValue is below the threshold
        // if it is, send notification to my phone
        if (digitalRead(14) == LOW)
        {
                HTTPClient http;
                http.begin("http://maker.ifttt.com/trigger/" + event_name + "/with/key/" + key + "?value1=" + value1 + "&value2=" + value2 + "&value3=" + value3);
                http.GET();
                http.end();
        }
        else
        {
                Serial.print("done");
        }
        delay(1000);
}