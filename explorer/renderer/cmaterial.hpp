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
            const int numColors = 6;
            std::size_t index = std::rand() % numColors;

            
            if( g_vecMaterials.find( index ) != g_vecMaterials.end() ) {
                return g_vecMaterials[index];
            } 

            unsigned char colors[numColors][3] = {
                { 0x9B, 0xEF, 0xE7 },
                { 0x9B, 0xCE, 0xEF },
                { 0x9B, 0xEF, 0xBD },
                { 0xEA, 0x9B, 0xEF },
                { 0xAB, 0xEF, 0x9B },
                { 0x9B, 0xEF, 0xAD },
            };

            // Generates a dev texture with borders
            unsigned char buffer[256 * 256 * 4];
            for( int y = 0; y < 256; y++ ) {
                for( int x = 0; x < 256; x++ ) {
                    unsigned char color[3] = { colors[index][0], colors[index][1], colors[index][2] };
                    if( x < 4 || x > 251 || y < 4 || y > 251 || x > 124 && x < 126 || y > 124 && y < 126 ) {
                        color[0] = 0xFF - color[0] < 0x30 ? 0xFF : color[0] + 0x30;
                        color[1] = 0xFF - color[1] < 0x30 ? 0xFF : color[1] + 0x30;
                        color[2] = 0xFF - color[2] < 0x30 ? 0xFF : color[2] + 0x30;
                    }

                    buffer[(y * 256 + x) * 4 + 0] = color[0];
                    buffer[(y * 256 + x) * 4 + 1] = color[1];
                    buffer[(y * 256 + x) * 4 + 2] = color[2];
                    buffer[(y * 256 + x) * 4 + 3] = 0xFF;
                }
            }


            std::shared_ptr<CMaterial> material = std::make_shared<CMaterial>( buffer, 256, 256 );

            g_vecMaterials.emplace( std::make_pair( index, material ) );

            return material;
        }

        CMaterial( unsigned char *buffer, int16_t width, int16_t height ) {
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

