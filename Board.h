#pragma once
#include "Pieces.h"
#include <string>

using namespace std;

class Board
{
private:
    Piece* squares[8][8];
    bool whiteTurn;

public:
    Board();
    ~Board();

    void initializeBoard();
    void display();
    bool isInCheck(bool whiteKing);
    bool wouldBeInCheck(int fromRow, int fromCol, int toRow, int toCol, bool whitePlayer);
    bool isCheckmate(bool whitePlayer);
    bool makeMove(string from, string to);
    bool isWhiteTurn() const;
    bool hasKing(bool white);
};
