#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <C:/Users/Equipo/Documents/CuboRubik/GLFW_GLAD_GLUT_GLEW_cmake_project/src/rubik/lib/stb_image/stb_image.h>
#include <C:/Users/Equipo/Documents/CuboRubik/GLFW_GLAD_GLUT_GLEW_cmake_project/src/rubik/shader.h>

#include "rubik.h"
#include "solver.h"


#include <thread>
#include <chrono>

//#include "cube.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

using glm::vec4;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const std::string CURRENT_PATH = "C:/Users/Equipo/Documents/CuboRubik/GLFW_GLAD_GLUT_GLEW_cmake_project/src/rubik/";


Solver solver;


// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


Cube cube_1('A', std::vector<char>({ 'O', 'B', 'W', 'R', 'G'}));
Cube cube_2('B', std::vector<char>({ 'B', 'O', 'R', 'G' }));
Cube cube_3('C', std::vector<char>({ 'B', 'Y', 'O', 'R', 'G' }));

RubikCube rubik;
const int num_cubes = 26;

bool flag_rotation = false;

int main()
{    
   
    solver.get_steps(true);
    //solver.get_htpp_steps();
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Comp. Grafica (UCSP) - Cubo Rubik", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------    
    std::string vertex_shader = CURRENT_PATH + "vertex_shader.vs";
    std::string fragment_shader = CURRENT_PATH + "fragment_shader.fs";

    Shader ourShader(vertex_shader, fragment_shader);
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    
    /*
    
    std::vector<glm::vec3> pos = {
        glm::vec3(-0.40f,  0.50f, -0.40f), glm::vec3(-0.40f, -0.55f, -0.40f), glm::vec3(-0.40f, -1.60f, -0.40f)
    };

    unsigned int VBO[3], VAO[3];
    glGenVertexArrays(3, VAO);
    glGenBuffers(3, VBO);

    //cube_1.translation(pos[0]);
    //Cube 1
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_1.vertex.size(), static_cast<void*>(cube_1.vertex.data()), GL_STATIC_DRAW);

    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    
    
    cube_2.translation(pos[1]);
    //Cube2
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_2.vertex.size(), static_cast<void*>(cube_2.vertex.data()), GL_STATIC_DRAW);
    

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    cube_3.translation(pos[2]);
    //Cube 3
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_3.vertex.size(), static_cast<void*>(cube_3.vertex.data()), GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    */
    
    const int num_cubes = 26;
    RubikCube rubik;
    
    unsigned int VBO[num_cubes], VAO[num_cubes];
    glGenVertexArrays(num_cubes, VAO);
    glGenBuffers(num_cubes, VBO);
    
    int i = 0;
    for (auto iter = rubik.cubes.begin(); iter != rubik.cubes.end(); ++iter) {
        //std::cout << i <<" Debugger 3000" << std::endl;
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)* iter->second->vertex.size(), static_cast<void*>(iter->second->vertex.data()), GL_STATIC_DRAW);
        
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // color coord attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        i++;        
    }
    
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.81f, 0.89f, 1.00f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // render boxes        
        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ourShader.setMat4("view", view);
        

        
        //rubik.move_left_group((float)glfwGetTime());
        int i = 0;
        for (auto iter = rubik.cubes.begin(); iter != rubik.cubes.end(); ++iter) {
            glBindVertexArray(VAO[i]);
            glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second->vertex.size(), static_cast<void*>(iter->second->vertex.data()), GL_STATIC_DRAW);                
            i++;
        }
        
        
        for (int j = 0; j < num_cubes; j++) {
            glBindVertexArray(VAO[j]);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        

  
        
              
        //cube_1.rotation(20.0f);
        //cube_2.rotation(20.0f);
        //cube_3.rotation(20.0f);

        //glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_1.vertex.size(), static_cast<void*>(cube_1.vertex.data()), GL_STATIC_DRAW);
        
        //glBindVertexArray(VAO[0]);
        /*
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, pos[0]);
        float angle = 20.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        ourShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        */


        //cube_2.rotation(true);
        //glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_2.vertex.size(), static_cast<void*>(cube_2.vertex.data()), GL_STATIC_DRAW);
        
        //glBindVertexArray(VAO[1]);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        //glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_3.vertex.size(), static_cast<void*>(cube_3.vertex.data()), GL_STATIC_DRAW);

        //glBindVertexArray(VAO[2]);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //std::this_thread::sleep_for(std::chrono::milliseconds(270));
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(3, VAO);
    glDeleteBuffers(3, VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse) 
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {        
        flag_rotation = true;
    }
}