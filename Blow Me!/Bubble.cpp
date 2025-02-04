//tmp header for move
#include <iostream>
#include <algorithm>
#include <raylib.h>
#include "Bubble.hpp"

void Bubble::show(int64_t& globalFrames)
{
    if (!isDead) this->display(globalFrames);
}

Bubble::Bubble(float radius_, float velocity_,
    int scrH, const char* path, Vector2 pos, int frameSpd,
    int frameCnt, float velocityX, bool shouldInvert, float scale) : Entity(path, pos, frameSpd,
   frameCnt,  velocityX,  shouldInvert,  scale), maxHeigth(0), minHeight(scrH)
{
    position.x = pos.x;
    position.y = pos.y;
    radius = radius_ * scale;
    velocity = velocity_;
    weight_factor = 1;
}

Bubble::Bubble(float radius_, float velocity_, 
    int scrH, Texture2D & txtr, Vector2 pos, int frameSpd,
    int frameCnt, float velocityX, bool shouldInvert, float scale) : Entity(txtr, pos, frameSpd,
   frameCnt,  velocityX,  shouldInvert,  scale), maxHeigth(0), minHeight(scrH)
{
    position.x = pos.x;
    position.y = pos.y;
    radius = radius_ * scale;
    velocity = velocity_;
    weight_factor = 1;
}

Bubble::~Bubble()
{
}

void Bubble::move()
{
    position.y += velocity;
    if (position.y < maxHeigth)
        position.y = maxHeigth;
    else if (position.y + radius > minHeight)
        position.y = minHeight - radius;
}

std::pair<bool, enemyType> Bubble::checkCollisionWithEntity(EntityQueue& eq)
{
    //bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);
    auto res = std::make_pair<bool, enemyType>(false, DUCK);
    auto queue = eq.getQueue();
    int queueSize = queue.size();
    int counter = 0;
    while (counter < queueSize)
    {
        auto queueElem = queue.front();
        queue.pop();
        queue.push(queueElem);
        
        if (CheckCollisionCircleRec(position, radius, queueElem.first->getCollider()))
        {
            res = { true, queueElem.second };
            return res;
        }
        counter++;
    }
    return res;
}

void Bubble::manageWeightFactor()
{
    if (weight_factor != 1.0f)
    {
        framesElapsedSinceWeightFactorChanged++;
        if (framesElapsedSinceWeightFactorChanged >= 90)
        {
            changeWeightFactor(1.f);
            framesElapsedSinceWeightFactorChanged = 0;
        }
    }
}

void Bubble::checkCollision( int screenHeight, EntityQueue& eq)
{
    auto entityCollisonResult = checkCollisionWithEntity(eq);

    if (position.y - radius / 2 <= 0 
        || position.y + radius + 1 >= screenHeight 
        || (entityCollisonResult.first ))
    {
        // DrawRectangle(0, 0, 1000, 900, RED);
        

        if (entityCollisonResult.second == CLOUD)
        {
            changeWeightFactor(3.5f);
        }
        else
        {
            isDead = true;
        }

        // std::cout << "collided" << std::endl;
    }

}

void Bubble::checkFanInfluence(Fan& fan)
{
    if(fan.checkCollision(position.x + radius/2))
    {
        if (fan.getFanState() == WIND)
        {
            velocity += VELOCITY_UP * (1.f / weight_factor) * 0.1f;
        } 
    }
    else
    {
        velocity += VELOCITY_DOWN * ( weight_factor) * 0.1f;
    }
    velocity = std::clamp(velocity, -6.f, 4.5f);
}




//void Bubble::show()
//{
//    std::cout <<"y: "<< position.y << std::endl;
//}

void Bubble::update(Fan& fan)
{
    checkFanInfluence(fan);
    manageWeightFactor();
    move();
}
