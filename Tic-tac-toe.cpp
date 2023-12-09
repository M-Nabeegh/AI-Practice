#include <iostream>
#include <climits>


const int boardSize = 3;

void printBoard(char board[boardSize][boardSize]) {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool isWinner(char board[boardSize][boardSize], char player) {

    for (int i = 0; i < boardSize; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

bool isBoardFull(char board[boardSize][boardSize]) {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}


int evaluateBoard(char board[boardSize][boardSize]) {
    if (isWinner(board, 'X')) {
        return 10; 
    } else if (isWinner(board, 'O')) {
        return -10; 
    } else {
        return 0; 
    }
}

int minimax(char board[boardSize][boardSize], int depth, bool isMaximizingPlayer, int alpha, int beta) {
    int score = evaluateBoard(board);

    if (score != 0) {
        return score;
    }

    if (isBoardFull(board)) {
        return 0;
    }

    if (isMaximizingPlayer) {
        int maxEval = INT_MIN;
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int eval = minimax(board, depth + 1, false, alpha, beta);
                    board[i][j] = ' '; 

                    maxEval = std::max(maxEval, eval);
                    alpha = std::max(alpha, eval);

                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int eval = minimax(board, depth + 1, true, alpha, beta);
                    board[i][j] = ' '; 

                    minEval = std::min(minEval, eval);
                    beta = std::min(beta, eval);

                    if (beta <= alpha) {
                        break; 
                    }
                }
            }
        }
        return minEval;
    }
}

void findBestMove(char board[boardSize][boardSize]) {
    int bestVal = INT_MIN;
    int bestMoveI = -1, bestMoveJ = -1;

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                int moveVal = minimax(board, 0, false, INT_MIN, INT_MAX);
                board[i][j] = ' '; 
                if (moveVal > bestVal) {
                    bestMoveI = i;
                    bestMoveJ = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    std::cout << "AI's Move: (" << bestMoveI + 1 << ", " << bestMoveJ + 1 << ")" << std::endl;
    board[bestMoveI][bestMoveJ] = 'X';
}

int main() {
    char board[boardSize][boardSize] = {{' ', ' ', ' '},
                                        {' ', ' ', ' '},
                                        {' ', ' ', ' '}};

    int currentPlayer = 1; 

    std::cout << "Welcome to Tic-Tac-Toe! You are O, and the AI is X." << std::endl;

    while (true) {
        printBoard(board);

        if (currentPlayer == 1) {
            
            int row, col;
            std::cout << "Your Move (row [1-3] and column [1-3]): ";
            std::cin >> row >> col;

            row--;
            col--;

            if (row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col] != ' ') {
                std::cout << "Invalid move. Try again." << std::endl;
                continue;
            }

            board[row][col] = 'O';
        } else {
           
            findBestMove(board);
        }

    
        if (isWinner(board, 'O')) {
            printBoard(board);
            std::cout << "You win! Congratulations!" << std::endl;
            break;
        } else if (isWinner(board, 'X')) {
            printBoard(board);
            std::cout << "AI wins! Better luck next time." << std::endl;
            break;
        } else if (isBoardFull(board)) {
            printBoard(board);
            std::cout << "It's a draw!" <<std::endl;
            break;
        }

        currentPlayer = -currentPlayer; // Switch player turn
    }

    return 0;
}

