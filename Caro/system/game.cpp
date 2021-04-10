#include <iostream>
#include <time.h>
#include <deque>
#include <string.h>

#include "../game.h"

    /*======================*/
    /*      ESSENTIALS      */
    /*======================*/

void Game::clear_board()
{
    for (int i=0;i<29;i++)
        for (int j=0;j<29;j++) BOARD[i][j]=' ';
}

int Game::check_win(int x, int y, char syb)
{
    int dx[4] = {1, 0, 1, -1};
    int dy[4] = {0, 1, 1,  1};

    for (int i=0;i<4;i++)
    {
        int visit[MAX_N][MAX_N];
        memset(visit,0,sizeof(visit));

        std::deque<CORD> cord_queue;
        cord_queue.push_back({x,y});

        int cnt = 0;

        while (!cord_queue.empty())
        {
            int curr_x = cord_queue.front().X,
                curr_y = cord_queue.front().Y;

            cord_queue.pop_front();

            if (visit[curr_x][curr_y]
                || curr_x<0 || curr_x>=N
                || curr_y<0 || curr_y>=N) continue;

            visit[curr_x][curr_y]=1;

            if (getSymbol(curr_x,curr_y) != syb)    continue;

            cnt++;
            if (cnt==5) return 1;

            cord_queue.push_back({curr_x+dx[i],
                                  curr_y+dy[i]}
                                 );

            cord_queue.push_back({curr_x-dx[i],
                                  curr_y-dy[i]}
                                 );
        }
        cord_queue.clear();
    }
    return 0;
}

    /*===========================*/
    /*      GETTER & SETTER      */
    /*===========================*/

void Game::setN(int n)
{
    N = n;
}

int  Game::getN()
{
    return N;
}

void Game::toggleTurn()
{
    turn = !turn;
}

void Game::setTurn(int t)
{
    turn = t;
}

int  Game::getTurn()
{
    return turn;
}

void Game::setPlaying(int state)
{
    playing = state;
}

int  Game::isPlaying()
{
    return playing;
}

char Game::getSymbol(int x, int y)
{
    return BOARD[x][y];
}

void Game::setSymbol(int x, int y, char symbol)
{
    BOARD[x][y] = symbol;
    setPlaying(!check_win(x,y,symbol));
}

void Game::setCord(int x, int y)
{
    PTR = {x, y};
}

    /*========================*/
    /*      CONSTRUCTORS      */
    /*========================*/

Game::Game()
{
    srand(time(NULL));
    clear_board();

    setPlaying(1);
    setTurn(rand()%2);

    do
    {
        INTERFACE = Interface(this);
        if (isPlaying())
        {
            setSymbol(PTR.X,PTR.Y,SYB[turn]);
            toggleTurn();
        }
        else
        {
            break;
        }

    } while (1);
}

    /*=======================*/
    /*      DESTRUCTORS      */
    /*=======================*/

Game::~Game() {



}

