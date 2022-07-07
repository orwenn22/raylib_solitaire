#ifndef CARDROW_H
#define CARDROW_H

#include "card.h"

class Game;

class CardRow {
    public:
    CardRow(Vector2 pos, Game* game);
    ~CardRow();

    void Update();
    void Draw();

    void Add(Card* newcard);

    Game* m_parrent;
    std::vector<Card*> m_cards;
    Vector2 m_origin;
};

#endif