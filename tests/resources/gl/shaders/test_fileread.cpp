#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
void readFile2(const char* vertexPath, const char* fragmentPath);

int main()
{

  readFile2("fragment.fs", "vertex.vs");
  // ifstream inputFile("fragment.fs");

  // if(!inputFile.is_open())
  // {
  //   cerr<<"Error opening the file!"<<endl;
  //   return 1;
  // }

  // string line;
  // cout <<"File content: "<<endl;
  // while(getline(inputFile, line)) 
  // {
  //   cout << line << endl;
  // }
  // inputFile.close();
  return 0;
}


void readFile2(const char* vertexPath, const char* fragmentPath) 
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

  cout << "vShaderCode: "<<vShaderCode<<endl;
  cout <<"fShaderCode: "<<fragmentCode<<endl;

}