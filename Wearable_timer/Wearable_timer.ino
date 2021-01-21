#define startBtn 2
#define plusBtn 7
#define minusBtn 6
#define oneBtn 11
#define twoBtn 10
#define threeBtn 9
#define fourBtn 8
#define buzzer 3
#define oled_power A0
#define batt_voltage A2

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
float timeRead = 0.4;
float timeRush = 0.4;
float timeRelease = 0.4;

float bat_level = 3.7;
float curr_voltage = 0.0;

float tempRhythm,tempRead, tempRush, tempRelease;
  
int mode = 0; //rhythm, read, rush, release
bool delayed_start = 0;  //buzz three beeps on delayed start

bool timer_run = false;

unsigned long last_active_time = 0;
unsigned int wake_duration = 120000;

void setup() {
   Serial.begin(115200);
   pinMode(oled_power,OUTPUT);
   pinMode(batt_voltage,INPUT);
   digitalWrite(oled_power,HIGH);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  //display.display();
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
  //delay(50);
  noTone(buzzer);

  delay(2000);
  //read_switch();
  //preStartBuzz();
  //timerRun();

  
  Serial.println("Initialized");

}

void loop() {
  display_time();
  read_switch();
  battery_read();
  delay(50);
  

  if (millis()- last_active_time > wake_duration) goToSleep();
  //Serial.println("Active");
  digitalWrite(oled_power,HIGH);
}

void goToSleep(){
  Serial.println("sleep");
  //display.clearDisplay();
  //display.display();
  //display.ssd1306_command(SSD1306_DISPLAYOFF);
  digitalWrite(oled_power,LOW);
  //display.ssd1306_command(0x8D);            // disable charge pump
  sleep_enable();
  attachInterrupt(0,wakeUp,LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();

  //continue below after waking up
  //display.ssd1306_command(SSD1306_DISPLAYON);
  digitalWrite(oled_power,HIGH);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  //display.display();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  last_active_time = millis();
  delay(250);
}

void wakeUp(){
  sleep_disable(); 
  //display.ssd1306_command(0x8D);
  //
  //display.ssd1306_command(SSD1306_DISPLAYON);
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  detachInterrupt(0);
  Serial.println("woke up");
  
}

void battery_read(){
  curr_voltage = getVoltage()/100;
  bat_level = (bat_level*0.95)+(curr_voltage*0.05);
}

int getVoltage(void) // Returns actual value of Vcc (x 100)
{
    // For 168/328 boards
    const long InternalReferenceVoltage = 1056L;  // Adjust this value to your boards specific internal BG voltage x1000

    // REFS1 REFS0          --> 0 1, AVcc internal ref. -Selects AVcc external reference
    // MUX3 MUX2 MUX1 MUX0  --> 1110 1.1V (VBG)         -Selects channel 14, bandgap voltage, to measure
    ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (0<<MUX0);

    delay(50);  // Let mux settle a little to get a more stable A/D conversion
    
    // Start a conversion  
    ADCSRA |= _BV( ADSC );
    
    // Wait for it to complete
    while( ( (ADCSRA & (1<<ADSC)) != 0 ) );
    
    // Scale the value
    int results = (((InternalReferenceVoltage * 1024L) / ADC) + 5L) / 10L; // calculates for straight line value 
    
    return results;
}
