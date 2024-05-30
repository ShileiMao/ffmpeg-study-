#include "Window.hpp"
#include<iostream>

using namespace std; 

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   ourColor = aColor;\n"
"}\n";

const char* fragmentShaderSource = "#version 330 core \n"
"out vec3 FragColor;\n"
"in vec3 ourColor;\n"
"void main() \n"
"{\n"
"   FragColor = ourColor;\n"
"}\n";

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}


static void frameBufferSizeCallback(GLFWwindow* window, int height, int width) 
{
  cout<<"Window frame size changed:" <<height<<","<<height<<endl;
}


void error_callback(int error, const char* description) 
{
  // fputs(description, stderr);

  fprintf(stderr, "Error: %s\n", description);
}


Window::Window(int width, int height, const char* title) 
{
  cout << "Creating Window..."<<endl;

  if(!glfwInit()) {
    printf("Failed to init GLFW\n");
    return;
  }

  
  glfwSetErrorCallback(error_callback);

  // config the glfw
  // glfwDefaultWindowHints();
  // set it invisiable until we initialized the window
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  // on Mac OS siwtch on this option to make sure it compies 
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


  // glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  // glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  // glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
  // glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
  // glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);


  // create the window
  this->window = glfwCreateWindow(width, height, title, NULL, NULL);
  if(!window) {
    cerr << "Failed to open window"<<endl;
    glfwTerminate();
    return;
  }

  // make the OPENGL context current
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return;
  }    
  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

  // enable the v-sync (buffer swapping)
  // glfwSwapInterval(1); // swap every single frame (no wait time, as fast as we can)
  // make the window visible
  glfwShowWindow(window);

}


void Window::showWindow() 
{
  
  // gladLoadGL(glfwGetProcAddress);
  glfwSwapInterval(1);

  // create shader object
  Shader myShader("resources/gl/shaders/vertex.vs", "resources/gl/shaders/fragment.fs");

  // setup vertex data (and buffer(s)) and configure vertex attributes
  float vertices[] = {
    // vertices           // colors
    -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom left
     0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // bottom right
     0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f// top
  };

  float rectangle_vertices[] = {
      // positions           // colors
      0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // top right
      0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// bottom left
      -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top left 
  };

  unsigned int indices[] = {  // we start from 0!
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
  };


  GLuint vertex_buffer_object, vertex_array_object, element_buffer_object;
  // generate a buffer with buffer ID
  glGenVertexArrays(1, &vertex_array_object);
  glGenBuffers(1, &vertex_buffer_object);
  // glGenBuffers(1, &element_buffer_object);
  
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(vertex_array_object);

  // open GL allows us to bind to several bufferes at once, as long as they have 
  // different buffer type. We can bind the newely created buffer to GL_ARRAY_BUFFER,
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
  // from this point, any buffer calls we make on the GL_ARRAY_BUFFER target will be used
  // to configure the currently bonded buffer, which is `vertex_buffer`
  // below is to copy previously defined vertices buffer into the buffer's memory
  //
  // three options: 
  // - GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times
  // - GL_STATIC_DRAW: the data is set only once and used many times
  // - GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);  

  float seed = rand() % 1;

  while(!glfwWindowShouldClose(window))
  {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // int width, height;
    // glfwGetFramebufferSize(window, &width, &height);
    // glViewport(0, 0, width, height);
    
    float time_value = glfwGetTime();
    float green_value = (sin(time_value) / 2.0f);
    float red_value = (cos(time_value) / 2.0f);
    float blue_value = sin(time_value);

    myShader.use();
    glBindVertexArray(vertex_array_object);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glDeleteBuffers(1, &vertex_array_object);
  glDeleteBuffers(1, &element_buffer_object);
  glDeleteVertexArrays(1, &vertex_array_object);
}

void Window::destroyWidnow()
{
  if(this->window) {
    glfwDestroyWindow(window);
    this->window = NULL;
  }
}

Window::~Window()
{
  cout << "We are trying to release the window...."<<endl;
  destroyWidnow();
  glfwTerminate();
}