#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <GL\glew.h>

class Shader {
private:
    unsigned int m_RendererID;
    mutable std::unordered_map<std::string, int> m_UniformCache;

    std::string readShaderFile(const std::string& filepath);

    void checkCompileErrors(unsigned int shader, const std::string& type);

    unsigned int compileShader(unsigned int type, const std::string& source);

    unsigned int createProgram(const std::string& vertexPath, const std::string& fragmentPath);

    int getLocation(const std::string& name) const {
        auto it = m_UniformCache.find(name);
        if (it != m_UniformCache.end()) return it->second;

        int location = glGetUniformLocation(m_RendererID, name.c_str());
        m_UniformCache[name] = location;
        if (location == -1) {
            std::cout << "WARNING: Uniform '" << name << "' not found!" << std::endl;
        }
        return location;
    }

    void setUniformValue(int location, int v0) const { glUniform1i(location, v0); }
    void setUniformValue(int location, unsigned int v0) const { glUniform1ui(location, v0); }
    void setUniformValue(int location, float v0) const { glUniform1f(location, v0); }
    void setUniformValue(int location, double v0) const { glUniform1d(location, v0); }

    void setUniformValue(int location, int v0, int v1) const { glUniform2i(location, v0, v1); }
    void setUniformValue(int location, float v0, float v1) const { glUniform2f(location, v0, v1); }

    void setUniformValue(int location, int v0, int v1, int v2) const { glUniform3i(location, v0, v1, v2); }
    void setUniformValue(int location, float v0, float v1, float v2) const { glUniform3f(location, v0, v1, v2); }

    void setUniformValue(int location, int v0, int v1, int v2, int v3) const { glUniform4i(location, v0, v1, v2, v3); }
    void setUniformValue(int location, float v0, float v1, float v2, float v3) const { glUniform4f(location, v0, v1, v2, v3); }

    void setUniformValue(int location, const float* values, int count) const { glUniform1fv(location, count, values); }
    void setUniformValue(int location, const int* values, int count) const { glUniform1iv(location, count, values); }

    template<typename... Args>
    void setUniformImpl(const std::string& name, Args&&... args) const {
        int location = getLocation(name);
        setUniformValue(location, std::forward<Args>(args)...);
    }

public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;
    void unuse() const;

    template<typename... Args>
    void setUniform(const std::string& name, Args&&... args) const {
        setUniformImpl(name, std::forward<Args>(args)...);
    }
};