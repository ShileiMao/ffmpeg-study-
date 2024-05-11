#include<stdio.h>
#include <GLFW/glfw3.h>

bool load_frame(const char* filename, int* width, int* height, unsigned char** data);

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

  int frame_width, frame_height;
  unsigned char* frame_data;
  if(!load_frame("/Users/shileimao/Downloads/20211028_151916.mp4", &frame_width, &frame_height, &frame_data)) {
    printf("Failed to load frame data!\n");
    return 1;
  }

  
  glfwMakeContextCurrent(window);

  GLuint tex_handle;
  glGenTextures(1, &tex_handle);
  glBindTexture(GL_TEXTURE_2D, tex_handle);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 100, 100, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame_data);
  
  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    int window_width, window_height;
    glfwGetFramebufferSize(window, &window_width, &window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(0, window_width, 0, window_height, -1, 1);  
    glOrtho(0, window_width, window_height, 0, -1, 1); // flip up side down
    glMatrixMode(GL_MODELVIEW);

    // render 
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glBegin(GL_QUADS);
      glTexCoord2d(0, 0);glVertex2i(0, 0);
      glTexCoord2d(1, 0); glVertex2i(100 + frame_width , 0);
      glTexCoord2d(1, 1); glVertex2i(100 + frame_width, 100 + frame_height);
      glTexCoord2d(0, 1); glVertex2i(0, 100 + frame_height);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // the openGL has two buffers, when you draw it's on the back buffers
    // when it renders, it uses the front buffer, we need sawp buffer to the front
    // otherwise it wont display cause it's always on the back buffer
    glfwSwapBuffers(window);
    

    glfwWaitEvents();
  }

  return 0;
}
