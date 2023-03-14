#include <raylib.h>
#include <string>

int main()
{
    // TODO: Make the app detect the width and height of the phone automatically
    // Background texture size - 288x512
    const int WIDTH = 288;
    const int HEIGHT = 512;

    const int SPEED = 1;

    const std::string TITLE = "Cheappy bird";

    InitWindow(WIDTH, HEIGHT, TITLE.c_str());
    SetTargetFPS(60);

    // TODO: Make the background change depending on the clock
    Texture2D background = LoadTexture("./sprites/background-day.png");
    Texture2D bird = LoadTexture("./sprites/redbird-midflap.png");

    int birdX = WIDTH / 2;
    int birdY = HEIGHT / 2;

    // Main game loop:
    while (!WindowShouldClose()) {
        // Update
        birdX += SPEED;

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(bird, birdX, birdY, WHITE);
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(bird);
    CloseWindow();
    return 0;
}
