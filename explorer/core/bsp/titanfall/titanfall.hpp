/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#pragma once

#include <string>

#include "titanfall_structs.hpp"
#include "fmt/core.h"
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
        std::vector<uint8_t>                     m_lmpLightmapDataSky;
        std::vector<Titanfall::CMGrid_t>         m_lmpCMGrid;
        std::vector<Titanfall::CMGeoSet_t>       m_lmpGeoSets;
        std::vector<Titanfall::CMBound_t>        m_lmpCMGeoBounds;
        std::vector<Titanfall::CMPrimitive_t>    m_lmpPrimitives;
        std::vector<Titanfall::CMBound_t>        m_lmpCMPrimitiveBounds;

        void SetRendererMeshes_Meshes( bool lightmaps );
        void SetRendererMeshes_CMGrid();
        void SetRendererMeshes_CMGeoSets();
        void SetRendererMeshes_CMPrimitives();

        void DrawWindow_Meshes();
        void DrawWindow_LightmapHeaders();
        void DrawWindow_CMGrid();
        void DrawWindow_CMGeoSets();
        void DrawWindow_CMPrimitives();
    public:
        CTitanfallBsp(const char *filename) : IBsp(filename) { // g++ wont let me define this in the .cpp ???
            CopyLump( (int)eTitanfallLumps::VERTICES,            m_lmpVertices );
            CopyLump( (int)eTitanfallLumps::VERTEX_NORMALS,      m_lmpVertexNormals );
            CopyLump( (int)eTitanfallLumps::VERTEX_UNLIT,        m_lmpUnlitVertices );
            CopyLump( (int)eTitanfallLumps::VERTEX_LIT_FLAT,     m_lmpLitFlatVertices );
            CopyLump( (int)eTitanfallLumps::VERTEX_LIT_BUMP,     m_lmpLitBumpVertices );
            CopyLump( (int)eTitanfallLumps::VERTEX_UNLIT_TS,     m_lmpUnlitTSVertices );
            CopyLump( (int)eTitanfallLumps::MESH_INDICES,        m_lmpMeshIndices );
            CopyLump( (int)eTitanfallLumps::MESHES,              m_lmpMeshes );
            CopyLump( (int)eTitanfallLumps::MATERIAL_SORT,       m_lmpMaterialSorts );
            CopyLump( (int)eTitanfallLumps::LIGHTMAP_HEADERS,    m_lmpLightmapHeaders );
            CopyLump( (int)eTitanfallLumps::LIGHTMAP_DATA_SKY,   m_lmpLightmapDataSky );
            CopyLump( (int)eTitanfallLumps::CM_GRID,             m_lmpCMGrid );
            CopyLump( (int)eTitanfallLumps::CM_GEO_SETS,         m_lmpGeoSets );
            CopyLump( (int)eTitanfallLumps::CM_GEO_SET_BOUNDS,   m_lmpCMGeoBounds );
            CopyLump( (int)eTitanfallLumps::CM_PRIMITIVES,       m_lmpPrimitives );
            CopyLump( (int)eTitanfallLumps::CM_PRIMITIVE_BOUNDS, m_lmpCMPrimitiveBounds );
            CloseFile();

            // Create materials for lightmap headers
            std::size_t offset = 0;
            for( std::size_t i = 0 ; i < this->m_lmpLightmapHeaders.size(); i++ ) {
                Titanfall::LightmapHeader_t &header = this->m_lmpLightmapHeaders.at(i);

                std::string name = fmt::format("{}_lightmapheader_{}", filename, i);
                CMaterial::AllocateNewMaterial( name, this->m_lmpLightmapDataSky.data() + offset, header.width, header.height );

                offset += header.width * header.height;
            }
        }
        virtual std::string                 GetGameName();
        virtual std::vector<LumpDef_t>      GetLumps();
        virtual void                        DrawLumpInspectWindow( int index );
        virtual std::vector<DrawableType_t> GetDrawableTypes();
        virtual void                        SetRendererMeshes( int id );
};