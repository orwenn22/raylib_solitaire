#include "gamemouse.h"

GameMouse::GameMouse(Game* game) {
    m_parrent = game;
}

GameMouse::~GameMouse() {
    int vecsize = m_cardselection.size();
    for(int i = 0; i < vecsize; i++) {
        delete m_cardselection[i];
    }
}

void GameMouse::Update() {
    m_position = GetMousePosition();
}

void GameMouse::PostUpdate() {
    if(IsMouseButtonUp(MOUSE_LEFT_BUTTON) && m_cardselection.size() != 0) {
        int vecsize = m_cardselection.size();
        for(int i = 0; i < vecsize; i++) {
            m_cardsource->push_back(m_cardselection[m_cardselection.size()-1]);
            m_cardselection.pop_back();
        }
    }
}

void GameMouse::Draw() {
    DrawPixelV(m_position, RED);
    if(m_cardselection.size() > 0) {
        DrawCard(m_position.x, m_position.y, *(m_cardselection[m_cardselection.size()-1]));
    }
}