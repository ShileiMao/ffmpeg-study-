#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) 
{
  // 1. retrieve the vertex/ragment source code from filepath
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  // ensure ifstream objects can throw exceptions:
  vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

  try 
  {
    // open files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into strign
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } 
  catch (std::ifstream::failure e) 
  {
    std::cout << "Error::shader::FILE_NOT_SUCCESSFULY_READ"<<std::endl;
    std::cout <<e.what()<<std::endl;
  }

  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  std::cout<<"vShaderCode: "<<vShaderCode<<std::endl;
  std::cout<<"fShaderCode: "<<fShaderCode<<std::endl;

  // 2. compile shaders
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  // print compile errors if any
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if(!success) 
  {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout<< "Error::Shader::Vertex::Compilation_failed\n"<<infoLog<<std::endl;
  }

  // fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if(!success) 
  {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout<< "Error::Shader::Fragment::Compilation_failed\n"<<infoLog<<std::endl;
  }

  // shader program
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  // print linking errors if any
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if(!success) 
  {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cout<<"Error::Shader::Program::Linking_failed\n"<<infoLog<<std::endl;
  }

  // delete the shader as they are linked into our program now and no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);

}

void Shader::use()
{
  glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}

void Shader::setInt(const std:: string &name, int value) const 
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const 
{
  glUniform1f(glGetUniformLocation(ID, name.c_str()),  value);
}
