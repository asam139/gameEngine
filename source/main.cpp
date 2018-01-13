#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <iostream>

#include "../headers/shader.h"

void onChangeFramebufferSize(GLFWwindow* window, const GLint width, const int32_t height) {
    glViewport(0, 0, width, height);
}

void handleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void render(GLuint VAO, uint size, const void * indices, Shader& shader) {
    shader.use();
    glBindVertexArray(VAO);

    GLfloat time = (float)glfwGetTime();
    shader.set("time", time);

    GLfloat radius = 0.25f;
    shader.set("refPoint", glm::vec3(radius * cosf(time), radius * sinf(time), 0));

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
    window = glfwCreateWindow(800, 800, "New Window", nullptr, nullptr);
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

    // To draw only the lines
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Enable Culling
    glEnable(GL_CULL_FACE);
    // To not draw back faces
    glCullFace(GL_BACK);

    while (!glfwWindowShouldClose(window)) { //Loop until user closes the window
        // Handle Input
        handleInput(window);

        // Clear
        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Render VAO
        render(triangle_VAO, verticesSize, nullptr, shader);

        //Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    ////////////////////////////
    // Delete VAO and VBO
    glDeleteVertexArrays(1, &triangle_VAO);
    glDeleteBuffers(1, &triangle_VBO);
    glDeleteBuffers(1, &triangle_EBO);
    ///////////////////////////

    glfwTerminate();
    return 0;
}
