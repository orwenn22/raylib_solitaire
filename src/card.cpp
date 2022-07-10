#include "card.h"

#include <raylib.h>
#include <vector>

Texture2D colortextures[4];

Card::Card(u8 num, u8 col) {
    m_number = num;
    m_color = col;
    m_ishidden = false;

    m_isred = col == COL_COEUR || col == COL_CAREAU;
}

void LoadCardTextures() {
    colortextures[0] = LoadTexture("res/pic.png");
    colortextures[1] = LoadTexture("res/heart.png");
    colortextures[2] = LoadTexture("res/carreau.png");
    colortextures[3] = LoadTexture("res/clover.png");
}

void UnloadCardTextures() {
    for(int i = 0; i < 4; i++) UnloadTexture(colortextures[i]);
}

void DrawCard(float x, float y, Card card) {
    if(card.m_ishidden) {
        DrawRectangleRec({x, y, 50, 80}, BLUE);
        DrawRectangleLinesEx({x, y, 50, 80}, 1, BLACK);
    } else {
        Color col;
        if(card.m_color == 1 || card.m_color == 2) col = RED;
        else col = BLACK;

        DrawRectangleRec({x, y, 50, 80}, WHITE);
        DrawRectangleLinesEx({x, y, 50, 80}, 1, BLACK);
        
        const char* cardsnumbers[14] = {" ", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        DrawText(cardsnumbers[card.m_number], (int)x+5, (int)y+5, 20, col);

        //const char* colorletters[4] = {"P", "<3", "C", "T"};
        //DrawText(colorletters[card.m_color], (int)x+5, (int)y+25, 20, col);
        DrawTexture(colortextures[card.m_color], (int)x+25, (int)y+5, col);
        DrawTextureEx(colortextures[card.m_color], {x+5.0f, y+30.0f}, 0.0f, 2.0f, col);
    }
}



bool IsCardInVector(std::vector<Card*>* vec, Card* card) {
    int vecsize = vec->size();
    for(int i = 0; i < vecsize; i++) {
        if((*vec)[i]->m_color == card->m_color && (*vec)[i]->m_number == card->m_number) {
            return true;
        }
    }
    return false;
}