#include "ccamera.hpp"

#include "../utils/logging.hpp"


CCamera::CCamera() {
    m_fFov = 70.0f;
    m_fSpeed = 10.0f;
    m_v3Origin = glm::vec3( 0.0f, 0.0f, 0.0f );
    m_v2Rotation = glm::vec2( 0.0f, 0.0f );
    m_m4ViewMatrix = glm::mat4( 1.0f );
    m_bCursorCaptured = false;
}

CCamera::~CCamera() {

}

void CCamera::Move( int key ) {
    switch( key ) {
        case GLFW_KEY_W:
            m_v3Origin -= m_v3Front * m_fSpeed;
            break;
        case GLFW_KEY_S:
            m_v3Origin += m_v3Front * m_fSpeed;
            break;
        case GLFW_KEY_A:
            m_v3Origin += m_v3Right * m_fSpeed;
            break;
        case GLFW_KEY_D:
            m_v3Origin -= m_v3Right * m_fSpeed;
            break;
        case GLFW_KEY_E:
            m_v3Origin += m_v3Up * m_fSpeed;
            break;
        case GLFW_KEY_Q:
            m_v3Origin -= m_v3Up * m_fSpeed;
            break;
    }
}

void CCamera::Update( float width, float height ) {
    // Calculate direction vectors
    m_v3Front.x = sin( glm::radians( m_v2Rotation.x ) ) * cos(glm::radians(m_v2Rotation.y + 90));
    m_v3Front.y = cos( glm::radians( m_v2Rotation.x ) ) * cos(glm::radians(m_v2Rotation.y + 90));
    m_v3Front.z = -sin( glm::radians( m_v2Rotation.y + 90 ) );

    m_v3Right = glm::normalize( glm::cross( glm::vec3( 0.0, 0.0, -1.0f ), m_v3Front ) );
    m_v3Front = glm::normalize( m_v3Front );
    m_v3Up = glm::vec3( 0.0, 0.0, -1.0f );

    glm::mat4 l_m4Perspective = glm::perspective( glm::radians( m_fFov ), width / height, 0.1f, 1000000.0f );

    m_m4ViewMatrix = glm::rotate( l_m4Perspective, glm::radians( m_v2Rotation.y ), glm::vec3( 1.0, 0.0, 0.0 ) );
    m_m4ViewMatrix = glm::rotate( m_m4ViewMatrix, glm::radians( m_v2Rotation.x ), glm::vec3( 0.0, 0.0, 1.0 ) );

    m_m4ViewMatrix = glm::translate( m_m4ViewMatrix, m_v3Origin );
}

void CCamera::Rotate( float dX, float dY ) {
    if( !this->m_bCursorCaptured )
        return;

    this->m_v2Rotation.x -= dX * 0.2;
    this->m_v2Rotation.y -= dY * 0.2;

    this->m_v2Rotation.y = this->m_v2Rotation.y > 0 ? 0: this->m_v2Rotation.y;
    this->m_v2Rotation.y = this->m_v2Rotation.y < -180 ? -180: this->m_v2Rotation.y;

}

glm::mat4 CCamera::GetViewMatrix() {
    return this->m_m4ViewMatrix;
}

void CCamera::ToggleMouseCapture(GLFWwindow *window) {
    if( this->m_bCursorCaptured ) {
        glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
    } else {
        glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    }

    this->m_bCursorCaptured = !this->m_bCursorCaptured;
}