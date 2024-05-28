#ifndef __SHADER_HPP__
#define __SHADER_HPP__
#include <glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader 
{
  public: 
  // program ID;
  unsigned int ID;

  Shader(const char* vertexPath, const char* fragmentPath);

  void use();

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &nane, int value) const;
  void setFloat(const std::string &name, float value) const;
};
#endif