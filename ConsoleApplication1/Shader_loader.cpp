#include "shader_loader.h"

std::string Shader::readShaderFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "ERROR: Failed to open shader file: " << filepath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Shader::checkCompileErrors(unsigned int shader, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    checkCompileErrors(id, (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT");
    return id;
}

unsigned int Shader::createProgram(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = readShaderFile(vertexPath);
    std::string fragmentCode = readShaderFile(fragmentPath);

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    checkCompileErrors(program, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    m_RendererID = createProgram(vertexPath, fragmentPath);
}

Shader::~Shader() {
    glDeleteProgram(m_RendererID);
}

void Shader::use() const {
    glUseProgram(m_RendererID);
}

void Shader::unuse() const {
    glUseProgram(0);
}