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
//RubikCube rubik;
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
std::vector< std::pair <char, std::string> > features = { std::make_pair('B', "1.png") };
std::vector< std::pair <char, std::string> > features_2 = { std::make_pair('Y', "5.png") };

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
    unsigned int VBO[12], VAO[12];
    
    glGenVertexArrays(12, VAO);
    glGenBuffers(12, VBO);


    GLuint* textures = new GLuint[12];
    glGenTextures(12, textures);

    int counter = 0;
    for (auto iter = cube.container_vertex.begin(); iter != cube.container_vertex.end(); iter++) {

        char key = iter->first;
        std::string texture_path = route;
        if (cube.container_textures.find(key) != cube.container_textures.end()) {
            texture_path = texture_path + cube.container_textures[key];
            std::cout << "Key Exists!" << " - "  << key << std::endl;
            std::cout << texture_path << std::endl;
        }
        else {
            texture_path = texture_path + "null.png";
            std::cout << "Key No Exists!" << " - " << key << std::endl;
            std::cout <<texture_path << std::endl;
        }

        glBindVertexArray(VAO[counter]);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[counter]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second.size(), static_cast<void*>(iter->second.data()), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


        
        // texture 1
        // ---------
        //glGenTextures(1, texture1);
        //glBindTexture(GL_TEXTURE_2D, texture1[counter]);
        glBindTexture(GL_TEXTURE_2D, textures[counter]);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.


        
        unsigned char* data = stbi_load(texture_path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        //ourShader.use();
        //ourShader.setInt("texture1", 0);
        std::cout << "1: " << counter << std::endl;
        counter++;
    }

    for (auto iter = cube2.container_vertex.begin(); iter != cube2.container_vertex.end(); iter++) {

        char key = iter->first;
        std::string texture_path = route;
        if (cube2.container_textures.find(key) != cube2.container_textures.end()) {
            texture_path = texture_path + cube2.container_textures[key];
            std::cout << "Key Exists!" << " - " << key << std::endl;
            std::cout << texture_path << std::endl;
        }
        else {
            texture_path = texture_path + "null.png";
            std::cout << "Key No Exists!" << " - " << key << std::endl;
            std::cout << texture_path << std::endl;
        }

        glBindVertexArray(VAO[counter]);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[counter]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iter->second.size(), static_cast<void*>(iter->second.data()), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);



        // texture 1
        // ---------
        //glGenTextures(1, texture1);
        //glBindTexture(GL_TEXTURE_2D, texture1[counter]);
        glBindTexture(GL_TEXTURE_2D, textures[counter]);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.



        unsigned char* data = stbi_load(texture_path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        std::cout << "2: " << counter << std::endl;
        counter++;
    }

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
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)* cube.container_vertex['B'].size(), static_cast<void*>(cube.container_vertex['B'].data()), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)* cube.container_vertex['D'].size(), static_cast<void*>(cube.container_vertex['D'].data()), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)* cube.container_vertex['F'].size(), static_cast<void*>(cube.container_vertex['F'].data()), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)* cube.container_vertex['L'].size(), static_cast<void*>(cube.container_vertex['L'].data()), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)* cube.container_vertex['R'].size(), static_cast<void*>(cube.container_vertex['R'].data()), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)* cube.container_vertex['U'].size(), static_cast<void*>(cube.container_vertex['U'].data()), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube2.container_vertex['B'].size(), static_cast<void*>(cube2.container_vertex['B'].data()), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[7]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube2.container_vertex['D'].size(), static_cast<void*>(cube2.container_vertex['D'].data()), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[8]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube2.container_vertex['F'].size(), static_cast<void*>(cube2.container_vertex['F'].data()), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[9]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube2.container_vertex['L'].size(), static_cast<void*>(cube2.container_vertex['L'].data()), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[10]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube2.container_vertex['R'].size(), static_cast<void*>(cube2.container_vertex['R'].data()), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[11]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube2.container_vertex['U'].size(), static_cast<void*>(cube2.container_vertex['U'].data()), GL_STATIC_DRAW);

        

        ourShader.use();
        ourShader.setMat4("projection", camera.projection);
        ourShader.setMat4("view", camera.view);


        
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 9);

        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindTexture(GL_TEXTURE_2D, textures[2]);
        glBindVertexArray(VAO[2]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindTexture(GL_TEXTURE_2D, textures[3]);
        glBindVertexArray(VAO[3]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glBindVertexArray(VAO[4]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindTexture(GL_TEXTURE_2D, textures[5]);
        glBindVertexArray(VAO[5]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        // Otro cube
        glBindTexture(GL_TEXTURE_2D, textures[6]);
        glBindVertexArray(VAO[6]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindTexture(GL_TEXTURE_2D, textures[7]);
        glBindVertexArray(VAO[7]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindTexture(GL_TEXTURE_2D, textures[8]);
        glBindVertexArray(VAO[8]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindTexture(GL_TEXTURE_2D, textures[9]);
        glBindVertexArray(VAO[9]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindTexture(GL_TEXTURE_2D, textures[10]);
        glBindVertexArray(VAO[10]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindTexture(GL_TEXTURE_2D, textures[11]);
        glBindVertexArray(VAO[11]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(12, VAO);
    glDeleteBuffers(12, VBO);

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