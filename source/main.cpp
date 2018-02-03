#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Camera.h"
#include "shader.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"

#include "Plane.h"
#include "Cube.h"
#include "Sphere.h"

#include "BitmaskEnum.h"

///////////////////////
// Static variables

const uint32_t kScreenWidth = 800;
const uint32_t kScreenHeight = 800;

// To control time
static float deltaTime = 0.0f;

// Camera
Camera camera(glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3(0.f, 1.f, 0.f), -10.f);

// Mouse
bool firstMouse = true;
float lastX = (float)kScreenWidth / 2.f;
float lastY = (float)kScreenHeight / 2.f;

// Plane
glm::vec3 planePosition = glm::vec3(0.0f, 0.0f, 0.0f);

// Cube
glm::vec3 cubePosition = glm::vec3(2.0f, 0.0f, 0.0f);


///////////////////////

// Resize callback
void onChangeFramebufferSize(GLFWwindow* window, const GLint width, const int32_t height) {
    glViewport(0, 0, width, height);
}


// Mouse callback

void onMouse(GLFWwindow* window, double xpos, double ypos) {
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
void onScroll(GLFWwindow* window, double xOffset, double yOffset) {
    camera.handleMouseScroll(static_cast<const float>(yOffset));
}

// Handle Input
void handleInput(GLFWwindow* window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        return;
    }

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

// Render
void render(Plane& plane, Cube& cube, Sphere& sphere, Light& light) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), (float)kScreenWidth / (float)kScreenHeight, 0.1f, 100.f);
    glm::mat4 view = camera.getViewMatrix();
    glm::vec3 cameraPos = camera.getPosition();

    light.configureShader();

    /////////////////////////////////
    // Plane
    ////////////////////////////////
    plane.setPosition(planePosition);
    plane.setScale(glm::vec3(10.f, 1.0f, 10.f)); // Works with glm::vec3(10.0f)
    plane.display(projection, view, cameraPos);

    /////////////////////////////////
    // Light
    ////////////////////////////////
    sphere.setPosition(light.getPosition());
    sphere.setScale(glm::vec3(0.3f));
    sphere.display(projection, view, cameraPos);

    /////////////////////////////////
    // Sphere
    ////////////////////////////////
    cube.setPosition(cubePosition);
    cube.setScale(glm::vec3(1.0f));
    cube.display(projection, view, cameraPos);
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

    // Resize callback
    glfwSetFramebufferSizeCallback(window, &onChangeFramebufferSize);

    // Mouse callback
    glfwSetCursorPosCallback(window, onMouse);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Scroll callback
    glfwSetScrollCallback(window, onScroll);

    ///////////////////////////

    ///////////////////////////
    // Configure Camera
    camera.setMovementAxis(MovementAxisX | MovementAxisY | MovementAxisZ);
    ///////////////////////////


    ///////////////////////////
    // Create program
    Shader phongShader("../shader/phongVertexShader.glsl", "../shader/phongFragmentShader.glsl");

    // Create Light
    Light light(&phongShader);
    light.setPosition(glm::vec3(-1.0f, 2.5f, -5.0f));
    light.setAmbientColor(glm::vec3(0.8f));
    light.setDiffuseColor(glm::vec3(0.8f));
    light.setSpecularColor(glm::vec3(0.5f));
    light.configureShader();

    ///////////////////////////
    // Create White Texture
    Texture defaultText("../textures/whiteTex.png", GL_RGB);

    ///////////////////////////
    // Create Objects
    ///////////////////////////
    Plane plane;
    Renderer* planeRenderer = plane.getRenderer();

    std::unique_ptr<Material> planeMaterial_ptr = std::unique_ptr<Material>(new Material(&phongShader));
    planeMaterial_ptr->setAmbientColor(glm::vec3(0.1f));
    planeMaterial_ptr->setDiffuseColor(glm::vec3(0.0f));
    planeMaterial_ptr->setDiffuseTexture(&defaultText);
    planeMaterial_ptr->setSpecularColor(glm::vec3(.1f));
    planeMaterial_ptr->setSpecularTexture(&defaultText);
    planeMaterial_ptr->setShininess(16.0f);

    planeRenderer->setMaterial(std::move(planeMaterial_ptr));


    Cube cube(glm::vec3(0.0f, -0.5f, 0.0f), 1.f);
    Renderer* cubeRenderer = cube.getRenderer();

    Texture diffText("../textures/diffuseTex.jpg", GL_RGB);
    Texture specText("../textures/specularTex.jpg", GL_RGB);

    std::unique_ptr<Material> cubeMaterial_ptr = std::unique_ptr<Material>(new Material(&phongShader));
    cubeMaterial_ptr->setAmbientColor(glm::vec3(0.25f));
    cubeMaterial_ptr->setDiffuseColor(glm::vec3(1.0f));
    cubeMaterial_ptr->setDiffuseTexture(&diffText);
    cubeMaterial_ptr->setSpecularColor(glm::vec3(1.0f));
    cubeMaterial_ptr->setSpecularTexture(&specText);
    cubeMaterial_ptr->setShininess(32.0f);

    cubeRenderer->setMaterial(std::move(cubeMaterial_ptr));


    Sphere lightR(glm::vec3(0.0f, -1.0f, 0.0f), 1.f);
    Renderer* lightRRenderer = lightR.getRenderer();

    std::unique_ptr<Material> lightRMaterial_ptr = std::unique_ptr<Material>(new Material(&phongShader));
    // Special configuration to draw Object as light source
    lightRMaterial_ptr->setAmbientColor(glm::vec3(1.0f));
    lightRMaterial_ptr->setDiffuseColor(glm::vec3(1.0f));
    lightRMaterial_ptr->setDiffuseTexture(&defaultText);
    lightRMaterial_ptr->setSpecularColor(glm::vec3(0.0f));
    lightRMaterial_ptr->setSpecularTexture(&defaultText);
    lightRMaterial_ptr->setShininess(32.0f);

    lightRRenderer->setMaterial(std::move(lightRMaterial_ptr));


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

            // Handle Input
            handleInput(window);

            // Clear
            glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            //Render VAO
            render(plane, cube, lightR, light);

            //Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}

