//
// Created by Max Heartfield on 29.03.18.
//

#include <sstream>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(string vertexPath, string fragPath) {
    ifstream vertexShader, fragShader;
    vertexShader.exceptions(ifstream::failbit | ifstream::badbit);
    fragShader.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        vertexShader.open(vertexPath);
        fragShader.open(fragPath);
        stringstream vertexStream, fragStream;
        vertexStream << vertexShader.rdbuf();
        fragStream << fragShader.rdbuf();
        const char *vsSource = vertexStream.str().c_str();
        const char *fsSource = fragStream.str().c_str();
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vsSource, nullptr);
        glCompileShader(vs);

        char infoLog[512];
        int success;
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vs, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fsSource, nullptr);
        glCompileShader(fs);

        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fs, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        programId = glCreateProgram();
        glAttachShader(programId, fs);
        glAttachShader(programId, vs);
        glLinkProgram(programId);

        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(programId, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
    catch (ifstream::failure &e) {
        cerr << e.what();
        exit(EXIT_FAILURE);
    }
}

void ShaderProgram::enable() {
    glUseProgram(programId);
}

void ShaderProgram::disable() {
    glUseProgram(0);
}

void ShaderProgram::setUniformVec4(string name, float x, float y, float z, float w) {
    int location = glGetUniformLocation(programId, name.c_str());
    glUniform4f(location, x, y, z, w);
}

void ShaderProgram::setUniformFloat(string name, float x) {
    int location = glGetUniformLocation(programId, name.c_str());
    glUniform1f(location, x);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(programId);
    glDeleteShader(vsId);
    glDeleteShader(fsId);
}
