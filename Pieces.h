#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

void setColor(int color);
void resetColor();
class Piece
{
protected:
    bool isWhite;
    int row, col;
    char symbol;

public:
    Piece(bool white, int r, int c, char sym) : isWhite(white), row(r), col(c), symbol(sym)
    {
        if (r < 0 || r > 7 || c < 0 || c > 7)
            throw out_of_range("Piece position out of board bounds");
    }
    virtual ~Piece() {}

    bool getColor() const { return isWhite; }
    int getRow() const { return row; }
    int getCol() const { return col; }
    char getSymbol() const { return symbol; }
bool isInsideBoard(int r, int c) const
{
    return r >= 0 && r < 8 && c >= 0 && c < 8;
}
    void setPosition(int r, int c)
    {
        if (r < 0 || r > 7 || c < 0 || c > 7)
            throw out_of_range("setPosition: coordinates out of board bounds");
        row = r;
        col = c;
    }

    virtual bool isValidMove(int destRow, int destCol, Piece* board[8][8]) = 0;
    virtual char getType() const = 0;
};

class Pawn : public Piece
{
public:
    Pawn(bool white, int r, int c) : Piece(white, r, c, white ? 'P' : 'p') {}

    char getType() const { return 'P'; }

    bool isValidMove(int destRow, int destCol, Piece* board[8][8])
    {
        if (!isInsideBoard(destRow, destCol))
        return false;
        int direction = isWhite ? -1 : 1;
        int startRow = isWhite ? 6 : 1;

        if (destCol == col)
        {
            if (destRow == row + direction && board[destRow][destCol] == nullptr)
                return true;

            if (row == startRow && destRow == row + 2 * direction &&
                board[row + direction][col] == nullptr && board[destRow][destCol] == nullptr)
                return true;
        }

        if (abs(destCol - col) == 1 && destRow == row + direction)
        {
            if (board[destRow][destCol] != nullptr && board[destRow][destCol]->getColor() != isWhite)
                return true;
        }

        return false;
    }
};

class Rook : public Piece
{
public:
    Rook(bool white, int r, int c) : Piece(white, r, c, white ? 'R' : 'r') {}

    char getType() const { return 'R'; }

    bool isValidMove(int destRow, int destCol, Piece* board[8][8])
    {
        if (row != destRow && col != destCol)
            return false;

        int rowStep = (destRow > row) ? 1 : (destRow < row) ? -1 : 0;
        int colStep = (destCol > col) ? 1 : (destCol < col) ? -1 : 0;

        int currentRow = row + rowStep;
        int currentCol = col + colStep;

        while (currentRow != destRow || currentCol != destCol)
        {
            if (board[currentRow][currentCol] != nullptr)
                return false;
            currentRow += rowStep;
            currentCol += colStep;
        }

        return true;
    }
};

class Knight : public Piece
{
public:
    Knight(bool white, int r, int c) : Piece(white, r, c, white ? 'N' : 'n') {}

    char getType() const { return 'N'; }

    bool isValidMove(int destRow, int destCol, Piece* board[8][8])
    {
        int rowDiff = abs(destRow - row);
        int colDiff = abs(destCol - col);
        return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
    }
};

class Bishop : public Piece
{
public:
    Bishop(bool white, int r, int c) : Piece(white, r, c, white ? 'B' : 'b') {}

    char getType() const { return 'B'; }

    bool isValidMove(int destRow, int destCol, Piece* board[8][8])
    {
        if (abs(destRow - row) != abs(destCol - col))
            return false;

        int rowStep = (destRow > row) ? 1 : -1;
        int colStep = (destCol > col) ? 1 : -1;

        int currentRow = row + rowStep;
        int currentCol = col + colStep;

        while (currentRow != destRow || currentCol != destCol)
        {
            if (board[currentRow][currentCol] != nullptr)
                return false;
            currentRow += rowStep;
            currentCol += colStep;
        }

        return true;
    }
};

class Queen : public Piece
{
public:
    Queen(bool white, int r, int c) : Piece(white, r, c, white ? 'Q' : 'q') {}

    char getType() const { return 'Q'; }

    bool isValidMove(int destRow, int destCol, Piece* board[8][8])
    {
        if (row == destRow || col == destCol)
        {
            int rowStep = (destRow > row) ? 1 : (destRow < row) ? -1 : 0;
            int colStep = (destCol > col) ? 1 : (destCol < col) ? -1 : 0;

            int currentRow = row + rowStep;
            int currentCol = col + colStep;

            while (currentRow != destRow || currentCol != destCol)
            {
                if (board[currentRow][currentCol] != nullptr)
                    return false;
                currentRow += rowStep;
                currentCol += colStep;
            }
            return true;
        }

        if (abs(destRow - row) == abs(destCol - col))
        {
            int rowStep = (destRow > row) ? 1 : -1;
            int colStep = (destCol > col) ? 1 : -1;

            int currentRow = row + rowStep;
            int currentCol = col + colStep;

            while (currentRow != destRow || currentCol != destCol)
            {
                if (board[currentRow][currentCol] != nullptr)
                    return false;
                currentRow += rowStep;
                currentCol += colStep;
            }
            return true;
        }

        return false;
    }
};

class King : public Piece
{
public:
    King(bool white, int r, int c) : Piece(white, r, c, white ? 'K' : 'k') {}

    char getType() const { return 'K'; }

    bool isValidMove(int destRow, int destCol, Piece* board[8][8])
    {
        return abs(destRow - row) <= 1 && abs(destCol - col) <= 1;
    }
};
