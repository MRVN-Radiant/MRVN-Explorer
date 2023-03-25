/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#include "ccamera.hpp"

#include "../utils/logging.hpp"


CCamera::CCamera() {
    m_fFov = 70.0f;
    m_fSpeed = 10.0f;
    m_v3Origin = glm::vec3( 0.0f, 0.0f, 0.0f );
    m_v2Rotation = glm::vec2( 0.0f, -90.0f );
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

void CCamera::Update( GLFWwindow *window, float width, float height ) {
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

    //
    if( glfwGetKey( window, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS )
        this->m_fSpeed = 100.0f;
    
    if( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS )
        this->Move( GLFW_KEY_W );
    if( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS )
        this->Move( GLFW_KEY_S );
    if( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS )
        this->Move( GLFW_KEY_A );
    if( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS )
        this->Move( GLFW_KEY_D );
    if( glfwGetKey( window, GLFW_KEY_E ) == GLFW_PRESS )
        this->Move( GLFW_KEY_E );
    if( glfwGetKey( window, GLFW_KEY_Q ) == GLFW_PRESS )
        this->Move( GLFW_KEY_Q );
    
    this->m_fSpeed = 10.0f;
    bool l_bIgnore = false;

    static int l_iLastEscState = GLFW_RELEASE;
    int        l_iCurrentEscState = glfwGetKey( window, GLFW_KEY_ESCAPE );
    if( l_iCurrentEscState != l_iLastEscState && l_iLastEscState == GLFW_PRESS ) {
        this->ToggleMouseCapture(window);
        l_bIgnore = true;
    }

    l_iLastEscState = l_iCurrentEscState;

    static double l_dLastMousePosX, l_dLastMousePosY;
    static double l_dCurrMousePosX, l_dCurrMousePosY;
    glfwGetCursorPos(window, &l_dCurrMousePosX, &l_dCurrMousePosY );

    float l_fDeltaX, l_fDeltaY;
    l_fDeltaX = l_dLastMousePosX - l_dCurrMousePosX;
    l_fDeltaY = l_dLastMousePosY - l_dCurrMousePosY;

    l_dLastMousePosX = l_dCurrMousePosX; l_dLastMousePosY = l_dCurrMousePosY;

    if( !l_bIgnore )
        this->Rotate( l_fDeltaX, l_fDeltaY );
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