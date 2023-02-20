#pragma once

#include <fstream>
#include <vector>
#include <string>

#include "../../utils/logging.hpp"


// File structs
struct LumpEntry_t {
    int32_t offset;
    int32_t length;
    int32_t version;
    int32_t padding;
};

struct Header_t {
    char ident[4];      // "rBSP"
    int32_t version;    // 29 - r1; 37 - r2; 47 - r5
    int32_t mapVersion; // Always 30 on respawn maps
    int32_t lastLump;   // Always 127
    LumpEntry_t lumps[128];
};

// Our lump definition for UI
struct LumpDef_t {
    const char    *name;
    int32_t        size;
    std::size_t entries;
    int32_t     version;
    int32_t gameVersion;
    bool     canInspect;
};

struct DrawableType_t {
    const char *name;
    int         id;
};

class IBsp {
    public:
        Header_t m_header;

        IBsp(const char *filename);
        ~IBsp();

        int GetBspVersion();

        virtual std::string                 GetGameName() = 0;
        virtual std::vector<LumpDef_t>      GetLumps() = 0;
        virtual void                        DrawLumpInspectWindow( int index ) = 0;
        virtual std::vector<DrawableType_t> GetDrawableTypes() = 0;
};