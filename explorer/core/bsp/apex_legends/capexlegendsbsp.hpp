#pragma once

#include <string>

#include "../ibsp.hpp"

class CApexLegendsBsp : public IBsp {
    public:
        CApexLegendsBsp(const char *filename) : IBsp(filename) {}; // g++ wont let me define this in the .cpp ???
        virtual std::string                 GetGameName();
        virtual std::vector<LumpDef_t>      GetLumps();
        virtual void                        DrawLumpInspectWindow( int index );
        virtual std::vector<DrawableType_t> GetDrawableTypes();
};