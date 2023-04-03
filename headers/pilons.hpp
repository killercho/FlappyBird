#include "constants.hpp"
#include <raylib.h>

#ifndef PILON
#define PILON

class Pilon {
private:
    Texture2D pilon;
    Vector2 topPos;
    Vector2 bottomPos;
    Vector2 scorePos;

    Rectangle pilonTopHitbox;
    Rectangle pilonBottomHitbox;
    Rectangle scoreHitbox;

    void initPilonPositions(float); // Initialises all vectors with a given x and a random y
    void updateHitboxes();          // Updates the hitboxes on every move called

public:
    static const int HOLE_SIZE = 150; // optimal for game - 100
    static const int PILON_HEIGHT = 620;
    static const int PILON_WIDTH = 52;
    static const int SCORE_HEIGHT = HOLE_SIZE;
    static const int SCORE_WIDTH = 1;
    static const int MINY = 120;
    static const int MAXY = 450;

    Pilon(const char*, float); // Constructor setting the initial textire and the x value
    ~Pilon();                  // Destructor unloading the pilon texture

    void movePilon(int); // Function moving the pilon with a x value, also includes the chage of sides

    Texture2D getTexture() const; // Returns the texture

    Rectangle getTopHitbox() const;    // Returns the top hitbox
    Rectangle getBottomHitbox() const; // Returns the top hitbox
    Rectangle getScoreHitbox() const;  // Returns the top hitbox

    Vector2 getTopPos() const;    // Returns the top position
    Vector2 getBottomPos() const; // Returns the top position
    Vector2 getScorePos() const;  // Returns the top position
};

#endif
