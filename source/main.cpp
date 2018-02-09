#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Camera.h"
#include "SceneGraph.h"

#include "Plane.h"
#include "Cube.h"
#include "Sphere.h"


//////////////////////////////////////
// Declaration

void runGame(GLFWwindow *window);
void menuKeyControl(GLFWwindow *window, int key, int scancode, int action, int mode);
void gameKeyControl(GLFWwindow *window, int key, int scancode, int action, int mode);
void winKeyControl(GLFWwindow *window, int key, int scancode, int action, int mode);
void loseKeyControl(GLFWwindow *window, int key, int scancode, int action, int mode);
//To test
void loopKeyControl(GLFWwindow *window);

void freeOpenGLProgram();
void generateLevelBlocks();
void initOpenGLProgram();

void drawSceneAndDetectCollisions(GLFWwindow *window, float padDeltaX, float ballDeltaX[], float ballDeltaY[]);
void drawMenu(GLFWwindow *window);
void drawWIN(GLFWwindow *window);
void drawLOSE(GLFWwindow *window);

//////////////////////////////////////

enum class GameState: unsigned int {
    Menu = 0,
    Game = 1,
    Win = 2,
    Lose = 3
};

GameState gameState = GameState::Menu;
bool pause = false;

unsigned int  kScreenWidth = 1024, kScreenHeight = 768;
const unsigned int ballCount = 1;
const unsigned int levelColumns = 7;
const unsigned int levelRows = 12;

float padVelocityX = 0.0f;

///////////////////////////////////////

Cube *leftWall;
Cube *rightWall;
Cube *upperWall;
Cube *ground;
Cube *pad;
Sphere *ball;

GameObject *levelBlocks[levelColumns * levelRows];

///////////////////////////////////////

// To control time
static float deltaTime = 0.0f;

// Camera
Camera camera(glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3(0.f, 1.f, 0.f), -10.f);

// Mouse
bool firstMouse = true;
float lastX = (float)kScreenWidth / 2.f;
float lastY = (float)kScreenHeight / 2.f;

//////////////////////////////////////


void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    switch (gameState) {
        case GameState::Menu:
            menuKeyControl(window, key, scancode, action, mode);
            break;
        case GameState::Game:

            gameKeyControl(window, key, scancode, action, mode);
            break;
        case GameState::Win:
            winKeyControl(window, key, scancode, action, mode);
            break;
        case GameState::Lose:
            loseKeyControl(window, key, scancode, action, mode);
            break;
    }
}

// Resize callback
void framebufferSizeCallck(GLFWwindow* window, const GLint width, const int32_t height) {
    kScreenWidth = static_cast<float>(width);
    kScreenHeight = static_cast<float>(height);
    camera.setAspect(kScreenWidth/kScreenHeight);

    glViewport(0, 0, width, height);
}

// Mouse callback
void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    // Initial values the first frame
    if (firstMouse) {
        lastX = static_cast<float> (xpos);
        lastY = static_cast<float> (ypos);
        firstMouse = false;
    }

    // Calc offset movement since last frame
    auto xOffset = static_cast<float> (xpos - lastX);
    // Reversed y-coords go from bottom to top
    auto yOffset = static_cast<float> (lastY - ypos);
    lastX = static_cast<float> (xpos);
    lastY = static_cast<float> (ypos);

    camera.handleMouseMovement(xOffset, yOffset);
}

// Scroll callback
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    camera.handleMouseScroll(static_cast<const float>(yOffset));
}



void menuKeyControl(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GL_TRUE);
            return;
        }
        gameState = GameState::Game;
        glfwSetTime(0);
    }
}


void gameKeyControl(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE)  {
            glfwSetWindowShouldClose(window, GL_TRUE);
            return;
        }
        if (key == GLFW_KEY_LEFT) {
            padVelocityX = 30;
        }
        if (key == GLFW_KEY_RIGHT) {
            padVelocityX = -30;
        }
        if (key == GLFW_KEY_P) {
            pause = !pause;
        }
        if( key == GLFW_KEY_R) {
            initOpenGLProgram();
            glfwSetTime(0);
        }
    }

    if (action == GLFW_RELEASE) {
        padVelocityX = 0;
    }
}

void winKeyControl(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GL_TRUE);
            return;
        }
        initOpenGLProgram();
        gameState = GameState::Game;
        glfwSetTime(0);
    }
}

void loseKeyControl(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
            return;
        }
        initOpenGLProgram();
        gameState = GameState::Game;
        glfwSetTime(0);
    }
}


//////////////////////////////////

// Handle Input
void loopKeyControl(GLFWwindow *window) {
    Movement movementMask = MovementNone;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        movementMask |= MovementForward;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        movementMask |= MovementBackward;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    movementMask |= MovementRight;
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        movementMask |= MovementLeft;
    }

    camera.handleKeyboard(movementMask, deltaTime);
}

int main (int argc, char *argv[]) {

    if (!glfwInit()) {       //Initialize the library
        std::cout << "Failed To Initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //Core Profile

    GLFWwindow *window;    //Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(kScreenWidth, kScreenHeight, "New Window", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed To Create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);  //Make the window's context current


    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {  //Init GLAD

        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Key callback
    glfwSetKeyCallback(window, keyCallback);

    // Resize callback
    glfwSetFramebufferSizeCallback(window, &framebufferSizeCallck);

    // Mouse callback
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Scroll callback
    glfwSetScrollCallback(window, scrollCallback);

    ///////////////////////////
    // Configure Camera
    camera.setAspect(kScreenWidth/kScreenHeight);
    camera.setMovementAxis(MovementAxisX | MovementAxisY | MovementAxisZ);

    ///////////////////////////
    // SceneGraph
    GameObject gameObjectRoot;
    SceneGraph sceneGraph(&gameObjectRoot);

    ///////////////////////////
    // Create program
    auto shader_ptr = std::shared_ptr<Shader>(new Shader ("../shader/phongVertexShader.glsl", "../shader/phongFragmentShader.glsl"));

    ///////////////////////////
    // Create White Texture
    auto defaultTexture_ptr = std::shared_ptr<Texture>(new Texture("../textures/whiteTex.png", GL_RGB));

    ///////////////////////////
    // Create Objects

    // Plane
    auto plane_ptr = std::unique_ptr<Plane>(new Plane());
    plane_ptr->getTransform().setPosition(glm::vec3(0.0f));
    plane_ptr->getTransform().setScale(glm::vec3(10.f, 1.0f, 10.f)); // Works with glm::vec3(10.0f)

    auto& planeRenderer = plane_ptr->GetComponent<Renderer>();

    auto planeMaterial_ptr = std::unique_ptr<Material>(new Material(shader_ptr));
    planeMaterial_ptr->setAmbientColor(glm::vec3(0.1f));
    planeMaterial_ptr->setDiffuseColor(glm::vec3(0.0f));
    planeMaterial_ptr->setDiffuseTexture(defaultTexture_ptr);
    planeMaterial_ptr->setSpecularColor(glm::vec3(.1f));
    planeMaterial_ptr->setSpecularTexture(defaultTexture_ptr);
    planeMaterial_ptr->setShininess(16.0f);

    planeRenderer.setMaterial(std::move(planeMaterial_ptr));

    gameObjectRoot.AddChild(std::move(plane_ptr));

    // Cube
    auto cube_ptr = std::unique_ptr<Cube>(new Cube(glm::vec3(0.0f, 0.0f, 0.0f), 1.f));
    cube_ptr->getTransform().setPosition(glm::vec3(0.0f, 0.5f, 0.0f));
    auto& cubeRenderer = cube_ptr->GetComponent<Renderer>();

    auto diffTexture_ptr = std::shared_ptr<Texture>(new Texture("../textures/diffuseTex.jpg", GL_RGB));
    auto specTexture_ptr = std::shared_ptr<Texture>(new Texture("../textures/specularTex.jpg", GL_RGB));
    auto emissionTexture_ptr = std::shared_ptr<Texture>(new Texture("../textures/emissiveTex.jpg", GL_RGB));

    auto cubeMaterial_ptr = std::shared_ptr<Material>(new Material(shader_ptr));

    cubeMaterial_ptr->setAmbientColor(glm::vec3(0.25f));
    cubeMaterial_ptr->setDiffuseColor(glm::vec3(1.0f));
    cubeMaterial_ptr->setDiffuseTexture(diffTexture_ptr);
    cubeMaterial_ptr->setSpecularColor(glm::vec3(1.0f));
    cubeMaterial_ptr->setSpecularTexture(specTexture_ptr);
    cubeMaterial_ptr->setShininess(32.0f);

    cubeMaterial_ptr->setEmissionActive(true);
    cubeMaterial_ptr->setEmissiveColor(glm::vec3(1.0f));
    cubeMaterial_ptr->setEmissiveTexture(emissionTexture_ptr);

    cubeRenderer.setMaterial(cubeMaterial_ptr);
    cube_ptr->AddComponent<BoxCollider>("BoxCollider", (GameObject *)cube_ptr.get());

    auto subCube_ptr = std::unique_ptr<Cube>(new Cube(glm::vec3(0.0f), 1.f));
    subCube_ptr->getTransform().setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
    subCube_ptr->getTransform().setRotation(M_PI_4, glm::vec3(0.f, 1.f, 0.f));

    auto& subCubeRenderer = subCube_ptr->GetComponent<Renderer>();
    subCubeRenderer.setMaterial(cubeMaterial_ptr);
    subCube_ptr->AddComponent<BoxCollider>("BoxCollider", (GameObject *)subCube_ptr.get());

    cube_ptr->AddChild(std::move(subCube_ptr));
    gameObjectRoot.AddChild(std::move(cube_ptr));

    //////////////////////////
    // Sphere as Light
    auto sphere_ptr = std::shared_ptr<Sphere>(new Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 1.f));
    sphere_ptr->getTransform().setPosition(glm::vec3(-1.0f, 2.5f, -5.0f));
    sphere_ptr->getTransform().setScale(glm::vec3(0.3f));

    auto& lightRRenderer = sphere_ptr->GetComponent<Renderer>();
    auto lightRMaterial_ptr = std::unique_ptr<Material>(new Material(shader_ptr));
    // Special configuration to draw Object as light source
    lightRMaterial_ptr->setAmbientColor(glm::vec3(1.0f));
    lightRMaterial_ptr->setDiffuseColor(glm::vec3(1.0f));
    lightRMaterial_ptr->setDiffuseTexture(defaultTexture_ptr);
    lightRMaterial_ptr->setSpecularColor(glm::vec3(0.0f));
    lightRMaterial_ptr->setSpecularTexture(defaultTexture_ptr);
    lightRMaterial_ptr->setShininess(32.0f);

    lightRRenderer.setMaterial(std::move(lightRMaterial_ptr));

    // Create Light
    sphere_ptr->AddComponent<Light>("Light", sphere_ptr.get());

    auto& lightRef = sphere_ptr->GetComponent< Light >();
    lightRef.setAmbientColor(glm::vec3(0.8f));
    lightRef.setDiffuseColor(glm::vec3(0.8f));
    lightRef.setSpecularColor(glm::vec3(0.5f));

    gameObjectRoot.AddChild(sphere_ptr);

    ///////////////////////////

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // To draw only the lines
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // To not draw back faces
    glCullFace(GL_BACK);
    // Enable Culling
    glEnable(GL_CULL_FACE);

    // Enable Depth
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    // To control FPS
    const float maxFPS = 60.f;
    const float maxPeriod = 1.f / maxFPS;
    // approx ~ 16.666 ms

    float lastTime = 0.0;


    while (!glfwWindowShouldClose(window)) { //Loop until user closes the window+
        auto time = static_cast<float>(glfwGetTime());
        deltaTime = time - lastTime;



        if( deltaTime >= maxPeriod ) {
            lastTime = time;
            //////////////////////////////
            // Code here gets called with max FPS
            //////////////////////////////

            // Loop Key Control
            loopKeyControl(window);


            // Clear
            glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            GameObject& root = *sceneGraph.root;
            GameObject& lightObject = *sphere_ptr;

            sceneGraph.update(deltaTime);

            camera.render(root, lightObject);

            //Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}


void initOpenGLProgram() {
    
}
