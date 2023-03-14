#include <raylib.h>
#include <string>

int main()
{
    // TODO: Make the app detect the width and height of the phone automatically
    // Background texture size - 288x512
    const int SCREEN_WIDTH = 288;
    const int SCREEN_HEIGHT = 512;

    const float SPEED = 1;
    const float JUMPFORCE = 60;
    const float GRAVITY = 2;
    const int HOLE_SIZE = 100;
    const int PILON_HEIGHT = 620;
    const int PILON_WIDTH = 52;
    const int BIRD_HEIGHT = 24;
    const int BIRD_WIDTH = 34;

    const std::string TITLE = "Cheappy bird";

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE.c_str());
    SetTargetFPS(60);

    // TODO: Make the background change depending on the clock
    // TODO: Add the different sprites of the bird
    // TODO: Add a curve for the bird falling and jumping
    // TODO: Add bird rotation when falling and jumping
    Texture2D background = LoadTexture("./sprites/background-day.png");
    Texture2D bird = LoadTexture("./sprites/redbird-midflap.png");
    Texture2D pilon = LoadTexture("./sprites/pipe-red.png");

    Vector2 birdPosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };
    const int MINY = 120;
    const int MAXY = 450;
    int randomOffset = GetRandomValue(MINY, MAXY);
    Vector2 pilon1PosTop = { (float)400, (float)randomOffset - PILON_HEIGHT - HOLE_SIZE };
    Vector2 pilon1PosBottom = { (float)400, (float)randomOffset };

    randomOffset = GetRandomValue(MINY, MAXY);
    Vector2 pilon2PosTop = { (float)600, (float)randomOffset - PILON_HEIGHT - HOLE_SIZE };
    Vector2 pilon2PosBottom = { (float)600, (float)randomOffset };

    Rectangle birdHitbox;

    Rectangle pilon1TopHitbox;
    Rectangle pilon1BottomHitbox;

    Rectangle pilon2TopHitbox;
    Rectangle pilon2BottomHitbox;

    bool gameOver = false;

    // Main game loop:
    while (!WindowShouldClose()) {
        // Update
        birdPosition.y += GRAVITY;
        pilon1PosTop.x -= SPEED;
        pilon1PosBottom.x -= SPEED;
        pilon2PosTop.x -= SPEED;
        pilon2PosBottom.x -= SPEED;

        if (pilon1PosTop.x <= -PILON_WIDTH) {
            pilon1PosTop.x = SCREEN_WIDTH + PILON_WIDTH;
            pilon1PosBottom.x = SCREEN_WIDTH + PILON_WIDTH;
            randomOffset = GetRandomValue(MINY, MAXY);
            pilon1PosBottom.y = randomOffset;
            pilon1PosTop.y = randomOffset - PILON_HEIGHT - HOLE_SIZE;
        }

        if (pilon2PosTop.x <= -PILON_WIDTH) {
            pilon2PosTop.x = SCREEN_WIDTH + PILON_WIDTH;
            pilon2PosBottom.x = SCREEN_WIDTH + PILON_WIDTH;
            randomOffset = GetRandomValue(MINY, MAXY);
            pilon2PosBottom.y = randomOffset;
            pilon2PosTop.y = randomOffset - PILON_HEIGHT - HOLE_SIZE;
        }

        if (birdPosition.y < 0)
            birdPosition.y = 0;
        if (birdPosition.y > SCREEN_HEIGHT - BIRD_HEIGHT)
            birdPosition.y = SCREEN_HEIGHT - BIRD_HEIGHT;

        birdHitbox = (Rectangle) {
            birdPosition.x,
            birdPosition.y,
            BIRD_WIDTH,
            BIRD_HEIGHT,
        };

        pilon1TopHitbox = (Rectangle) {
            pilon1PosTop.x,
            pilon1PosTop.y,
            PILON_WIDTH,
            PILON_HEIGHT,
        };

        pilon1BottomHitbox = (Rectangle) {
            pilon1PosBottom.x,
            pilon1PosBottom.y,
            PILON_WIDTH,
            PILON_HEIGHT,
        };

        pilon2TopHitbox = (Rectangle) {
            pilon2PosTop.x,
            pilon2PosTop.y,
            PILON_WIDTH,
            PILON_HEIGHT,
        };

        pilon2BottomHitbox = (Rectangle) {
            pilon2PosBottom.x,
            pilon2PosBottom.y,
            PILON_WIDTH,
            PILON_HEIGHT,
        };

        // Input
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
            birdPosition.y -= JUMPFORCE;

        // Collision
        bool hitPilon = CheckCollisionRecs(birdHitbox, pilon1TopHitbox);
        hitPilon |= CheckCollisionRecs(birdHitbox, pilon1BottomHitbox);
        hitPilon |= CheckCollisionRecs(birdHitbox, pilon2TopHitbox);
        hitPilon |= CheckCollisionRecs(birdHitbox, pilon2BottomHitbox);

        if (hitPilon)
            gameOver = true;

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        if (!gameOver) {
            DrawTexture(background, 0, 0, WHITE);
            DrawTexture(bird, birdPosition.x, birdPosition.y, WHITE);

            DrawTextureRec(pilon, { 0, 0, PILON_WIDTH, -PILON_HEIGHT }, pilon1PosTop, WHITE);
            DrawTextureRec(pilon, { 0, 0, PILON_WIDTH, PILON_HEIGHT }, pilon1PosBottom, WHITE);

            DrawTextureRec(pilon, { 0, 0, PILON_WIDTH, -PILON_HEIGHT }, pilon2PosTop, WHITE);
            DrawTextureRec(pilon, { 0, 0, PILON_WIDTH, PILON_HEIGHT }, pilon2PosBottom, WHITE);
        } else
            DrawText("Game over", 0, 0, 25, BLACK);
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(bird);
    CloseWindow();
    return 0;
}
