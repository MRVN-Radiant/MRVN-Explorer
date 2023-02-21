#pragma once

#include <memory>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CCamera {
    private:
        float m_fFov, m_fSpeed;

        glm::vec3 m_v3Origin;
        glm::vec2 m_v2Rotation;

        glm::vec3 m_v3Front, m_v3Right, m_v3Up;
        glm::mat4 m_m4ViewMatrix;

        bool m_bCursorCaptured;
    public:
        CCamera();
        ~CCamera();

        void Update( GLFWwindow *window, float width, float height );
        void Move( int key );
        void Rotate( float dX, float dY );
        void ToggleMouseCapture(GLFWwindow *window);

        glm::mat4 GetViewMatrix();
};

inline std::shared_ptr<CCamera> g_pCamera;