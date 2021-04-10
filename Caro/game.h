#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "interface/interface.h"
#include "player/player.h"

#define MAX_PLAYER 2

#define MIN_N 2
#define MAX_N 30

struct CORD {
    int X, Y;
};

class Game {
private:

    int         N = 0           ,
                turn            ,
                playing         ,
                winning_N = 0   ,
                turn_cnt = 0    ,
                winner          ;

    char        BOARD[MAX_N][MAX_N] ;

    Interface   INTERFACE           ;
    Player      PLAYER[MAX_PLAYER]  ;

    CORD        PTR;

public:

    // ESSENTIALS

    char    SYB[2]  = {'O','X'};
    void    clear_board();
    int     check_win(int,int,int);

    // CONSTRUCTORS

    Game();

    // DESTRUCTORS

    ~Game();

    // GETTER & SETTER

    void    setN(int);
    int     getN();

    void    setWinningN(int);
    int     getWinningN();

    void    toggleTurn();
    void    setTurn(int);
    int     getTurn();

    void    add_turn();
    int     getTurnCnt();

    void    setWinner(int);
    int     getWinner();

    void    setCord(int,int);

    void    setPlaying(int);
    int     isPlaying();

    void    setSymbol(int,int,int);
    char    getSymbol(int,int);

};

#endif // GAME_H_INCLUDED
