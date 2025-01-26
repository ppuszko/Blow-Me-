#ifndef BUBBLE_HPP
#define BUBBLE_HPP
#include <raylib.h>

#include "Fan.hpp"
#include "Entity.hpp"

class Bubble : public Entity
{
private:
    int maxHeigth = 20.0;
    int minHeight = 0.0;
    const float VELOCITY_UP = -2.0;
    const float VELOCITY_DOWN = 1.0;
    float radius;
    float velocity;
    float weight_factor;
    void checkFanInfluence(Fan& fan);
    void move();
    std::pair<bool, enemyType> checkCollisionWithEntity(EntityQueue& eq);
    bool shouldDisplay = true;
   

    //debug
   

public:
    Bubble(float radius_, float velocity_, int scrH, const char* path, Vector2 pos,
        int frameSpd, int frameCnt, float velocityX, bool shouldInvert, float scale = 1.f);
    Bubble(float radius_, float velocity_, int scrH, Texture2D & txtr, Vector2 pos,
        int frameSpd, int frameCnt, float velocityX, bool shouldInvert, float scale = 1.f);
    ~Bubble();
    void update(Fan& fan);
    void checkCollision(int screenHeight, EntityQueue& eq);
    void show(int64_t& globalframes);
};

#endif
