#pragma once

#include <string>

#include "../ibsp.hpp"

class CTitanfallBsp : public IBsp {
    public:
        CTitanfallBsp(const char *filename) : IBsp(filename) {}; // g++ wont let me define this in the .cpp ???
        virtual std::string                 GetGameName();
        virtual std::vector<LumpDef_t>      GetLumps();
        virtual void                        DrawLumpInspectWindow( int index );
        virtual std::vector<DrawableType_t> GetDrawableTypes();
};