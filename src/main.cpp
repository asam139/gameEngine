#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <iostream>

void onChangeFramebufferSize(GLFWwindow* window, const GLint width, const int32_t height) {
    glViewport(0, 0, width, height);
}

void handleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void render(GLuint VAO, uint size, const void * indices, GLuint program) {
    glUseProgram(program);
    glBindVertexArray(VAO);
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

    glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return VAO;
}

bool checkShader(GLuint shader) {
    GLint success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Error Compiling Shader" << std::endl << infoLog << std::endl;
        return false;
    }

    return true;
}

bool checkProgram(GLuint program) {
    GLint success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "Error Linking Program" << std::endl << infoLog << std::endl;
        return false;
    }

    return true;
}

GLuint createProgram(const char *vertexShaderSource, const char *fragmentShaderSource) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    checkShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
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
    // Hexagon
    GLfloat hexagon_vertices[18] = {0.f};
    GLfloat radius = 0.5;
    for (int i = 0; i < 6; ++i) {
        hexagon_vertices[3 * i] = radius * cosf(i * 60 * M_PI/180);
        hexagon_vertices[3 * i + 1] = radius * sinf(i * 60 * M_PI/180);
        hexagon_vertices[3 * i +2] = 0.f;
    }

    GLuint hexagon_indices[] = {
            0, 1, 2,
            0, 2, 3,
            0, 3, 4,
            0, 4, 5
    };
    GLuint hexagon_VBO, hexagon_EBO;
    GLuint hexagon_VAO = createVertexData(hexagon_vertices, 18, hexagon_indices, 12,  &hexagon_VBO, &hexagon_EBO);
    ///////////////////////////

    // Create Vertex and Fragment Shader sources
    const char *vertexShaderSource =
            "#version 330core\n"
                    "layout (location = 0) in vec3 aPos;\n"
                    "void main() {\n"
                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.f);\n"
                    "}\0";

    const char *blueFragmentShaderSource =
            "#version 330core\n"
                    "out vec4 fragColor;\n"
                    "void main() {\n"
                    "   fragColor = vec4(0.f, 0.f, 1.0f, 1.f);\n"
                    "}\0";

    // Create program
    GLuint blueProgram = createProgram(vertexShaderSource, blueFragmentShaderSource);

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
        render(hexagon_VAO, 12, nullptr, blueProgram);

        //Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    ////////////////////////////
    // Delete VAO and VBO
    glDeleteVertexArrays(1, &hexagon_VAO);
    glDeleteBuffers(1, &hexagon_VBO);
    glDeleteBuffers(1, &hexagon_EBO);
    ///////////////////////////

    // Delete program
    glDeleteProgram(blueProgram);

    glfwTerminate();
    return 0;
}

/*
#include <iostream>

int main (int argc, char *argv[]) {
    std::cout << "Hello World" << std::endl;
    return 0;
}*/