/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#include "titanfall.hpp"

#include "../../../utils/logging.hpp"

void CTitanfallBsp::DrawWindow_Meshes() {
    ImGui::Text( "Count: %i", this->m_lmpMeshes.size() );

    ImGui::Separator();

    ImGui::BeginTable("Meshes", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg );
    ImGui::TableSetupColumn( "Field" );
    ImGui::TableSetupColumn( "Value" );
    ImGui::TableHeadersRow();

    for( std::size_t i = 0; i < this->m_lmpMeshes.size(); i++ ) {
        Titanfall::Mesh_t &mesh = this->m_lmpMeshes[i];

        ImGui::TableNextColumn();
        if( ImGui::TreeNode(fmt::to_string(i).c_str()) ) {
            ImGui::TableNextColumn();
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("triOffset");
            ImGui::TableNextColumn();
            ImGui::Text("%i", mesh.triOffset);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("triCount");
            ImGui::TableNextColumn();
            ImGui::Text("%i", mesh.triCount);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("vertexOffset");
            ImGui::TableNextColumn();
            ImGui::Text("%i", mesh.vertexOffset);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("vertexCount");
            ImGui::TableNextColumn();
            ImGui::Text("%i", mesh.vertexCount);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("vertexType");
            ImGui::TableNextColumn();
            ImGui::Text("%i", mesh.vertexType);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("unused");
            ImGui::TableNextColumn();
            ImGui::Text("%i", mesh.unused);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("const");
            ImGui::TableNextColumn();
            ImGui::Text("%i", mesh.const0);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("unk1");
            ImGui::TableNextColumn();
            ImGui::Text("%i", mesh.unk1);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("unk2");
            ImGui::TableNextColumn();
            ImGui::Text("%i", mesh.unk2);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("unk3");
            ImGui::TableNextColumn();
            ImGui::Text("%i", mesh.unk3);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("materialOffset");
            ImGui::TableNextColumn();
            ImGui::Text("%i", mesh.materialOffset);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("flags");
            ImGui::TableNextColumn();
            ImGui::Text("%i", mesh.flags);

            ImGui::TreePop();
        } else {
            ImGui::TableNextColumn();
        }
        
        ImGui::TableNextRow();
    }
    
    ImGui::EndTable();
}

void CTitanfallBsp::DrawWindow_LightmapHeaders() {
    ImGui::Text( "Count: %i", this->m_lmpLightmapHeaders.size() );

    ImGui::Separator();

    std::size_t offset = 0;

    ImGui::BeginTable("Lightmap headers", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg );
    ImGui::TableSetupColumn( "Field" );
    ImGui::TableSetupColumn( "Value" );
    ImGui::TableHeadersRow();

    for( std::size_t i = 0; i < this->m_lmpLightmapHeaders.size(); i++ ) {
        Titanfall::LightmapHeader_t &header = this->m_lmpLightmapHeaders[i];

        ImGui::TableNextColumn();
        if( ImGui::TreeNode(fmt::to_string(i).c_str()) ) {
            ImGui::TableNextColumn();
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("type");
            ImGui::TableNextColumn();
            ImGui::Text("%i", header.type);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("width");
            ImGui::TableNextColumn();
            ImGui::Text("%i", header.width);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("height");
            ImGui::TableNextColumn();
            ImGui::Text("%i", header.height);
            ImGui::TableNextColumn();

            if( ImGui::TreeNode( "INSPECT" ) ) {
                std::string name = fmt::format("{}_lightmapheader_{}", this->GetFilename(), i);

                std::shared_ptr<CMaterial> material = CMaterial::GetMaterialByName( name );

                material->Use();
                ImGui::Image( (void*)(intptr_t)material->GetID(), ImVec2( material->GetWidth(), material->GetHeight() ) );
                ImGui::TableNextRow();
                ImGui::TreePop();
            }

            ImGui::TreePop();
        } else {
            ImGui::TableNextColumn();
        }

        offset += header.width + header.height;
        ImGui::TableNextRow();
    }

    ImGui::EndTable();
}

void CTitanfallBsp::DrawWindow_CMGrid() {
    ImGui::BeginTable("CM Grid", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg );
    ImGui::TableSetupColumn( "Field" );
    ImGui::TableSetupColumn( "Value" );
    ImGui::TableHeadersRow();

    ImGui::TableNextColumn();
    ImGui::TableNextColumn();
    ImGui::TableNextRow();

    ImGui::TableNextColumn();
    ImGui::Text("scale");
    ImGui::TableNextColumn();
    ImGui::Text("%f", this->m_lmpCMGrid[0].scale);
    ImGui::TableNextRow();

    ImGui::TableNextColumn();
    ImGui::Text("xOffset");
    ImGui::TableNextColumn();
    ImGui::Text("%i", this->m_lmpCMGrid[0].xOffset);
    ImGui::TableNextRow();

    ImGui::TableNextColumn();
    ImGui::Text("yOffset");
    ImGui::TableNextColumn();
    ImGui::Text("%i", this->m_lmpCMGrid[0].yOffset);
    ImGui::TableNextRow();

    ImGui::TableNextColumn();
    ImGui::Text("xCount");
    ImGui::TableNextColumn();
    ImGui::Text("%i", this->m_lmpCMGrid[0].xCount);
    ImGui::TableNextRow();

    ImGui::TableNextColumn();
    ImGui::Text("yCount");
    ImGui::TableNextColumn();
    ImGui::Text("%i", this->m_lmpCMGrid[0].yCount);
    ImGui::TableNextRow();

    ImGui::TableNextColumn();
    ImGui::Text("straddleGroupCount");
    ImGui::TableNextColumn();
    ImGui::Text("%i", this->m_lmpCMGrid[0].straddleGroupCount);
    ImGui::TableNextRow();

    ImGui::TableNextColumn();
    ImGui::Text("brushSidePlaneOffset");
    ImGui::TableNextColumn();
    ImGui::Text("%i", this->m_lmpCMGrid[0].brushSidePlaneOffset);
    
    ImGui::EndTable();
}

void CTitanfallBsp::DrawWindow_CMGeoSets() {
    ImGui::Text( "Count: %i", this->m_lmpGeoSets.size() );

    ImGui::Separator();

    ImGui::BeginTable("Geo Sets", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg );
    ImGui::TableSetupColumn( "Field" );
    ImGui::TableSetupColumn( "Value" );
    ImGui::TableHeadersRow();

    for( std::size_t i = 0; i < this->m_lmpGeoSets.size(); i++ ) {
        Titanfall::CMGeoSet_t &set = this->m_lmpGeoSets[i];

        ImGui::TableNextColumn();
        if( ImGui::TreeNode(fmt::to_string(i).c_str()) ) {
            ImGui::TableNextColumn();
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("straddleGroup");
            ImGui::TableNextColumn();
            ImGui::Text("%i", set.straddleGroup);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("primitiveCount");
            ImGui::TableNextColumn();
            ImGui::Text("%i", set.primitiveCount);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("uniqueContentsIndex");
            ImGui::TableNextColumn();
            ImGui::Text("%i", set.uniqueContentsIndex);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("collisionShapeIndex");
            ImGui::TableNextColumn();
            ImGui::Text("%i", set.collisionShapeIndex);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("collisionShapeType");
            ImGui::TableNextColumn();
            ImGui::Text("%i", set.collisionShapeType);
            ImGui::TableNextColumn();

            ImGui::TreePop();
        } else {
            ImGui::TableNextColumn();
        }

        ImGui::TableNextRow();
    }

    ImGui::EndTable();
}

void CTitanfallBsp::DrawWindow_CMPrimitives() {
    ImGui::Text( "Count: %i", this->m_lmpPrimitives.size() );

    ImGui::Separator();

    ImGui::BeginTable("Geo Sets", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg );
    ImGui::TableSetupColumn( "Field" );
    ImGui::TableSetupColumn( "Value" );
    ImGui::TableHeadersRow();

    for( std::size_t i = 0; i < this->m_lmpPrimitives.size(); i++ ) {
        Titanfall::CMPrimitive_t &set = this->m_lmpPrimitives[i];

        ImGui::TableNextColumn();
        if( ImGui::TreeNode(fmt::to_string(i).c_str()) ) {
            ImGui::TableNextColumn();
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("uniqueContentsIndex");
            ImGui::TableNextColumn();
            ImGui::Text("%i", set.uniqueContentsIndex);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("collisionShapeIndex");
            ImGui::TableNextColumn();
            ImGui::Text("%i", set.collisionShapeIndex);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("collisionShapeType");
            ImGui::TableNextColumn();
            ImGui::Text("%i", set.collisionShapeType);
            ImGui::TableNextColumn();

            ImGui::TreePop();
        } else {
            ImGui::TableNextColumn();
        }

        ImGui::TableNextRow();
    }

    ImGui::EndTable();
}

void CTitanfallBsp::DrawLumpInspectWindow( int index ) {
    switch( index ) {
        case (int)eTitanfallLumps::MESHES:
            CTitanfallBsp::DrawWindow_Meshes();
            break;
        case (int)eTitanfallLumps::LIGHTMAP_HEADERS:
            CTitanfallBsp::DrawWindow_LightmapHeaders();
            break;
        case (int)eTitanfallLumps::CM_GRID:
            CTitanfallBsp::DrawWindow_CMGrid();
            break;
        case (int)eTitanfallLumps::CM_GEO_SETS:
            CTitanfallBsp::DrawWindow_CMGeoSets();
            break;
        case (int)eTitanfallLumps::CM_PRIMITIVES:
            CTitanfallBsp::DrawWindow_CMPrimitives();
            break;
    }
}