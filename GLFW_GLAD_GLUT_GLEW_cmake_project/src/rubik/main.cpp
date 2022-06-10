#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "C:/Users/Equipo/Documents/CuboRubik/GLFW_GLAD_GLUT_GLEW_cmake_project/src/rubik/stb_image.h"
#include <C:/Users/Equipo/Documents/CuboRubik/GLFW_GLAD_GLUT_GLEW_cmake_project/src/rubik/shader.h>

#include "camera.h"
#include "global.h"
#include "rubik.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <thread>
#include <chrono>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window);

Camera camera;
RubikCube rubik;

int timing = 40;

// camera
bool move_camara_right = false;
bool move_camara_left = false;

bool left = false;
bool right = false;
bool front = false;
bool bottom = false;
bool top = false;
bool down = false;


int main()
{
    //Camera
    camera.define_perspective();
    camera.define_view();

    //rubik.view_cubes();

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
    GLFWwindow* window = glfwCreateWindow(tools::SCR_WIDTH, tools::SCR_HEIGHT, "Comp. Grafica - Rubik", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure tools opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------

    Shader ourShader(tools::vertex_shader, tools::fragment_shader);

    unsigned int VBO[tools::CUBES], VAO[tools::CUBES];
    glGenVertexArrays(tools::CUBES, VAO);
    glGenBuffers(tools::CUBES, VBO);

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

    ourShader.use();
    ourShader.setMat4("projection", camera.projection);
    ourShader.setMat4("view", camera.view);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.81f, 0.89f, 1.00f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ourShader.use();
        
        if (move_camara_right) {
            camera.update_view(true);
            ourShader.setMat4("view", camera.view);
            move_camara_right = false;
        }
        else if (move_camara_left) {
            camera.update_view(false);
            ourShader.setMat4("view", camera.view);
            move_camara_left = false;
        }

        
        // Movimiento: Left        
        if (left) {
            for (int i = 0; i < 9; i++) {                
                rubik.move_group('L');
                int k = 0;

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                for (auto iter = rubik.cubes.begin(); iter != rubik.cubes.end(); ++iter) {
                    glBindBuffer(GL_ARRAY_BUFFER, VBO[k]);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second->vertex.size(), static_cast<void*>(iter->second->vertex.data()), GL_STATIC_DRAW);                    
                    k++;
                }             
                for (int j = 0; j < tools::CUBES; j++) {
                    glBindVertexArray(VAO[j]);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }

                tools::sleep(timing);
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
            left = false;
        }
        
        // Movimiento: Right
        else if (right) {
            for (int i = 0; i < 9; i++) {
                rubik.move_group('R');
                int k = 0;

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                for (auto iter = rubik.cubes.begin(); iter != rubik.cubes.end(); ++iter) {
                    glBindBuffer(GL_ARRAY_BUFFER, VBO[k]);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second->vertex.size(), static_cast<void*>(iter->second->vertex.data()), GL_STATIC_DRAW);
                    k++;
                }

                for (int j = 0; j < tools::CUBES; j++) {
                    glBindVertexArray(VAO[j]);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
            right = false;
        }

        // Movimiento: Front
        else if (front) {
            for (int i = 0; i < 9; i++) {
                rubik.move_group('F');
                int k = 0;

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                for (auto iter = rubik.cubes.begin(); iter != rubik.cubes.end(); ++iter) {
                    glBindBuffer(GL_ARRAY_BUFFER, VBO[k]);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second->vertex.size(), static_cast<void*>(iter->second->vertex.data()), GL_STATIC_DRAW);
                    k++;
                }

                for (int j = 0; j < tools::CUBES; j++) {
                    glBindVertexArray(VAO[j]);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(40));
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
            front = false;
        }

        // Movimiento: Bottom
        else if (bottom) {
            for (int i = 0; i < 9; i++) {
                rubik.move_group('B');
                int k = 0;

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                for (auto iter = rubik.cubes.begin(); iter != rubik.cubes.end(); ++iter) {
                    glBindBuffer(GL_ARRAY_BUFFER, VBO[k]);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second->vertex.size(), static_cast<void*>(iter->second->vertex.data()), GL_STATIC_DRAW);
                    k++;
                }

                for (int j = 0; j < tools::CUBES; j++) {
                    glBindVertexArray(VAO[j]);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(40));
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
            bottom = false;
        }
        
        // Movimiento: Top
        else if (top) {
            for (int i = 0; i < 9; i++) {
                rubik.move_group('T');
                int k = 0;

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                for (auto iter = rubik.cubes.begin(); iter != rubik.cubes.end(); ++iter) {
                    glBindBuffer(GL_ARRAY_BUFFER, VBO[k]);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second->vertex.size(), static_cast<void*>(iter->second->vertex.data()), GL_STATIC_DRAW);
                    k++;
                }

                for (int j = 0; j < tools::CUBES; j++) {
                    glBindVertexArray(VAO[j]);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(40));
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
            top = false;
        }

        else if (down) {
        for (int i = 0; i < 9; i++) {
            rubik.move_group('B');
            int k = 0;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (auto iter = rubik.cubes.begin(); iter != rubik.cubes.end(); ++iter) {
                glBindBuffer(GL_ARRAY_BUFFER, VBO[k]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second->vertex.size(), static_cast<void*>(iter->second->vertex.data()), GL_STATIC_DRAW);
                k++;
            }

            for (int j = 0; j < tools::CUBES; j++) {
                glBindVertexArray(VAO[j]);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(40));
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        down = false;
        }

        for (int j = 0; j < tools::CUBES; j++) {
            glBindVertexArray(VAO[j]);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(tools::CUBES, VAO);
    glDeleteBuffers(tools::CUBES, VBO);

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

    //Movimientos camara
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) move_camara_right = true;
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) move_camara_left = true;

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        left = true;
    }
    else if (key == GLFW_KEY_E && action == GLFW_PRESS) right = true;
    else if (key == GLFW_KEY_Z && action == GLFW_PRESS) front = true;
    else if (key == GLFW_KEY_C && action == GLFW_PRESS) bottom = true;
    else if (key == GLFW_KEY_A && action == GLFW_PRESS) top = true;
    else if (key == GLFW_KEY_D && action == GLFW_PRESS) down = true;
    
}



