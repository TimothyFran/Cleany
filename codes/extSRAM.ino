  /*THE ADDRESS IN WICH TO STORE THE BYTE OF EACH CELL ARE DETERMINED BY THE
   *  X AND Y VALUES OF THE CELL CONCANTENATED IN BINARY FORMAT.
   *  THERE IS NO RISK OF RIDUNDANCY
   *  
   *  THE BYTE VALUE IS AS FOLLOWING:
   *  
   *  BIT0:   bitCode 1    1 = from up     0 = nothing (during path planning)
   *  BIT1:   bitCode 2    1 = from down   0 = nothing (during path planning)
   *  BIT2:   bitCode 3    1 = from right  0 = nothing (during path planning)
   *  BIT3:   bitCode 4    1 = from left   0 = nothing (during path planning)
   *  BIT4:   bitCode 5    1 = full        0 = free
   *  BIT5:   bitCode 6    1 = close list  0 = nothing (during path planning)
   *  BIT6:   bitCode 7    1 = open list   0 = nothing (during path planning)
   *  BIT7:   bitCode 8    1 = clean       0 = dirty
   *  
   *  
   *  SRAM1
   *  The following values are for a map of 100x100 cells
   *          MAPPA
   *                       0000000000000000         0
   *                       0010011100010000         10000
   *                       
   *          OPEN LIST
   *                       0010011100010001         10001
   *                       0111110100000000         32000
   *                       
   *          VUOTO
   *                       0111110100000001         32001
   *                       0111111111111111         32767
   *   SRAM2
   *          CLOSED LIST
   *                       0000000000000001         1
   *                       0110000110101000         25000
   *                       
   *          VUOTO
   *                       0110000110101001         25001
   *                       0111111111111111         32767
   *  
   */

bool readMap(byte X,byte Y, byte bitCode) {

  return(bitRead(ram1.readByte(cellToAddress(X,Y)),bitCode));
  
}

///////////////////////////////////////////////////////////////////////////////

void setAdiacente(byte X, byte Y, byte direzione) {

  byte static lettura;
  lettura = ram1.readByte(cellToAddress(X,Y));

  bitWrite(lettura, direzione, 1);
  ram1.writeByte(cellToAddress(X,Y), lettura);
  
}

///////////////////////////////////////////////////////////////////////////////

void writeMap(byte X, byte Y, byte bitCode, bool valore) {

  static byte settaggio;
  
  settaggio = ram1.readByte(cellToAddress(X,Y));

  bitWrite(settaggio, bitCode, valore);

  ram1.writeByte(cellToAddress(X,Y), settaggio);
  
}

///////////////////////////////////////////////////////////////////////////////

int cellToAddress(byte X, byte Y) {

  /*
   * Each cell has an address on the sram1 external sram.
   * The addresses are assigned in order:
   *     1        1    2    3    4    5    ....... 99    100
   *     2       101  102  103  104  105   ....... 199   200
   *     3       201  202  203  204  205   ....... 299   300
   *             ...........................................
   *     99      9801 9802 9803 9804 9805  ....... 8999 9900
   *     100     9901 9902 9903 9904 9905  ....... 9999 10000
   */

  static int indirizzo;
  
  indirizzo = (Y-1) * maxX;
  
  return(indirizzo + X);
  
}

///////////////////////////////////////////////////////////////////////////////

int getIndirizzo(byte X, byte Y) {
  bool tempAddress[16];
  for(int i = 7;i>=0;i--) {
    tempAddress[i+9] = bitRead(X, i);
  }
  for(int i = 7;i>=0;i--) {
    tempAddress[i+1] = bitRead(Y, i);
  }
  int indirizzo;
  for(int i = 15; i >= 0; i--) {
    indirizzo = indirizzo | tempAddress[i+1] << i;
  }
  return(indirizzo);
}

///////////////////////////////////////////////////////////////////////////////

byte openX;
byte openY;

void readOpenList(int item) {

  //OPEN LIST starts from address 10001 of the sram1. So the openID must be added to 10000 when used as address.
  
  openX = ram1.readByte(item+10000);
  openY = ram1.readByte(item+10001);
  
}

///////////////////////////////////////////////////////////////////////////////

void writeOpenList(int ID, byte X, byte Y) {

  /*
   * X e Y sono scritti in serie a partire dall'indirizzo 10000, quindi:
   * 
   * ID = 1 :
   *        X = ADD(10001) (1 + 10000)
   *        Y = ADD(10002) (2 + 10000)
   *        
   * ID = 2 :
   *        X = ADD(10003) (3 + 10000)
   *        Y = ADD(10004) (4 + 10000)
   *        
   * ID = 100 :
   *        X = ADD(10199) (199 + 10000)
   *        Y = ADD(10200) (200 + 10000)
   * 
   */

  ram1.writeByte(((ID*2)-1) + 10000 , X);
  ram1.writeByte((ID*2)     + 10000 , Y);
  
}

///////////////////////////////////////////////////////////////////////////////

void clearOpenList(int ID) {
  writeOpenList(ID, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////

void writeClosedList(int ID, byte X, byte Y) {
  
  /*
   * X e Y sono scritti in serie a partire dall'indirizzo 1, quindi:
   * 
   * ID = 1 :
   *        X = ADD(1)
   *        Y = ADD(2)
   *        
   * ID = 2 :
   *        X = ADD(3)
   *        Y = ADD(4)
   *        
   * ID = 100 :
   *        X = ADD(199)
   *        Y = ADD(200)
   * 
   */

  ram2.writeByte((ID*2), Y);
  ram2.writeByte((ID*2) - 1, X);
   
}


///////////////////////////////////////////////////////////////////////////////

byte closedX;
byte closedY;

void readClosedList(int ID) {

  closedX = ram2.readByte((ID*2)-1);
  closedY = ram2.readByte((ID*2));
  
}
