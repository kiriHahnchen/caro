#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Game;

class Player {
private:

    char            NAME[24];
    char            SYMBOL;
    int             WINS;

public:

    Player();
    Player(char*);

    Play(int,int,Game*);

    ~Player();
};

#endif // PLAYER_H_INCLUDED
