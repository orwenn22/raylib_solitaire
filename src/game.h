#ifndef GAME_H
#define GAME_H

#include "card.h"

class CardDeck;
class CardRow;
class CardStack;
class GameMouse;

class Game {
    public:
    Game();
    ~Game();

    void Update();
    void Draw();

    CardDeck* m_deck;
    CardRow* m_rows[7];
    CardStack* m_stacks[4];
    GameMouse* m_mouse;

    unsigned int m_movecount;

    unsigned int m_timeinsec;
    unsigned int m_framecount;
};

#endif