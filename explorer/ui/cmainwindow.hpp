#pragma once

#include <cstdlib>
#include <cstdio>
#include <memory>

#include "../renderer/crenderer.hpp"

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "../utils/globals.hpp"
#include "../utils/logging.hpp"

#include "../core/cscene.hpp"

class CMainWindow {
    private:
        GLFWwindow *m_pWindow;
        bool        m_bShouldClose;
        int         m_iFps;
        int         m_iTempFps;
        double      m_dSecondsStart;

        bool m_bDrawFileInformationWindow;
        bool m_bDrawViewportControlWindow;
        bool m_bDrawDemoWindow;
        bool m_bDrawConsoleWindow;
        bool m_bDrawDebugOverlay;
        bool m_bDrawControlsModal;
        bool m_bDrawAboutModal;

        void DrawMenuBar();
        void DrawFileInfo();
        void DrawViewportControl();
        void DrawConsole();

        void DrawDebugOverlay();

        void DrawAboutModal();
        void DrawControlsModal();
        void DrawFileChooserModal();
        void DrawErrorModal();
    public:
        CMainWindow();
        ~CMainWindow();
        void Loop();
        void Close();
};