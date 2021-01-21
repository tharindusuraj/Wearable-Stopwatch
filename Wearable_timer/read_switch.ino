
void read_switch(){
  if (digitalRead(oneBtn) == 0){
    mode = 1;
    last_active_time = millis();
    delay(100);
  }

  else if (digitalRead(twoBtn) == 0){
    mode = 2;
    last_active_time = millis();
    delay(100);
  }

  else if (digitalRead(threeBtn) == 0){
    mode = 3;
    last_active_time = millis();
    delay(100);
  }

  else if (digitalRead(fourBtn) == 0){
    mode = 4;
    last_active_time = millis();
    delay(100);
  }

  else if (digitalRead(plusBtn) == 0){

    if (mode == 1){
      timeRhythm = timeRhythm + 0.1;
      if (timeRhythm > 9.9) timeRhythm = 9.9;
    }

    else if (mode == 2){
      timeRead = timeRead + 0.1;
      if (timeRead > 9.9) timeRead = 9.9;
    }

    else if (mode == 3){
      timeRush = timeRush + 0.1;
      if (timeRush > 9.9) timeRush = 9.9;
    }

    else if (mode == 4){
      timeRelease = timeRelease + 0.1;
      if (timeRelease > 9.9) timeRelease = 9.9;
    }

    for (int i = 0; i < 10; i++){
      if (digitalRead(minusBtn) == 0){
        delayed_start = !delayed_start;
        delay(500);
      }
      
      delay(8);
    }
    last_active_time = millis();

  }

  else if (digitalRead(minusBtn) == 0){

    if (mode == 1){
      timeRhythm = timeRhythm - 0.1;
      if (timeRhythm < 0.0) timeRhythm = 0.0;
    }

    else if (mode == 2){
      timeRead = timeRead - 0.1;
      if (timeRead < 0.0) timeRead = 0.0;
    }

    else if (mode == 3){
      timeRush = timeRush - 0.1;
      if (timeRush < 0.0) timeRush = 0.0;
    }

    else if (mode == 4){
      timeRelease = timeRelease - 0.1;
      if (timeRelease < 0.0) timeRelease = 0.0;
    }
    delay(100);
    last_active_time = millis();
    
  }

  else if (digitalRead(startBtn) == 0){
    mode = 0;
    last_active_time = millis();

    tempRhythm = timeRhythm;
    tempRead = timeRead;
    tempRush = timeRush;
    tempRelease = timeRelease;

    timerRun();

    timeRhythm = tempRhythm;
    timeRead = tempRead;
    timeRush = tempRush;
    timeRelease = tempRelease;

    
    delay(100);
  }
}
