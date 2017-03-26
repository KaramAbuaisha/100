int board [8][8];
int blackCounter = 0, redCounter = 0;


void newGame();
bool checkWinner();
void checkKing(bool blacksTurn);
bool canCapture(bool blacksTurn);
bool doubleCapture(bool blacksTurn, int row, int col);
bool legalMove(bool blacksTurn, int currentRow, int currentCol, int toRow, int toCol);
bool legalMove2(bool blacksTurn, int currentRow, int currentCol, int toRow, int toCol);
void updateBoard(bool blacksTurn, int currentRow,int currentCol, int toRow, int toCol,int jumpRow, int jumpCol);
void anotherCapture(bool blacksTurn, int currentRow, int currentCol);
void makeMove(bool blacksTurn);
void getPos(int lineNum, int &row, int &col);


void newGame(){
	//I is row, J is col

	for (int i = 0; i < 8;i++){
		for (int j = 0; j < 8; j++){
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

void getPos(int lineNum, int &row, int &col) {
	char cols[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	row = 3; col = 3;

	// select row
	while (nNxtButtonPressed != 3) {
		displayString(lineNum, "SELECT ROW: %d", row + 1);
		while (nNxtButtonPressed == -1) {}
		if (nNxtButtonPressed == 1 && row < 7) {  // increase, 1 is right arrow
			++(row);
		}
		else if (nNxtButtonPressed == 2 && row > 0) { // decrease, 2 is left arrow
			--(row);
		}
		wait1Msec(200);
	}

	// select column
	while (nNxtButtonPressed != 3) {
		displayString(lineNum + 1, "SELECT COLUMN: %c", cols[col]);
		while (nNxtButtonPressed == -1) {}
		if (nNxtButtonPressed == 1 && col < 7) {
			++(col);
		}
		else if (nNxtButtonPressed == 2 && col > 0) {
			--(col);
		}
		wait1Msec(100);
	}
}


void makeMove(bool blacksTurn) {
	int currentRow = -1, currentCol = -1, toRow = -1, toCol = -1;

	while (true) {
		if(canCapture(blacksTurn)){
			displayString(7, "CAN CAPTURE");
		}
		displayString(0, "MOVE THIS PIECE");
		getPos(1, currentRow, currentCol);
		displayString(2, "TO WHERE?");
		getPos(3, toRow, toCol);
		if (!legalMove(blacksTurn, currentRow, currentCol, toRow, toCol)) {
			displayString(5, "ILLEGAL MOVE");
			wait1Msec(1000);
			eraseDisplay();
		}
		else {
			break;
		}
	}
	getInPosition(-1, -1, currentRow, currentCol);
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
		for(int j = 1; j<8; j += 2){
			if(board[7][j] == 1){
				board[7][j] = 3;
			}
		}
	}
	else{
		for(int j = 0; j<8; j += 2){
			if(board[0][j] == 2){
				board[0][j] = 4;
			}
		}
	}
}

bool canCapture(bool blacksTurn){
  for (int i = 0; i < 8; i++){ //iterating through rows
    for (int j = 0; j < 8; j++){ //iterating through columns

      if (blacksTurn){
        //Black Piece Cases
        if ( (board[i][j] == 1 || board[i][j] == 3) && j < 6 && i < 6 && ((board[(int) (i+1)][(int) (j+1)] == 2 || board[(int) (i+1)][(int) (j+1)] == 4) && (board[(int) (i+2)][(int) (j+2)] == 0))){
          return true;
        }
        else if ( (board[i][j] == 1 || board[i][j] == 3) && j > 1 && i < 6 && ((board[(int) (i+1)][(int) (j-1)] == 2 || board[(int) (i+1)][(int) (j-1)] == 4) && (board[(int) (i-2)][(int) (j-2)] == 0))){
          return true;
        }

        //Extra King Checks
        else if (board[i][j] == 3 && j < 6 && i > 1 && ( ((board[(int) (i-1)][(int) (j+1)] == 2) || (board[(int) (i-1)][(int) (j+1)] == 4)) && (board[(int) (i-2)][(int) (j+2)] == 0))){
          return true;
        }
        else if  (board[i][j] == 3 && j > 1 && i > 1 && ( ((board[(int) (i-1)][(int) (j-1)] == 2 || board[(int) (i-1)][(int) (j-1)] == 4 )) && (board[(int) (i-2)][(int) (j-2)] == 0))){
          return true;
        }
      }
      else{
        //Red Piece Cases
        if ((board[i][j] == 2 || board[i][j] == 4) && j < 6 && i > 1 && ((board[(int) (i-1)][(int) (j+1)] == 1 || board[(int) (i-1)][(int) (j+1)] == 3) && (board[(int) (i-2)][(int) (j+2)] == 0))){
          return true;
        }
        else if  ((board[i][j] == 2 || board[i][j] == 4) && j > 1 && i > 1 && ((board[(int) (i-1)][(int) (j-1)] == 1 || board[(int) (i-1)][(int) (j-1)] == 3) && (board[(int) (i-2)][(int) (j-2)] == 0))){
          return true;
        }
        //Extra King Checks
        else if (board[i][j] == 4 && j < 6 && i < 6 && ( ((board[(int) (i+1)][(int) (j+1)] == 1 || board[(int) (i+1)][(int) (j+1)] == 3)) && (board[(int) (i+2)][(int) (j+2)] == 0))){
          return true;
        }
        else if  (board[i][j] == 4 && j > 1 && i < 6 && (((board[(int) (i+1)][(int) (j-1)] == 1 || board[(int) (i+1)][(int) (j-1)] == 3)) && (board[(int) (i+2)][(int) (j-2)] == 0))){
          return true;
        }
      }
    }
  }
  return false;
}

bool doubleCapture(bool blacksTurn, int row, int col){
  if (blacksTurn){
    //Black Piece Cases
    if ( (board[row][col] == 1 || board[row][col] == 3) && col < 6 && row < 6 &&  ((board[(int) (row+1)][(int) (col+1)] == 2 || board[(int) (row+1)][(int) (col+1)] == 4) && (board[(int) (row+2)][(int) (col+2)] == 0))){
      return true;
    }
    else if ( (board[row][col] == 1 || board[row][col] == 3) && col > 1 && row < 6 &&  ((board[(int) (row+1)][(int) (col-1)] == 2 || board[(int) (row+1)][(int) (col-1)] == 4) && (board[(int) (row+2)][(int) (col-2)] == 0))){
      return true;
    }

    //Extra King Checks
    else if (board[row][col] == 3 && col < 6 && row > 1 && ( ((board[(int) (row-1)][(int) (col+1)] == 2) || (board[(int) (row-1)][(int) (col+1)] == 4)) && (board[(int) (row-2)][(int) (col+2)] == 0))){
      return true;
    }
    else if  (board[row][col] == 3 && col > 1 && row > 1 && ( ((board[(int) (row-1)][(int) (col-1)] == 2 || board[(int) (row-1)][(int) (col-1)] == 4 )) && (board[(int) (row-2)][(int) (col-2)] == 0))){
      return true;
    }
  }
  else{
    //Red Piece Cases
    if ((board[row][col] == 2 || board[row][col] == 4) && col < 6 && row > 1 && ((board[(int) (row-1)][(int) (col+1)] == 1 || board[(int) (row-1)][(int) (col+1)] == 3) && (board[(int) (row-2)][(int) (col+2)] == 0))){
      return true;
    }
    else if  ((board[row][col] == 2 || board[row][col] == 4) && col > 1 && row > 1 && ((board[(int) (row-1)][(int) (col-1)] == 1 || board[(int) (row-1)][(int) (col-1)] == 3) && (board[(int) (row-2)][(int) (col-2)] == 0))){
      return true;
    }
    //Extra King Checks
    else if (board[row][col] == 4 && col < 6 && row < 6 &&  ( ((board[(int) (row+1)][(int) (col+1)] == 1 || board[(int) (row+1)][(int) (col+1)] == 3)) && (board[(int) (row+2)][(int) (col+2)] == 0))){
      return true;
    }
    else if  (board[row][col] == 4 && col > 1 && row < 6 &&  (((board[(int) (row+1)][(int) (col-1)] == 1 || board[(int) (row+1)][(int) (col-1)] == 3)) && (board[(int) (row+2)][(int) (col-2)] == 0))){
      return true;
    }
  }
  return false;
}

void updateBoard(bool blacksTurn, int currentRow,int currentCol, int toRow, int toCol,int jumpRow, int jumpCol){
	board[toRow][toCol] = board[currentRow][currentCol];
	board[currentRow][currentCol] = 0;
	checkKing(blacksTurn);
	if (jumpRow != -1){
		board[jumpRow][jumpCol] = 0;
		jump(currentRow, currentCol, toRow, toCol);
		getInPosition(toRow, toCol, jumpRow, jumpCol);
		removePiece(jumpRow, jumpCol);
		calibrate();
		if(blacksTurn){
			redCounter += 1;
		}
		else{
			blackCounter +=1;
		}
		if(doubleCapture(blacksTurn, toRow, toCol)){
			anotherCapture(blacksTurn, toRow, toCol);
		}
	}
	else{
		step(currentRow, currentCol, toRow, toCol);
		calibrate();
	}
}


//Checks if a move is legal, returns a boolean, called by the makeMove
bool legalMove(bool blacksTurn, int currentRow, int currentCol, int toRow, int toCol){
	//Legal move conditions, 1 diagonal, jump over piece, jump over multiple pieces - will be hard to implement

	int jumpRow = -1, jumpCol = -1;
	bool legal = false;
	//Check if a piece moves single piece diagonally


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

bool legalMove2(bool blacksTurn, int currentRow, int currentCol, int toRow, int toCol){
	//Legal move conditions for second capture, jumps only

	int jumpRow = -1, jumpCol = -1;
	bool legal = false;

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

void anotherCapture(bool blacksTurn, int currentRow, int currentCol){
	int toRow = -1, toCol = -1;//remove this curly bracket

	while(true){
		displayString(0, "TO WHERE?");
		getPos(1, toRow, toCol);
		if (!legalMove2(blacksTurn, currentRow, currentCol, toRow, toCol)) {
			displayString(3, "ILLEGAL MOVE");
			wait1Msec(1000);
			eraseDisplay();
		}
		else {
			break;
		}
	}
}

