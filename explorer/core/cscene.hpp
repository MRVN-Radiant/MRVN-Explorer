#pragma once

#include <memory>
#include <vector>

#include "bsp/ibsp.hpp"

#include "../utils/logging.hpp"
#include "../utils/globals.hpp"

class CScene {
    private:
        std::string m_szName;
        int m_iID;
        bool m_bOpen;
        bool m_bValid;

        std::unique_ptr<IBsp> m_pBsp;
    public:
        std::string Name();
        int         ID();
        void        Remove();
        bool       *IsOpen();
        bool        IsValid();
                    CScene(const char *filename);
                    ~CScene();
};

inline std::vector<std::shared_ptr<CScene>> g_vecpScenes;
inline std::shared_ptr<CScene> g_pScene;