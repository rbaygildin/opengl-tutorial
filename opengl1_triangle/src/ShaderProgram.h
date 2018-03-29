//
// Created by Max Heartfield on 29.03.18.
//

#ifndef OPENGL1_TRIANGLE_SHADERPROGRAM_H
#define OPENGL1_TRIANGLE_SHADERPROGRAM_H

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <strstream>

#define VEC4(X, Y, Z, W) X, Y, Z, W
#define VEC3(X, Y, Z) X, Y, Z

using namespace std;

class ShaderProgram {
public:
    ShaderProgram(string vertexPath, string fragPath);
    void enable();
    void disable();
    void setUniformVec4(string name, float x, float y, float z, float w);
    void setUniformFloat(string name, float x);
    ~ShaderProgram();

private:
    GLuint programId, vsId, fsId;
};


#endif //OPENGL1_TRIANGLE_SHADERPROGRAM_H
