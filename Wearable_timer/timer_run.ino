
int startTone = 1500;
int startBeep = 1800;
int midBuzz = 2200;

int buzzer_duration = 50;
unsigned long buzz_timer;
int timeStep = 100;

void timerRun(){
  if (delayed_start) preStartBuzz();

  buzz_timer = millis();
  tone(buzzer, startBeep);

  if (timeRhythm > 0.0){
    if (timeRhythm>0.3) timeRhythm = timeRhythm - 0.1;
    unsigned int time_dif = millis() - buzz_timer;
    while (time_dif < tempRhythm*1000){
      if (time_dif > buzzer_duration) noTone(buzzer);
      timeRhythm = tempRhythm - (time_dif/1000.0);
      display_time();
      time_dif = millis() - buzz_timer;
    }
  }

  buzz_timer = millis();
  tone(buzzer, midBuzz);

  if (timeRead > 0.0){
    if (timeRead>0.3) timeRead = timeRead - 0.1;
    unsigned int time_dif = millis() - buzz_timer;
    while (time_dif < tempRead*1000){
      if (time_dif > buzzer_duration) noTone(buzzer);
      timeRead = tempRead - (time_dif/1000.0);
      display_time();
      time_dif = millis() - buzz_timer;
      
    }
  }

  buzz_timer = millis();
  tone(buzzer, midBuzz);

  if (timeRush > 0.0){
    if (timeRush>0.3) timeRush = timeRush - 0.1;
    unsigned int time_dif = millis() - buzz_timer;
    while (time_dif < tempRush*1000){
      if (time_dif > buzzer_duration) noTone(buzzer);
      timeRush = tempRush - (time_dif/1000.0);
      display_time();
      time_dif = millis() - buzz_timer;      
    }
  }

  buzz_timer = millis();
  tone(buzzer, midBuzz);  

  if (timeRelease > 0.0){
    if (timeRelease>0.3) timeRelease = timeRelease - 0.1;
    unsigned int time_dif = millis() - buzz_timer;
    while (time_dif < tempRelease*1000){
      if (time_dif > buzzer_duration) noTone(buzzer);
      timeRelease = tempRelease - (time_dif/1000.0);
      display_time();
      time_dif = millis() - buzz_timer; 
    }
  }
  tone(buzzer, midBuzz);
  delay(400);
  noTone(buzzer);
  
}


void preStartBuzz(){
  tone(buzzer, startTone);
  delay(500);
  noTone(buzzer);
  delay(500);

  tone(buzzer, startTone);
  delay(500);
  noTone(buzzer);
  delay(500);
}
