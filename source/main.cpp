#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define  STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

#include "shader.h"
#include "Camera.h"

#include "Cube.h"
#include "Plane.h"

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
glm::vec3 cubePosition = glm::vec3(1.0f, 0.0f, 0.0f);

// Light
glm::vec3 lightPosition = glm::vec3(-1.0f, 2.5f, -5.0f);

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
void handleInput(GLFWwindow* window, const Shader& shader) {

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
void render(const Plane& plane, const Cube& cube, const Shader& shader, const GLuint tex) {
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(camera.getFOV()), (float)kScreenWidth / (float)kScreenHeight, 0.1f, 100.f);
    shader.set("view", camera.getViewMatrix());
    shader.set("projection", projection);

    camera.setMovementAxis(MovementAxisX | MovementAxisY | MovementAxisZ);

    /////////////////////////////////
    // Plane
    ////////////////////////////////
    glBindVertexArray(plane.getVAO());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    glm::mat4 planeModel = glm::mat4(1.0f);
    planeModel = glm::translate(planeModel, planePosition);
    planeModel = glm::scale(planeModel, glm::vec3(10.f, 1.f, 10.f));
    shader.set("model", planeModel);

    shader.set("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    glDrawElements(GL_TRIANGLES, plane.getIndecesSize(), GL_UNSIGNED_INT, nullptr);

    // Duplicate code to learn easily
    /////////////////////////////////
    // Light
    ////////////////////////////////
    glBindVertexArray(cube.getVAO());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPosition);
    lightModel = glm::scale(lightModel, glm::vec3(0.3f));
    shader.set("model", lightModel);

    shader.set("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    shader.set("material.ambient", 1.0f, 1.0f, 1.0f);

    glDrawElements(GL_TRIANGLES, cube.getIndecesSize(), GL_UNSIGNED_INT, nullptr);


    /////////////////////////////////
    // Cube
    ////////////////////////////////
    glBindVertexArray(cube.getVAO());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    glm::mat4 cubeModel = glm::mat4(1.0f);
    cubeModel = glm::translate(cubeModel, cubePosition);
    cubeModel = glm::translate(cubeModel, cubePosition);
    shader.set("model", cubeModel);

    shader.set("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    glm::mat3 cNormalMat = glm::inverse(glm::transpose(glm::mat3(cubeModel)));
    shader.set("normalMat", cNormalMat);
    shader.set("lightPos", lightPosition);
    shader.set("lightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    shader.set("viewPos", camera.getPosition());

    shader.set("material.ambient", 1.0f, 0.5f, 0.3f);
    shader.set("material.diffuse", 1.0f, 0.5f, 0.3f);
    shader.set("material.specular", 0.5f, 0.5f, 0.5f);
    shader.set("material.shininess", 32.0f);

    glDrawElements(GL_TRIANGLES, cube.getIndecesSize(), GL_UNSIGNED_INT, nullptr);
}

GLuint createTexture (const char* path, GLenum type) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLint width, height, nChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    } else {
        std::cout << "Failed To Load Texture" << path << std::endl;
    }

    return texture;
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Scroll callback
    glfwSetScrollCallback(window, onScroll);

    ///////////////////////////
    // Configure stb
    stbi_set_flip_vertically_on_load(true);

    ///////////////////////////

    ///////////////////////////
    // Create VBOs and VAOs
    ///////////////////////////
    Plane plane;
    Cube cube(glm::vec3(0.0f, -0.5f, 0.0f), 1.f);

    ///////////////////////////

    // Create program
    Shader shader("../shader/vertexShader.glsl", "../shader/fragmentShader.glsl");

    GLuint defaultTex = createTexture("../textures/whiteTex.png", GL_RGB);

    shader.use();
    shader.set("tex", defaultTex);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
            handleInput(window, shader);

            // Clear
            glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            //Render VAO
            render(plane, cube, shader, defaultTex);

            //Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }
    }

    ////////////////////////////
    // Delete Textures
    glDeleteTextures(1, &defaultTex);

    glfwTerminate();
    return 0;
}

