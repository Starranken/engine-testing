#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    //Make the new window object the current context
    glfwMakeContextCurrent(window);

    //Tell GLAD where the OS system functions are to point to
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Set the viewport size
    glViewport(0, 0, 800, 600);

    //Set the window resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /*
    Prerender commands here...
    */

    //Set the clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

   //Triangle points
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

   //Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Give the VBO data (triangle's vertices)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);








    //Render Loop
    while(!glfwWindowShouldClose(window))
    {
        //Process input
        processInput(window);

        //Clear the screen with the clear color
        glClear(GL_COLOR_BUFFER_BIT);

        /*
        Render commands here...
        */

       


        //check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Terminate GLFW
    glfwTerminate();
    return 0;
}

//Function to process input based on the window object
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

//Function to resize the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}