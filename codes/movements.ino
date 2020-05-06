//////VARIABILI///////
const int maxStepTime PROGMEM = 3000;
bool interblocco = false;

bool muoviAvanti (byte steps) {
  /*
   * Used to move forward
   * Returns 1 if successfull
   * Returns 0 if unsuccesfull (failed or interlock occurring)
   */
  shiftRegister(0, 1);
  shiftRegister(0, 2);
  digitalWrite(MDXma, HIGH);
  digitalWrite(MSXma, HIGH);
  static byte stepFatti = 0;
  interblocco = false;

  if(avantiInterbloccato() == true) {
    interblocco = true;
    return(0);
  }
  
  while(stepFatti < steps){
    
    if(avantiInterbloccato() == true) {
      interblocco = true;
      return(0);
    }
    
    unsigned long startTime = millis();
    
    while((digitalRead(MDXstp) == LOW && digitalRead(MSXstp) == LOW)) {
      
      if(digitalRead(MDXstp) == HIGH) {
        //PASSO DESTRA
        digitalWrite(MDXma, LOW);
      }

      if(digitalRead(MSXstp) == HIGH) {
        //PASSO SINISTRA
        digitalWrite(MSXma, LOW);
      }

      if (millis() - startTime < maxStepTime) {
        //MAX TIME EXCEEDED
        digitalWrite(MDXma, LOW);
        digitalWrite(MSXma, LOW);

        if(seriale==true){
          Serial.println(F("ERROR 001: max time exceeded in forward"));
        }
        
        return(0);
      }
    }
    
    digitalWrite(MDXma, HIGH);
    digitalWrite(MSXma, HIGH);

    startTime = millis();
    while((digitalRead(MDXstp) == HIGH || digitalRead(MSXstp) == HIGH)) {
      
      if(digitalRead(MDXstp) == LOW) {
        //PASSO DESTRA
        digitalWrite(MDXma, LOW);
      }

      if(digitalRead(MSXstp) == LOW) {
        //PASSO SINISTRA
        digitalWrite(MSXma, LOW);
      }

      if (millis() - startTime < maxStepTime) {
        //MAX TIME EXCEEDED
        digitalWrite(MDXma, LOW);
        digitalWrite(MSXma, LOW);

        if(seriale==true){
          Serial.println(F("ERROR 001: max time exceeded in forward"));
        }
        
        return(0);
      }
    }
    
    stepFatti++;
  }

  digitalWrite(MDXma, LOW);
  digitalWrite(MSXma, LOW);

  return(1);
}



bool muoviIndietro (byte steps) {
  /*
   * Used to move backward
   * Returns 1 when successfull
   * Returns 0 when unsuccesfull (failed or interlock occurred)
   */

  digitalWrite(MDXma, LOW);
  digitalWrite(MSXma, LOW);
  shiftRegister(1, 1);
  shiftRegister(1, 2);
  static byte stepFatti = 0;
  interblocco = false;

  if (indietroInterbloccato() == true) {
    interblocco = true;
    return(0);
  }

  while(stepFatti < steps){
    if(avantiInterbloccato() == true) {
      interblocco = true;
      return(0);
    }
    
    unsigned long startTime = millis();
    
    while((digitalRead(MDXstp) == LOW && digitalRead(MSXstp) == LOW)) {
      
      if(digitalRead(MDXstp) == HIGH) {
        //PASSO DESTRA
        shiftRegister(0, 1);
      }

      if(digitalRead(MSXstp) == HIGH) {
        //PASSO SINISTRA
        shiftRegister(0, 2);
      }

      if (millis() - startTime < maxStepTime) {
        //MAX TIME EXCEEDED
        shiftRegister(0, 2);
        shiftRegister(0, 1);

        if(seriale==true){
          Serial.println(F("ERROR 001: max time exceeded in backward"));
        }
        
        return(0);
      }
    }
    
    digitalWrite(MDXma, HIGH);
    digitalWrite(MSXma, HIGH);

    startTime = millis();
    while((digitalRead(MDXstp) == HIGH || digitalRead(MSXstp) == HIGH)) {
      
      if(digitalRead(MDXstp) == LOW) {
        //PASSO DESTRA
        digitalWrite(MDXma, LOW);
      }

      if(digitalRead(MSXstp) == LOW) {
        //PASSO SINISTRA
        digitalWrite(MSXma, LOW);
      }

      if (millis() - startTime < maxStepTime) {
        //MAX TIME EXCEEDED
        shiftRegister(0, 2);
        shiftRegister(0, 1);

        if(seriale==true){
          Serial.println(F("ERROR 001: max time exceeded in backward"));
        }
        
        return(0);
      }
    }
    
    stepFatti++;
  }

  digitalWrite(MDXma, LOW);
  digitalWrite(MSXma, LOW);

  return(1);
}



bool ruotaDestra() {
  return(true);
}



bool ruotaSinistra() {
  return(true);
}



bool ruota180(){
  if(ruotaDestra()==0) {return(0);}
  if(ruotaDestra()==0) {return(0);}
  return(1);
}



bool avantiInterbloccato() {
  //return 0 when no interlocks
  return(0);
}


bool indietroInterbloccato() {
  //return 0 when no interlocks
  return(0);
}
