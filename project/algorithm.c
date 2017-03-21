short board[8][8];
short blackCounter = 0, redCounter = 0;

void newGame(); 
bool checkWinner();
void checkKing(bool blacksTurn);
bool canCapture(bool blacksTurn);
bool doubleCapture(bool blacksTurn, short row, short col);
bool legalMove(bool blacksTurn, short currentRow, short currentCol, short toRow, short toCol);
bool legalMove2(bool blacksTurn, short currentRow, short currentCol, short toRow, short toCol);
void updateBoard(bool blacksTurn, short currentRow,short currentCol, short toRow, short toCol,short jumpRow, short jumpCol);
void anotherCapture(bool &blacksTurn, short currentRow, short currentCol);
void makeMove(bool blacksTurn);
void getPos(short lineNum, short& row, short& col);


void newGame(){
  //I is row, J is col

  for (short i = 0; i < 8;i++){
      for (short j = 0; j < 8; j++){
        //Setting default pieces

        // //Black pieces 1
        if (i < 3){
          if (i%2 == 0){
            if (j%2 == 0){
              board[i][j] = 1;
            }
          }
          else if (i%2 == 1){
            if (j%2 == 1){
              board[i][j] = 1;
            }
          }
        }
        else if (i > 4){
          if (i%2 == 0){
            if (j%2 == 0){
              board[i][j] = 2;
            }
          }
          else if (i%2 == 1){
            if (j%2 == 1){
              board[i][j] = 2;
            }
          }
        }
      }
    }

}


void getPos(short lineNum, short& row, short& col) {
  char cols[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  row = 3, col = 3;

  // select row
  while (nNxtButtonPressed != 3) {
    displayString(lineNum, "SELECT ROW: %d", row + 1);
    while (nNxtButtonPressed == -1) {}
    if (nNxtButtonPressed == 1 && row < 7) {  // increase, 1 is right arrow
      ++row;
    }
    else if (nNxtButtonPressed == 2 && row > 0) { // decrease, 2 is left arrow
      --row;
    }
    wait1Msec(200);
  }

  // select column
  while (nNxtButtonPressed != 3) {
    displayString(lineNum + 1, "SELECT COLUMN: %c", cols[col]);
    while (nNxtButtonPressed == -1) {}
    if (nNxtButtonPressed == 1 && col < 7) {
      ++col;
    }
    else if (nNxtButtonPressed == 2 && col > 0) {
      --col;
    }
    wait1Msec(200);
  }
}


void makeMove(bool blacksTurn) {
	short currentRow = -1, currentCol = -1, toRow = -1, toCol = -1;
	
	while (true) {
		displayString(0, "MOVE THIS PIECE");
		getPos(currentRow, currentCol);
		displayString(0, "TO WHERE?");
		getPos(toRow, toCol);
		if (!legalMove(blacksTurn, currentRow, currentCol, toRow, toCol)) {
			eraseDisplay();
			displayString(2, "ILLEGAL MOVE");
			wait1Msec(1000);
		}
		else {
			break;
		}
	}
}

bool checkWinner(){
  if(redCounter == 12 || blackCounter == 12){
    return true;
  }
  else{
  return false;
  }
}
//Turns a checker piece shorto a king
void checkKing(bool blacksTurn){
  if(blacksTurn){
    for(short j = 1; j<8; j += 2){
      if(board[7][j] == 1){
        board[7][j] = 3;
      }
    }
  }
  else{
    for(short j = 0; j<8; j += 2){
      if(board[0][j] == 2){
        board[0][j] = 4;
      }
    }
  }
}

bool canCapture(bool blacksTurn){
  for (short i = 0; i < 8; i++){ //iterating through rows
    for (short j = 0; j < 8; j++){ //iterating through columns

      if (blacksTurn){
        //Black Piece Cases
        if ( (board[i][j] == 1 || board[i][j] == 3) && j < 6 && i < 6 && ((board[i+1][j+1] == 2 || board[i+1][j+1] == 4) && (board[i+2][j+2] == 0))){
          return true;
        }
        else if ( (board[i][j] == 1 || board[i][j] == 3) && j > 1 && i < 6 && ((board[i+1][j-1] == 2 || board[i+1][j-1] == 4) && (board[i-2][j-2] == 0))){
          return true;
        }

        //Extra King Checks
        else if (board[i][j] == 3 && j < 6 && i > 1 && ( ((board[i-1][j+1] == 2) || (board[i-1][j+1] == 4)) && (board[i-2][j+2] == 0))){
          return true;
        }
        else if  (board[i][j] == 3 && j > 1 && i > 1 && ( ((board[i-1][j-1] == 2 || board[i-1][j-1] == 4 )) && (board[i-2][j-2] == 0))){
          return true;
        }
      }
      else{
        //Red Piece Cases
        if ((board[i][j] == 2 || board[i][j] == 4) && j < 6 && i > 1 && ((board[i-1][j+1] == 1 || board[i-1][j+1] == 3) && (board[i-2][j+2] == 0))){
          return true;
        }
        else if  ((board[i][j] == 2 || board[i][j] == 4) && j > 1 && i > 1 && ((board[i-1][j-1] == 1 || board[i-1][j-1] == 3) && (board[i-2][j-2] == 0))){
          return true;
        }
        //Extra King Checks
        else if (board[i][j] == 4 && j < 6 && i < 6 && ( ((board[i+1][j+1] == 1 || board[i+1][j+1] == 3)) && (board[i+2][j+2] == 0))){
          return true;
        }
        else if  (board[i][j] == 4 && j > 1 && i < 6 && (((board[i+1][j-1] == 1 || board[i+1][j-1] == 3)) && (board[i+2][j-2] == 0))){
          return true;
        }
      }
    }
  }
  return false;
}

bool doubleCapture(bool blacksTurn, short row, short col){
  if (blacksTurn){
    //Black Piece Cases
    if ( (board[row][col] == 1 || board[row][col] == 3) && col < 6 && row < 6 &&  ((board[row+1][col+1] == 2 || board[row+1][col+1] == 4) && (board[row+2][col+2] == 0))){
      return true;
    }
    else if ( (board[row][col] == 1 || board[row][col] == 3) && col > 1 && row < 6 &&  ((board[row+1][col-1] == 2 || board[row+1][col-1] == 4) && (board[row+2][col-2] == 0))){
      return true;
    }

    //Extra King Checks
    else if (board[row][col] == 3 && col < 6 && row > 1 && ( ((board[row-1][col+1] == 2) || (board[row-1][col+1] == 4)) && (board[row-2][col+2] == 0))){
      return true;
    }
    else if  (board[row][col] == 3 && col > 1 && row > 1 && ( ((board[row-1][col-1] == 2 || board[row-1][col-1] == 4 )) && (board[row-2][col-2] == 0))){
      return true;
    }
  }
  else{
    //Red Piece Cases
    if ((board[row][col] == 2 || board[row][col] == 4) && col < 6 && row > 1 && ((board[row-1][col+1] == 1 || board[row-1][col+1] == 3) && (board[row-2][col+2] == 0))){
      return true;
    }
    else if  ((board[row][col] == 2 || board[row][col] == 4) && col > 1 && row > 1 && ((board[row-1][col-1] == 1 || board[row-1][col-1] == 3) && (board[row-2][col-2] == 0))){
      return true;
    }
    //Extra King Checks
    else if (board[row][col] == 4 && col < 6 && row < 6 &&  ( ((board[row+1][col+1] == 1 || board[row+1][col+1] == 3)) && (board[row+2][col+2] == 0))){
      return true;
    }
    else if  (board[row][col] == 4 && col > 1 && row < 6 &&  (((board[row+1][col-1] == 1 || board[row+1][col-1] == 3)) && (board[row+2][col-2] == 0))){
      return true;
    }
  }
  return false;
}

void updateBoard(bool blacksTurn, short currentRow,short currentCol, short toRow, short toCol,short jumpRow, short jumpCol){
  board[toRow][toCol] = board[currentRow][currentCol];
  board[currentRow][currentCol] = 0;
  checkKing(blacksTurn);
  if (jumpRow != -1){
    board[jumpRow][jumpCol] = 0;
    //run move function
    //run remove captured piece function
    if(blacksTurn){
      redCounter += 1;
    }
    else{
      blackCounter +=1;
    }
    if(doubleCapture(blacksTurn, toRow, toCol)){
      displayBoard();
      anotherCapture(blacksTurn, toRow, toCol);
    }
  }
  else{
    //run diagonal moving function
  }
}


//Checks if a move is legal, returns a boolean, called by the makeMove
bool legalMove(bool blacksTurn, short currentRow, short currentCol, short toRow, short toCol){
  //Legal move conditions, 1 diagonal, jump over piece, jump over multiple pieces - will be hard to implement

  short jumpRow = -1, jumpCol = -1;
  bool legal = false;
  //Check if a piece moves single piece diagonally

  //cout << endl << currentRow << currentCol << toRow << toCol << endl;

  //Black moves
  if (blacksTurn){
    if (( (toRow - currentRow) == 1) && (abs(toCol - currentCol) == 1) && (board[currentRow][currentCol] == 1) && (board[toRow][toCol] == 0) ){
      legal = true;
    }
    else if ( (abs(toRow - currentRow) == 1) && (abs(toCol - currentCol) == 1) && (board[currentRow][currentCol] == 3) && (board[toRow][toCol] == 0) ){
      legal = true;
    }
    //Jumps
    else if ( (toRow - currentRow == 2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 1) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 2 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 4)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
    else if( (abs(toRow - currentRow) == 2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 3) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 2 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 4)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
  }

  //Red moves
  else{
    if (( (toRow - currentRow) == -1) && (abs(toCol - currentCol) == 1) && (board[currentRow][currentCol] == 2) && (board[toRow][toCol] == 0) ){
      legal = true;
    }
    else if ( (abs(toRow - currentRow) == 1) && (abs(toCol - currentCol) == 1) && (board[currentRow][currentCol] == 4) && (board[toRow][toCol] == 0) ){
      legal = true;
    }
    //Jumps
    else if ( (toRow - currentRow == -2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 2) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 1 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 3)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
    else if( (abs(toRow - currentRow) == 2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 4) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 1 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 3)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
  }

  if (legal){
    updateBoard(blacksTurn, currentRow,currentCol,toRow,toCol,jumpRow,jumpCol);
  }
  return legal;
}

bool legalMove2(bool blacksTurn, short currentRow, short currentCol, short toRow, short toCol){
//Legal move conditions for second capture, jumps only

  short jumpRow = -1, jumpCol = -1;
  bool legal = false;

  cout << endl << currentRow << currentCol << toRow << toCol << endl;

  //Black moves
  if (blacksTurn){
    //Jumps
    if ( (toRow - currentRow == 2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 1) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 2 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 4)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
    else if( (abs(toRow - currentRow) == 2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 3) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 2 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 4)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
  }

  //Red moves
  else{
    //Jumps
    if ( (toRow - currentRow == -2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 2) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 1 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 3)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
    else if( (abs(toRow - currentRow) == 2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 4) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 1 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 3)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
  }

  if (legal){
    updateBoard(blacksTurn, currentRow,currentCol,toRow,toCol,jumpRow,jumpCol);
  }
  return legal;
}

void anotherCapture(bool blacksTurn, short currentRow, short currentCol){
  short toRow = -1, toCol = -1;
  displayString(0, "TO WHERE?");
  getPos(toRow, toCol);
  if (!legalMove(blacksTurn, currentRow, currentCol, toRow, toCol)) {
    eraseDisplay();
    displayString(2, "ILLEGAL MOVE");
    wait1Msec(1000);
  }
  else {
    break;
  }
}

task main() {
}
