#pragma once

#include <vector>
#include <memory>

#include <GLFW/glfw3.h>

#include "ccamera.hpp"
#include "../utils/math.hpp"


class CRenderer {
    private:
        std::shared_ptr<CCamera> m_pCamera;
    public:
        CRenderer();
        ~CRenderer();
        void Update(GLFWwindow *window);
};


struct RenderVertex_t {
    Vector3f position;
    Vector3f normal;
};

struct RenderMesh_t {
    int triStart;
    int triCount;
};


inline std::vector<RenderMesh_t> g_vecRenderMehses;