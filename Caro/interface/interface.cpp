#include <iostream>
#include <windows.h>
#include <conio.h>

#include "../game.h"

    /*=====================*/
    /*      FUNCTIONS      */
    /*=====================*/

// INITIALIZE

void Interface::Init(Game *GAME)
{
    int input_N = 0         ,
        input_winning_N = 0 ;

    do
    {
        int input;

        /* INPUT SCREEN */

        system("cls");
        std::cout   << std::endl
                    << " [*] Welcome to Caro!" << std::endl
                    << std::endl
                    << " Enter board size (nxn): "
                    ;

        /* INPUT & VALIDATION */

        if (!input_N)
        {
            fflush(stdin);
            std::cin >> input;

            if ( (unsigned)input-MIN_N > MAX_N-MIN_N )
            {
                system("cls");
                std::cout   << std::endl
                            << " [*] Invalid input! Try again." << std::endl
                            << std::endl
                            << " "
                            ;

                fflush(stdin);
                getch();
                continue;
            }
            else
            {
                input_N = input;
            }
        }
        else
        {
            std::cout  << input_N << std::endl;
        }

        std::cout   << std::endl
                    << " Enter winning amount: ";

        if (!input_winning_N)
        {
            fflush(stdin);
            std::cin >> input;

            if ( (unsigned)input-MIN_N > input_N-MIN_N )
            {
                system("cls");
                std::cout   << std::endl
                            << " [*] Invalid input! Try again." << std::endl
                            << std::endl
                            << " "
                            ;
                fflush(stdin);
                getch();
                continue;
            }
            else
            {
                input_winning_N = input;
            }
        }

        GAME->setN(input_N);
        GAME->setWinningN(input_winning_N);
        return;

    } while (1);
}

// GOTO(X,Y)

void Interface::gotoxy(int x, int y)
{
    static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x,y};
    SetConsoleCursorPosition(h,c);
}

// PRINT CURRENT BOARD

void Interface::print_game(Game *GAME)
{
    int Turn    = GAME->getTurn()   ,
        n       = GAME->getN()      ;
    /* INFO BOARD */

    system("cls");
    std::cout       << std::endl;

    if (!GAME->isPlaying())
    {
        std::cout   << std::endl;
    }
    else
    {
        std::cout   << " [*] Player " << Turn << "'s turn" << std::endl;
    }
    std::cout       << std::endl;
                ;

    /* GAME BOARD */

    for (int i=0; i < (n-1)*2+1; i++)
    {
        std::cout   << std::endl
                    << " ";

        for (int j=0; j < (n-1)*2+1; j++)
        {
            if (!(i%2) && !(j%2))
            {
                std::cout << GAME->getSymbol(i>>1,j>>1);
            }
            else if ((i%2) && (j%2))
            {
                std::cout << "+";
            }
            else if (!(i%2) && (j%2))
            {
                std::cout << "|";
            }
            else if ((i%2) && !(j%2))
            {
                std::cout << "-";
            }
        }
    }
}

// NEXT MOVE

void Interface::next_move(Game *GAME)
{
    int n = GAME->getN(),
        x_inp           ,
        y_inp           ;
    do
    {
        print_game(GAME);
        std::cout   << std::endl
                    << std::endl
                    << " [*] Enter X cord: ";

        fflush(stdin);
        std::cin    >> x_inp;

        std::cout   << " [*] Enter Y cord: ";

        fflush(stdin);
        std::cin    >> y_inp;

        fflush(stdin);
        if (x_inp>=0 && x_inp<n && y_inp>=0 && y_inp<n)
        {
            if (GAME->getSymbol(x_inp,y_inp) == ' ')
                {
                GAME->setCord(x_inp,y_inp);
                break;
            }
            else
            {
                std::cout   << std::endl
                            << "Already occupied! Try again."
                            << std::endl
                            << std::endl
                            ;
                getch();
            }
        }
        else
        {
            std::cout   << std::endl
                        << "Out of bounds! Try again."
                        << std::endl
                        << std::endl
                        ;
            getch();
        }
    } while (1);
}

// END GAME PRINTING

void Interface::game_over(Game *GAME, int winner)
{
    fflush(stdin);
    print_game(GAME);
    std::cout   << std::endl
                << std::endl;
    if (!winner)
    {
        std::cout   << " [*] It's a draw!" << std::endl;
    }
    else
    {
        std::cout   << " [*] Player " << winner-1 << " wins!" << std::endl;
    }
    std::cout << std::endl;
    getch();
}

    /*========================*/
    /*      CONSTRUCTORS      */
    /*========================*/

Interface::Interface() {}

Interface::Interface(Game *GAME)
{
    /* INITIALIZE */

    fflush(stdin);

    if (!GAME->getN() || !GAME->getWinningN())
    {
        Init(GAME);
    }

    /* CHECK IF STILL PLAYING */

    if (GAME->isPlaying())
    {
        next_move(GAME);
    }
    else
    {
        game_over(GAME, GAME->getWinner());
    }
}

    /*=======================*/
    /*      DESTRUCTORS      */
    /*=======================*/

Interface::~Interface()
{
}
