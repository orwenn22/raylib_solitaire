#include <vector>
#include <random>
#include <raylib.h>

#include "game.h"
#include "card.h"

int main(int argc, char const *argv[]) {
    InitWindow(960, 540, "solitaire :D");
    SetTargetFPS(60);

    LoadCardTextures();

    Game* mygame = new Game();

    while (!WindowShouldClose()) {
        //UPDATE
        if(IsKeyPressed(KEY_R)) {
            delete mygame;
            mygame = new Game();
        }

        mygame->Update();

        //DRAW
        BeginDrawing();
            ClearBackground({0x23, 0x7b, 0x3f, 0xff});
            mygame->Draw();
            //DrawText(TextFormat("%i", GetFPS()), 850, 10, 20, BLACK);
        EndDrawing();
    }
    
    delete mygame;

    UnloadCardTextures();
    CloseWindow();
    return 0;
}
