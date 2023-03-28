/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#pragma once

#include <memory>
#include <vector>

#include "imgui.h"

#include "bsp/ibsp.hpp"
#include "bsp/apex_legends/apexlegends.hpp"
#include "bsp/titanfall/titanfall.hpp"

#include "../utils/logging.hpp"
#include "../utils/globals.hpp"

class CScene {
    private:
        std::string m_szName;
        int  m_iID;
        bool m_bOpen;
        bool m_bValid;

        std::unique_ptr<IBsp>    m_pBsp;
        std::shared_ptr<CCamera> m_pCamera;

        bool m_abOpenWindows[128] = {0};

        // Settings
        bool m_bCullBackFaces;
        bool m_bDrawUnlit;
        bool m_bDrawLitFlat;
        bool m_bDrawLitBump;
        bool m_bDrawUnlitTS;
    public:
        CScene(const char *filename);
        ~CScene();

        std::string Name();
        int         ID();
        void        Remove();
        bool       *IsOpen();
        bool        IsValid();

        std::string GetGameName();
        int         GetBspVersion();

        void DrawLumpsList( bool hideUnused );
        void DrawViewportOptions();
        void DrawLumpWindows();

        void UpdateRenderMeshes( int id );
};

inline std::vector<std::shared_ptr<CScene>> g_vecpScenes;
inline std::shared_ptr<CScene> g_pScene;