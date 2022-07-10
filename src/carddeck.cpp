#include "carddeck.h"
#include "game.h"
#include "gamemouse.h"

CardDeck::CardDeck(Vector2 pos, Game* game) {
    m_parrent = game;
    m_origin = pos;

    m_hiddendeckhitbox = {m_origin.x, m_origin.y, 50, 80};
    m_displayeddeckhitbox = {m_origin.x + 70.0f, m_origin.y, 50, 80};
}

CardDeck::~CardDeck() {
    int vecsize;

    vecsize = m_hiddendeck.size();
    for(int i = 0; i < vecsize; i++) {
        delete m_hiddendeck[i];
    }

    vecsize = m_displayeddeck.size();
    for(int i = 0; i < vecsize; i++) {
        delete m_displayeddeck[i];
    }
}

void CardDeck::Update() {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if(CheckCollisionPointRec(m_parrent->m_mouse->m_position, m_hiddendeckhitbox)) {        //PIOCHE
            if(m_hiddendeck.size() != 0) {      //AFFICHER LA CARTE SUIVANTE
                m_displayeddeck.push_back(m_hiddendeck[m_hiddendeck.size()-1]);
                m_hiddendeck.pop_back();
                m_parrent->m_movecount++;
            } else {                //REMETTRE TOUTES LES CARTES DANS LE TAS FACE CACHÉ
                int vecsize = m_displayeddeck.size();
                for(int i = 0; i < vecsize; i++) {
                    m_hiddendeck.push_back(m_displayeddeck[m_displayeddeck.size()-1]);
                    m_displayeddeck.pop_back();
                    m_parrent->m_movecount++;
                }
            }
        }

        if(CheckCollisionPointRec(m_parrent->m_mouse->m_position, m_displayeddeckhitbox)) {     //PRENDRE LA CARTE PIOCHÉ
            if(m_displayeddeck.size() > 0) {
                m_parrent->m_mouse->m_cardsource = &m_displayeddeck;
                m_parrent->m_mouse->m_cardselection.push_back(m_displayeddeck[m_displayeddeck.size()-1]);
                m_displayeddeck.pop_back();
            }
        }
    }
}

void CardDeck::Draw() {
    if(m_hiddendeck.size() > 0) DrawRectangleRec({m_origin.x, m_origin.y, 50, 80}, BLUE);
    DrawRectangleLinesEx({m_origin.x, m_origin.y, 50, 80}, 1, BLACK);

    if(m_displayeddeck.size() > 0) DrawCard(m_origin.x + 70.0f, m_origin.y, *(m_displayeddeck[m_displayeddeck.size()-1]));

    DrawText(TextFormat("%li", m_hiddendeck.size()), m_origin.x+5, m_origin.y+83, 10, GREEN);
}

void CardDeck::Add(Card* newcard) {
    m_hiddendeck.push_back(newcard);
}