#include <MsTimer2.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(8, 7);

#include <Adafruit_NeoPixel.h>  
int RGB_PIN = 3;  
int NUMPIXELS = 8;  
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

#include <DHT.h> 
int DHT_PIN = 5;  
DHT dht(DHT_PIN, DHT11);

int TRIG_PIN = 10;  
int ECHO_PIN = 12;  
int CDS_PIN = A0;  
int temp_1 = 23, temp_2 = 26;  
int cds_1 = 530, cds_2 = 950;  
int dis_1 = 100, dis_2 = 300, dis_3 = 500;  
int r, g, b, celsius; 
double cds_cur, cds_pre = cds_1;
boolean DEBUG = true, RGB_Completed = false;
int rainbow[6][3] = {
  {255, 0, 0},     
  {255, 50, 0},    
  {255, 150, 0},   
  {0, 255, 0},     
  {0, 0, 255},     
  {100, 0, 200},   
};  
String RGB = "";


void setup() {
  pinMode(TRIG_PIN, OUTPUT);  
  pinMode(ECHO_PIN, INPUT);  
  pixels.begin();  
  pixels.show();  
  BT.begin(9600);
  RGB.reserve(30);
}


void loop() {
  while (BT.available()) {
    char ReadChar = (char)BT.read();

    if (ReadChar == ')')
      RGB_Completed = true;
    else
      RGB += ReadChar;
  }

  if (RGB_Completed) {
    DEBUG = true;
    MsTimer2::stop();

    if (RGB == "CH1_5") {
      MsTimer2::set(200, random_set);
      MsTimer2::start();
    }
    else if (RGB == "CH1_6") {
      MsTimer2::set(50, rain_set);
      MsTimer2::start();
    }
    else if (RGB == "CH2_2") {
      DEBUG = false;
      MsTimer2::set(1000, temp_set);
      MsTimer2::start();
    }
    else if (RGB == "CH2_3") {
      r = random(255);
      g = random(255);
      b = random(255);
      MsTimer2::set(60, cds_set);
      MsTimer2::start();
    }
    else if (RGB == "CH2_4") {
      MsTimer2::set(90, ultra_set);
      MsTimer2::start();
    }
    else rgb_set();

    RGB = "";
    RGB_Completed = false;
  }

  if ( !DEBUG )
    celsius = dht.readTemperature();  
}



void rgb_set() {
  int SP1 = RGB.indexOf(' ');
  int SP2 = RGB.indexOf(' ', SP1 + 1);
  int SP3 = RGB.indexOf(' ', SP2 + 1);
  int SP4 = RGB.indexOf(' ', SP3 + 1);
  String Red = RGB.substring(0, SP1);
  String Green = RGB.substring(SP1 + 1, SP2);
  String Blue = RGB.substring(SP2 + 1, SP3);
  String Bright = RGB.substring(SP3 + 1, SP4);

  for ( int i = 0; i < NUMPIXELS; i++ ) { 
    pixels.setPixelColor(i, pixels.Color( map(Bright.toInt(), 0, 255, 0, Red.toInt()), map(Bright.toInt(), 0, 255, 0, Green.toInt()), map(Bright.toInt(), 0, 255, 0, Blue.toInt()) ) ); 
    pixels.show(); 
  }
}



void random_set() {
  r = random(255);
  g = random(255);
  b = random(255);

  for ( int i = 0; i < NUMPIXELS; i++ ) { 
    pixels.setPixelColor(i, pixels.Color( r, g, b ) );  
    pixels.show(); 
  }
}



void rain_set() {
  static int rainbow_count;
  static int rain;

  if ( DEBUG ) {
    rainbow_count += 2;
    if ( rainbow_count >= 100 ) {
      rainbow_count = 100;
      DEBUG = false;
    }
  }
  else if ( !DEBUG ) {
    rainbow_count -= 1;
    if ( rainbow_count == 0 ) {
      DEBUG = true;
      rain++;
      if ( rain == 6)
        rain = 0;
    }
  }

  for ( int i = 0; i < 8; i++ ) { 
    pixels.setPixelColor(i, pixels.Color( map(rainbow_count, 0, 100, 0, rainbow[rain][0]) , map(rainbow_count, 0, 100, 0, rainbow[rain][1]) , map(rainbow_count, 0, 100, 0, rainbow[rain][2]) ) );  
    pixels.show(); 
  }

}



void temp_set() {

  if ( celsius < temp_1 ) {  
    r = 0;  
    g = 0;  
    b = 255;  
  }
  else if ( temp_1 <= celsius && celsius < temp_2 ) {  
    r = 0;
    g = 255;
    b = 0;
  }
  else if ( celsius >= temp_2 ) {  
    r = 255;
    g = 0;
    b = 0;
  }

  for ( int i = 0; i < NUMPIXELS; i++ ) { 
    pixels.setPixelColor(i, pixels.Color( r, g, b ) );  
    pixels.show(); 
  }
}



void cds_set() {
  int cds = analogRead(CDS_PIN);
  cds_cur = (0.99 * cds_pre) + (0.01 * cds);
  cds_pre = cds_cur;
  cds = cds_cur;

  if ( cds <= cds_1 )
    cds = cds_1;

  else if ( cds_2 < cds )
    cds = cds_2;

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color( map(cds, cds_1, cds_2, 0 , r) , map(cds, cds_1, cds_2, 0 , g) , map(cds, cds_1, cds_2, 0 , b) ) );
    pixels.show();
  }
}



void ultra_set() {
  static long dis_pre;
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = ((float)(340 * duration) / 1000) / 2 ;

  if ( distance > 2000 )
    distance = dis_pre;

  if ( distance < dis_1 )
    distance = dis_1;

  else if ( distance > dis_3 )
    distance = dis_3;

  dis_pre = distance;

  if ( dis_1 <= distance && distance <= dis_2 ) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color( 255 - map(distance, dis_1, dis_2, 0, 255) , map(distance, dis_1, dis_2, 0, 255) , 0) );
      pixels.show();
    }
  }
  else if ( dis_2 <= distance && distance <= dis_3 ) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color( 0 , 255 - map(distance, dis_2, dis_3, 0, 255) , map(distance, dis_2, dis_3, 0, 255) ) );
      pixels.show();
    }
  }
}
