#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void onChangeFramebufferSize(GLFWwindow* window, const int32_t width, const int32_t height) {
    glViewport(0, 0, width, height);
}

void handleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void render(uint32_t VAO, uint32_t shader) {
    glUseProgram(shader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

uint32_t createVertexData(uint32_t* VBO, float vertices[], uint size) {
    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, size/3,  GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return VAO;
}

bool checkShader(uint32_t shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Error Compiling Shader" << std::endl << infoLog << std::endl;
        return false;
    }

    return true;
}

bool checkProgram(uint32_t program) {
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "Error Linking Program" << std::endl << infoLog << std::endl;
        return false;
    }

    return true;
}

uint32_t createProgram() {
    const char *vertexShaderSource =
            "#version 330core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main() {\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.f);\n"
            "}\0";

    const char *fragmentShaderSource =
            "#version 330core\n"
            "out vec4 fragColor;\n"
            "void main() {\n"
            "   fragColor = vec4(0.2f, 0.7f, 0.2f, 1.f);\n"
            "}\0";

    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    checkShader(vertexShader);

    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader);

    uint32_t shaderProgram = glCreateProgram();
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
    window = glfwCreateWindow(800, 600, "New Window", nullptr, nullptr);
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
    // Triangle 1
    float triangle1_vertices[] = {
            0.8f, -0.4f, 0.f,
            0.4f, 0.6f, 0.f,
            0.f, -0.4f, 0.f
    };
    uint32_t triangle1_VBO;
    uint32_t triangle1_VAO = createVertexData(&triangle1_VBO, triangle1_vertices, 9);

    // Triangle 2
    float triangle2_vertices[] = {
            0.f, -0.4f, 0.f,
            -0.4f, 0.6f, 0.f,
            -0.8f, -0.4f, 0.f
    };

    uint32_t triangle2_VBO;
    uint32_t triangle2_VAO = createVertexData(&triangle2_VBO, triangle2_vertices, 9);
    ///////////////////////////


    // Create program
    uint32_t program = createProgram();

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
        glClearColor(0.6f, 0.f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Render the two VAOs
        render(triangle1_VAO, program);

        render(triangle2_VAO, program);

        //Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    ////////////////////////////
    // Delete VAOs and VBOs
    ///////////////////////////
    // Triangle 1
    glDeleteVertexArrays(1, &triangle1_VAO);
    glDeleteBuffers(1, &triangle1_VBO);

    //Triangle 2
    glDeleteVertexArrays(1, &triangle2_VAO);
    glDeleteBuffers(1, &triangle2_VBO);
    ///////////////////////////

    // Delete program
    glDeleteProgram(program);

    glfwTerminate();
    return 0;
}

/*
#include <iostream>

int main (int argc, char *argv[]) {
    std::cout << "Hello World" << std::endl;
    return 0;
}*/