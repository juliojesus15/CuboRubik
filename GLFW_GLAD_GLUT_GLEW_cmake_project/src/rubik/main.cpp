#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "C:/Users/Equipo/Documents/CuboRubik/GLFW_GLAD_GLUT_GLEW_cmake_project/src/rubik/stb_image.h"

#include "shader.h"
#include "camera.h"
#include "params.h"
#include "rubik.h"
#include "solver.h"
#include "cube.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera;
RubikCube rubik;
//Solver solverRubik;

//unsigned int VBO[params::CUBES], VAO[params::CUBES];
/*
void draw_cubes() {
    for (int j = 0; j < params::CUBES; j++) {
        glBindVertexArray(VAO[j]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
*/
//O W
std::string route = "C:/Users/Equipo/Documents/CuboRubik/GLFW_GLAD_GLUT_GLEW_cmake_project/src/rubik/texturas/back/";
std::vector< std::pair <char, std::string> > features = {   // R
            std::make_pair('B', "B/5.png"),
            std::make_pair('O', "O/5.png"),
            std::make_pair('W', "W/5.png")
};
std::vector< std::pair <char, std::string> > features_2 = { std::make_pair('G', "G/5.png") };

char id = 'A';
Cube cube(id, features);
Cube cube2('B', features_2);

int main() {
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
    GLFWwindow* window = glfwCreateWindow(params::SCR_WIDTH, params::SCR_HEIGHT, "Rubik Cube", NULL, NULL);
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

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure params opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    Shader ourShader(params::vertex_shader, params::fragment_shader);

    rubik.init_cubes();
    //cube.init();
    //cube2.init();

    ourShader.use();
    ourShader.setInt("texture1", 0);
    
    cube.translation(glm::vec3(-0.50f, 0.50f, -0.50f));
    cube2.translation(glm::vec3(0.70f, 0.50f, -0.50f));

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.81f, 0.89f, 1.00f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                   
        camera.update_perspective();
        camera.update_view();
      
        //cube.draw();
        //cube2.draw();
        rubik.draw_cubes();

        ourShader.use();
        ourShader.setMat4("projection", camera.projection);
        ourShader.setMat4("view", camera.view);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //cube.deleteBuffer();
    //cube2.deleteBuffer();
    rubik.delete_buffer_cubes();

    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.move_up(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.move_down(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.move_left(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.move_right(cameraSpeed);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float x_pos = static_cast<float>(xposIn);
    float y_pos = static_cast<float>(yposIn);

    if (firstMouse) {
        camera.mouse_x = x_pos;
        camera.mouse_y = y_pos;
        firstMouse = false;
    }

    camera.update_mouse_position(x_pos, y_pos);
    camera.update_target();
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.update_fov((float)yoffset);
}