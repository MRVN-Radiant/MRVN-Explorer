/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#include "titanfall.hpp"

#include "../../../utils/logging.hpp"


void CTitanfallBsp::SetRendererMeshes( int id ) {
    LOG_OPENGL_INFO("CTitanfallBsp::SetRendererMeshes: Set to {}", id)

    switch( id ) {
        case (int)eTitanfallLumps::MESHES:
            CTitanfallBsp::SetRendererMeshes_Meshes( false );
            break;
        case (int)eTitanfallLumps::LIGHTMAP_DATA_SKY:
            CTitanfallBsp::SetRendererMeshes_Meshes( true );
            break;
        case (int)eTitanfallLumps::CM_GRID:
            CTitanfallBsp::SetRendererMeshes_CMGrid();
            break;
    }
}

void CTitanfallBsp::SetRendererMeshes_CMGrid() {
    for( int x = 0; x < this->m_lmpCMGrid[0].xCount; x++ ) {
        for( int y = 0; y < this->m_lmpCMGrid[0].yCount; y++ ) {
            AABB<float> aabb;
            aabb.mins.vec[0] = ( this->m_lmpCMGrid[0].xOffset + x ) * this->m_lmpCMGrid[0].scale;
            aabb.mins.vec[1] = ( this->m_lmpCMGrid[0].yOffset + y ) * this->m_lmpCMGrid[0].scale;
            aabb.mins.vec[2] = -128.0f;

            aabb.maxs.vec[0] = ( this->m_lmpCMGrid[0].xOffset + x + 1 ) * this->m_lmpCMGrid[0].scale;
            aabb.maxs.vec[1] = ( this->m_lmpCMGrid[0].yOffset + y + 1 ) * this->m_lmpCMGrid[0].scale;
            aabb.maxs.vec[2] = 128.0f;

            Renderer_AddAABBToRenderPool( aabb );
        }
    }
}

void CTitanfallBsp::SetRendererMeshes_Meshes( bool lightmaps ) {
    const int S_VERTEX_LIT_FLAT      = 0x00000000;
    const int S_VERTEX_LIT_BUMP      = 0x00000200;
    const int S_VERTEX_UNLIT         = 0x00000400;
    const int S_VERTEX_UNLIT_TS      = 0x00000600;

    // Emit vertices
    // Lit Flat
    for( Titanfall::VertexLitFlat_t &vtx : this->m_lmpLitFlatVertices ) {
        RenderVertex_t &rv = g_vecRenderVertices.emplace_back();
        rv.position = this->m_lmpVertices[vtx.vertexIndex];
        rv.normal = this->m_lmpVertexNormals[vtx.normalIndex];
        rv.UV = vtx.uv0;
    }
    // Unlit
    for( Titanfall::VertexUnlit_t &vtx : this->m_lmpUnlitVertices ) {
        RenderVertex_t &rv = g_vecRenderVertices.emplace_back();
        rv.position = this->m_lmpVertices[vtx.vertexIndex];
        rv.normal = this->m_lmpVertexNormals[vtx.normalIndex];
        rv.UV = vtx.uv0;
    }
    // Lit Bump
    for( Titanfall::VertexLitBump_t &vtx : this->m_lmpLitBumpVertices ) {
        RenderVertex_t &rv = g_vecRenderVertices.emplace_back();
        rv.position = this->m_lmpVertices[vtx.vertexIndex];
        rv.normal = this->m_lmpVertexNormals[vtx.normalIndex];
        if( lightmaps )
            rv.UV = vtx.uv1;
        else
            rv.UV = vtx.uv0;
    }
    // Unlit TS
    for( Titanfall::VertexUnlitTS_t &vtx : this->m_lmpUnlitTSVertices ) {
        RenderVertex_t &rv = g_vecRenderVertices.emplace_back();
        rv.position = this->m_lmpVertices[vtx.vertexIndex];
        rv.normal = this->m_lmpVertexNormals[vtx.normalIndex];
        rv.UV = vtx.uv0;
    }

    for( Titanfall::Mesh_t &tfMesh : this->m_lmpMeshes ) {
        RenderMesh_t &rdMesh = g_vecRenderMehses.emplace_back();
        rdMesh.triStart = g_vecRenderIndices.size();
        rdMesh.pMaterial = CMaterial::AllocateNewMaterial();

        for( uint16_t idx = 0; idx < tfMesh.triCount * 3; idx++ ) {
            RenderIndex_t triOffset;
            triOffset = this->m_lmpMaterialSorts[tfMesh.materialOffset].vertexOffset;

            if( HAS_FLAG(tfMesh.flags, S_VERTEX_UNLIT) ) {
                triOffset += this->m_lmpLitFlatVertices.size();
                rdMesh.flags = RENDER_FLAG_UNLIT;
            } else if( HAS_FLAG(tfMesh.flags, S_VERTEX_LIT_BUMP) ) {
                triOffset += this->m_lmpLitFlatVertices.size() + this->m_lmpUnlitVertices.size();

                int i = this->m_lmpMaterialSorts.at(tfMesh.materialOffset).lightmapHeader;
                if( i != -1 && lightmaps ) {
                    std::string name = fmt::format("{}_lightmapheader_{}", this->GetFilename(), i);
                    rdMesh.pMaterial = CMaterial::GetMaterialByName(name);
                }

                rdMesh.flags = RENDER_FLAG_LITBUMP;
            } else if( HAS_FLAG(tfMesh.flags, S_VERTEX_UNLIT_TS) ) {
                triOffset += this->m_lmpLitFlatVertices.size() + this->m_lmpUnlitVertices.size() + this->m_lmpLitBumpVertices.size();
                rdMesh.flags = RENDER_FLAG_UNLITTS;
            } else {
                rdMesh.flags = RENDER_FLAG_LITFLAT;
            }

            g_vecRenderIndices.emplace_back(this->m_lmpMeshIndices[tfMesh.triOffset + idx] + triOffset);
        }

        rdMesh.triCount = g_vecRenderIndices.size() - rdMesh.triStart;
    }
}