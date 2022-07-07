#ifndef CARDSTACK_H
#define CARDSTACK_H

#include <vector>
#include "card.h"

class Game;

class CardStack {
    public:
    CardStack(u8 acceptedcolor, Vector2 pos, Game* game);
    ~CardStack();

    void Update();
    void Draw();

    Game* m_parrent;
    Rectangle m_hitbox;
    u8 m_acceptedcolor;
    std::vector<Card*> m_cards;
};

#endif