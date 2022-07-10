#include "cardstack.h"

#include "game.h"
#include "gamemouse.h"

//const char* colorletters[4] = {"P", "<3", "C", "T"};

CardStack::CardStack(u8 acceptedcolor, Vector2 pos, Game* game) {
    m_acceptedcolor = acceptedcolor;
    m_hitbox = {pos.x, pos.y, 50.0f, 80.0f};    
    m_parrent = game;
}

CardStack::~CardStack() {
    int vecsize = m_cards.size();
    for(int i = 0; i < vecsize; i++) {
        delete m_cards[i];
    }
}

void CardStack::Update() {
    if(CheckCollisionPointRec(m_parrent->m_mouse->m_position, m_hitbox)) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_cards.size() != 0) {       //prendre une carte
            m_parrent->m_mouse->m_cardsource = &m_cards;
            m_parrent->m_mouse->m_cardselection.push_back(m_cards[m_cards.size()-1]);
            m_cards.pop_back();
        }

        if(IsMouseButtonUp(MOUSE_BUTTON_LEFT) && m_parrent->m_mouse->m_cardselection.size() == 1) {     //déposer une carte
            if(m_cards.size() == 0) {
                if(m_parrent->m_mouse->m_cardselection[0]->m_color == m_acceptedcolor
                && m_parrent->m_mouse->m_cardselection[0]->m_number == 1) {
                    //accèpter le dépot
                    m_cards.push_back(m_parrent->m_mouse->m_cardselection[0]);
                    m_parrent->m_mouse->m_cardselection.pop_back();

                    if(m_parrent->m_mouse->m_cardsource != &m_cards) {
                        m_parrent->m_movecount++;
                    }
                }
            }
            else {
                if(m_parrent->m_mouse->m_cardselection[0]->m_color == m_acceptedcolor
                && m_parrent->m_mouse->m_cardselection[0]->m_number == m_cards[m_cards.size()-1]->m_number+1) {
                    //accèpter le dépot
                    m_cards.push_back(m_parrent->m_mouse->m_cardselection[0]);
                    m_parrent->m_mouse->m_cardselection.pop_back();

                    if(m_parrent->m_mouse->m_cardsource != &m_cards) {
                        m_parrent->m_movecount++;
                    }
                }
            }
        }
    }
}

void CardStack::Draw() {
    if(m_cards.size() == 0) {
        DrawRectangleLinesEx(m_hitbox, 1, BLACK);
        //DrawText(colorletters[m_acceptedcolor], m_hitbox.x+5, m_hitbox.y+5, 20, GREEN);
        DrawTexture(colortextures[m_acceptedcolor], m_hitbox.x+25, m_hitbox.y+5, GREEN);
    }
    else {
        DrawCard(m_hitbox.x, m_hitbox.y, *(m_cards[m_cards.size()-1]));
    }
}