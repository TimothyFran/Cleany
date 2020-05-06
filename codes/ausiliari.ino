/////RUOTA DESTRA////
const byte MDXma  PROGMEM  = 12; //ruota destra marcia avanti
const byte MDXstp PROGMEM  = 2;  //ruota destra step
//         MDXmi  PROGMEM  = SR; //ruota destra marcia indietro (shift register pos1)


////RUOTA SINISTRA////
const byte MSXma  PROGMEM  = 13; //ruota sinistra marcia avanti
const byte MSXstp PROGMEM  = 23; //ruota sinistra step
//         MSXmi  PROGMEM  = SR; //ruota sinistra marcia indietro (shift register pos2)


////SHIFT REGISTER/////
const bool SRin   PROGMEM  = 0;  //shift register data input
const bool SRclk  PROGMEM  = 1;  //shift register clock


////SRAM ESTERNA//////
const byte SRAMIn  PROGMEM = 3;
const byte SRAMOut PROGMEM = 14;
const byte SRAMSck PROGMEM = 18;
const byte SRAMCs  PROGMEM = 27; //A3
const byte SRAMCs2 PROGMEM = 30; //A6
SRAM ram1(SRAMCs);
SRAM ram2(SRAMCs2);

void pinModes() {
  pinMode(MDXma,  OUTPUT);
  pinMode(MSXma,  OUTPUT);
  pinMode(MDXstp, INPUT);
  pinMode(MSXstp, INPUT);
  pinMode(SRin,   OUTPUT);
  pinMode(SRclk,  OUTPUT);
  pinMode(SRAMIn, OUTPUT);
  pinMode(SRAMOut,INPUT);
  pinMode(SRAMSck,OUTPUT);
}

void initializions() {
  ram1.begin();
  ram2.begin();
  Serial.begin(9600);
}

static bool sspos[8];

void shiftReset() {
  for (byte i = 1; i<=8;i++){
    shiftRegister(0,i);
  }
}

void shiftRegister(bool valore, byte posizione) {
  //AGGIORNAMENTO VARIABILI
  sspos[posizione] = valore;
  PORTB &= 0b11111101;      //digitalWrite(SRclk, LOW);
  
  //AGGIORNAMENTO SHIFT REGISTER
  for (int i=1; i<=8; i++) {
    if(sspos[i]==0){
      PORTB &= 0b00000000;  //digitalWrite(SRin, LOW);
    } else {
      PORTB |= 0b00000001;  //digitalWrite(SRin, HIGH);
    }
    PORTB |= 0b00000010;    //digitalWrite(SRclk, HIGH);
    delay(1);
    PORTB &= 0b11111101;    //digitalWrite(SRclk, LOW);
  }
  
  PORTB &= 0b11111101;      //digitalWrite(SRclk, LOW);
}
