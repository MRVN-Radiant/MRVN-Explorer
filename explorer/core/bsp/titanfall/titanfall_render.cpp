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
            CTitanfallBsp::SetRendererMeshes_Meshes();
            break;
    }
}

void CTitanfallBsp::SetRendererMeshes_Meshes() {
    const int S_VERTEX_LIT_FLAT      = 0x00000000;
    const int S_VERTEX_LIT_BUMP      = 0x00000200;
    const int S_VERTEX_UNLIT         = 0x00000400;
    const int S_VERTEX_UNLIT_TS      = 0x00000600;

    g_pRenderer->Clear();

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