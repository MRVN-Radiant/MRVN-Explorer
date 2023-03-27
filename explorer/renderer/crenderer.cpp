/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#include "crenderer.hpp"


CRenderer::CRenderer() {
    fs::path shadersDir = fs::path("./shaders/");

    if(!fs::exists(shadersDir)) {
        LOG_FILESYSTEM_ERROR("CRenderer::CRenderer: \"shaders\" dir not found!")
        exit(-1);
    }

    if( glewInit() != GLEW_OK ) {
        LOG_OPENGL_ERROR("Failed to initilaze GLEW!")
        exit(-1);
    }
    LOG_OPENGL_INFO("GLEW Initilazed")

    g_vecpShaders.emplace_back( std::make_shared<CShader>(fs::path(shadersDir / "basic.vert"), fs::path(shadersDir / "basic.frag")) );

    glEnable( GL_DEPTH_TEST );
    glCullFace( GL_FRONT );
    glEnable( GL_CULL_FACE );
}

CRenderer::~CRenderer() {

}

void CRenderer::Render(GLFWwindow *window) {
    if( g_pCamera != NULL ) {
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);

        g_pCamera->Update(window, display_w, display_h);

        unsigned int transLoc = glGetUniformLocation( GetDefaultShader()->GetID(), "transform" );
        glUniformMatrix4fv( transLoc, 1, GL_FALSE, glm::value_ptr( g_pCamera->GetViewMatrix() ) );
    }

    glm::fvec3 colors[6] = {
        glm::fvec3(0.5f, 0.9f, 0.9f),
        glm::fvec3(0.6f, 0.9f, 0.5f),
        glm::fvec3(0.8f, 0.5f, 0.9f),
        glm::fvec3(0.9f, 0.6f, 0.5f),
        glm::fvec3(0.7f, 0.8f, 0.3f),
        glm::fvec3(0.6f, 0.3f, 0.8f)
    };

    for( std::size_t i = 0; i < g_vecRenderMehses.size(); i++ ) {
        RenderMesh_t &rm = g_vecRenderMehses[i];

        if( !(rm.flags & g_iRenderFlags) )
            continue;

        // glm::fvec3 color = colors[i % 6];
        // unsigned int colorLoc = glGetUniformLocation( g_vecpShaders[0]->GetID(), "base" );
        // glUniform3fv( colorLoc, 1, glm::value_ptr( color ) );
        // unsigned int loc = glGetUniformLocation( g_vecpShaders[0]->GetID(), "CurrentTexture" );
        // glUniform1i( loc, 0 );

        rm.pMaterial->Use();

        glDrawElements( GL_TRIANGLES, rm.triCount, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * rm.triStart ) );
    }
}

void CRenderer::Update() {
    LOG_OPENGL_INFO("CRenderer::Update: Updating to {} vertices using {} triangles", g_vecRenderVertices.size(), g_vecRenderIndices.size() / 3)
    glGenBuffers( 1, &vertexBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(RenderVertex_t) * g_vecRenderVertices.size(), &g_vecRenderVertices.front(), GL_STATIC_DRAW );

    glGenBuffers( 1, &indexBuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(RenderIndex_t) * g_vecRenderIndices.size(), &g_vecRenderIndices.front(), GL_STATIC_DRAW );

    GetDefaultShader()->Use();

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( RenderVertex_t ), (void*)offsetof( RenderVertex_t, position ) );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( RenderVertex_t ), (void*)offsetof( RenderVertex_t, normal ) );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( RenderVertex_t ), (void*)offsetof( RenderVertex_t, UV ) );
    glEnableVertexAttribArray( 2 );
}

void CRenderer::Clear() {
    g_vecRenderMehses.clear();
    g_vecRenderVertices.clear();
    g_vecRenderIndices.clear();
}