#include <iostream>
#include <test/opengl.hpp>
#include <glfw3.h>
GLuint G_CUBE_VAO = 0;

void initCube() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    std::cout<<"generate vao "<<vao<<" for cube"<<std::endl;

    const GLfloat cube_verts[] = {
        // front
       -1.0f, -1.0f,  1.0,
        1.0f, -1.0f,  1.0,
        1.0f,  1.0f,  1.0,
       -1.0f,  1.0f,  1.0,
        //back
       -1.0f, -1.0f, -1.0,
        1.0f, -1.0f, -1.0,
        1.0f,  1.0f, -1.0,
       -1.0f,  1.0f, -1.0,
    };

    const GLfloat cube_colors[] = {
        // front
        1.0f,  0.0f,  0.0,
        0.0f,  1.0f,  0.0,
        0.0f,  0.0f,  1.0,
        1.0f,  1.0f,  1.0,
        //back
        1.0f,  0.0f,  0.0,
        0.0f,  1.0f,  0.0,
        0.0f,  0.0f,  1.0,
        1.0f,  1.0f,  1.0,
    };

    const GLushort cube_indices[] = {
        //front
        0, 1, 2,
        2, 3, 0,
        // top
        3, 2, 6,
        6, 7, 3,
        //back
        7, 6, 5,
        5, 4, 7,
        // bottom
        4, 5, 1,
        1, 0, 4,
        //left
        4, 0, 3,
        3, 7, 4,
        //right
        1, 5, 6,
        6, 2, 1,
    };

    // skip normals for now. We'll come back to them.
    // TODO: make this one glGenBuffers call, filling into an array
    GLuint vbo_verts, vbo_colors, vbo_index;
    glGenBuffers(1, &vbo_verts);
    glGenBuffers(1, &vbo_colors);
    glGenBuffers(1, &vbo_index);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_verts);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verts), cube_verts, GL_STATIC_DRAW);
    // TODO: un-hardcode the 0 here
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
    // TODO: un-hardcode the 0 here
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1 , 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );


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

    window = glfwCreateWindow(1024, 768, "Test", nullptr, nullptr); if (window == nullptr) {
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

    initPrimitives();
    return window;
}

