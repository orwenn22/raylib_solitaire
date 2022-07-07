#ifndef GAMEMOUSE_H
#define GAMEMOUSE_H

#include "card.h"

class Game;

class GameMouse {
    public:
    GameMouse(Game* game);
    ~GameMouse();

    void Update();
    void PostUpdate();
    void Draw();

    Game* m_parrent;
    Vector2 m_position;
    std::vector<Card*> m_cardselection;
    std::vector<Card*>* m_cardsource;
};

#endif