#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>


void printGPUInfo() {
    // Retrieve the GPU model/renderer name
    const GLubyte* renderer = glGetString(GL_RENDERER);

    // Retrieve the GPU manufacturer/vendor
    const GLubyte* vendor = glGetString(GL_VENDOR);

    // Retrieve the supported OpenGL version
    const GLubyte* version = glGetString(GL_VERSION);

    const GLubyte* compiler = glGetString(GL_SHADING_LANGUAGE_VERSION);

    if (renderer && vendor) {
        std::cout << "GPU Vendor: " << vendor << std::endl;
        std::cout << "GPU Model: " << renderer << std::endl;
        std::cout << "OpenGL Version: " << version << std::endl;
        std::cout << "OpenGL GL_SHADING_LANGUAGE_VERSION: " << compiler << std::endl;

    }
    else {
        std::cerr << "Failed to retrieve GPU info. Is the OpenGL context active?" << std::endl;
    }
}


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";



int main() {


    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // 


    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    // viewport goes from x = 0, y = 0, to x = 800, y = 600
    glViewport(0, 0, 800, 600);


    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);    

    // Create a shader program and link the vertex and fragment shaders
    GLuint shaderProgram = glCreateProgram();

    // Attach the vertex and fragment shaders to the shader program
    glAttachShader(shaderProgram, vertexShader);    
    glAttachShader(shaderProgram, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(shaderProgram);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 


    // Creating the Triangle 

    GLfloat vertices[] = {
        -0.1f, -0.1f, 0.0f, // left  
         0.1f, -0.1f, 0.0f, // right 
        -0.1f,  0.1f, 0.0f,  // top   
        // Second Triangle
        -0.1f, 0.1f, 0.0f, // left  
         0.05f, 0.1f, 0.0f, // right 
        -0.1f,  0.2f, 0.0f  // top   
    };


    // Create reference containers for the Vartex Array Object and the Vertex Buffer Object
    GLuint VAO, VBO;

    // Make sure to generate this before VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);



    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Nice to have 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);




    // Color of the background
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);


    // Get GPU info from above function
    printGPUInfo();

    // Triangle 



    while (!glfwWindowShouldClose(window)) {
        // We need to have these Clearn Function here 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        // Activate shader Program
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);

        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLES, 0, 6);  // Adding 6 vertices as i changes adding another traingle
        // M<ake sure to swap the buffersA
        glfwSwapBuffers(window);

        // Take care of all GLFW events
        glfwPollEvents();
    }



    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();



    return 0;
}