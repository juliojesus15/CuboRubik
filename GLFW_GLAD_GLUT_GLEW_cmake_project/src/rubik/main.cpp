#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "C:/Users/Equipo/Documents/CuboRubik/GLFW_GLAD_GLUT_GLEW_cmake_project/src/rubik/stb_image.h"

#include "shader.h"
#include "camera.h"
#include "params.h"
#include "rubik.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

bool firstMouse = true;
float deltaTime = 0.0f;	
float lastFrame = 0.0f;

Camera camera;
RubikCube rubik;

unsigned int VBO[params::CUBES], VAO[params::CUBES];

void draw_cubes() {
    for (int j = 0; j < params::CUBES; j++) {
        glBindVertexArray(VAO[j]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

//Render transformation
void processing_group(GLFWwindow* window, unsigned int VBO[], unsigned int VAO[], char group_id, bool clockwise) {
    for (int i = 0; i < 9; i++) {
        rubik.move_group(group_id, clockwise);
        int k = 0;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto iter = rubik.cubes.begin(); iter != rubik.cubes.end(); ++iter) {
            glBindBuffer(GL_ARRAY_BUFFER, VBO[k]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second->vertex.size(), static_cast<void*>(iter->second->vertex.data()), GL_STATIC_DRAW);
            k++;
        }

        draw_cubes();
        params::sleep();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }    
}

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
    GLFWwindow* window = glfwCreateWindow(params::SCR_WIDTH, params::SCR_HEIGHT, "Cubo Rubik - UCSP", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
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
    
    glGenVertexArrays(params::CUBES, VAO);
    glGenBuffers(params::CUBES, VBO);

    int i = 0;
    for (auto iter = rubik.cubes.begin(); iter != rubik.cubes.end(); ++iter) {
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second->vertex.size(), static_cast<void*>(iter->second->vertex.data()), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // color coord attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        i++;
    }
    std::cout << "====================================" << std::endl;
    std::cout << "Controles Rubik" << std::endl;
    std::cout << "Q (Rotacion Left)" << std::endl;
    std::cout << "E (Rotacion Rgithizquierda)" << std::endl;
    std::cout << "A (Rotacion Top)" << std::endl;
    std::cout << "D (Rotacion Down)" << std::endl;
    std::cout << "Z (Rotacion Front)" << std::endl;
    std::cout << "C (Rotacion Back)" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "Controles Camara:" << std::endl;
    std::cout << "KEY_UP: Arriba" << std::endl;
    std::cout << "KEY_DOWN: Abajo" << std::endl;
    std::cout << "KEY_RIGHT: Derecha" << std::endl;
    std::cout << "KEY_LEFT: Izquierda" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "Notas: " << std::endl;
    std::cout << "1) Por ahora solo se mueven en un solo sentido" << std::endl;
    std::cout << "2) Las camadas aun no se actualizan en cada rotacion" << std::endl;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.81f, 0.89f, 1.00f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        camera.update_perspective();
        camera.update_view();

        ourShader.use();
        ourShader.setMat4("projection", camera.projection);
        ourShader.setMat4("view", camera.view);
     
        draw_cubes();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(params::CUBES, VAO);
    glDeleteBuffers(params::CUBES, VBO);

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {    
    
    // Grupo izquierdo, True gira en sentido horario, Falso en sentido antihorario
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        processing_group(window, VBO, VAO, 'L', true);
    else if (key == GLFW_KEY_W && action == GLFW_PRESS)
        processing_group(window, VBO, VAO, 'L', false);

    // Grupo derecho, True gira en sentido horario, Falso en sentido antihorario
    else if (key == GLFW_KEY_E && action == GLFW_PRESS)
        processing_group(window, VBO, VAO, 'R', true);
    else if (key == GLFW_KEY_R && action == GLFW_PRESS)
        processing_group(window, VBO, VAO, 'R', false);

    // Grupo frontal, True gira en sentido horario, Falso en sentido antihorario
    else if (key == GLFW_KEY_Z && action == GLFW_PRESS) 
        processing_group(window, VBO, VAO, 'F', true);
    else if (key == GLFW_KEY_X && action == GLFW_PRESS)
        processing_group(window, VBO, VAO, 'F', false);

    // Grupo posterior, True gira en sentido horario, Falso en sentido antihorario
    else if (key == GLFW_KEY_C && action == GLFW_PRESS)
        processing_group(window, VBO, VAO, 'B', true);
    else if (key == GLFW_KEY_V && action == GLFW_PRESS)
        processing_group(window, VBO, VAO, 'B', false);
    
    // Grupo superior, True gira en sentido horario, Falso en sentido antihorario
    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
        processing_group(window, VBO, VAO, 'U', true);
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
        processing_group(window, VBO, VAO, 'U', false);

    // Grupo inferior, True gira en sentido horario, Falso en sentido antihorario
    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
        processing_group(window, VBO, VAO, 'D', true);
    else if (key == GLFW_KEY_F && action == GLFW_PRESS)
        processing_group(window, VBO, VAO, 'D', false);
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