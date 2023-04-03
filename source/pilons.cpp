#include "../headers/pilons.hpp"
#include <raylib.h>

void Pilon::initPilonPositions(float x)
{
    int randomOffcet = GetRandomValue(Pilon::MINY, Pilon::MAXY);
    topPos = { x, (float)(randomOffcet - Pilon::PILON_HEIGHT - Pilon::HOLE_SIZE) };
    bottomPos = { x, (float)(randomOffcet) };
    scorePos = { x, (float)(randomOffcet - Pilon::PILON_HEIGHT) };
}

void Pilon::updateHitboxes()
{
    pilonTopHitbox = (Rectangle) {
        topPos.x,
        topPos.y,
        PILON_WIDTH,
        PILON_WIDTH,
    };

    pilonBottomHitbox = (Rectangle) {
        bottomPos.x,
        bottomPos.y,
        PILON_WIDTH,
        PILON_WIDTH,
    };

    scoreHitbox = (Rectangle) {
        scorePos.x,
        scorePos.y,
        PILON_WIDTH,
        PILON_WIDTH,
    };
}

Pilon::Pilon(const char* pilonTexture, float x)
{
    pilon = LoadTexture(pilonTexture);
    initPilonPositions(x);
}

Pilon::~Pilon()
{
    UnloadTexture(pilon);
}

void Pilon::movePilon(int speed)
{
    topPos.x -= speed;
    bottomPos.x -= speed;
    scorePos.x -= speed;

    if (topPos.x <= -PILON_WIDTH)
        initPilonPositions(SCREEN_WIDTH + PILON_WIDTH);

    updateHitboxes();
}

Texture2D Pilon::getTexture() const
{
    return pilon;
}

Rectangle Pilon::getTopHitbox() const
{
    return pilonTopHitbox;
}

Rectangle Pilon::getBottomHitbox() const
{
    return pilonBottomHitbox;
}

Rectangle Pilon::getScoreHitbox() const
{
    return scoreHitbox;
}

Vector2 Pilon::getTopPos() const
{
    return topPos;
}

Vector2 Pilon::getBottomPos() const
{
    return bottomPos;
}

Vector2 Pilon::getScorePos() const
{
    return scorePos;
}
