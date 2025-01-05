#include <main/includes.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

float mixValue = 0.2f;

int windowWidth = 800;
int windowHeight = 600;

vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Create a window object
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL);
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
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }


    //Set the viewport size
    glViewport(0, 0, 800, 600);
    //Set the window resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /*
    Prerender commands here...
    */




    //New shader code
    Shader bestShader("../../src/shaders/shader1.vert", "../../src/shaders/shader1.frag");  




    //Triangle points
    float vertices[] = {
        //positions             //colors                //texture coords
        -0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f,       0.0f, 0.0f,     //lower left corner
        0.5f, -0.5f, 0.5f,      1.0f, 0.0f, 0.0f,       1.0f, 0.0f,     //lower right corner
        -0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 1.0f,       0.0f, 1.0f,     //top left corner
        0.5f, 0.5f, 0.5f,       1.0f, 0.0f, 1.0f,       1.0f, 1.0f      //top right corner

        //backside of cube      //colors                //texture coords    
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,       0.0f, 0.0f,     //lower left corner
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 1.0f,       1.0f, 0.0f,     //lower right corner
        -0.5f, 0.5f, -0.5f,     0.0f, 1.0f, 0.0f,       0.0f, 1.0f,     //top left corner
        0.5f, 0.5f, -0.5f,      1.0f, 0.0f, 0.0f,       1.0f, 1.0f      //top right corner
    };

    unsigned int indices[] = {
        //front face        //top face          //right face
        1, 0, 2, 1, 3, 2,   3, 2, 6, 3, 7, 6,   3, 1, 5, 3, 7, 5,

        //left face         //bottom face       //back face
        0, 2, 6, 0, 4, 6,   1, 0, 4, 1, 5, 4,   4, 5, 7, 4, 6, 7

    };

    float cubeVertices[] = {
        //x    y    z               u     v
        -0.5f, -0.5f, -0.5f,        0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,         1.0f, 0.0f,
        0.5f, 0.5f, -0.5f,          1.0f, 1.0f,
        0.5f, 0.5f, -0.5f,          1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f,         0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,        0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,         0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,          1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,           1.0f, 1.0f,
        0.5f, 0.5f, 0.5f,           1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,          0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,         0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f,          1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,         1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,        0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,        0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,         0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,          1.0f, 0.0f,

        0.5f, 0.5f, 0.5f,           1.0f, 0.0f,
        0.5f, 0.5f, -0.5f,          1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,         0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,         0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,          0.0f, 0.0f,
        0.5f, 0.5f, 0.5f,           1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,        0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,         1.0f, 1.0f,
        0.5f, -0.5f, 0.5f,          1.0f, 0.0f,
        0.5f, -0.5f, 0.5f,          1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,         0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,        0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f,         0.0f, 1.0f,
        0.5f, 0.5f, -0.5f,          1.0f, 1.0f,
        0.5f, 0.5f, 0.5f,           1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,           1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,          0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,         0.0f, 1.0f
    };

    vec3 cubePositions[] = {
        vec3( 0.0f, 0.0f, 0.0f),
        vec3( 2.0f, 5.0f, -15.0f),
        vec3(-1.5f, -2.2f, -2.5f),
        vec3(-3.8f, -2.0f, -12.3f),
        vec3( 2.4f, -0.4f, -3.5f),
        vec3(-1.7f, 3.0f, -7.5f),
        vec3( 1.3f, -2.0f, -2.5f),
        vec3( 1.5f, 2.0f, -2.5f),
        vec3( 1.5f, 0.2f, -1.5f),
        vec3(-1.3f, 1.0f, -1.5f)
    };




    string brickPath = "../../src/textures/brick.png";
    string secondPath = "../../src/textures/amongus.png";

    //Create texture object and generate a texture
    unsigned int texture1;
    glGenTextures(1, &texture1);
    //Bind the texture
    glBindTexture(GL_TEXTURE_2D, texture1);  
    //Sets the texture wrapping settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Load the texture into an unsigned char array
    int width, height, nrChannels;
    unsigned char *data = stbi_load(brickPath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);   
        glGenerateMipmap(GL_TEXTURE_2D);
        cout << "Texture loaded successfully" << endl;
    }
    else
    {
        cout << "Texture failed to load" << endl;
    }
    stbi_image_free(data);

    //Create and bind amongus texture like above
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    data = stbi_load(secondPath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);   
        glGenerateMipmap(GL_TEXTURE_2D);
        cout << "Texture loaded successfully " << endl;
    }
    else
    {
        cout << "Failed to load texture" << endl;
    }
    stbi_image_free(data);




    //Set the clear color
    glClearColor(-0.33f, 0.54f, 0.68f, 1.0f);




    //Vertex Objects
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    //Bind the VAO, VBO, and EBO
    glBindVertexArray(VAO);

    //Bind VBA and give it data (triangle's vertices)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    cout << glGetError() << endl; 
    //Bind EBO and give it data (order of vertices)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    cout << glGetError() << endl; 


    //Element Array Pointers
    /*
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    */
    

    //Object Array Pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    



    //Tell OpenGL to use the shader program
    bestShader.use();
    bestShader.setInt("texture2", 1);

    //Enable depth testing
    glEnable(GL_DEPTH_TEST);



    //Render Loop
    while(!glfwWindowShouldClose(window))
    {
        //Process input
        processInput(window);

        //Clear the screen with the clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Time for time
        float timeValue = (float)glfwGetTime();
        deltaTime = timeValue - lastFrame;
        lastFrame = timeValue;

        /*
        Render commands here...
        */
        
        /*idek what this is
        vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);
        vec3 up = vec3(0.0f, 1.0f, 0.0f);

        vec3 cameraDirection = normalize(cameraPos - cameraTarget);
        vec3 cameraRight = normalize(cross(up, cameraDirection));
        vec3 cameraUp = cross(cameraDirection, cameraRight);
        */


        //Bind the textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        

        bestShader.use();




        
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        float moveValue = (sin(timeValue) / 5.0f);

        bestShader.setFloat("displace", moveValue);
        bestShader.setVec3("myColor", 0.0f, greenValue, 0.0f);
        bestShader.setFloat("mixValue", mixValue);


        //create the matrices
        //mat4 model = mat4(1.0f);
        mat4 view = mat4(1.0f);
        mat4 projection = mat4(1.0f);
       
        //set data for each matrix
        view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        projection = perspective(radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

        //Pass data to each matrix
        //bestShader.setMat4("model", model);
        bestShader.setMat4("view", view);
        bestShader.setMat4("projection", projection);

        glBindVertexArray(VAO);
        

        for(int i = 1; i <= 10; i++)
        {
            mat4 model = mat4(1.0f);
            float angle = 20.0f * i;

            model = translate(model, cubePositions[i-1]);

            if (i % 3 == 1){
                model = rotate(model, radians((float)glfwGetTime() * angle), vec3(3.0f, 0.5f, 0.7f));
            } else
            {
                model = rotate(model, radians(angle), vec3(1.0f, 0.3f, 0.5f));
            }
            

            bestShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //Draw the triangle
        
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); 


        //check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Delete the VAO and VBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    //Terminate GLFW
    glfwTerminate();
    return 0;
}




//Function to process input based on the window object
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);


    //excercise code (change the mix value with arrow keys)
    /*
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        mixValue += 0.0002f;
        if(mixValue >= 1.0f)
        mixValue = 1.0f;
    } else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        mixValue -= 0.0002f;
        if(mixValue <= 0.0f)
        mixValue = 0.0f;
    }; 
    */

    float cameraSpeed = 10.0f * deltaTime; 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= normalize(cross(cameraFront, cameraUp)) *
        cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += normalize(cross(cameraFront, cameraUp)) *
        cameraSpeed;

}




//Function to resize the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}