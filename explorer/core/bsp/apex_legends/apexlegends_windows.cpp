/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#include "apexlegends.hpp"

#include "../../../utils/logging.hpp"

#include "imgui.h"

void CApexLegendsBsp::DrawLump_BVHLeafData() {
    ImGui::Text("BVHLeafData");
}

void CApexLegendsBsp::DrawLumpInspectWindow( int index ) {
    switch( index ) {
        case (int)eApexLegendsLumps::BVH_LEAF_DATA:
            DrawLump_BVHLeafData();
            break;
    }
}