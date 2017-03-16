#include <iostream>
#include <cmath>
using namespace std;

//Global 2D Array for board
int board[8][8];
int blackCounter = 0, redCounter = 0;

void displayBoard(){
  for (int i = 7; i >= 0;i--){
      for (int j = 0; j < 8; j++){
        //cout << "[" << board[i][j] << "]";
        if (board[i][j] == 0) {
        	cout << "[ ]";
        }
        else if (board[i][j] == 1) {
        	cout << "[1]";
        }
        else if (board[i][j] == 2) {
        	cout << "[2]";
        }
        else if (board[i][j] == 3) {
        	cout << "[3]";
        }
        else{
        	cout << "[4]";
        }
      }
      cout << " " << i+1 << endl;
    }
    cout << endl;
    cout << " "<< "a" << "  " <<  "b" << "  "  << "c" << "  "
    << "d" << "  " << "e" << "  " << "f" << "  " << "g"  << "  "<< "h";
}

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
//Checks for winner using a counter
bool checkWinner(){
  if(redCounter == 12 || blackCounter == 12){
    return true;
  }
  else{
  return false;
  }
}
//Turns a checker piece into a king
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
        if ( (board[i][j] == 1 || board[i][j] == 3) && j < 6 && ((board[i+1][j+1] == 2 || board[i+1][j+1] == 4) && (board[i+2][j+2] == 0))){
          return true;
        }
        else if ( (board[i][j] == 1 || board[i][j] == 3) && j > 1 && ((board[i+1][j-1] == 2 || board[i+1][j-1] == 4) && (board[i-2][j-2] == 0))){
          return true;
        }
        
        //Extra King Checks
        else if (board[i][j] == 3 && j < 6 && ( ((board[i-1][j+1] == 2) || (board[i-1][j+1] == 4)) && (board[i-2][j+2] == 0))){
          return true;
        }
        else if  (board[i][j] == 3 && j > 1 && ( ((board[i-1][j-1] == 2 || board[i-1][j-1] == 4 )) && (board[i-2][j-2] == 0))){
          return true;
        }
      }
      else{
        //Red Piece Cases
        if ((board[i][j] == 2 || board[i][j] == 4) && j < 6 && ((board[i-1][j+1] == 1 || board[i-1][j+1] == 3) && (board[i-2][j+2] == 0))){
          return true;
        }
        else if  ((board[i][j] == 2 || board[i][j] == 4) && j > 1 && ((board[i-1][j-1] == 1 || board[i-1][j-1] == 3) && (board[i-2][j-2] == 0))){
          return true;
        }
        //Extra King Checks
        else if (board[i][j] == 4 && j < 6 && ( ((board[i+1][j+1] == 1 || board[i+1][j+1] == 3)) && (board[i+2][j+2] == 0))){
          return true;
        }
        else if  (board[i][j] == 4 && j > 1 && (((board[i+1][j-1] == 1 || board[i+1][j-1] == 3)) && (board[i+2][j-2] == 0))){
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
    if ( (board[row][col] == 1 || board[row][col] == 3) && col < 6 && ((board[row+1][col+1] == 2 || board[row+1][col+1] == 4) && (board[row+2][col+2] == 0))){
      return true;
    }
    else if ( (board[row][col] == 1 || board[row][col] == 3) && col > 1 && ((board[row+1][col-1] == 2 || board[row+1][col-1] == 4) && (board[row+2][col-2] == 0))){
      return true;
    }
    
    //Extra King Checks
    else if (board[row][col] == 3 && col < 6 && ( ((board[row-1][col+1] == 2) || (board[row-1][col+1] == 4)) && (board[row-2][col+2] == 0))){
      return true;
    }
    else if  (board[row][col] == 3 && col > 1 && ( ((board[row-1][col-1] == 2 || board[row-1][col-1] == 4 )) && (board[row-2][col-2] == 0))){
      return true;
    }
  }
  else{
    //Red Piece Cases
    if ((board[row][col] == 2 || board[row][col] == 4) && col < 6 && ((board[row-1][col+1] == 1 || board[row-1][col+1] == 3) && (board[row-2][col+2] == 0))){
      return true;
    }
    else if  ((board[row][col] == 2 || board[row][col] == 4) && col > 1 && ((board[row-1][col-1] == 1 || board[row-1][col-1] == 3) && (board[row-2][col-2] == 0))){
      return true;
    }
    //Extra King Checks
    else if (board[row][col] == 4 && col < 6 && ( ((board[row+1][col+1] == 1 || board[row+1][col+1] == 3)) && (board[row+2][col+2] == 0))){
      return true;
    }
    else if  (board[row][col] == 4 && col > 1 && (((board[row+1][col-1] == 1 || board[row+1][col-1] == 3)) && (board[row+2][col-2] == 0))){
      return true;
    }
  } 
  return false;
}
void updateBoard(bool &blacksTurn, int currentRow,int currentCol, int toRow, int toCol,int jumpRow, int jumpCol){
  board[toRow][toCol] = board[currentRow][currentCol];
  board[currentRow][currentCol] = 0;
  checkKing(blacksTurn);
  if (jumpRow != -1){
    board[jumpRow][jumpCol] = 0;
    if(blacksTurn){
      redCounter += 1;
    }
    else{
      blackCounter +=1;
    }
    if(doubleCapture(blacksTurn, toRow, toCol)){
      blacksTurn = !blacksTurn;
    }
  }
}

//Checks if a move is legal, returns a boolean, called by the makeMove
bool legalMove(bool &blacksTurn, int currentRow, int currentCol, int toRow, int toCol){
  //Legal move conditions, 1 diagonal, jump over piece, jump over multiple pieces - will be hard to implement
  
  int jumpRow = -1, jumpCol = -1;
  bool legal = false;
  //Check if a piece moves single piece diagonally

  cout << endl << currentRow << currentCol << toRow << toCol << endl;

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

void makeMove(bool &blacksTurn){
  int currentRow = -1, currentCol = -1, toRow = -1, toCol = -1;
  string curr = "x", to = "x";

  cout << endl << "Force? " << canCapture(blacksTurn); // DEBUGGINGPURPOSE
  do{
    cout << endl << "Which piece would you like to move? ";
    cin >> curr;
    cout << "To where? ";
    cin >> to;
    currentCol = curr.at(0) - 97; //Converts letter input to an integer number, COLUMN INPUT
    currentRow = curr.at(1) - '0' - 1; //Converts char number to integer number, ROW INPUT

    toCol = to.at(0) - 97;
    toRow = to.at(1) - '0' - 1;
    cout << currentRow << currentCol <<endl<<toRow << toCol;

  } while (!legalMove(blacksTurn,currentRow,currentCol,toRow,toCol));
}

int main() {
    int counter = 0;
    bool blacksTurn = true;
    
    newGame();
    displayBoard();

    while(!checkWinner()){
      makeMove(blacksTurn);
      cout << endl;
      displayBoard();
      blacksTurn = !blacksTurn;

    }

    return 0;
}
