/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#pragma once

#include <cstdlib>
#include <memory>
#include <map>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "cshader.hpp"

class CMaterial;

inline std::map<std::size_t,std::shared_ptr<CMaterial>> g_vecMaterials;

class CMaterial {
    private:
        std::shared_ptr<CShader> m_pShader;
        int16_t m_iWidth, m_iHeight;
        GLuint m_iTexture;
    public:
        static std::shared_ptr<CMaterial> AllocateNewMaterial() {
            glm::fvec3 colors[6] = {
                glm::fvec3(0.5f, 0.9f, 0.9f),
                glm::fvec3(0.6f, 0.9f, 0.5f),
                glm::fvec3(0.8f, 0.5f, 0.9f),
                glm::fvec3(0.9f, 0.6f, 0.5f),
                glm::fvec3(0.7f, 0.8f, 0.3f),
                glm::fvec3(0.6f, 0.3f, 0.8f)
            };

            int i = std::rand() % 6;
            char buffer[4] = { 0x6, 0x6, 0x6, 0x6 };


            std::shared_ptr<CMaterial> material = std::make_shared<CMaterial>( buffer, 1, 1 );

            g_vecMaterials.emplace( std::make_pair( 0, material ) );

            return material;
        }

        CMaterial( char *buffer, int16_t width, int16_t height ) {
            this->m_iWidth = width;
            this->m_iHeight = height;

            m_pShader = GetDefaultShader();

            glGenTextures( 1, &this->m_iTexture );
            glBindTexture( GL_TEXTURE_2D, this->m_iTexture );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glGenerateMipmap(GL_TEXTURE_2D);


            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, this->m_iWidth, this->m_iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer );
        }

        void Use() {
            glBindTexture( GL_TEXTURE_2D, this->m_iTexture );
        }

        GLuint GetID() {
            return this->m_iTexture;
        }
};

