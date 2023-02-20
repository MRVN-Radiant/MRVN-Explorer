#pragma once

#include <cstdlib>
#include <cstdio>
#include <memory>

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "../utils/globals.hpp"
#include "../utils/logging.hpp"

#include "../core/cscene.hpp"

#include "../renderer/crenderer.hpp"

class CMainWindow {
    private:
        GLFWwindow                *m_pWindow;
        bool                       m_bShouldClose;
        std::unique_ptr<CRenderer> m_pRenderer;

        void DrawMenuBar();
        void DrawFileInfo();
        void DrawViewportControl();
        void DrawConsole();

        void DrawDebugOverlay();

        void DrawAboutModal();
        void DrawFileChooserModal();
        void DrawErrorModal();
    public:
        CMainWindow();
        ~CMainWindow();
        void Loop();
        void Close();
};