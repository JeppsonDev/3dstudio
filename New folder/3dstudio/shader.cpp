#include "shader.hpp"

namespace Umu 
{
    Shader::Shader(std::string vShader, std::string fShader)
    {
        m_program = initProgram(vShader, fShader);
        
        //Register properties
        m_properties["vPosition"] = glGetAttribLocation(m_program, "vPosition");
        m_properties["vNormal"] = glGetAttribLocation(m_program, "vNormal");
        m_properties["vTexCoords"] = glGetAttribLocation(m_program, "vTexCoords");
        m_properties["u_Model"] = glGetUniformLocation(m_program, "u_Model");
        m_properties["u_View"] = glGetUniformLocation(m_program, "u_View");
        m_properties["u_Projection"] = glGetUniformLocation(m_program, "u_Projection");
        m_properties["u_LightPosition"] = glGetUniformLocation(m_program, "u_LightPosition");
        m_properties["u_AmbientLight"] = glGetUniformLocation(m_program, "u_AmbientLight");
        m_properties["u_LightIntensity"] = glGetUniformLocation(m_program, "u_LightIntensity");
        m_properties["u_AmbientConstant"] = glGetUniformLocation(m_program, "u_AmbientConstant");
        m_properties["u_DiffuseConstant"] = glGetUniformLocation(m_program, "u_DiffuseConstant");
        m_properties["u_SpecularConstant"] = glGetUniformLocation(m_program, "u_SpecularConstant");
        m_properties["u_Shininess"] = glGetUniformLocation(m_program, "u_Shininess");
        m_properties["u_Texture"] = glGetUniformLocation(m_program, "u_Texture");
        m_properties["u_ShouldRenderTexture"] = glGetUniformLocation(m_program, "u_ShouldRenderTexture");

        m_properties["u_LightSpaceMatrix"] = glGetUniformLocation(m_program, "u_LightSpaceMatrix"); //For shadow mapping
        m_properties["u_ShadowMap"] = glGetUniformLocation(m_program, "u_ShadowMap"); //For shadow mapping
    }

    Shader::Shader()
    {
    }

    Shader::~Shader()
    {
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    void Shader::setMat4(std::string uniformKey, mat4 matrix)
    {
        glUniformMatrix4fv(getProperty(uniformKey), 1, false, value_ptr(matrix));
    }

    void Shader::setVec3(std::string uniformKey, vec3 vector)
    {
        glUniform3fv(getProperty(uniformKey), 1, value_ptr(vector));
    }

    void Shader::setFloat(std::string uniformKey, float val)
    {
        glUniform1f(getProperty(uniformKey), val);
    }

    void Shader::setInt(std::string uniformKey, int val)
    {
        glUniform1i(getProperty(uniformKey), val);
    }

    GLuint Shader::getProperty(std::string key)
    {
        if(m_properties.find(key) == m_properties.end())
        {
            std::cerr << "COULD NOT FIND PROPERTY " << key << std::endl;
            return -1;
        }
        
        return m_properties[key];
    }

    void Shader::start()
    {
        glUseProgram(m_program);
    }

    void Shader::stop()
    {
        glUseProgram(0);
    }

    //-----------------------------------------PRIVATE------------------------------------------//
    std::string Shader::readShaderSource(const std::string shaderFile)
    {
        std::string shaderSource;
        std::string line;

        std::fstream fs(shaderFile, std::ios::in);
        if(!fs)
            return shaderSource;

        while (!fs.eof()) {
            getline(fs, line);
            shaderSource.append(line + '\n');
        }
        fs.close();
        return shaderSource;
    }

    GLuint Shader::initProgram(const std::string vertexPath, const std::string fragmentPath)
    {
        unsigned int ID;
        const char* geometryPath = nullptr;

        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
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
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();			
            // if geometry shader path is present, also load a geometry shader
            if(geometryPath != nullptr)
            {
                gShaderFile.open(geometryPath);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // if geometry shader is given, compile geometry shader
        unsigned int geometry;
        if(geometryPath != nullptr)
        {
            const char * gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if(geometryPath != nullptr)
            glAttachShader(ID, geometry);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        if(geometryPath != nullptr)
            glDeleteShader(geometry);
            
        return ID;
    }

    void Shader::checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if(type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
}