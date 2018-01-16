#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define  STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

#include "shader.h"

///////////////////////
// Static variables

const uint32_t kScreenWidth = 800;
const uint32_t kScreenHeight = 800;

// To control time
static double deltaTime = 0.0f;

///////////////////////

void onChangeFramebufferSize(GLFWwindow* window, const GLint width, const int32_t height) {
    glViewport(0, 0, width, height);
}

void handleInput(GLFWwindow* window, const Shader& shader) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }


    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {

    } else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {

    }
}

void render(const GLuint VAO, const uint size, const void * indices, const Shader& shader, const GLuint text0) {
    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, text0);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.f), glm::vec3(1.f, 0.f, 0.f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.f), (float)kScreenWidth / (float)kScreenHeight, 0.1f, 100.f);

    shader.set("model", model);
    shader.set("view", view);
    shader.set("projection", projection);

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.f, 0.f, 1.f));
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    shader.set("transform", trans);

    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, indices);
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

    glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3,  GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2,  GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

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

    glfwSetFramebufferSizeCallback(window, &onChangeFramebufferSize);


    ///////////////////////////
    // Configure stb
    stbi_set_flip_vertically_on_load(true);

    ///////////////////////////

    ///////////////////////////
    // Create VBOs and VAOs
    ///////////////////////////
    // Triangle
    GLint verticesSize = 32;
    GLfloat triangle_vertices[] = {
        .5f,    .5f,    0.f,        1.f,    0.f,    0.f,        1.f,    1.f,
        .5f,    -.5f,   0.f,        0.f,    1.f,    0.f,        1.f,    0.f,
        -0.5f,  -.5f,   0.f,        0.f,    0.f,    1.0f,       0.f,    0.f,
        -0.5f,  .5f,    0.f,        1.f,    1.f,    0.f,        0.f,    1.f
    };


    GLint  indicesSize = 6;
    GLuint triangle_indices[] = {
        0,  3,  1,
        1,  3,  2
    };

    GLuint triangle_VBO, triangle_EBO;
    GLuint triangle_VAO = createVertexData(triangle_vertices, verticesSize, triangle_indices, indicesSize,  &triangle_VBO, &triangle_EBO);
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

    // Enable Culling
    glEnable(GL_CULL_FACE);
    // To not draw back faces



    // To control FPS
    const double maxFPS = 60.0;
    const double maxPeriod = 1.0 / maxFPS;
    // approx ~ 16.666 ms

    double lastTime = 0.0;


    while (!glfwWindowShouldClose(window)) { //Loop until user closes the window+
        double time = glfwGetTime();
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
            glClear(GL_COLOR_BUFFER_BIT);


            //Render VAO
            render(triangle_VAO, verticesSize, nullptr, shader, text0);

            //Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }
    }

    ////////////////////////////
    // Delete VAO and VBO
    glDeleteVertexArrays(1, &triangle_VAO);
    glDeleteBuffers(1, &triangle_VBO);
    glDeleteBuffers(1, &triangle_EBO);
    ///////////////////////////

    ////////////////////////////
    // Delete Textures
    glDeleteTextures(1, &text0);

    glfwTerminate();
    return 0;
}
