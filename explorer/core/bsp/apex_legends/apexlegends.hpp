/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#pragma once

#include <string>

#include "apexlegends_structs.hpp"
#include "../ibsp.hpp"
#include "../../../renderer/crenderer.hpp"




class CApexLegendsBsp : public IBsp {
    private:
        std::vector<Vector3f>                   m_lmpVertices;
        std::vector<Vector3f>                   m_lmpVertexNormals;
        std::vector<ApexLegends::VertexUnlit_t>   m_lmpUnlitVertices;
        std::vector<ApexLegends::VertexLitFlat_t> m_lmpLitFlatVertices;
        std::vector<ApexLegends::VertexLitBump_t> m_lmpLitBumpVertices;
        std::vector<ApexLegends::VertexUnlitTS_t> m_lmpUnlitTSVertices;
        std::vector<uint16_t>                   m_lmpMeshIndices;
        std::vector<ApexLegends::Mesh_t>          m_lmpMeshes;
        std::vector<ApexLegends::MaterialSort_t>  m_lmpMaterialSorts;

        void DrawWindow_Meshes();
    public:
        CApexLegendsBsp(const char *filename) : IBsp(filename) { // g++ wont let me define this in the .cpp ???
            CopyLump( (int)eApexLegendsLumps::VERTICES,        m_lmpVertices );
            CopyLump( (int)eApexLegendsLumps::VERTEX_NORMALS,  m_lmpVertexNormals );
            CopyLump( (int)eApexLegendsLumps::VERTEX_UNLIT,    m_lmpUnlitVertices );
            CopyLump( (int)eApexLegendsLumps::VERTEX_LIT_FLAT, m_lmpLitFlatVertices );
            CopyLump( (int)eApexLegendsLumps::VERTEX_LIT_BUMP, m_lmpLitBumpVertices );
            CopyLump( (int)eApexLegendsLumps::VERTEX_UNLIT_TS, m_lmpUnlitTSVertices );
            CopyLump( (int)eApexLegendsLumps::MESH_INDICES,    m_lmpMeshIndices );
            CopyLump( (int)eApexLegendsLumps::MESHES,          m_lmpMeshes );
            CopyLump( (int)eApexLegendsLumps::MATERIAL_SORT,   m_lmpMaterialSorts );
            CloseFile();
        }
        virtual std::string                 GetGameName();
        virtual std::vector<LumpDef_t>      GetLumps();
        virtual void                        DrawLumpInspectWindow( int index );
        virtual std::vector<DrawableType_t> GetDrawableTypes();
        virtual void                        SetRendererMeshes( int id );
};