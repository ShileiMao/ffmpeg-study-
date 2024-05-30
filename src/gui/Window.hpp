#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__
#define GLFW_INCLUDE_NONE
#include <glad.h>
#include <GLFW/glfw3.h>
#include <linmath.h>
#include <functional>
#include <iostream>
#include "gl/Shader.hpp"

class Window {
	public: 
		Window(int width, int height, const char* title);
		void showWindow();
		void destroyWidnow();
		~Window();
	private: 
		GLFWwindow *window = NULL;
		bool windowVisible = true;
		GLuint vertex_buffer, vertex_shader, fragment_shader, program;
		GLuint mvp_location, vpos_location, vcol_location;
};
#endif
