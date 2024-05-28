#include<stdio.h>
#include "video_reader.hpp"
#include "render_color.hpp"
#include "gui/Window.hpp"

bool load_frame(const char* filename, int* width, int* height, unsigned char** data);

int main() {

  Window window = Window(1080, 640, "Hello world");
  window.showWindow();

  /*
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
  const char* file_name = "../tests/resources/file_example_MP4_480_1_5MG.mp4";
  unsigned char* frame_data;
  VideoReaderState vr_state;

  if(!video_reader_open(&vr_state, file_name)) {
    printf("Failed to open file\n");
    return 1;
  }

  if(!load_frame(file_name, &frame_width, &frame_height, &frame_data)) {
    printf("Failed to load frame data!\n");
    return 1;
  }

  
  glfwMakeContextCurrent(window);

  // generate texture
  GLuint tex_handle;
  glGenTextures(1, &tex_handle);
  glBindTexture(GL_TEXTURE_2D, tex_handle);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  //  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // allocate frame buffer
  frame_width = vr_state.width;
  frame_height = vr_state.height;
  frame_data = new uint8_t[frame_width * frame_height * 3];
  
  uint8_t* test_gradient = new uint8_t[255 * 255 * 4];
  uint8_t start_color[4] = {199, 184, 34, 0};
  uint8_t end_color[4] = {31, 72, 234, 0};
  frame_width = 255;
  frame_height = 255;

  generate_gradient(start_color, end_color, test_gradient);

  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int window_width, window_height;
    glfwGetFramebufferSize(window, &window_width, &window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window_width, 0, window_height, -1, 1);  
    //glOrtho(0, window_width, window_height, 0, -1, 1); // flip up side down
    glMatrixMode(GL_MODELVIEW);

    // render 
    // read the frame data and project on the screen
     if(!video_reader_read_frame(&vr_state, frame_data)) {
       printf("Failed to read frame\n");
       return 1;
     }
    
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, test_gradient);



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glBegin(GL_QUADS);
      glTexCoord2d(0, 0);glVertex2i(100, 100);
      glTexCoord2d(1, 0); glVertex2i(100 + frame_width , 100);
      glTexCoord2d(1, 1); glVertex2i(100 + frame_width, 100 + frame_height);
      glTexCoord2d(0, 1); glVertex2i(100, 100 + frame_height);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, NULL);
    // the openGL has two buffers, when you draw it's on the back buffers
    // when it renders, it uses the front buffer, we need sawp buffer to the front
    // otherwise it wont display cause it's always on the back buffer
    glfwSwapBuffers(window);

    glfwWaitEvents();
  }

  video_reader_close(&vr_state);
  video_reader_free(&vr_state);

  */

  return 0;
}


// void draw(uint8_t* buffer, int texture_id) {
  
//   // setup FBO
//   glGenFramebuffers( 1, buffer);
//   glBindFramebuffer( GL_FRAMEBUFFER, FFrameBuffer );
//   glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0 );
//   glBindFramebuffer( GL_FRAMEBUFFER, 0 );

//   // render to FBO
//   glBindFramebuffer( GL_FRAMEBUFFER, FFrameBuffer );
//   glViewport( 0, 0, YourTextureWidth, YourTextureHeight );
  
//   glBindFramebuffer( GL_FRAMEBUFFER, 0 );

//   // cleanup
//   glBindFramebuffer( GL_FRAMEBUFFER, 0 );
//   glDeleteFramebuffers( 1, buffer );
// }
