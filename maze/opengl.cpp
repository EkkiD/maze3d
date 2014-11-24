#include <iostream>
#include <maze/opengl.hpp>
#include <maze/common.hpp>
#include <GLFW/glfw3.h> 
GLuint G_CUBE_VAO = 0; 
void initCube() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    std::cout<<"generate vao "<<vao<<" for cube"<<std::endl;

    const GLfloat cube_verts[] = {
        // front
        0.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        0.0f,  1.0f,  1.0f,

        // top
        0.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,

        //back
        0.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,

        // bottom
        0.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,

        // left
        0.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  1.0f,  1.0f,
        0.0f,  1.0f,  0.0f,

        // right
        1.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  1.0f,
    };

    const GLfloat cube_normals[] = {
        // front
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,

        // top
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,

        //back
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,

        //bottom
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,

        // left
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        // right
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
    };

    const GLfloat cube_colors[] = {
        // front
        1.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,

        // top
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,

        //back
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,

        // bottom
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,

        // left
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,

        // right
        0.6f,  0.0f,  1.0f,
        0.6f,  0.0f,  1.0f,
        0.6f,  0.0f,  1.0f,
        0.6f,  0.0f,  1.0f,
    };


    const GLushort cube_indices[] = {
        //front
        0, 1, 2,
        2, 3, 0,
        // top
        4, 5, 6,
        6, 7, 4,
        //back
        8, 9, 10,
        10, 11, 8,
        // bottom
        12, 13, 14,
        14, 15, 12,
        //left
        16, 17, 18,
        18, 19, 16,
        //right
        20, 21, 22,
        22, 23, 20,
    };

    // skip normals for now. We'll come back to them.
    // TODO: make this one glGenBuffers call, filling into an array
    GLuint vbo_verts, vbo_colors, vbo_index, vbo_normals;
    glGenBuffers(1, &vbo_verts);
    glGenBuffers(1, &vbo_colors);
    glGenBuffers(1, &vbo_index);
    glGenBuffers(1, &vbo_normals);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_verts);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verts), cube_verts, GL_STATIC_DRAW);
    // TODO: un-hardcode the 0 here
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
    // TODO: un-hardcode the 1 here
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1 , 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_normals), cube_normals, GL_STATIC_DRAW);
    // TODO: un-hardcode the 2 here
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2 , 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    G_CUBE_VAO = vao;
}

void initPrimitives() {
    initCube();
}


GLFWwindow* initGL() {
    GLFWwindow* window;
    if (!glfwInit()) {
        std::cerr<<"Failed to init GLFW"<<std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_X, WINDOW_Y, "Test", nullptr, nullptr); if (window == nullptr) {
        std::cerr<<"Failed to open GLFW window."<<std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr<<"Failed to init GLEW"<<std::endl;
        return nullptr;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glCullFace(GL_BACK);

    initPrimitives();
    return window;
}
