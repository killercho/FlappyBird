#include "./headers/pilons.hpp"
#include <raylib.h>
#include <string>

#include <iostream>

int main()
{
    // TODO: Make the app detect the width and height of the phone automatically
    // Background texture size - 288x512

    const float SPEED = 1;
    const float JUMPFORCE = 60;
    const float GRAVITY = 2;
    const int BIRD_HEIGHT = 24;
    const int BIRD_WIDTH = 34;

    const std::string TITLE = "Cheappy bird";

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE.c_str());
    SetTargetFPS(60);

    // TODO: Make the background change depending on the clock
    // TODO: Add the different sprites of the bird
    // TODO: Add a curve for the bird falling and jumping
    // TODO: Add bird rotation when falling and jumping
    // TODO: Sometimes the collision with the score hitbox is not detected (might not be there)
    // TODO: Move everything in classes
    // TODO: Make a makefile
    Texture2D background = LoadTexture("./sprites/background-day.png");
    Texture2D bird = LoadTexture("./sprites/redbird-midflap.png");
    Pilon* pilon1 = new Pilon("./sprites/pipe-red.png", 400);
    Pilon* pilon2 = new Pilon("./sprites/pipe-red.png", 600);

    Vector2 birdPosition
        = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };

    Rectangle birdHitbox;

    bool gameOver = false;
    int score = 0;

    bool collidedScore1 = false;
    bool collidedScore2 = false;

    // Main game loop:
    while (!WindowShouldClose()) {
        // Update
        birdPosition.y += GRAVITY;
        pilon1->movePilon(SPEED);
        pilon2->movePilon(SPEED);

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

        // Input
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
            birdPosition.y -= JUMPFORCE;

        // Collision
        bool hitPilon = CheckCollisionRecs(birdHitbox, pilon1->getTopHitbox());
        hitPilon |= CheckCollisionRecs(birdHitbox, pilon1->getBottomHitbox());
        hitPilon |= CheckCollisionRecs(birdHitbox, pilon2->getTopHitbox());
        hitPilon |= CheckCollisionRecs(birdHitbox, pilon2->getBottomHitbox());

        bool hitScore1 = CheckCollisionRecs(birdHitbox, pilon1->getScoreHitbox());
        bool hitScore2 = CheckCollisionRecs(birdHitbox, pilon2->getScoreHitbox());

        if (hitPilon)
            gameOver = true;

        if (hitScore1 && !collidedScore1) {
            score++;
            collidedScore1 = true;
            collidedScore2 = false;
            std::cout << "Score from score 1: " << score << '\n';
        }

        if (hitScore2 && !collidedScore2) {
            score++;
            collidedScore1 = false;
            collidedScore2 = true;
            std::cout << "Score from score 2: " << score << '\n';
        }

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        if (!gameOver) {
            DrawTexture(background, 0, 0, WHITE);
            DrawTexture(bird, birdPosition.x, birdPosition.y, WHITE);

            DrawTextureRec(pilon1->getTexture(), { 0, 0, Pilon::PILON_WIDTH, -Pilon::PILON_HEIGHT }, pilon1->getTopPos(), WHITE);
            DrawTextureRec(pilon1->getTexture(), { 0, 0, Pilon::PILON_WIDTH, -Pilon::PILON_HEIGHT }, pilon1->getBottomPos(), WHITE);
            DrawTextureRec(pilon2->getTexture(), { 0, 0, Pilon::PILON_WIDTH, -Pilon::PILON_HEIGHT }, pilon2->getTopPos(), WHITE);
            DrawTextureRec(pilon2->getTexture(), { 0, 0, Pilon::PILON_WIDTH, -Pilon::PILON_HEIGHT }, pilon2->getBottomPos(), WHITE);
        } else {
            DrawText("Game over", 0, 0, 25, BLACK);
            DrawText(TextFormat("Your score is: %d", score), 0, 0, 25, BLACK);
        }
        EndDrawing();
    }

    delete pilon1;
    delete pilon2;

    UnloadTexture(background);
    UnloadTexture(bird);
    CloseWindow();
    return 0;
}
