//
// Created by Saul Moreno Abril on 16/01/2018.
//

#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Default Camera Values
const float kYaw = -90.0f;

const float kMaxPitch = 89.f;
const float kMinPitch = -89.f;
const float kPitch = 0.0f;

const float kSpeed = 5.f;

const float kSensitivity = 0.1f;

const float kMaxFov = 60.f;
const float kMinFov = 1.f;
const float kFov = kMaxFov;

class Camera {
public:
    //Possible options for camera movement
    enum Movement {
        None = 0u << 0,
        Forward = 1u << 0,
        Backward = 1u << 1,
        Left = 1u << 2,
        Right = 1u << 3,
    };
    Camera(); //Empty Constructor
    ~Camera(); //Destructor

    //Constructor with Vectors
    Camera(const glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           const float pitch = kPitch);

    //Constructor with Scalars
    Camera(const float posX, const float posY, const float posZ,
           const float upX, const float upY, const float upZ,
           const float pitch);

    //Returns current view matrix
    glm::mat4 getViewMatrix() const;
    glm::vec3  getPosition() const;
    float getFOV() const; //Returns the FOV

    //Process input from keyboard
    void handleKeyboard(const Movement direction, const float deltaTime);

    //Process mouse movement
    void handleMouseMovement(const float xoffset, const float yoffset,
                             const bool constrainPitch = true);
    //Process mouse scroll
    void handleMouseScroll(const float yoffset);

private:
    void updateCameraVectors(); //Calculates front vector
    glm::vec3 _position, _front, _up, _right, _worldUp; // Camera Attributes
    float _yaw, _pitch; // Euler Angles
    float _fov; // Camera options
};


#endif //GAMEENGINE_CAMERA_H
