#include "shader.hpp"

namespace Umu 
{
    Shader::Shader(std::string vShader, std::string fShader)
    {
        m_program = initProgram(vShader, fShader);

        //TODO: Figure out how to abstract things like GenVertexArrays etc
        //into seperate functions
        start();
        glGenVertexArrays(1, &vao);
        bindVAO();

        glGenBuffers( 1, &vBuffer);
        glBindBuffer( GL_ARRAY_BUFFER, vBuffer);

        glGenBuffers(1, &iBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);

        //TODO:: This.. maybe shouldnt be in the base class
        locVertices = glGetAttribLocation(m_program, "vPosition");

        unbindVAO();
        stop();
    }

    Shader::~Shader()
    {
    }

    //-----------------------------------------PUBLIC------------------------------------------//

    void Shader::start()
    {
        glUseProgram(m_program);
    }

    void Shader::bindVAO()
    {
        glBindVertexArray(vao);
    }

    void Shader::prepareReadData()
    {
        glVertexAttribPointer(locVertices, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(locVertices);
    }

    void Shader::unbindVAO()
    {
        glBindVertexArray(0);
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