#include "Board.h"
#include <iostream>
#include <stdexcept>

using namespace std;
void setColor(int color)
{
    cout << "\033[" << color << "m";
}

void resetColor()
{
    cout << "\033[0m";
}
Board::Board()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            squares[i][j] = nullptr;

    whiteTurn = true;

    try
    {
        initializeBoard();
    }
    catch (const bad_alloc& e)
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                delete squares[i][j];
                squares[i][j] = nullptr;
            }
        throw runtime_error("Board initialization failed: out of memory");
    }
}

Board::~Board()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            delete squares[i][j];
            squares[i][j] = nullptr;
        }
}

void Board::initializeBoard()
{
    squares[0][0] = new Rook(false, 0, 0);
    squares[0][1] = new Knight(false, 0, 1);
    squares[0][2] = new Bishop(false, 0, 2);
    squares[0][3] = new Queen(false, 0, 3);
    squares[0][4] = new King(false, 0, 4);
    squares[0][5] = new Bishop(false, 0, 5);
    squares[0][6] = new Knight(false, 0, 6);
    squares[0][7] = new Rook(false, 0, 7);

    for (int i = 0; i < 8; i++)
        squares[1][i] = new Pawn(false, 1, i);

    for (int i = 0; i < 8; i++)
        squares[6][i] = new Pawn(true, 6, i);

    squares[7][0] = new Rook(true, 7, 0);
    squares[7][1] = new Knight(true, 7, 1);
    squares[7][2] = new Bishop(true, 7, 2);
    squares[7][3] = new Queen(true, 7, 3);
    squares[7][4] = new King(true, 7, 4);
    squares[7][5] = new Bishop(true, 7, 5);
    squares[7][6] = new Knight(true, 7, 6);
    squares[7][7] = new Rook(true, 7, 7);
}

void Board::display()
{
    cout << "\n";
    setColor(36);
    cout << "   a  b  c  d  e  f  g  h\n";
    cout << "  ------------------------\n";
    resetColor();

    for (int i = 0; i < 8; i++)
    {
        setColor(36);
        cout << 8 - i << " |";
        resetColor();

        for (int j = 0; j < 8; j++)
        {
            if (squares[i][j] != nullptr)
            {
                if (squares[i][j]->getColor())
                    setColor(97);
                else
                    setColor(90);

                cout << squares[i][j]->getSymbol() << "  ";
                resetColor();
            }
            else
            {
                setColor(33);
                cout << ".  ";
                resetColor();
            }
        }

        setColor(36);
        cout << "| " << 8 - i << "\n";
        resetColor();
    }

    setColor(36);
    cout << "  ------------------------\n";
    cout << "   a  b  c  d  e  f  g  h\n\n";
    resetColor();
}

bool Board::isInCheck(bool whiteKing)
{
    int kingRow = -1, kingCol = -1;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (squares[i][j] != nullptr && squares[i][j]->getType() == 'K' &&
                squares[i][j]->getColor() == whiteKing)
            {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
        if (kingRow != -1)
            break;
    }

    if (kingRow == -1)
        return false;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (squares[i][j] != nullptr && squares[i][j]->getColor() != whiteKing)
                if (squares[i][j]->isValidMove(kingRow, kingCol, squares))
                    return true;

    return false;
}

bool Board::wouldBeInCheck(int fromRow, int fromCol, int toRow, int toCol, bool whitePlayer)
{
    Piece* temp = squares[toRow][toCol];
    squares[toRow][toCol] = squares[fromRow][fromCol];
    squares[fromRow][fromCol] = nullptr;
    squares[toRow][toCol]->setPosition(toRow, toCol);

    bool inCheck = isInCheck(whitePlayer);

    squares[fromRow][fromCol] = squares[toRow][toCol];
    squares[toRow][toCol] = temp;
    squares[fromRow][fromCol]->setPosition(fromRow, fromCol);

    return inCheck;
}

bool Board::isCheckmate(bool whitePlayer)
{
    if (!isInCheck(whitePlayer))
        return false;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (squares[i][j] != nullptr && squares[i][j]->getColor() == whitePlayer)
            {
                for (int di = 0; di < 8; di++)
                {
                    for (int dj = 0; dj < 8; dj++)
                    {
                        if (i == di && j == dj)
                            continue;
                        if (squares[di][dj] != nullptr && squares[di][dj]->getColor() == whitePlayer)
                            continue;
                        if (squares[i][j]->isValidMove(di, dj, squares))
                            if (!wouldBeInCheck(i, j, di, dj, whitePlayer))
                                return false;
                    }
                }
            }
        }
    }

    return true;
}

bool Board::makeMove(string from, string to)
{
    if (from.length() != 2 || to.length() != 2)
        return false;

    int fromCol = from[0] - 'a';
    int fromRow = 8 - (from[1] - '0');
    int toCol = to[0] - 'a';
    int toRow = 8 - (to[1] - '0');

    if (fromRow < 0 || fromRow > 7 || fromCol < 0 || fromCol > 7 ||
        toRow < 0 || toRow > 7 || toCol < 0 || toCol > 7)
        return false;

    Piece* piece = squares[fromRow][fromCol];

    if (piece == nullptr)
        return false;
    if (piece->getColor() != whiteTurn)
        return false;
    if (squares[toRow][toCol] != nullptr && squares[toRow][toCol]->getColor() == whiteTurn)
        return false;
    if (!piece->isValidMove(toRow, toCol, squares))
        return false;
    if (wouldBeInCheck(fromRow, fromCol, toRow, toCol, whiteTurn))
        return false;

    Piece* captured = squares[toRow][toCol];
    squares[toRow][toCol] = piece;
    squares[fromRow][fromCol] = nullptr;
    piece->setPosition(toRow, toCol);

    if (piece->getType() == 'P' && (toRow == 0 || toRow == 7))
    {
        Piece* promoted = nullptr;
        try
        {
            promoted = new Queen(whiteTurn, toRow, toCol);
        }
        catch (const bad_alloc& e)
        {
            squares[fromRow][fromCol] = squares[toRow][toCol];
            squares[toRow][toCol] = captured;
            squares[fromRow][fromCol]->setPosition(fromRow, fromCol);
            throw runtime_error("Pawn promotion failed: out of memory");
        }
        delete squares[toRow][toCol];
        squares[toRow][toCol] = promoted;
    }

    delete captured;
    whiteTurn = !whiteTurn;
    return true;
}

bool Board::isWhiteTurn() const
{
    return whiteTurn;
}

bool Board::hasKing(bool white)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (squares[i][j] != nullptr && squares[i][j]->getType() == 'K' &&
                squares[i][j]->getColor() == white)
                return true;
    return false;
}