#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "C:/Users/Equipo/Documents/CuboRubik/GLFW_GLAD_GLUT_GLEW_cmake_project/src/rubik/stb_image.h"

#include "shader.h"
#include "camera.h"
#include "params.h"
#include "rubik.h"
#include "solver.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera;
RubikCube rubik;
Solver solverRubik;

bool solver = false;

// Serie de pasos para mezclar el cubo rubik
std::vector<std::string> mix = { 
    "D2", "R", "F", "B'", "F2", 
    "R" , "U", "B'", "L" 
};

std::vector<std::string> sol = { 
    "R2", "U'", "R'", "U'", "R", "U", "R", "U", "R", "U'", "R",
    "R2", "U'", "R'", "U'", "R", "U", "R", "U", "R", "U'", "R",
    "R2", "U'", "R'", "U'", "R", "U", "R", "U", "R", "U'", "R" 
};

std::vector<std::string> sol2 = {
    "D2", "F'", "D'", "F'", "D", "F", "D", "F", "D", "F'", "D",
    "D2", "F'", "D'", "F'", "D", "F", "D", "F", "D", "F'", "D",
    "D2", "F'", "D'", "F'", "D", "F", "D", "F", "D", "F'", "D"
};

std::vector<std::string> sol3 = {
    "L2", "B'", "L'", "B'", "L", "B", "L", "B", "L", "B'", "L",
    "L2", "B'", "L'", "B'", "L", "B", "L", "B", "L", "B'", "L",
    "L2", "B'", "L'", "B'", "L", "B", "L", "B", "L", "B'", "L"
};

std::vector<std::string> sol4 = {
    "L", "B", "L'", "B", 
    "L", "B", "L'", "B", 
    "L", "B", "L'", "B", 
    "L", "B", "L'", "B", 
    "L", "B", "L'", "B"    
};


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

    glfwSetKeyCallback(window, key_callback);
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

    ourShader.use();
    ourShader.setInt("texture1", 0);
    
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.933f, 0.933f, 0.933f, 1.0f);
                   
        camera.update_perspective();
        camera.update_view();
        
        if (solver) {
            SolverInput input = rubik.map_groups();

            solverRubik.set_white_face(input['U']);
            solverRubik.set_yellow_face(input['D']);
            solverRubik.set_red_face(input['B']);
            solverRubik.set_orange_face(input['F']);
            solverRubik.set_blue_face(input['L']);
            solverRubik.set_green_face(input['R']);

            std::vector<std::string> steps = solverRubik.get_steps(true);
            rubik.do_movements(window, steps);
            solver = false;
        }

        ourShader.use();
        ourShader.setMat4("projection", camera.projection);
        ourShader.setMat4("view", camera.view);
       
        // Draw
        rubik.draw_cubes(window);        
    }

    rubik.delete_buffer_cubes();
    
    // glfw: borrando todos los recursos GLFW previamente asignados.
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


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // True gira en sentido horario, Falso en sentido antihorario
    // Grupo izquierdo
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        rubik.render_move_group(window, 'L', true);
    else if (key == GLFW_KEY_J && action == GLFW_PRESS)
        rubik.render_move_group(window, 'L', false);

    // Grupo derecho
    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
        rubik.render_move_group(window, 'R', true);
    else if (key == GLFW_KEY_L && action == GLFW_PRESS)
        rubik.render_move_group(window, 'R', false);

    // Grupo superior
    else if (key == GLFW_KEY_W && action == GLFW_PRESS)
        rubik.render_move_group(window, 'U', true);
    else if (key == GLFW_KEY_I && action == GLFW_PRESS)
        rubik.render_move_group(window, 'U', false);

    // Grupo inferior
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
        rubik.render_move_group(window, 'D', true);
    else if (key == GLFW_KEY_K && action == GLFW_PRESS)
        rubik.render_move_group(window, 'D', false);

    // Grupo frontal
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        rubik.render_move_group(window, 'F', true);
    else if (key == GLFW_KEY_U && action == GLFW_PRESS)
        rubik.render_move_group(window, 'F', false);

    // Grupo posterior
    else if (key == GLFW_KEY_E && action == GLFW_PRESS)
        rubik.render_move_group(window, 'B', true);
    else if (key == GLFW_KEY_O && action == GLFW_PRESS)
        rubik.render_move_group(window, 'B', false);

    else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        rubik.do_movements(window, mix);
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        solver = true;
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        rubik.do_movements(window, sol);
        rubik.do_movements(window, sol2);
        rubik.do_movements(window, sol3);
        rubik.do_movements(window, sol4);
    }
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS) {        
        rubik.render_animation_1(window);
        //rubik.cubes['S']->transformation_ts(glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.5, 1.5, 1.5));
    }
    

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

