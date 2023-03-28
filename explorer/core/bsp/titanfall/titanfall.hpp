/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#pragma once

#include <string>

#include "titanfall_structs.hpp"
#include "../ibsp.hpp"
#include "../../../renderer/crenderer.hpp"


class CTitanfallBsp : public IBsp {
    private:
        std::vector<Vector3f>                    m_lmpVertices;
        std::vector<Vector3f>                    m_lmpVertexNormals;
        std::vector<Titanfall::VertexUnlit_t>    m_lmpUnlitVertices;
        std::vector<Titanfall::VertexLitFlat_t>  m_lmpLitFlatVertices;
        std::vector<Titanfall::VertexLitBump_t>  m_lmpLitBumpVertices;
        std::vector<Titanfall::VertexUnlitTS_t>  m_lmpUnlitTSVertices;
        std::vector<uint16_t>                    m_lmpMeshIndices;
        std::vector<Titanfall::Mesh_t>           m_lmpMeshes;
        std::vector<Titanfall::MaterialSort_t>   m_lmpMaterialSorts;
        std::vector<Titanfall::LightmapHeader_t> m_lmpLightmapHeaders;

        void DrawWindow_Meshes();
        void DrawWindow_LightmapHeaders();
    public:
        CTitanfallBsp(const char *filename) : IBsp(filename) { // g++ wont let me define this in the .cpp ???
            CopyLump( (int)eTitanfallLumps::VERTICES,         m_lmpVertices );
            CopyLump( (int)eTitanfallLumps::VERTEX_NORMALS,   m_lmpVertexNormals );
            CopyLump( (int)eTitanfallLumps::VERTEX_UNLIT,     m_lmpUnlitVertices );
            CopyLump( (int)eTitanfallLumps::VERTEX_LIT_FLAT,  m_lmpLitFlatVertices );
            CopyLump( (int)eTitanfallLumps::VERTEX_LIT_BUMP,  m_lmpLitBumpVertices );
            CopyLump( (int)eTitanfallLumps::VERTEX_UNLIT_TS,  m_lmpUnlitTSVertices );
            CopyLump( (int)eTitanfallLumps::MESH_INDICES,     m_lmpMeshIndices );
            CopyLump( (int)eTitanfallLumps::MESHES,           m_lmpMeshes );
            CopyLump( (int)eTitanfallLumps::MATERIAL_SORT,    m_lmpMaterialSorts );
            CopyLump( (int)eTitanfallLumps::LIGHTMAP_HEADERS, m_lmpLightmapHeaders );
            CloseFile();
        }
        virtual std::string                 GetGameName();
        virtual std::vector<LumpDef_t>      GetLumps();
        virtual void                        DrawLumpInspectWindow( int index );
        virtual std::vector<DrawableType_t> GetDrawableTypes();
        virtual void                        SetRendererMeshes( int id );
};