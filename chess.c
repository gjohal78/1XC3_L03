#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>




// ♔ ♕ ♖ ♗ ♘ ♙

/* ┌ └ ┐ ┘

├ ┤ ┬ ┴
 
─ │ ┼
 
 might need these...
 
 ╟ ╢ ╧ ╤
 
*/

showBoard (int board[8][8]) {
    printf("   0 1 2 3 4 5 6 7");
    printf("\n  ╔═╤═╤═╤═╤═╤═╤═╤═╗\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i); 
        printf("║"); 
        bool flag = true;
        for (int j = 0; j < 8; j++) {
            if (!flag) {
                printf("│"); 
            }
            flag = false;
//            printf(""); 
            switch (board[i][j]) {
                case 0: 
                    if ((i + j) % 2 == 0) {
                        printf(" ");
                    } else {
                        printf("▒");
                    }
                    break;
                case 1:
                    printf("♔");
                    break;
                case 2: 
                    printf("♕");
                    break;
                case 3: 
                    printf("♗");
                    break;
                case 4: 
                    printf("♘");
                    break;
                case 5:
                    printf("♖");
                    break;
                case 6: 
                    printf("♙");
            }
        }
        printf("║\n") ;
        if (i < 7) {
            printf("  ╟─┼─┼─┼─┼─┼─┼─┼─╢\n") ;
        }
    }
    printf("  ╚═╧═╧═╧═╧═╧═╧═╧═╝\n");
}



//bool memberOf (int *ValidMoves[2], int x, int y) ; 

bool isValidMove (char* input, int board[8][8]) {
	int start_y = input[0] - 48;
	int start_x = input[1] - 48;
	int end_y = input[3] - 48;
	int end_x = input[4] - 48;
	
	// out of bounds check
	if (start_x > 7 || start_x < 0) {
		return false;
	} else if (start_y > 7 || start_y < 0) {
		return false;
	} else if (end_x > 7 || end_x < 0) {
		return false;
	} else if (end_y > 7 || end_y < 0) {
		return false;
	}
	
	// piece move checks 
	int* validMoves[2];
	int xcheck = start_x;
	int ycheck = start_y;
	int piecesInWay = 0;
    switch (board[start_x][start_y]) {
        case 0:
            return false;
        case 1:
            if (abs(start_x - end_x) <= 1 && abs(start_y-end_y) <= 1) {
			    return true;
		    }
        case 2:
             //printf("Queen Selected\n");
            while (true) {
                xcheck += (start_x > end_x)? -1 : 1;
                ycheck += (start_y > end_y)? -1 : 1;
                if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
                    break;
                }
                if (board[xcheck][ycheck] != 0) {
                    piecesInWay += 1;
                } 
                if (piecesInWay == 2) {
                    break;
                }
                if (xcheck == end_x && ycheck == end_y) {
                    return true;
                }
            }
            xcheck = start_x;
            ycheck = start_y;
            piecesInWay = 0;		
            while (true) {
                //printf("Calculating Rook Movement at %d, %d\n", ycheck, xcheck);
                if (start_y == end_y) {
                    //printf("Horzontal!\n");
                    xcheck += (start_x > end_x)? -1 : 1;
                } else if (start_x == end_x) {
                    //printf("Vertical!\n");
                    ycheck += (start_y > end_y)? -1 : 1;
                } 
                //printf("Now checking %d, %d\n", ycheck, xcheck);
            
                if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
                    //printf("Out of bounds!\n");
                    break;
                }
                if (board[xcheck][ycheck] != 0) {
                    //printf("Hit Piece: %d\n", board[xcheck][ycheck]);
                    piecesInWay += 1;
                } 	
                if (piecesInWay == 2) {
                    //printf("Hit Second Piece: %d\n", board[xcheck][ycheck]);
                    break;
                }	
                if (xcheck == end_x && ycheck == end_y) {
                    return true;
                }
            }
        case 3:
            while (true) {
                xcheck += (start_x > end_x)? -1 : 1;
                ycheck += (start_y > end_y)? -1 : 1;
                if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
                    break;
                }
                if (board[xcheck][ycheck] != 0) {
                    piecesInWay += 1;
                } 
                if (piecesInWay == 2) {
                    break;
                }
                if (xcheck == end_x && ycheck == end_y) {
                    return true;
                }
            } 
        case 4:
            if (abs(start_x - end_x) == 1) {
                if (abs(end_y - start_y) == 2) {
                    return true;
                }
            } else if (abs(start_x - end_x) == 2) {
                if (abs(end_y - start_y) == 1) {
                    return true;
                }
            }
        case 5:
            while (true) {
                if (start_y == end_y) {
                    xcheck += (start_x > end_x)? -1 : 1;
                } else if (start_x == end_x) {
                    ycheck += (start_y > end_y)? -1 : 1;
                } else {
                    return false;
                }
                
                if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
                    break;
                }
                if (board[xcheck][ycheck] != 0) {
                    piecesInWay += 1;
                } 
                if (piecesInWay == 2) {
                    break;
                }
                if (xcheck == end_x && ycheck == end_y) {
                    return true;
                }
            }
        case 6:
            if (start_y - end_y == 1 && start_x == end_x) { // forward one
                if (board[start_x][end_y] == 0) {
                    return true;
                }
            } else if (start_x - end_x == 2 && start_y == end_y) { // forward two
    //			printf("Detected forward move by 2\n");
                if (board[end_x][end_y] == 0 && board[end_x+1][end_y] == 0 && start_x == 6) {
                    return true;
                }
            } else if (abs(start_y - end_y) == 1 && start_x-end_x == 1) { // capture left or right
                //printf("Detected Capture\n");
                if (board[end_x][end_y] != 0) {
                    return true;
                }
            }
    }
	return false;
}


void makeMove (char* input, int board[8][8]) {

	int start_y = input[0] - 48;
	int start_x = input[1] - 48;
	int end_y = input[3] - 48;
	int end_x = input[4] - 48;
	
	board[end_x][end_y] = board[start_x][start_y];
	board[start_x][start_y] = 0;

}

//bool memberOf (int *ValidMoves[2], int x, int y) ; 



int main () {
	printf("Welcome to Terminal Chess!\n");



	printf("Initializing Board...\n")	;

	int board [8][8] = { {5, 4, 3, 1, 2, 3, 4, 5}
		           , {6, 6, 6, 6, 6, 6, 6, 6}
				 	     , {0, 0, 0, 0, 0, 0, 0, 0}
					     , {0, 0, 0, 0, 0, 0, 0, 0}
				             , {0, 0, 0, 0, 0, 0, 0, 0} 
				             , {0, 0, 0, 0, 0, 0, 0, 0}
				             , {6, 6, 6, 6, 6, 6, 6, 6}
				             , {5, 4, 3, 2, 1, 3, 4, 5}
				             } ;
  char buf[100];
  bool whitesMove = true;
	printf("Board Initialized!\n") ;

	
// 	showBoard(board);

  printf("Enter `q` to quit at any time.\n");
  printf("Moves are entered as co-ordinate pairs, such as \"13-33\" \n");
  do {

    bool flag = false; 
    showBoard(board);

    do {
	if (flag) {
		printf("Move Invalid! Try again!");
	}
    	if (whitesMove) {
      		printf("White to move.\n");
    	} else {
      		printf("Black to move.\n");
    	}
    	printf("♔ >> ");
	scanf("%s", buf);
	flag = true;



    } while (!isValidMove(buf, board) && buf[0] != 'q' && buf[0] !='Q' );
       makeMove(buf, board);
       whitesMove = !whitesMove;


  } while (buf[0] != 'q' && buf[0] != 'Q') ;
    
	printf("Terminating...\n") ;

}
