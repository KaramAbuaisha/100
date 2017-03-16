int board[8][8];

struct position {
	short row, col;
}

void getPos(short lineNum, position &pos) {
  char cols[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  short row = 3, col = 3;

  // select row
  while (nNxtButtonPressed != 3) {
    displayString(lineNum + 1, "SELECT ROW: %d", row + 1);
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
    displayString(lineNum + 2, "SELECT COLUMN: %c", cols[col]);
    while (nNxtButtonPressed == -1) {}
    if (nNxtButtonPressed == 1 && col < 7) {
      ++col;
    }
    else if (nNxtButtonPressed == 2 && col > 0) {
      --col;
    }
    wait1Msec(200);
  }

	pos.row = row;
	pos.col = col;
}

bool legalMove(bool blacksTurn, position current, position to) {
	return true;
	//...
}

void makeMove(bool blacksTurn) {
	position current, to;
	while (true) {
		displayString(0, "MOVE THIS PIECE");
		getPos(1, current);
		displayString(0, "MOVE THIS PIECE");
		getPos(4, to);
		if (!legalMove(blacksTurn, current, to)) {
			eraseDisplay();
			displayString(2, "ILLEGAL MOVE");
			wait1Msec(1000);
		}
		else {
			break;
		}
	}
}

void updateBoard(bool blacksTurn, position current, position to, position jump) {
	board[to.row][to.col] = board[current.row][current.col];
	board[current.row][current.col] = 0;

	if (jump.row != -1) {
		board[jump.row][jump.col] = 0;
	}
}

task main() {
}
