#include<stdio.h>
#include <GLFW/glfw3.h>

int main() {
  GLFWwindow *window;
  if(!glfwInit()) {
    printf("Failed to init GLFW\n");
    return 1;
  }
  window = glfwCreateWindow(640, 480, "Hello world", NULL, NULL);
  if(!window) {
    printf("Failed to open window\n");
    return 1;
  }
  
  unsigned char* data = new unsigned char [100 * 100 * 3];
  for(int y = 0; y < 100; y++) {
    for(int x= 0; x < 100; x ++){
      data[y * 100 * 3 + x * 3    ] = 0xff;
      data[y * 100 * 3 + x * 3 + 1] = 0x00;
      data[y * 100 * 3 + x * 3 + 2] = 0x00;
    }
  }

  glfwMakeContextCurrent(window);
  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    // the openGL has two buffers, when you draw it's on the back buffers
    // when it renders, it uses the front buffer, we need sawp buffer to the front
    // otherwise it wont display cause it's always on the back buffer
    glfwSwapBuffers(window);
    

    glfwWaitEvents();
  }

  return 0;
}
