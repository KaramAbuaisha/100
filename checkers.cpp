#include <iostream>
#include <cmath>
using namespace std;

void boardOutput(int arr[8][8]){
  for (int i = 7; i >= 0;i--){
      for (int j = 0; j < 8; j++){
        cout << "[" << arr[i][j] << "]";
      }
      cout << " " << i+1 << endl;
    }
    cout << endl;
    cout << " "<< "a" << "  " <<  "b" << "  "  << "c" << "  "
    << "d" << "  " << "e" << "  " << "f" << "  " << "g"  << "  "<< "h";
}

void newGame(int board[8][8]){
  //I is row, J is col
  for (int i = 0; i < 8;i++){
      for (int j = 0; j < 8; j++){
        //Setting default pieces

        //Black pieces 1

        //Row 1
        if ((i+1) == 1){
          if (j%2 == 1){
            board[i][j] = 1;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Row 2
        else if ((i+1) == 2){
          if (j%2 == 0){
            board[i][j] = 1;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Row 3
         else if ((i+1) == 3){
          if (j%2 == 1){
            board[i][j] = 1;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Row 6
        else if ((i+1) == 6){
          if (j%2 == 0){
            board[i][j] = 2;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Row 7
        else if ((i+1) == 7){
          if (j%2 == 1){
            board[i][j] = 2;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Row 8
        else if ((i+1) == 8){
          if (j%2 == 0){
            board[i][j] = 2;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Set blank spaces to 0
        else{
        board[i][j] = 0;
        }
      }
    }
}

bool whosTurn(){
  return false; //keep true for now
  //later make true if it's black turn and false if red turn
}

bool checkWinner(int board[8][8]){
  return false;
}

//Turns a checker piece into a king
void makeKing(){

}

//Checks if a piece is a king
void checkKing(){

}

//Checks if a move is legal, returns a boolean, called by the makeMove
bool legalMove(int board[8][8], string curr, string to, bool king){
  //Legal move conditions, 1 diagonal, jump over piece, jump over multiple pieces - will be hard to implement

  //Check if a piece moves single piece diagonally
  int curr1 = curr.at(0) - 97; //Converts letter input to an integer number, COLUMN INPUT
  int curr2 = curr.at(1) - '0' - 1; //Converts char number to integer number, ROW INPUT

  int to1 = to.at(0) - 97;
  int to2 = to.at(1) - '0' - 1;

  cout << endl << curr1 << curr2 << to1 << to2 << endl;
  //For nonking black pieces - single diagonal move, can only move forward, left/right, piece must be there and destination should be empty
  if (whosTurn()){
    if (( (abs(to1 - curr1)) == 1) && (to2 - curr2 == 1) && (board[curr2][curr1] == 1) && (board[to2][to1] == 0) ){
      cout << true;
      return true;
    }
  }

  //For nonking red pieces - single diagonal move, can only move forward, left/right, piece must be there and destination should be empty
  if (!whosTurn()){
    if (( (abs(to1 - curr1)) == 1) && (to2 - curr2 == -1) && (board[curr2][curr1] == 2) && (board[to2][to1] == 0) ){
      cout << true;
      return true;
    }
  }

  //Check jumping over pieces for nonking black
  if (whosTurn()){
    //Check if current space contains black nonking and final square is blank
    //Then check if intermediate spaces hold correct
  }

  cout << false;
  return false;
}

void makeMove(int board[8][8]){
  do{
    string curr = "X",to = "X";
    cout << endl << "Which piece would you like to move? ";
    cin >> curr;
    cout << "To where? ";
    cin >> to;} while (!legalMove(board,curr,to,false));

  //whosTurn = !whosTurn

}

int main() {
    int counter = 0;
    int board[8][8];

    newGame(board);
    boardOutput(board);

    while(!checkWinner(board)){
      makeMove(board);
    }

    return 0;
}
