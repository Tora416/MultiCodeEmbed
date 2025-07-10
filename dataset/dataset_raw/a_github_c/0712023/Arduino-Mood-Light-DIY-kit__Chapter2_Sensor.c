#include <Adafruit_NeoPixel.h>  
int RGB_PIN = 3;  
int NUMPIXELS = 8;  
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

#include <DHT.h> 
int DHT_PIN = 5;  
DHT dht(DHT_PIN, DHT11);

int TOUCH_PIN = 4;  
int TRIG_PIN = 10;  
int ECHO_PIN = 12;  
int CDS_PIN = A0;  
int POTEN_PIN = A5;  
int r, g, b, R, G, B, Mode, touch_count;  
int Mode_EA = 5;  
int temp_1 = 23, temp_2 = 26;  
int cds_1 = 530, cds_2 = 1000;  
int dis_1 = 100, dis_2 = 300, dis_3 = 500;  
boolean touch = true, cds_RGB = true;  
double cds_cur, cds_pre = cds_1;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);  
  pinMode(ECHO_PIN, INPUT);  
  pixels.begin();  
  pixels.show();  
}


void loop() {
  Mode_set();  
  int poten = analogRead(POTEN_PIN);  

  if ( Mode == 0 || Mode == 1 || Mode == 2 ) {  
    for ( int i = 0; i < NUMPIXELS; i++ ) { 
      pixels.setPixelColor(i, pixels.Color( map(poten, 0, 1023, 0, r) , map(poten, 0, 1023, 0, g) , map(poten, 0, 1023, 0, b) ) );  
      pixels.show(); 
    }
  }

  
  if ( digitalRead(TOUCH_PIN) == 1 ) {  
    touch_count++;  
    delay(10);  

    if ( touch_count >= 100 ) {  
      if ( r == 0 && g == 0 && b == 0 ) {  
        r = 1;
      }

      else if ( r != 0 || g != 0 || b != 0 ) {  
        r = 0;
        g = 0;
        b = 0;
        Mode = 0;
      }

      touch_count = 0;  
    }

    else if ( touch && ( r != 0 || g != 0 || b != 0 ) ) {  
      Mode++;

      if ( Mode > Mode_EA ) {
        cds_RGB = true;
        Mode = 1;
      }

      touch = false;
    } else;                                                   
  }

  else {
    touch = true;
    touch_count = 0 ;
  }
  
}


void Mode_set() {
  if ( Mode == 1) {
    r = 210;
    g = 100;
    b = 10;
  }

  else if ( Mode == 2 ) {
    temp_set();
  }

  else if ( Mode == 3 ) {
    cds_set();
  }

  else if ( Mode == 4 ) {
    ultra_set();
  }

  else if ( Mode == 5 ) {
    temp_set();
    cds_set();
  }
}



void temp_set() {
  int celsius = dht.readTemperature();  

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
}



void cds_set() {

  if ( cds_RGB ) {
    r = random(255);
    g = random(255);
    b = random(255);
    cds_RGB = false;
  }

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
  delay(50);

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
