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
        m_properties["u_LightSpaceMatrix"] = glGetUniformLocation(m_program, "u_LightSpaceMatrix");

        m_properties["u_CameraPosition"] = glGetUniformLocation(m_program, "u_CameraPosition");
        m_properties["u_LightPosition"] = glGetUniformLocation(m_program, "u_LightPosition");
        m_properties["u_AmbientLight"] = glGetUniformLocation(m_program, "u_AmbientLight");
        m_properties["u_LightIntensity"] = glGetUniformLocation(m_program, "u_LightIntensity");
        m_properties["u_AmbientConstant"] = glGetUniformLocation(m_program, "u_AmbientConstant");
        m_properties["u_DiffuseConstant"] = glGetUniformLocation(m_program, "u_DiffuseConstant");
        m_properties["u_SpecularConstant"] = glGetUniformLocation(m_program, "u_SpecularConstant");
        m_properties["u_Shininess"] = glGetUniformLocation(m_program, "u_Shininess");
        m_properties["u_Texture"] = glGetUniformLocation(m_program, "u_Texture");
        m_properties["u_DepthTexture"] = glGetUniformLocation(m_program, "u_DepthTexture");
        m_properties["u_ShouldRenderTexture"] = glGetUniformLocation(m_program, "u_ShouldRenderTexture");
    }

    Shader::Shader()
    {
    }

    Shader::~Shader()
    {
        std::cout << "Freeing shader" << std::endl;
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
            //std::cerr << "Could not find property " << key << std::endl;
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

    GLuint Shader::initProgram(const std::string vShaderFile, const std::string fShaderFile)
    {
        GLuint program;
        int i;
        GLint  linked;

        struct shaders_t{
            std::string   filename;
            GLenum   type;
        };

        shaders_t shaders[2] = {
            { vShaderFile, GL_VERTEX_SHADER },
            { fShaderFile, GL_FRAGMENT_SHADER }
        };

        program = glCreateProgram();
        for (i = 0; i < 2; ++i ) {
            GLuint shader;
            GLint  compiled;

            std::string shaderSource = readShaderSource( shaders[i].filename );
            if ( shaderSource.empty() ) {
                std::cerr << "Failed to read " << shaders[i].filename << std::endl;
                exit( EXIT_FAILURE );
            }

            shader = glCreateShader( shaders[i].type );
            const char *shaderSrc = shaderSource.c_str();
            glShaderSource( shader, 1, &shaderSrc, NULL );
            glCompileShader( shader );
            GLenum glError = glGetError();
            
            while (glError != GL_NO_ERROR) {
                std::cerr << "glError: " << glError << std::endl;
                glError = glGetError();
            }

            glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
            if ( !compiled ) {
                GLint  logSize;

                std::cerr << "Failed to compile " << shaders[i].filename << std::endl;
                glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
                if (logSize > 0) {
                    char logMsg[logSize+1];
                    glGetShaderInfoLog( shader, logSize, nullptr, &(logMsg[0]) );
                    std::cerr << "Shader info log: " << logMsg << std::endl;
                }
                exit( EXIT_FAILURE );
            }
            glAttachShader( program, shader );
        }

        /* link  and error check */
        glLinkProgram(program);
        GLenum glError = glGetError();
        
        while (glError != GL_NO_ERROR) {
            std::cerr << "glError: " << glError << std::endl;
            glError = glGetError();
        }

        glGetProgramiv( program, GL_LINK_STATUS, &linked );
        if ( !linked ) {
            GLint  logSize;

            std::cerr << "Shader program failed to link!" << std::endl;

            glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
            if ( logSize > 0 ) {
                char logMsg[logSize+1];
                glGetProgramInfoLog( program, logSize, NULL, &(logMsg[0]) );
                std::cerr << "Program info log: " << logMsg << std::endl;
                free(logMsg);
            }
            exit( EXIT_FAILURE );
        }

        return program;
    }
}