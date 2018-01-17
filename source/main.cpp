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

///////////////////////
// Static variables

const uint32_t kScreenWidth = 800;
const uint32_t kScreenHeight = 800;

// To control time
static float deltaTime = 0.0f;

// Camera
Camera camera(glm::vec3(0.f, 0.f, 3.f));

// Mouse
bool firstMouse = true;
float lastX = (float)kScreenWidth / 2.f;
float lastY = (float)kScreenHeight / 2.f;

// Objects
glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};

///////////////////////

// Resize callback
void onChangeFramebufferSize(GLFWwindow* window, const GLint width, const int32_t height) {
    glViewport(0, 0, width, height);
}


// Mouse callback

void onMouse(GLFWwindow* window, double xpos, double ypos) {
    // Initial values the first frame
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    // Calc offset movement since last frame
    float xOffset = xpos - lastX;
    // Reversed y-coords go from bottom to top
    float yOffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.handleMouseMovement(xOffset, yOffset);
}

// Scroll callback
void onScroll(GLFWwindow* window, double xOffset, double yOffset) {
    camera.handleMouseScroll(yOffset);
}

// Handle Input
void handleInput(GLFWwindow* window, const Shader& shader) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    Camera::Movement movementMask = Camera::Movement::None;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        movementMask = (Camera::Movement)(movementMask | Camera::Movement::Forward);
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        movementMask = (Camera::Movement)(movementMask | Camera::Movement::Backward);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        movementMask = (Camera::Movement)(movementMask | Camera::Movement::Right);
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        movementMask = (Camera::Movement)(movementMask | Camera::Movement::Left);
    }

    camera.handleKeyboard(movementMask, deltaTime);
}

// Render
void render(const GLuint VAO, const uint size, const void * indices, const Shader& shader, const GLuint text0) {
    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, text0);


    glm::mat4 projection;
    projection = glm::perspective(glm::radians(camera.getFOV()), (float)kScreenWidth / (float)kScreenHeight, 0.1f, 100.f);

    shader.set("view", camera.getViewMatrix());
    shader.set("projection", projection);

    for (uint8_t i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 10.0f + (20.0f * i);
        model = glm::rotate(model, /*(float) glfwGetTime() **/ glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
        shader.set("model", model);
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, indices);
    }
}

GLuint createVertexData(GLfloat* vertices, GLuint vSize, GLuint* indices, GLuint iSize,  GLuint* VBO, GLuint* EBO) {
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, vSize * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2,  GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return VAO;
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
    // Cube
    GLint verticesSize = 120;
    GLfloat vertices[] = {
            // Position             // UVs
            -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, //Front
            0.5f, -0.5f, 0.5f,      1.0f, 0.0f,
            0.5f, 0.5f, 0.5f,       1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f,      0.0f, 1.0f,
            0.5f, -0.5f, 0.5f,      0.0f, 0.0f, //Right
            0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
            0.5f, 0.5f, -0.5f,      1.0f, 1.0f,
            0.5f, 0.5f, 0.5f,       0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, //Back
            -0.5f, 0.5f, -0.5f,     1.0f, 1.0f,
            0.5f, 0.5f, -0.5f,      0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,     1.0f, 0.0f, //Left
            -0.5f, 0.5f, 0.5f,      1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,     0.0f, 1.0f, //Bottom
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
            0.5f, -0.5f, 0.5f,      1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f,      0.0f, 0.0f, //Top
            0.5f, 0.5f, 0.5f,       1.0f, 0.0f,
            0.5f, 0.5f, -0.5f,      1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f,     0.0f, 1.0f
    };
    GLint  indicesSize = 36;
    GLuint indices[] = {
            0, 1, 2,        0, 2, 3, //Front
            4, 5, 6,        4, 6, 7, //Right
            8, 9, 10,       8, 10, 11, //Back
            12, 13, 14,     12, 14, 15, //Left
            16, 17, 18,     16, 18, 19, //Bottom
            20, 21, 22,     20, 22, 23 //Top
    };

    GLuint VBO, EBO;
    GLuint VAO = createVertexData(vertices, verticesSize, indices, indicesSize,  &VBO, &EBO);
    ///////////////////////////

    // Create program
    Shader shader("../shader/vertexShader.glsl", "../shader/fragmentShader.glsl");

    GLuint text0 = createTexture("../textures/animeMemesTexture.jpg", GL_RGB);

    shader.use();
    shader.set("texture1", 0);

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
    const float maxFPS = 60.0;
    const float maxPeriod = 1.0 / maxFPS;
    // approx ~ 16.666 ms

    float lastTime = 0.0;


    while (!glfwWindowShouldClose(window)) { //Loop until user closes the window+
        float time = glfwGetTime();
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
            render(VAO, indicesSize, nullptr, shader, text0);

            //Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }
    }

    ////////////////////////////
    // Delete VAO and VBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    ///////////////////////////

    ////////////////////////////
    // Delete Textures
    glDeleteTextures(1, &text0);

    glfwTerminate();
    return 0;
}
