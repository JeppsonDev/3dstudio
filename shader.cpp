#include "shader.hpp"

namespace Umu 
{
    Shader::Shader(std::string vShader, std::string fShader)
    {
        m_program = initProgram(vShader, fShader);

        //TODO: All of these variables can be removed and put directly into m_properties
        m_vPosition = glGetAttribLocation(m_program, "vPosition");
        m_vNormal = glGetAttribLocation(m_program, "vNormal");
        m_uModel = glGetUniformLocation(m_program, "u_Model");
        m_uView = glGetUniformLocation(m_program, "u_View");
        m_uProjection = glGetUniformLocation(m_program, "u_Projection");
        m_uLightPosition = glGetUniformLocation(m_program, "u_LightPosition");
        m_uAmbientLight = glGetUniformLocation(m_program, "u_AmbientLight");
        m_uLightIntensity = glGetUniformLocation(m_program, "u_LightIntensity");
        m_uAmbientConstant = glGetUniformLocation(m_program, "u_AmbientConstant");
        m_uDiffuseConstant = glGetUniformLocation(m_program, "u_DiffuseConstant");
        m_uSpecularConstant = glGetUniformLocation(m_program, "u_SpecularConstant");

        //Register properties
        m_properties["vPosition"] = m_vPosition;
        m_properties["vNormal"] = m_vNormal;
        m_properties["vTexCoords"] = glGetAttribLocation(m_program, "vTexCoords");
        m_properties["u_Model"] = m_uModel;
        m_properties["u_View"] = m_uView;
        m_properties["u_Projection"] = m_uProjection;
        m_properties["u_LightPosition"] = m_uLightPosition;
        m_properties["u_AmbientLight"] = m_uAmbientLight;
        m_properties["u_LightIntensity"] = m_uLightIntensity;
        m_properties["u_AmbientConstant"] = m_uAmbientConstant;
        m_properties["u_DiffuseConstant"] = m_uDiffuseConstant;
        m_properties["u_SpecularConstant"] = m_uSpecularConstant;
        m_properties["u_Shininess"] = glGetUniformLocation(m_program, "u_Shininess");
        m_properties["u_Texture"] = glGetUniformLocation(m_program, "u_Texture");
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
            //checkOpenGLError();

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
        //checkOpenGLError();

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