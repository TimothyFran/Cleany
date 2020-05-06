/*
 * OPEN LIST:   LIST OF CELLS TO BE CONSIDERED
 * CLOSED LIST: LIST OF CELLS ALREADY CHECKED
 * 
 * adiacenti[][]
 *   X1  Y1
 *   X2  Y2
 *   X3  Y3
 *   X4  Y4
 */

 /*
  *     0)   AGGIUNGO START ALLA OPEN LIST
  *          1) CERCO IL F PIU' BASSO NELLA OPEN LIST
  *          2) AGGIUNGO GLI ADIACENTI ALLA OPEN LIST (SE OK)
  *          3) IMPOSTO ATTUALE COME GENITORE
  *          3) AGGIUNGO IL NODO ALLA CLOSED LIST
  *          4) RIMUOVO IL NODO DALLA CLOSED LIST
  *     1)   RIPERCORRO TUTTO ALLA ROVESCIA
  */

void navigation(byte goalX, byte goalY) {

  openID = 1;
  closedID = 1;
  static bool trovato = false;
  static int lowestFID;

  //AGGIUNGO START ALLA OPEN LIST
  writeOpenList(openID, posX, posY);
  openID = openID + 2;

  while(trovato==false) {

    //CERCO IL F PIU' BASSO NELLA OPEN LIST
    lowestFID = findLowestF(goalX, goalY);

    readOpenList(lowestFID);
    if(openX == goalX && openY == goalY) {trovato=true;}

    //AGGIUNGO GLI ADIACENTI ALLA OPEN LIST SE ADATTI
    trovaAdiacenti(lowestFID);
    for(byte i = 1; i<=4;i++) {
      if(checkCellForOpenList(adiacenti[i][1],adiacenti[i][2])==true) {
        writeOpenList(openID,adiacenti[i][1],adiacenti[i][2]);
        openID = openID + 2;
      }
    }   

    //AGGIUNGO ATTUALE COME GENITORE
    for(byte i = 1; i<=4;i++) {
      setAdiacente(adiacenti[i][1],adiacenti[i][2],i);
    }

    //AGGIUNGO ATTUALE ALLA CLOSED LIST
    writeClosedList(closedID,posX,posY);
    closedID = closedID + 2;

    //RIMUOVO ATTUALE DALLA OPEN LIST
    clearOpenList(openID);
    
  }

  //RIPERCORRERE TUTTI I GENITORI PER CREARE PERCORSO
  
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void trovaAdiacenti(int currentOpenID) {
  //FIND ADIACENT AND SET CURRENT CELL AS PARENT

  readOpenList(currentOpenID);
  
  adiacenti[2][1] = openX;
  adiacenti[2][2] = openY + 1; //SOPRA

  adiacenti[1][1] = openX;
  adiacenti[1][2] = openY - 1; //SOTTO

  adiacenti[4][1] = openX + 1; //DESTRA
  adiacenti[4][2] = openY;

  adiacenti[3][2] = openX - 1; //SINISTRA
  adiacenti[3][2] = openY;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int findLowestF(byte goalX, byte goalY) {

  int lowestFound = 1;
  int lowCost;

  readOpenList(1);
  lowCost = (abs(openX - goalX) + abs(openY - goalY));
  
  for(int i = 2; i<=openID;i++) {
    readOpenList(i);

    if(((abs(openX - goalX) + abs(openY - goalY)) < lowCost) && (openX + openY > 0)) {
      lowestFound = i;
      lowCost = (abs(openX - goalX) + abs(openY - goalY));
    }
    
  }

  return(lowestFound);
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool checkCellForOpenList(byte reqX, byte reqY) {

  if(readMap(reqX, reqY, 6)==false && readMap(reqX,reqY,7)==false && readMap(reqX,reqY,5)==false){

    //NOT IN THE CLOSED LIST
    //NOT IN THE OPEN LIST
    //NOT FULL

    return(true);
    
  }

  return(false);
  
}
