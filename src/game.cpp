#include <random>

#include "game.h"
#include "gamemouse.h"
#include "cardrow.h"
#include "cardstack.h"
#include "carddeck.h"

Game::Game() {
    m_movecount = 0;
    m_timeinsec = 0;
    m_framecount = 0;

    m_mouse = new GameMouse(this);

    std::vector<Card*> existingcards;

    for(int i = 0; i < 4; i++) {
        m_stacks[i] = new CardStack(i, {220.0f + (float)(i*70), 10.0f}, this);
    }

    srand(time(NULL));
    m_deck = new CardDeck({10.0f, 10.0f}, this);

    for(int i = 0; i < 7; i++) {
        m_rows[i] = new CardRow({(float)(10+70*i), 120.0f}, this);
        
        //mettre les cartes
        for(int j = 0; j < i+1; j++) {
            Card* newcard = new Card((u8)((rand()%12)+1), (u8)(rand()%4));
            if(IsCardInVector(&existingcards, newcard)) {
                j--;
                delete newcard;
            }
            else {
                m_rows[i]->Add(newcard);
                existingcards.push_back(newcard);
                newcard->m_ishidden = (j != i);
            }
        }
    }

    while(existingcards.size() < 48) {
        Card* newcard = new Card((u8)((rand()%12)+1), (u8)(rand()%4));
        if(!IsCardInVector(&existingcards, newcard)) {
            m_deck->Add(newcard);
            existingcards.push_back(newcard);
        } else {
            delete newcard;
        }
    }
}

Game::~Game() {
    delete m_mouse;
    delete m_deck;
    for(int i = 0; i < 7; i++) delete m_rows[i];
    for(int i = 0; i < 4; i++) delete m_stacks[i];
}

void Game::Update() {
    m_mouse->Update();
    m_deck->Update();
    for(int i = 0; i < 7; i++) m_rows[i]->Update();
    for(int i = 0; i < 4; i++) m_stacks[i]->Update();

    m_mouse->PostUpdate();

    m_framecount++;
    if(m_framecount >= 120) {
        m_framecount = 0;
        m_timeinsec++;
    }
}

void Game::Draw() {
    DrawText(TextFormat("Move count: %i", m_movecount), 135, 10, 10, BLACK);
    DrawText(TextFormat("Time: %i", m_timeinsec), 135, 23, 10, BLACK);
    m_deck->Draw();
    for(int i = 0; i < 7; i++) m_rows[i]->Draw();
    for(int i = 0; i < 4; i++) m_stacks[i]->Draw();
    m_mouse->Draw();
}