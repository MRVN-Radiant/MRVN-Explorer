/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#pragma once

#include <vector>
#include <memory>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "imgui.h"

#include "cshader.hpp"
#include "ccamera.hpp"
#include "cmaterial.hpp"
#include "../utils/math.hpp"
#include "../utils/globals.hpp"
#include "../utils/logging.hpp"

#define RENDER_FLAG_UNLIT   ( 1 << 0 )
#define RENDER_FLAG_LITFLAT ( 1 << 1 )
#define RENDER_FLAG_LITBUMP ( 1 << 2 )
#define RENDER_FLAG_UNLITTS ( 1 << 3 )

class CRenderer {
    private:
        unsigned int vertexBuffer, indexBuffer;
    public:
        CRenderer();
        ~CRenderer();
        void Render(GLFWwindow *window);
        void Update();
        void Clear();
};

struct RenderVertex_t {
    Vector3f position;
    Vector3f normal;
    Vector2f UV;
};

struct RenderMesh_t {
    int triStart;
    int triCount;
    int flags;

    std::shared_ptr<CMaterial> pMaterial;
};

using RenderIndex_t = uint32_t;

inline int g_iRenderFlags;

inline std::unique_ptr<CRenderer> g_pRenderer;

inline std::vector<RenderMesh_t> g_vecRenderMehses;
inline std::vector<RenderVertex_t> g_vecRenderVertices;
inline std::vector<RenderIndex_t> g_vecRenderIndices;

template<typename T>
void Renderer_AddAABBToRenderPool( AABB<T> aabb ) {
    RenderMesh_t &mesh = g_vecRenderMehses.emplace_back();
    mesh.triStart = g_vecRenderIndices.size();
    mesh.flags = -1;
    mesh.pMaterial = CMaterial::AllocateNewMaterial();

    RenderIndex_t offset = g_vecRenderVertices.size();
    
    RenderVertex_t vertex;
    vertex.position = Vector3f ( aabb.mins.x(), aabb.mins.y(), aabb.mins.z() );
    vertex.normal = Vector3f ( -0.5, -0.5, -0.5 );
    g_vecRenderVertices.push_back( vertex );

    vertex.position = Vector3f ( aabb.mins.x(), aabb.maxs.y(), aabb.mins.z() );
    vertex.normal = Vector3f ( -0.5, 0.5, -0.5 );
    g_vecRenderVertices.push_back( vertex );

    vertex.position = Vector3f ( aabb.maxs.x(), aabb.maxs.y(), aabb.mins.z() );
    vertex.normal = Vector3f ( 0.5, 0.5, -0.5 );
    g_vecRenderVertices.push_back( vertex );

    vertex.position = Vector3f ( aabb.maxs.x(), aabb.mins.y(), aabb.mins.z() );
    vertex.normal = Vector3f ( 0.5, -0.5, -0.5 );
    g_vecRenderVertices.push_back( vertex );

    vertex.position = Vector3f ( aabb.mins.x(), aabb.mins.y(), aabb.maxs.z() );
    vertex.normal = Vector3f ( -0.5, -0.5, 0.5 );
    g_vecRenderVertices.push_back( vertex );

    vertex.position = Vector3f ( aabb.mins.x(), aabb.maxs.y(), aabb.maxs.z() );
    vertex.normal = Vector3f ( -0.5, 0.5, 0.5 );
    g_vecRenderVertices.push_back( vertex );

    vertex.position = Vector3f ( aabb.maxs.x(), aabb.maxs.y(), aabb.maxs.z() );
    vertex.normal = Vector3f ( 0.5, 0.5, 0.5 );
    g_vecRenderVertices.push_back( vertex );

    vertex.position = Vector3f ( aabb.maxs.x(), aabb.mins.y(), aabb.maxs.z() );
    vertex.normal = Vector3f ( 0.5, -0.5, 0.5 );
    g_vecRenderVertices.push_back( vertex );

    // Indices
    g_vecRenderIndices.push_back( offset + 3 );
    g_vecRenderIndices.push_back( offset + 1 );
    g_vecRenderIndices.push_back( offset + 0 );

    g_vecRenderIndices.push_back( offset + 3 );
    g_vecRenderIndices.push_back( offset + 2 );
    g_vecRenderIndices.push_back( offset + 1 );

    g_vecRenderIndices.push_back( offset + 4 );
    g_vecRenderIndices.push_back( offset + 5 );
    g_vecRenderIndices.push_back( offset + 7 );

    g_vecRenderIndices.push_back( offset + 5 );
    g_vecRenderIndices.push_back( offset + 6 );
    g_vecRenderIndices.push_back( offset + 7 );

    g_vecRenderIndices.push_back( offset + 0 );
    g_vecRenderIndices.push_back( offset + 1 );
    g_vecRenderIndices.push_back( offset + 4 );

    g_vecRenderIndices.push_back( offset + 1 );
    g_vecRenderIndices.push_back( offset + 5 );
    g_vecRenderIndices.push_back( offset + 4 );

    g_vecRenderIndices.push_back( offset + 1 );
    g_vecRenderIndices.push_back( offset + 2 );
    g_vecRenderIndices.push_back( offset + 5 );

    g_vecRenderIndices.push_back( offset + 2 );
    g_vecRenderIndices.push_back( offset + 6 );
    g_vecRenderIndices.push_back( offset + 5 );

    g_vecRenderIndices.push_back( offset + 2 );
    g_vecRenderIndices.push_back( offset + 3 );
    g_vecRenderIndices.push_back( offset + 6 );

    g_vecRenderIndices.push_back( offset + 3 );
    g_vecRenderIndices.push_back( offset + 7 );
    g_vecRenderIndices.push_back( offset + 6 );

    g_vecRenderIndices.push_back( offset + 3 );
    g_vecRenderIndices.push_back( offset + 0 );
    g_vecRenderIndices.push_back( offset + 7 );

    g_vecRenderIndices.push_back( offset + 0 );
    g_vecRenderIndices.push_back( offset + 4 );
    g_vecRenderIndices.push_back( offset + 7 );

    mesh.triCount = g_vecRenderIndices.size() - mesh.triStart;
}
