#define startBtn 3
#define plusBtn 8
#define minusBtn 9
#define oneBtn 4
#define twoBtn 5
#define threeBtn 6
#define fourBtn 7
#define buzzer 2


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/sleep.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 4 );

float timeRhythm = 1.8;
float timeRead = 1.4;
float timeRush = 0.4;
float timeRelease = 0.4;

float tempRhythm,tempRead, tempRush, tempRelease;
  
int mode = 0; //rhythm, read, rush, release
bool delayed_start = 0;  //buzz three beeps on delayed start
int buzzer_duration = 40;

bool timer_run = false;

unsigned long last_active_time = 0;
unsigned int wake_duration = 15000;

void setup() {
   Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.display();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  pinMode(buzzer,OUTPUT);
  
  pinMode(startBtn, INPUT_PULLUP);
  pinMode(plusBtn, INPUT_PULLUP);
  pinMode(minusBtn, INPUT_PULLUP);
  pinMode(oneBtn, INPUT_PULLUP);
  pinMode(twoBtn, INPUT_PULLUP);
  pinMode(threeBtn, INPUT_PULLUP);
  pinMode(fourBtn, INPUT_PULLUP);

  tone(buzzer,2000);
  delay(50);
  noTone(buzzer);

}

void loop() {
  display_time();
  read_switch();

  delay(50);
  display.clearDisplay();

  if (millis()- last_active_time > wake_duration) goToSleep();

}

void goToSleep(){
  Serial.println("sleep");
  //display.clearDisplay();
  //display.display();
  display.ssd1306_command(SSD1306_DISPLAYOFF);
  //display.ssd1306_command(0x8D);            // disable charge pump
  sleep_enable();
  attachInterrupt(1,wakeUp,LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();

  //continue below after waking up
  Serial.println("woke up");
  display.ssd1306_command(SSD1306_DISPLAYON);
}

void wakeUp(){
  sleep_disable(); 
  //display.ssd1306_command(0x8D);
  //display.ssd1306_command(SSD1306_DISPLAYON);
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  detachInterrupt(1);
  //Serial.println("woke up");
  last_active_time = millis();
}
