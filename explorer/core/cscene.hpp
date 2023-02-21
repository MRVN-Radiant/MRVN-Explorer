#pragma once

#include <memory>
#include <vector>

#include "imgui.h"

#include "bsp/ibsp.hpp"
#include "bsp/apex_legends/capexlegendsbsp.hpp"
#include "bsp/titanfall/ctitanfallbsp.hpp"

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

        void UpdateRenderMeshes( int id );
};

inline std::vector<std::shared_ptr<CScene>> g_vecpScenes;
inline std::shared_ptr<CScene> g_pScene;