#include "cardrow.h"

#include "game.h"
#include "gamemouse.h"

#include <iostream>

CardRow::CardRow(Vector2 pos, Game* game) {
    m_parrent = game;
    m_origin = pos;
}

CardRow::~CardRow() {
    int vecsize = m_cards.size();
    for(int i = 0; i < vecsize; i++) {
        delete m_cards[i];
    }
}


void CardRow::Update() {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_cards.size() != 0) {   //prendre cartes
        if(CheckCollisionPointRec(m_parrent->m_mouse->m_position, {m_origin.x, m_origin.y, 50, (float)(80+20*((int)(m_cards.size())-1))})) {
            //determiner l'index de la carte cliquée
            int clickedcardindex = (int)((m_parrent->m_mouse->m_position.y - m_origin.y)/20);
            if(clickedcardindex >= m_cards.size()) clickedcardindex = m_cards.size()-1;
            //printf("%i\n", clickedcardindex);

            //mettre les cartes dans la souris
            if(m_cards[clickedcardindex]->m_ishidden == false) {
                m_parrent->m_mouse->m_cardsource = &m_cards;
                int numofcardtocopy = m_cards.size() - clickedcardindex;
                for(int i = 0; i < numofcardtocopy; i++) {
                    m_parrent->m_mouse->m_cardselection.push_back(m_cards[m_cards.size()-1]);
                    m_cards.pop_back();
                }
            }
        }
    }

    if(IsMouseButtonUp(MOUSE_BUTTON_LEFT) && m_parrent->m_mouse->m_cardselection.size() != 0) {        //déposer carte
        if(CheckCollisionPointRec(m_parrent->m_mouse->m_position, {m_origin.x, m_origin.y, 50, (float)(80+20*((int)(m_cards.size())-1))})) {
            if(m_cards.size() == 0 ) {      //accèpter que un roi
                if(m_parrent->m_mouse->m_cardselection[m_parrent->m_mouse->m_cardselection.size()-1]->m_number == 13) {
                    //accepter le dépot
                    while(m_parrent->m_mouse->m_cardselection.size() != 0) {
                        m_cards.push_back(m_parrent->m_mouse->m_cardselection[m_parrent->m_mouse->m_cardselection.size()-1]);
                        m_parrent->m_mouse->m_cardselection.pop_back();

                        if(m_parrent->m_mouse->m_cardsource != &m_cards) {
                            m_parrent->m_movecount++;
                        }
                    }
                }
            }
            else {      //check si la carte dans la main du joueur est la bonne
                if(m_cards[m_cards.size()-1]->m_number == m_parrent->m_mouse->m_cardselection[m_parrent->m_mouse->m_cardselection.size()-1]->m_number+1) {  //vérif numéro
                    if(m_cards[m_cards.size()-1]->m_isred != m_parrent->m_mouse->m_cardselection[m_parrent->m_mouse->m_cardselection.size()-1]->m_isred) {      //vérif la couleur
                        //accepter le dépot
                        while(m_parrent->m_mouse->m_cardselection.size() != 0) {
                            m_cards.push_back(m_parrent->m_mouse->m_cardselection[m_parrent->m_mouse->m_cardselection.size()-1]);
                            m_parrent->m_mouse->m_cardselection.pop_back();

                            if(m_parrent->m_mouse->m_cardsource != &m_cards) {
                                m_parrent->m_movecount++;
                            }
                        }
                    }
                }
            }
        }
    }

    //dévoiler la dernière carte si possible
    if(m_cards.size() != 0) {
        if(m_cards[m_cards.size()-1]->m_ishidden && m_parrent->m_mouse->m_cardselection.size()==0) {
            m_cards[m_cards.size()-1]->m_ishidden = false;
        }
    }
}

void CardRow::Draw() {
    DrawRectangleLinesEx({m_origin.x, m_origin.y, 50, 80}, 1, BLACK);

    float ypainter = m_origin.y;
    int vecsize = m_cards.size();
    for(int i = 0; i < vecsize; i++) {
        DrawCard(m_origin.x, ypainter, *(m_cards[i]));
        ypainter += 20;
    }
}

void CardRow::Add(Card* newcard) {
    m_cards.push_back(newcard);
}