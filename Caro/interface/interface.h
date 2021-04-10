#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

class Game;

class Interface {
private:
public:

    /* CONSTRUCTORS     */

    Interface();
    Interface(Game*);

    /*  DESTRUCTORS     */

    ~Interface();

    /*  FUNCTIONS       */

    void    gotoxy(int,int);
    void    Init(Game*);

    void    print_game(Game*);
    void    next_move(Game*);
    void    game_over(Game*,int);

};

#endif // INTERFACE_H_INCLUDED
