#ifndef RENDER_COLOR_HPP
#define RENDER_COLOR_HPP

#include <stdio.h>
#include <glad.h>
#include <GLFW/glfw3.h>

#include <math.h>

bool generate_gradient(uint8_t* start_color, uint8_t* end_color, uint8_t* gradient_out);

#endif