


void updateDisplay(){
  clearLCD();
  cursorSet(0,1);
  Serial1.print("Set:");
  Serial1.print(setpoint, 1);
  Serial1.write(0);
  cursorSet(12,1);
  if (elementPowerLevelPercent > 0){
    Serial1.print("H:");
    Serial1.print(elementPowerLevelPercent);
  }
  else {
    Serial1.print("      ");
  }
  cursorSet(0,2);
  Serial1.print("1:");
  Serial1.print(T1Temp, 1);
  Serial1.write(0);
  cursorSet(9,2);
  Serial1.print("2:");
  Serial1.print(T2Temp, 1);
  Serial1.write(0);
}

void serialEvent1() {
  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read(); 
    // add it to the keypadInputString:
    keypadInputString += inChar;
    //turn keypadInputString into setpoint once 3 chars come in
    if (keypadInputString.length() > 2) {
      setpoint = keypadInputString.toInt();
      clearLCD();
      updateDisplay();
      keypadInputString = "";
    } 
  }
}



//------------------------------------------
//  LCD  FUNCTIONS-- keep the ones you need. 

// clear the LCD
void clearLCD(){
  Serial1.write(12);
}

// start a new line
void newLine() { 
  Serial1.write(10); 
}

// move the cursor to the home position
void cursorHome(){
  Serial1.write(254);
  Serial1.write(72);
}

// move the cursor to a specific place
// e.g.: cursorSet(3,2) sets the cursor to x = 3 and y = 2
void cursorSet(int xpos, int ypos){  
  Serial1.write(254);
  Serial1.write(71);               
  Serial1.write(xpos);   //Column position   
  Serial1.write(ypos); //Row position 
} 

// backspace and erase previous character
void backSpace() { 
  Serial1.write(8); 
}

// move cursor left
void cursorLeft(){    
  Serial1.write(254); 
  Serial1.write(76);   
}

// move cursor right
void cursorRight(){
  Serial1.write(254); 
  Serial1.write(77);   
}

// set LCD contrast
void setContrast(int contrast){
  Serial1.write(254); 
  Serial1.write(80);   
  Serial1.write(contrast);   
}


// turn on backlight
void backlightOn(int minutes){
  Serial1.write(254); 
  Serial1.write(66);   
  Serial1.write(minutes); // use 0 minutes to turn the backlight on indefinitely   
}

// turn off backlight
void backlightOff(){
  Serial1.write(254); 
  Serial1.write(70);   
}

void LCDSetup(){
  //       Turn OFF AUTO line wrap
  Serial1.write(254); 
  Serial1.write(68); 
  delay(200);

  //       Turn OFF the block cursor    
  //       Note that setting both block and underline 
  //       cursors may give unpredictable results. 
  Serial1.write(254);
  Serial1.write(84);   
  delay(200);  

  //Enable Keypad Mode / Already default
  //Serial1.write(254);
  //  Serial1.write(37);
  //  Serial1.write(0);


  //Turn off auto transmit keypress
  //Serial1.write(254);
  //Serial1.write(79);

  //Turn on auto transmit keypress
  Serial1.write(254);
  Serial1.write(65);

  //       Turn ON the block cursor
  //         Serial1.write(254);
  //         Serial1.write(83);  

  //       Turn ON the underline cursor
  //         Serial1.write(254);
  //         Serial1.write(74);               

  //       Turn OFF the underline cursor
  //         Serial1.write(254);
  //         Serial1.write(75);               

  // Custom Character for ° symbol
  Serial1.write(254);
  Serial1.write(78);   
  Serial1.write(0); 
  Serial1.write(8); 
  Serial1.write(20); 
  Serial1.write(20); 
  Serial1.write(8); 
  Serial1.write(0); 
  Serial1.write(0);  
  Serial1.write(0); 
  Serial1.write(0);
  delay(200);

  // Update keypad keys
  Serial1.write(254);
  Serial1.write(213);
  Serial1.write(48);
  Serial1.write(57);
  Serial1.write(54);
  Serial1.write(51);
  Serial1.write(56);
  Serial1.write(53);
  Serial1.write(53);
  Serial1.write(50);
  Serial1.write(55);
  Serial1.write(57);
  Serial1.write(52);
  Serial1.write(49);
  Serial1.write(48);
  Serial1.write(57);
  Serial1.write(54);
  Serial1.write(51);
  Serial1.write(56);
  Serial1.write(53);
  Serial1.write(53);
  Serial1.write(50);
  Serial1.write(55);
  Serial1.write(57);
  Serial1.write(52);
  Serial1.write(49);

  clearLCD();
  Serial1.print("Booting"); 
}
