//#pragma once
//
//#include <glad/glad.h>
//#include <glm/glm.hpp>
//
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//
//class Shader
//{
//public:
//	Shader(const char* vertexPath, const char* fragmentPath);
//	~Shader();
//	void use();
//	void setBool(const std::string& name, bool value) const;
//	void setInt(const std::string& name, int value) const;
//	void setFloat(const std::string& name, float value) const;
//	void setFloatVec(const std::string& name, float* vec, int vec_size) const;
//	void setVec3(const std::string& name, glm::vec3 vec) const;
//	void setVec4(const std::string& name, glm::vec4 vec) const;
//	void setMatrix4F(const std::string& name, glm::mat4& m);
//	unsigned int ID();
//
//private:
//	unsigned int programID;
//	void checkCompileErrors(unsigned int shader, std::string type);
//};

#ifndef SHADER_HPP
#define SHADER_HPP 1
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <glew/include/GL/glew.h>
namespace EngineSpace
{
    class Shader
    {
        unsigned shaderId;
        GLenum type;

        std::string getSource(const std::string& fileName) const;
        std::string getCompileMessageErrorAndClear() const;

        Shader(const std::string& fileName, GLenum t);
    public:
        static Shader createVertexShader(const std::string& fileName)
        {
            return Shader(fileName, GL_VERTEX_SHADER);
        }

        static Shader createFragmentShader(const std::string& fileName)
        {
            return Shader(fileName, GL_FRAGMENT_SHADER);
        }

        static Shader createGeometryShader(const std::string& fileName)
        {
            return Shader(fileName, GL_GEOMETRY_SHADER);
        }

        static Shader createTessalationControlShader(const std::string& fileName)
        {
            return Shader(fileName, GL_TESS_CONTROL_SHADER);
        }

        static Shader createTessalationEvaluationShader(const std::string& fileName)
        {
            return Shader(fileName, GL_TESS_EVALUATION_SHADER);
        }

        static Shader createComputeShader(const std::string& fileName)
        {
            return Shader(fileName, GL_COMPUTE_SHADER);
        }

        void clear() const { glDeleteShader(shaderId); }

        unsigned getId() const { return shaderId; }
        GLenum getType() const { return type; }
    };
}
#endif
