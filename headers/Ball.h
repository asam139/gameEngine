//
// Created by Saul Moreno Abril on 10/02/2018.
//

#ifndef GAMEENGINE_BALL_H
#define GAMEENGINE_BALL_H

#include "Sphere.h"
#include "GameManager.h"

class Ball : public Sphere {
public:
    Ball();
    Ball(const glm::vec3 center, const float radius);


    void setVelocity(glm::vec3 velocity);
    glm::vec3 getVelocity();

    virtual void update(const float deltaTime);
    virtual void collide(Collider* collider);


    GameObject* leftWall;
    GameObject* rightWall;
    GameObject* upperWall;
    GameObject* ground;
    GameObject* pad;
    GameManager* gameManager;

private:
    glm::vec3 _velocity = glm::vec3(0.0f);
};


#endif //GAMEENGINE_BALL_H
