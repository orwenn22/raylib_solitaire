#ifndef CARD_H
#define CARD_H

#include <raylib.h>
#include <vector>

typedef unsigned char u8;

#define COL_PIC    0
#define COL_COEUR  1
#define COL_CAREAU 2
#define COL_TREFLE 3

extern Texture2D colortextures[4];

struct Card {
    u8 m_number;
    u8 m_color;
    bool m_ishidden;

    bool m_isred;

    Card(u8 num, u8 col);
};

void LoadCardTextures();
void UnloadCardTextures();
void DrawCard(float x, float y, Card card);
bool IsCardInVector(std::vector<Card*>* vec, Card* card);

#endif