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
};

struct RenderMesh_t {
    int triStart;
    int triCount;
    int flags;
};

using RenderIndex_t = uint32_t;

inline int g_iRenderFlags;

inline std::unique_ptr<CRenderer> g_pRenderer;

inline std::vector<RenderMesh_t> g_vecRenderMehses;
inline std::vector<RenderVertex_t> g_vecRenderVertices;
inline std::vector<RenderIndex_t> g_vecRenderIndices;