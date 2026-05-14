#include "Board.h"
#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

void displayWelcome()
{
    cout << "\n\n";
    setColor(31);
    cout << "             ***********************************************************************\n";
    cout << "             =======================================================================\n";
    cout << "              *        *  *******  *       *******  *******  *       *  ****** \n";
    cout << "              *        *  *        *       *        *     *  * *   * *  *      \n";
    cout << "              *        *  *        *       *        *     *  *  * *  *  *      \n";
    cout << "              *   *    *  *******  *       *        *     *  *   *   *  ******  \n";
    cout << "              *  *  *  *  *        *       *        *     *  *       *  *      \n";
    cout << "              * *    * *  *        *       *        *     *  *       *  *      \n";
    cout << "              *        *  *******  ******* *******  *******  *       *  ****** \n";
    cout << "            =======================================================================\n";
    cout << "            *********************************************************************** \n";
    resetColor();

    setColor(35);
    cout << "  ===============================================================================================\n";
    cout << "  TTTTTTT  H   H  EEEEE       CCCC  H   H  EEEEE  SSSS  SSSS       CCCCC  L      U   U  BBBB  \n";
    cout << "     T     H   H  E          C      H   H  E      S     S          C      L      U   U  B   B \n";
    cout << "     T     HHHHH  EEEEE      C      HHHHH  EEEEE   SSS   SSS       C      L      U   U  BBBB  \n";
    cout << "     T     H   H  E          C      H   H  E          S     S      C      L      U   U  B   B \n";
    cout << "     T     H   H  EEEEE       CCCC  H   H  EEEEE  SSSS  SSSS       CCCCC  LLLLL  UUUUU  BBBBB  \n";
    cout << "  ================================================================================================\n";
    resetColor();

    cout << "\n";
    setColor(96);
    cout << "                                CHALLANGE YOUR MIND &\n";
    cout << "                                  MASTER STRATEGY!\n";
    resetColor();
    cout << "\n";
    setColor(92);
    cout << "\n";
}

int main()
{
    try
    {
        displayWelcome();

        int choice;
        setColor(94);
        cout << "  ====================\n";
        cout << "     MAIN  MENU      \n";
        cout << "  ====================\n";
        resetColor();
        setColor(96);
        cout << "  1. Start Game\n";
        cout << "  2. Exit\n";
        resetColor();
        setColor(93);
        cout << "\nEnter your choice: ";
        resetColor();

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            setColor(91);
            cout << "\nInvalid input! Please enter a number.\n";
            resetColor();
            return 1;
        }

        switch (choice)
        {
        case 1:
        {
            Board chessBoard;
            string from, to;

            setColor(92);
            cout << "\n===============================\n";
            cout << "    CHESS GAME STARTED\n";
            cout << "===============================\n";
            resetColor();

            setColor(96);
            cout << "\nInstructions:\n";
            resetColor();
            cout << "  - Enter moves in format: e2 e4\n";
            setColor(97);
            cout << "  - White pieces: ";
            setColor(97);
            cout << "PRNBQK (bright)\n";
            resetColor();
            setColor(90);
            cout << "  - Black pieces: ";
            setColor(90);
            cout << "prnbqk (dark)\n";
            resetColor();
            cout << "  - Type 'quit' to exit the game\n\n";

            while (true)
            {
                chessBoard.display();

                if (!chessBoard.hasKing(true))
                {
                    setColor(91);
                    cout << "\n===============================================\n";
                    cout << "  *** BLACK WINS! White King Captured! ***   \n";
                    cout << "===============================================\n";
                    resetColor();
                    break;
                }
                if (!chessBoard.hasKing(false))
                {
                    setColor(92);
                    cout << "\n===============================================\n";
                    cout << "  *** WHITE WINS! Black King Captured! ***   \n";
                    cout << "===============================================\n";
                    resetColor();
                    break;
                }

                if (chessBoard.isCheckmate(chessBoard.isWhiteTurn()))
                {
                    if (chessBoard.isWhiteTurn())
                    {
                        setColor(91);
                        cout << "\n===================================\n";
                        cout << "  *** CHECKMATE! BLACK WINS! ***  \n";
                        cout << "===================================\n";
                        resetColor();
                    }
                    else
                    {
                        setColor(92);
                        cout << "\n===================================\n";
                        cout << "  *** CHECKMATE! WHITE WINS! ***  \n";
                        cout << "===================================\n";
                        resetColor();
                    }
                    break;
                }

                if (chessBoard.isInCheck(chessBoard.isWhiteTurn()))
                {
                    setColor(91);
                    cout << "*** CHECK! ***\n";
                    resetColor();
                }

                if (chessBoard.isWhiteTurn())
                {
                    setColor(97);
                    cout << "White's turn\n";
                    resetColor();
                }
                else
                {
                    setColor(90);
                    cout << "Black's turn\n";
                    resetColor();
                }

                setColor(93);
                cout << "Enter move (from to): ";
                resetColor();

                if (!(cin >> from))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    setColor(91);
                    cout << "\n*** INPUT ERROR! Try again. ***\n\n";
                    resetColor();
                    continue;
                }

                if (from == "quit")
                {
                    setColor(96);
                    cout << "\nThanks for playing!\n";
                    resetColor();
                    break;
                }

                if (!(cin >> to))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    setColor(91);
                    cout << "\n*** INPUT ERROR! Try again. ***\n\n";
                    resetColor();
                    continue;
                }

                try
                {
                    if (!chessBoard.makeMove(from, to))
                    {
                        setColor(91);
                        cout << "\n*** INVALID MOVE! ***\n\n";
                        resetColor();
                    }
                }
                catch (const runtime_error& e)
                {
                    setColor(91);
                    cout << "\n*** ERROR: " << e.what() << " ***\n\n";
                    resetColor();
                }
            }
            break;
        }
        case 2:
            setColor(96);
            cout << "\nGoodbye! Thanks for visiting the Chess Club!\n";
            resetColor();
            break;
        default:
            setColor(91);
            cout << "\nInvalid choice!\n";
            resetColor();
            break;
        }
    }
    catch (const bad_alloc& e)
    {
        resetColor();
        cerr << "\nFATAL ERROR: Out of memory. " << e.what() << "\n";
        return 1;
    }
    catch (const runtime_error& e)
    {
        resetColor();
        cerr << "\nFATAL ERROR: " << e.what() << "\n";
        return 1;
    }
    catch (const exception& e)
    {
        resetColor();
        cerr << "\nUNEXPECTED ERROR: " << e.what() << "\n";
        return 1;
    }

    return 0;
}