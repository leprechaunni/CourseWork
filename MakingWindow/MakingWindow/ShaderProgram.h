#pragma once

#include <glad/glad.h>
#include <string>

namespace RenderEngine {
    class ShaderProgram {
    public:
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        ~ShaderProgram();
        bool isCompiled() const { return m_isCompiled; }
        void use() const;
        void setInt(const std::string& name, const GLint value);
        void setFloat(const std::string& name, const GLfloat value);

        ShaderProgram() = delete;
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

    private:
        bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
        GLuint m_ID = 0;
        bool m_isCompiled = false;
    };
}