#include <iostream>
#include <windows.h>
#include <conio.h>

#include "../game.h"

    /*=====================*/
    /*      FUNCTIONS      */
    /*=====================*/

// INITIALIZE

int Interface::Init()
{
    int input;

    do
    {
        /* INPUT SCREEN */

        system("cls");
        std::cout   << std::endl
                    << " [*] Welcome to Caro!" << std::endl
                    << std::endl
                    << " Enter board size (nxn): "
                    ;

        /* READ INPUT */

        std::cin >> input;

        /* VALIDATION */

        if ( (unsigned)input-MIN_N <= MAX_N-MIN_N )
        {
            return input;
        }
        else
        {
            system("cls");
            std::cout   << std::endl
                        << " [*] Invalid input! Try again." << std::endl
                        << std::endl
                        << " "
                        ;
            system("pause");
        }

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

void Interface::game_over(Game *GAME)
{
    print_game(GAME);
    std::cout   << std::endl
                << std::endl
                << " [*] Player " << !(GAME->getTurn()) << " wins!" << std::endl
                << std::endl
                ;
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

    if (!GAME->getN())
    {
        GAME->setN(Init());
    }

    /* CHECK IF STILL PLAYING */

    if (GAME->isPlaying())
    {
        next_move(GAME);
    }
    else
    {
        game_over(GAME);
    }
}

    /*=======================*/
    /*      DESTRUCTORS      */
    /*=======================*/

Interface::~Interface()
{
}
