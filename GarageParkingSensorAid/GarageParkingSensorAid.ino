#include <ESP8266WiFi.h>
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 1
#define DATA_PIN 3

// utlrasonic pinout
#define ULTRASONIC_TRIG_PIN     5   // pin TRIG to D1
#define ULTRASONIC_ECHO_PIN     4   // pin ECHO to D2

//WiFi Parameters
const char* ssid     = "your-ssid";
const char* password = "your-password";


CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wifi
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // ultraonic setup 
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);

  // Define the array of leds
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {

  long duration, distance;
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);  
  delayMicroseconds(2); 
          
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10); 
          
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print("********** Ultrasonic Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
          
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
}
