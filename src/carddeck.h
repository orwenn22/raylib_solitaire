#ifndef CARDDECK_H
#define CARDDECK_H

#include "card.h"

class Game;

class CardDeck {
    public:
    CardDeck(Vector2 pos, Game* game);
    ~CardDeck();

    void Update();
    void Draw();

    void Add(Card* newcard);

    Game* m_parrent;
    std::vector<Card*> m_hiddendeck;
    std::vector<Card*> m_displayeddeck;
    
    Vector2 m_origin;
    Rectangle m_hiddendeckhitbox;
    Rectangle m_displayeddeckhitbox;
};

#endif