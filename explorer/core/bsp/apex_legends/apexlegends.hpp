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
        std::vector<Vector3f>                     m_lmpVertices;
        std::vector<ApexLegends::BVHNode_t>       m_lmpBVHNodes;
        std::vector<Vector3f>                     m_lmpVertexNormals;
        std::vector<ApexLegends::VertexUnlit_t>   m_lmpUnlitVertices;
        std::vector<ApexLegends::VertexLitFlat_t> m_lmpLitFlatVertices;
        std::vector<ApexLegends::VertexLitBump_t> m_lmpLitBumpVertices;
        std::vector<ApexLegends::VertexUnlitTS_t> m_lmpUnlitTSVertices;
        std::vector<uint16_t>                     m_lmpMeshIndices;
        std::vector<ApexLegends::Mesh_t>          m_lmpMeshes;
        std::vector<ApexLegends::MaterialSort_t>  m_lmpMaterialSorts;
        std::vector<Titanfall::LightmapHeader_t>  m_lmpLightmapHeaders;
        std::vector<uint8_t>                      m_lmpLightmapDataSky;

        void SetRendererMeshes_BVHNodes();
        void SetRendererMeshes_Meshes( bool lightmaps );

        void DrawWindow_Meshes();
        void DrawWindow_LightmapHeaders();
    public:
        CApexLegendsBsp(const char *filename) : IBsp(filename) { // g++ wont let me define this in the .cpp ???
            CopyLump( (int)eApexLegendsLumps::VERTICES,          m_lmpVertices );
            CopyLump( (int)eApexLegendsLumps::BVH_NODES,         m_lmpBVHNodes );
            CopyLump( (int)eApexLegendsLumps::VERTEX_NORMALS,    m_lmpVertexNormals );
            CopyLump( (int)eApexLegendsLumps::VERTEX_UNLIT,      m_lmpUnlitVertices );
            CopyLump( (int)eApexLegendsLumps::VERTEX_LIT_FLAT,   m_lmpLitFlatVertices );
            CopyLump( (int)eApexLegendsLumps::VERTEX_LIT_BUMP,   m_lmpLitBumpVertices );
            CopyLump( (int)eApexLegendsLumps::VERTEX_UNLIT_TS,   m_lmpUnlitTSVertices );
            CopyLump( (int)eApexLegendsLumps::MESH_INDICES,      m_lmpMeshIndices );
            CopyLump( (int)eApexLegendsLumps::MESHES,            m_lmpMeshes );
            CopyLump( (int)eApexLegendsLumps::MATERIAL_SORT,     m_lmpMaterialSorts );
            CopyLump( (int)eApexLegendsLumps::LIGHTMAP_HEADERS,  m_lmpLightmapHeaders );
            CopyLump( (int)eApexLegendsLumps::LIGHTMAP_DATA_SKY, m_lmpLightmapDataSky );
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