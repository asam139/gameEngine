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

#include "Text2D.h"
#include "Tools.h"

#include "Pad.h"
#include "Ball.h"

#include "GameManager.h"

unsigned int  kScreenWidth = 800, kScreenHeight = 800;

///////////////////////////////////////
// Shader
std::shared_ptr<Shader> shader;

// SceneGraph
std::shared_ptr<SceneGraph> sceneGraph;

// Camera
Camera* camera;

// Light
GameObject *lightGameObject;

//GameManager
std::shared_ptr<GameManager> gameManager;

///////////////////////////////////////
const unsigned int ballCount = 1;
const unsigned int levelColumns = 10;
const unsigned int levelRows = 5;
const unsigned int blockCount = levelColumns * levelRows;

const float widthEdges = 20.0f;
const float heightEdges = 10.0f;
const float widthWall = 1.0f;
const float widthPad = 2.0f;
const float widthBlock = 2.0f;
const float radiusBall = 0.3f;

const float padVelocity = 15.0f;
glm::vec3 ballVelocity = glm::vec3(7.5f, 7.5f, 0.0f);

GameObject* leftWall;
GameObject* rightWall;
GameObject* upperWall;
GameObject* ground;
Pad* pad;
Ball* ball;

GameObject *levelBlocks[blockCount];

///////////////////////////////////////

// To control time
static float deltaTime = 0.0f;

// Mouse
bool firstMouse = true;
float lastX = (float)kScreenWidth / 2.f;
float lastY = (float)kScreenHeight / 2.f;

//////////////////////////////////////
// Declaration

void menuKeyControl(GLFWwindow *window);
void gameKeyControl(GLFWwindow *window);
void winKeyControl(GLFWwindow *window);
void loseKeyControl(GLFWwindow *window);
void loopKeyControl(GLFWwindow *window);

void freeOpenGLProgram();
void generateLevelBlocks();
void newBall();
void initGame();

void runGame(GLFWwindow *window);
void drawMenu(GLFWwindow *window);
void drawWin(GLFWwindow *window);
void drawLose(GLFWwindow *window);
void draw(GLFWwindow *window);

//////////////////////////////////////

void loopKeyControl(GLFWwindow *window) {
    switch (gameManager->getGameState()) {
        case GameManager::GameState::Menu:
            menuKeyControl(window);
            break;
        case GameManager::GameState::Game:
            gameKeyControl(window);
            break;
        case GameManager::GameState::Win:
            winKeyControl(window);
            break;
        case GameManager::GameState::Lose:
            loseKeyControl(window);
            break;
    }
}

void draw(GLFWwindow *window) {
    switch (gameManager->getGameState()) {
        case GameManager::GameState::Menu:
            drawMenu(window);
            break;
        case GameManager::GameState::Game:
            runGame(window);
            break;
        case GameManager::GameState::Win:
            drawWin(window);
            break;
        case GameManager::GameState::Lose:
            drawLose(window);
            break;
    }
}

// Resize callback
void framebufferSizeCallback(GLFWwindow* window, const GLint width, const int32_t height) {
    kScreenWidth = static_cast<float>(width);
    kScreenHeight = static_cast<float>(height);
    if (camera) {
        camera->setAspect(kScreenWidth/kScreenHeight);
    }

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

    if (camera) {
        camera->handleMouseMovement(xOffset, yOffset);
    }
}

// Scroll callback
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    if (camera) {
        camera->handleMouseScroll(static_cast<const float>(yOffset));
    }
}



void menuKeyControl(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        initGame();
        gameManager->setGameState(GameManager::GameState::Game);
    }
}

void gameKeyControl(GLFWwindow *window) {
    //Control
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }

    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        initGame();
        return;
    }

    // Camera
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
    if (camera) {
        camera->handleKeyboard(movementMask, deltaTime);
    }


    // Pad
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        gameManager->setPause(!gameManager->getPause());
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        pad->setVelocityX(-padVelocity);
    } else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        pad->setVelocityX(padVelocity);
    } else {
        pad->setVelocityX(0.0f);
    }
}

void winKeyControl(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        initGame();
        gameManager->setGameState(GameManager::GameState::Game);
    }
}

void loseKeyControl(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        initGame();
        gameManager->setGameState(GameManager::GameState::Game);
    }
}


//////////////////////////////////

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
        return -1;
    }

    //GameManager
    gameManager = std::shared_ptr<GameManager>(new GameManager());

    ///////////////////////////
    initText2D("../textures/text.png");

    // Resize callback
    glfwSetFramebufferSizeCallback(window, &framebufferSizeCallback);

    // Mouse callback
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Scroll callback
    glfwSetScrollCallback(window, scrollCallback);

    ///////////////////////////

    // To control FPS
    const float maxFPS = 60.f;
    const float maxPeriod = 1.f / maxFPS;
    float lastTime = 0.0;
    while (!glfwWindowShouldClose(window)) { //Loop until user closes the window+
        auto time = static_cast<float>(glfwGetTime());
        deltaTime = time - lastTime;
        if( deltaTime >= maxPeriod ) {
            lastTime = time;
            //////////////////////////////
            // Code here gets called with max FPS
            //////////////////////////////
            loopKeyControl(window);
            draw(window);

            // Poll for and process events
            glfwPollEvents();
        }
    }

    freeOpenGLProgram();

    glfwTerminate();
    return 0;
}


void initGame() {
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

    ///////////////////////////
    gameManager->resetGame();

    ///////////////////////////
    // SceneGraph
    auto gameObjectRoot_ptr = std::shared_ptr<GameObject>(new GameObject());
    GameObject& gameObjectRoot = *gameObjectRoot_ptr;
    sceneGraph = std::shared_ptr<SceneGraph>(new SceneGraph(gameObjectRoot_ptr));


    ///////////////////////////
    // Create program
    shader = std::shared_ptr<Shader>(new Shader ("../shader/phongVertexShader.glsl", "../shader/phongFragmentShader.glsl"));

    ///////////////////////////
    // Create White Texture
    auto defaultTexture_ptr = std::shared_ptr<Texture>(new Texture("../textures/whiteTex.png", GL_RGB));

    // Creatte Other Textures
    auto diffTexture_ptr = std::shared_ptr<Texture>(new Texture("../textures/diffuseTex.jpg", GL_RGB));
    auto specTexture_ptr = std::shared_ptr<Texture>(new Texture("../textures/specularTex.jpg", GL_RGB));
    auto emissionTexture_ptr = std::shared_ptr<Texture>(new Texture("../textures/emissiveTex.jpg", GL_RGB));


    ///////////////////////////
    // Configure Camera
    // Camera
    auto cameraGO_ptr = std::shared_ptr<GameObject>(new GameObject());
    cameraGO_ptr->getTransform().setPosition(glm::vec3(0.0f, 2.0f, 20.0f));
    cameraGO_ptr->AddComponent<Camera>("Camera", cameraGO_ptr.get());
    camera = cameraGO_ptr->GetComponent<Camera>();
    camera->setAspect(kScreenWidth/kScreenHeight);
    camera->setMovementAxis(MovementAxisX | MovementAxisY | MovementAxisZ);
    gameObjectRoot.AddChild(std::move(cameraGO_ptr));

    ///////////////////////////
    // Create Objects

    // Material
    auto material_ptr = std::shared_ptr<Material>(new Material(shader));
    material_ptr->setAmbientColor(glm::vec3(0.25f));
    material_ptr->setDiffuseColor(glm::vec3(1.0f, 0.0f, 0.0f));
    material_ptr->setDiffuseTexture(defaultTexture_ptr);
    material_ptr->setSpecularColor(glm::vec3(1.0f));
    material_ptr->setSpecularTexture(defaultTexture_ptr);
    material_ptr->setShininess(32.0f);
    material_ptr->setEmissionActive(false);

    // Left Wall
    auto leftWall_ptr = std::unique_ptr<Cube>(new Cube(glm::vec3(0.0f), 1.f));
    leftWall_ptr->getTransform().setPosition(glm::vec3(-0.5f * (widthEdges + widthWall), 0.0f, 0.0f));
    leftWall_ptr->getTransform().setScale(glm::vec3(widthWall, heightEdges, widthWall));
    auto renderer = leftWall_ptr->GetComponent<Renderer>();
    renderer->setMaterial(material_ptr);
    leftWall_ptr->AddComponent<BoxCollider>("BoxCollider", leftWall_ptr.get());

    leftWall = (GameObject *)leftWall_ptr.get();
    gameObjectRoot.AddChild(std::move(leftWall_ptr));

    auto rightWall_ptr = std::unique_ptr<Cube>(new Cube(glm::vec3(0.0f), 1.f));
    rightWall_ptr->getTransform().setPosition(glm::vec3(0.5f * (widthEdges + widthWall), 0.0f, 0.0f));
    rightWall_ptr->getTransform().setScale(glm::vec3(widthWall, heightEdges, widthWall));
    renderer = rightWall_ptr->GetComponent<Renderer>();
    renderer->setMaterial(material_ptr);
    rightWall_ptr->AddComponent<BoxCollider>("BoxCollider", rightWall_ptr.get());

    rightWall = (GameObject *)rightWall_ptr.get();
    gameObjectRoot.AddChild(std::move(rightWall_ptr));

    auto upperWall_ptr = std::unique_ptr<Cube>(new Cube(glm::vec3(0.0f), 1.f));
    upperWall_ptr->getTransform().setPosition(glm::vec3(0.0f, 0.5f * (heightEdges + widthWall), 0.0f));
    upperWall_ptr->getTransform().setScale(glm::vec3(widthEdges + 2.0f * widthWall, widthWall, widthWall));
    renderer = upperWall_ptr->GetComponent<Renderer>();
    renderer->setMaterial(material_ptr);
    upperWall_ptr->AddComponent<BoxCollider>("BoxCollider", upperWall_ptr.get());

    upperWall = (GameObject *)upperWall_ptr.get();
    gameObjectRoot.AddChild(std::move(upperWall_ptr));

    auto ground_ptr = std::unique_ptr<Cube>(new Cube(glm::vec3(0.0f), 1.f));
    ground_ptr->getTransform().setPosition(glm::vec3(0.0f, -0.5f * (heightEdges + widthWall), 0.0f));
    ground_ptr->getTransform().setScale(glm::vec3(widthEdges + 2.0f * widthWall, widthWall, widthWall));
    renderer = ground_ptr->GetComponent<Renderer>();
    renderer->setMaterial(material_ptr);
    ground_ptr->AddComponent<BoxCollider>("BoxCollider", ground_ptr.get());

    ground = (GameObject *)ground_ptr.get();
    gameObjectRoot.AddChild(std::move(ground_ptr));


    // Pad
    material_ptr = std::shared_ptr<Material>(new Material(shader));
    material_ptr->setAmbientColor(glm::vec3(0.25f));
    material_ptr->setDiffuseColor(glm::vec3(0.0f, 0.0f, 1.0f));
    material_ptr->setDiffuseTexture(defaultTexture_ptr);
    material_ptr->setSpecularColor(glm::vec3(1.0f));
    material_ptr->setSpecularTexture(defaultTexture_ptr);
    material_ptr->setShininess(32.0f);
    material_ptr->setEmissionActive(false);

    auto pad_ptr = std::unique_ptr<Pad>(new Pad(glm::vec3(0.0f), 1.f));
    const float heightPad = 0.5f * widthWall;
    pad_ptr->getTransform().setPosition(glm::vec3(0.0f, -0.5 * (heightEdges - heightPad), 0.0f));
    pad_ptr->getTransform().setScale(glm::vec3(widthPad, heightPad, heightPad));
    renderer = pad_ptr->GetComponent<Renderer>();
    renderer->setMaterial(material_ptr);
    pad_ptr->AddComponent<BoxCollider>("BoxCollider", pad_ptr.get());

    pad_ptr->setMinX(-0.5f * (widthEdges - widthPad));
    pad_ptr->setMaxX(0.5f * (widthEdges - widthPad));

    pad = pad_ptr.get();
    gameObjectRoot.AddChild(std::move(pad_ptr));

    //////////////////////////
    // Ball
    material_ptr = std::shared_ptr<Material>(new Material(shader));
    material_ptr->setAmbientColor(glm::vec3(0.25f));
    material_ptr->setDiffuseColor(glm::vec3(0.0f, 1.0f, 1.0f));
    material_ptr->setDiffuseTexture(defaultTexture_ptr);
    material_ptr->setSpecularColor(glm::vec3(1.0f));
    material_ptr->setSpecularTexture(defaultTexture_ptr);
    material_ptr->setShininess(32.0f);
    material_ptr->setEmissionActive(false);

    auto ball_ptr = std::shared_ptr<Ball>(new Ball(glm::vec3(0.0f, 0.0f, 0.0f), 1.f));
    ball_ptr->getTransform().setPosition(glm::vec3(0.0f, -0.5 * (heightEdges - heightPad) + 0.5 * heightPad + radiusBall, 0.0f));
    ball_ptr->getTransform().setScale(glm::vec3(radiusBall));
    renderer = ball_ptr->GetComponent<Renderer>();
    renderer->setMaterial(material_ptr);
    ball_ptr->AddComponent<SphereCollider>("SphereCollider", ball_ptr.get());

    ball_ptr->setVelocity(ballVelocity);
    ball_ptr->upperWall = upperWall;
    ball_ptr->leftWall = leftWall;
    ball_ptr->rightWall = rightWall;
    ball_ptr->ground = ground;
    ball_ptr->pad = pad;
    ball_ptr->gameManager = gameManager.get();

    ball = ball_ptr.get();
    gameObjectRoot.AddChild(std::move(ball_ptr));

    //////////////////////////
    // Sphere as Light
    auto sphere_ptr = std::shared_ptr<Sphere>(new Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 1.f));
    sphere_ptr->getTransform().setPosition(glm::vec3(0.0f, 2.5f, 25.0f));
    sphere_ptr->getTransform().setScale(glm::vec3(0.3f));

    auto lightRRenderer = sphere_ptr->GetComponent<Renderer>();
    auto lightRMaterial_ptr = std::unique_ptr<Material>(new Material(shader));
    // Special configuration to draw Object as light source
    lightRMaterial_ptr->setAmbientColor(glm::vec3(1.0f));
    lightRMaterial_ptr->setDiffuseColor(glm::vec3(1.0f));
    lightRMaterial_ptr->setDiffuseTexture(defaultTexture_ptr);
    lightRMaterial_ptr->setSpecularColor(glm::vec3(0.0f));
    lightRMaterial_ptr->setSpecularTexture(defaultTexture_ptr);
    lightRMaterial_ptr->setShininess(32.0f);

    lightRRenderer->setMaterial(std::move(lightRMaterial_ptr));

    // Create Light
    sphere_ptr->AddComponent<Light>("Light", sphere_ptr.get());

    auto lightRef = sphere_ptr->GetComponent< Light >();
    lightRef->setAmbientColor(glm::vec3(0.8f));
    lightRef->setDiffuseColor(glm::vec3(0.8f));
    lightRef->setSpecularColor(glm::vec3(0.5f));

    lightGameObject = sphere_ptr.get();
    gameObjectRoot.AddChild(std::move(sphere_ptr));
    //////////////////////////

    generateLevelBlocks();
}

void generateLevelBlocks() {
    const float heightBlock = 0.5f * widthWall;
    for (int i = 0; i < levelRows; i++) {
        for (int j = 0; j < levelColumns; j++) {
            auto material_ptr = std::shared_ptr<Material>(new Material(shader));
            material_ptr->setAmbientColor(glm::vec3(0.25f));
            material_ptr->setDiffuseColor(glm::vec3(randomFloat(), randomFloat(), randomFloat()));
            material_ptr->setSpecularColor(glm::vec3(1.0f));
            material_ptr->setShininess(32.0f);
            material_ptr->setEmissionActive(false);

            auto block_ptr = std::unique_ptr<Cube>(new Cube(glm::vec3(0.0f), 1.f));
            block_ptr->getTransform().setPosition(glm::vec3(0.5f * widthEdges - (0.5f + j) * widthBlock, 0.5 * (heightEdges - heightBlock)- 0.5f * i, 0.0f));
            block_ptr->getTransform().setScale(glm::vec3(widthBlock, heightBlock, heightBlock));
            auto renderer = block_ptr->GetComponent<Renderer>();
            renderer->setMaterial(material_ptr);
            block_ptr->AddComponent<BoxCollider>("BoxCollider", block_ptr.get());

            // Save ref
            levelBlocks[levelColumns * i + j] = block_ptr.get();

            // Add to Root
            sceneGraph->getRoot()->AddChild(std::move(block_ptr));
        }
    }
}

void newBall () {
    const float heightPad = 0.5f * widthWall;
    pad->getTransform().setPosition(glm::vec3(0.0f, -0.5 * (heightEdges - heightPad), 0.0f));

    ball->getTransform().setPosition(glm::vec3(0.0f, -0.5 * (heightEdges - heightPad) + 0.5 * heightPad + radiusBall, 0.0f));
    ball->setVelocity(ballVelocity);
    ball->setActive(true);
}

void runGame(GLFWwindow *window) {
    if(!gameManager->getPause()) {
        sceneGraph->update(deltaTime);

        if (!ball->isActive()) {
            unsigned int lives = gameManager->getLives();
            if (lives > 1) {
                lives--;
                gameManager->setLives(lives);
                newBall();
            } else {
                gameManager->setGameState(GameManager::GameState::Lose);
            }

        } else {
            bool hasActiveBlocks = false;
            for (int i = 0; i < blockCount; ++i) {
                GameObject* block = levelBlocks[i];
                if (block->isActive()){
                    hasActiveBlocks = true;
                    break;
                }
            }
            if (!hasActiveBlocks) {
                gameManager->setGameState(GameManager::GameState::Win);
            }

        }
    }


    GameObject& root = *sceneGraph->getRoot();
    GameObject& lightObject = *lightGameObject;
    camera->render(root, lightObject);

    char livesString[100] = "Lives:";
    char livesBuffer[100];
    sprintf(livesBuffer, "%d", gameManager->getLives());
    strcat(livesString, livesBuffer);
    printText2D(livesString, 600, 570, 20);

    char pointsString[100] = "Points:";
    char pointsBuffer[100];
    sprintf(pointsBuffer, "%d", gameManager->getPoints());
    strcat(pointsString, pointsBuffer);
    printText2D(pointsString, 580, 550, 20);

    if(gameManager->getPause()) {
        printText2D("PAUSE", 250, 300, 60);
    }
    printText2D("esc - exit", 10, 570, 20);
    printText2D("p - pause", 10, 550, 20);
    printText2D("r - restart", 10, 530, 20);

    //Swap front and back buffers
    glfwSwapBuffers(window);
}

void drawMenu(GLFWwindow *window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    char string[] = "Press Enter key to start ...";
    printText2D(string , 130, 300, 20);

    glfwSwapBuffers(window);
}

void drawWin(GLFWwindow *window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    printText2D("You win !", 100, 300, 60);
    printText2D("Press Enter key to restart or esc to exit", 100, 250, 15);

    glfwSwapBuffers(window);
}
void drawLose(GLFWwindow *window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    printText2D("You lose !", 100, 300, 60);
    printText2D("Press Enter key to restart or esc to exit", 100, 250, 15);

    glfwSwapBuffers(window);
}

void freeOpenGLProgram() {
    cleanupText2D();
}
