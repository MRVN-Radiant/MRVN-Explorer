/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#pragma once

#include <fstream>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "../utils/globals.hpp"
#include "../utils/logging.hpp"


class CShader {
    private:
        unsigned int m_iID;
    public:
        CShader(fs::path vertPath, fs::path fragPath) {
            
            if( !fs::exists(vertPath) ) {
                LOG_OPENGL_ERROR("Vertex shader: \"{}\" doesnt exist", vertPath.string().c_str())
                return;
            }

            if( !fs::exists(fragPath) ) {
                LOG_OPENGL_ERROR("Fragment shader: \"{}\" doesnt exist", fragPath.string().c_str())
                return;
            }


            unsigned int vertex, fragment;
            int success;
            char buffer[512];

            // Load vert file
            std::ifstream vertFile(vertPath);
            std::string vertString( ( std::istreambuf_iterator<char>( vertFile ) ),
                                    ( std::istreambuf_iterator<char>() ) );
            vertFile.close();

            const char* vertCode = vertString.c_str();
            vertex = glCreateShader( GL_VERTEX_SHADER );
            glShaderSource( vertex, 1, &vertCode, NULL );
            glCompileShader( vertex );
            glGetShaderiv( vertex, GL_COMPILE_STATUS, &success );

            if( !success ) {
                glGetShaderInfoLog( vertex, 512, NULL, buffer );
                LOG_OPENGL_ERROR("An error occured while compiling the vertex shader!")
                LOG_OPENGL_ERROR("{}", buffer )
            }

            // Load frag file
            std::ifstream fragFile(fragPath);
            std::string fragString( ( std::istreambuf_iterator<char>( fragFile ) ),
                                    ( std::istreambuf_iterator<char>() ) );
            fragFile.close();

            const char* fragCode = fragString.c_str();
            fragment = glCreateShader( GL_FRAGMENT_SHADER );
            glShaderSource( fragment, 1, &fragCode, NULL );
            glCompileShader( fragment );
            glGetShaderiv( fragment, GL_COMPILE_STATUS, &success );

            if( !success ) {
                glGetShaderInfoLog( fragment, 512, NULL, buffer );
                LOG_OPENGL_ERROR("An error occured while compiling the fragment shader!")
                LOG_OPENGL_ERROR("{}", buffer )
            }

            this->m_iID = glCreateProgram();
            glAttachShader( this->m_iID, vertex );
            glAttachShader( this->m_iID, fragment );
            glLinkProgram(  this->m_iID );
            glGetProgramiv( this->m_iID, GL_LINK_STATUS, &success );
            if( !success ) {
                LOG_OPENGL_ERROR("An error occured while compiling the shader program!")
            }

            glDeleteShader( vertex );
            glDeleteShader( fragment );
        }

        void Use() {
            glUseProgram( this->m_iID );
        }

        unsigned int GetID() {
            return this->m_iID;
        }
};

inline std::vector<std::shared_ptr<CShader>> g_vecpShaders;



static std::shared_ptr<CShader> GetDefaultShader() {
    return g_vecpShaders.at(0);
}