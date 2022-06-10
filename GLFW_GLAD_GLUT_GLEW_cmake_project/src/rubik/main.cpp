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

// camera
bool move_camara_right = false;
bool move_camara_left = false;

bool left = false;
bool right = false;
bool front = false;
bool back = false;
bool top = false;
bool bottom = false;

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
    GLFWwindow* window = glfwCreateWindow(global::SCR_WIDTH, global::SCR_HEIGHT, "Comp. Grafica - Rubik", NULL, NULL);
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

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------

    Shader ourShader(global::vertex_shader, global::fragment_shader);

    unsigned int VBO[global::CUBES], VAO[global::CUBES];
    glGenVertexArrays(global::CUBES, VAO);
    glGenBuffers(global::CUBES, VBO);

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

        /*
        int partes = 0;
	while (partes != angulo/9) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				RUBIK[face[i][j]]->rotar(rotar, angulo/10);
		bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display(window); 
		glfwSwapBuffers(window);
		glfwPollEvents();
		partes++;
		_sleep(10);
	}
        */
        //rubik.move_left_group(1.0f);
        
        if (left) {
            for (int i = 0; i < 9; i++) {

                //std::cout << "Test: " << i << std::endl;
                
                rubik.move_left_group(1.0f);
                int k = 0;
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                for (auto iter = rubik.cubes.begin(); iter != rubik.cubes.end(); ++iter) {
                    glBindBuffer(GL_ARRAY_BUFFER, VBO[k]);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second->vertex.size(), static_cast<void*>(iter->second->vertex.data()), GL_STATIC_DRAW);                    
                    k++;
                }             
                for (int j = 0; j < global::CUBES; j++) {
                    glBindVertexArray(VAO[j]);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(50));                
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
            //rubik.move_left_group(1.0f);
            left = false;
        }
        
        if (right) {
            rubik.move_right_group(90.0f);
            right = false;
        }

        /*
        int i = 0;
        for (auto iter = rubik.cubes.begin(); iter != rubik.cubes.end(); ++iter) {
            //glBindVertexArray(VAO[i]);
            glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second->vertex.size(), static_cast<void*>(iter->second->vertex.data()), GL_STATIC_DRAW);
            i++;
        }*/

        for (int j = 0; j < global::CUBES; j++) {
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
    glDeleteVertexArrays(global::CUBES, VAO);
    glDeleteBuffers(global::CUBES, VBO);

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
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) left = true;    
    else if (key == GLFW_KEY_E && action == GLFW_PRESS) right = true;
}



