#ifndef SHADER_HPP
#define SHADER_HPP

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
GLuint LoadStringShaders(const std::string& vertex_file_path, const std::string& fragment_file_path);

#endif
