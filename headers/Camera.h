//
// Created by Saul Moreno Abril on 16/01/2018.
//

#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BitmaskEnum.h"
#include "GameObject.h"

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

typedef enum  {
    MovementAxisX = 0x01,
    MovementAxisY = 0x02,
    MovementAxisZ = 0x04
} MovementAxis;
ENABLE_BITMASK_OPERATORS(MovementAxis)

//Possible options for camera movement
typedef enum  {
    MovementNone = 0x00,
    MovementForward = 0x01,
    MovementBackward = 0x02,
    MovementLeft = 0x04,
    MovementRight = 0x08
} Movement;
ENABLE_BITMASK_OPERATORS(Movement)

class Camera {
public:
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

    void setAspect(float aspect);
    float getAspect();

    //Returns current view matrix
    glm::mat4 getViewMatrix() const;
    glm::vec3  getPosition() const;
    float getFOV() const; //Returns the FOV

    // Modify Movement Axis
    void setMovementAxis(MovementAxis movementAxis);

    //Process input from keyboard
    void handleKeyboard(const Movement direction, const float deltaTime);

    //Process mouse movement
    void handleMouseMovement(const float xoffset, const float yoffset,
                             const bool constrainPitch = true);
    //Process mouse scroll
    void handleMouseScroll(const float yoffset);

    // Render
    void render(GameObject& root, GameObject& lightObject);

private:
    void updateCameraVectors(); //Calculates front vector
    glm::vec3 _position, _front, _up, _right, _worldUp; // Camera Attributes
    float _yaw, _pitch; // Euler Angles
    float _fov; // Camera options

    float _aspect = 1.0f;

    // Movement Axis Allow
    MovementAxis _movementAxis = static_cast<MovementAxis >(MovementAxisX | MovementAxisY| MovementAxisZ);
};

#endif //GAMEENGINE_CAMERA_H
