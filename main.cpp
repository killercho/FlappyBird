#include <raylib.h>
#include <string>

int main()
{
    // TODO: Make the app detect the width and height of the phone automatically
    // Background texture size - 288x512
    const int WIDTH = 288;
    const int HEIGHT = 512;

    const float SPEED = 1;
    const float JUMPFORCE = 60;
    const float GRAVITY = 2;

    const std::string TITLE = "Cheappy bird";

    InitWindow(WIDTH, HEIGHT, TITLE.c_str());
    SetTargetFPS(60);

    // TODO: Make the background change depending on the clock
    // TODO: Add the different sprites of the bird
    // TODO: Add a curve for the bird falling and jumping
    // TODO: Add bird rotation when falling and jumping
    Texture2D background = LoadTexture("./sprites/background-day.png");
    Texture2D bird = LoadTexture("./sprites/redbird-midflap.png");
    Texture2D pilon = LoadTexture("./sprites/pipe-red.png");

    Vector2 birdPosition = { (float)WIDTH / 2, (float)HEIGHT / 2 };
    // TODO: Make the pilons in a group and move them together
    // TODO: Move the pilons with a random y
    // TODO: Add collision between the pilons and the bird
    Vector2 pilon1PosTop = { (float)400, (float)260 };
    Vector2 pilon1PosBottom = { (float)400, (float)0 };
    // TODO: Make a second pair of pilons that spawns a little after the first

    // TODO: Move the camera a little to the left
    // Camera2D camera = { { birdPosition.x + 20 }, { 0 } };

    // Main game loop:
    while (!WindowShouldClose()) {
        // Update
        birdPosition.y += GRAVITY;
        pilon1PosTop.x -= SPEED;
        pilon1PosBottom.x -= SPEED;

        if (pilon1PosTop.x <= -52) {
            pilon1PosTop.x = WIDTH + 52;
            pilon1PosBottom.x = WIDTH + 52;
        }

        // Input
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
            birdPosition.y -= JUMPFORCE;

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(bird, birdPosition.x, birdPosition.y, WHITE);

        DrawTextureRec(pilon, { 0, 0, 52, 320 }, pilon1PosTop, WHITE);
        DrawTextureRec(pilon, { 0, 0, 52, -160 }, pilon1PosBottom, WHITE);
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(bird);
    CloseWindow();
    return 0;
}
