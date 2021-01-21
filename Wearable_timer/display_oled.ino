
bool flash_text = 0;

///rhythm, read, rush, release 
void display_time(){

  display.clearDisplay();
  int digit1;
  int digit2;

  display.setTextSize(2);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text

  if (mode == 1){
    if (flash_text == 0){
      display.setCursor(5, 0);
      display.println("   ");
      flash_text = 1;
      display.setCursor(5, 16);
      display.println(" R2");
      display.setCursor(5, 32);
      display.println(" R3");
      display.setCursor(5, 48);
      display.println(" R4");
    }
    else {
      display_all_headings();
      flash_text = 0;
    }
  }

  else if (mode == 2){
    
    if (flash_text == 0){
      display.setCursor(5, 16);
      display.println("   ");
      flash_text = 1;
      display.setCursor(5, 0);
      display.println(" R1");
      display.setCursor(5, 32);
      display.println(" R3");
      display.setCursor(5, 48);
      display.println(" R4");
    }
    else {
      display_all_headings();
      flash_text = 0;
    }
  }

  else if (mode == 3){
    if (flash_text == 0){
      display.setCursor(5, 32);
      display.println("   ");
      flash_text = 1;
      display.setCursor(5, 0);
      display.println(" R1");
      display.setCursor(5, 16);
      display.println(" R2");
      display.setCursor(5, 48);
      display.println(" R4");
    }
    else {
      display_all_headings();
      flash_text = 0;
    }
  }

  else if (mode == 4){
    if (flash_text == 0){
      display.setCursor(5, 48);
      display.println("   ");
      flash_text = 1;
      display.setCursor(5, 0);
      display.println(" R1");
      display.setCursor(5, 16);
      display.println(" R2");
      display.setCursor(5, 32);
      display.println(" R3");
      
    }
    else {
      display_all_headings();
      flash_text = 0;
    }
  }

  else {
    display_all_headings();
  }

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);

  digit1 = int(timeRhythm);
  digit2 = int(timeRhythm*10)%10;

  display.setCursor(50, 0);
  display.println("- ");  
  display.setCursor(68, 0);
  display.println(digit1);
  display.setCursor(78, 0);
  display.println(".");
  display.setCursor(90, 0);
  display.println(digit2);

  digit1 = int(timeRead);
  digit2 = int(timeRead*10)%10;

  display.setCursor(50, 16);
  display.println("- ");  
  display.setCursor(68, 16);
  display.println(digit1);
  display.setCursor(78, 16);
  display.println(".");
  display.setCursor(90, 16);
  display.println(digit2);

  digit1 = int(timeRush);
  digit2 = int(timeRush*10)%10;

  display.setCursor(50, 32);
  display.println("- ");  
  display.setCursor(68, 32);
  display.println(digit1);
  display.setCursor(78, 32);
  display.println(".");
  display.setCursor(90, 32);
  display.println(digit2);
  
  digit1 = int(timeRelease);
  digit2 = int(timeRelease*10)%10;

  display.setCursor(50, 48);
  display.println("- ");  
  display.setCursor(68, 48);
  display.println(digit1);
  display.setCursor(78, 48);
  display.println(".");
  display.setCursor(90, 48);
  display.println(digit2);


  //delayed start display-------------------------------------------------
  display.setCursor(115, 48);
  
  if (delayed_start == 1){
    //display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.println("D");
  }

  else{
    display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
    display.println(" ");
  }

  //display battery level
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  if (bat_level>4.0){
    display.setCursor(120, 5);
    display.println("-");
    display.setCursor(120, 10);
    display.println("-");
    display.setCursor(120, 15);
    display.println("-");
    display.setCursor(120, 20);
    display.println("-");
  }

  else if (bat_level > 3.8){
    
    display.setCursor(120, 10);
    display.println("-");
    display.setCursor(120, 15);
    display.println("-");
    display.setCursor(120, 20);
    display.println("-");
  }

  else if (bat_level > 3.7){
    
    display.setCursor(120, 15);
    display.println("-");
    display.setCursor(120, 20);
    display.println("-");
  }

  else {
    
    display.setCursor(120, 20);
    display.println("-");
  }
  display.setCursor(120, 28);
    display.println("B");

  display.setCursor(100, 35);
    display.println(bat_level);
  display.display();
}

void display_all_headings(){
    display.setCursor(5, 0);
    display.println(" R1");
    display.setCursor(5, 16);
    display.println(" R2");
    display.setCursor(5, 32);
    display.println(" R3");
    display.setCursor(5, 48);
    display.println(" R4");
}
