/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#include "apexlegends.hpp"

#include "../../../utils/logging.hpp"

#include "imgui.h"

void CApexLegendsBsp::DrawWindow_Meshes() {
    ImGui::Text( "Count: %i", this->m_lmpMeshes.size() );

    ImGui::Separator();

    ImGui::BeginTable("Meshes", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg );
    ImGui::TableSetupColumn( "Field" );
    ImGui::TableSetupColumn( "Value" );
    ImGui::TableHeadersRow();

    for( std::size_t i = 0; i < this->m_lmpMeshes.size(); i++ ) {
        ApexLegends::Mesh_t &mesh = this->m_lmpMeshes[i];

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

            for( int i = 0; i < 8; i++ ) {
                ImGui::TableNextColumn();
                ImGui::Text("unknown_%i", i);
                ImGui::TableNextColumn();
                ImGui::Text("%i", mesh.unknown[i]);
                ImGui::TableNextRow();
            }

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

void CApexLegendsBsp::DrawWindow_LightmapHeaders() {
    ImGui::Text( "Count: %i", this->m_lmpLightmapHeaders.size() );

    ImGui::Separator();

    std::size_t offset = 0;

    ImGui::BeginTable("Meshes", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg );
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

            ImGui::TreePop();
        } else {
            ImGui::TableNextColumn();
        }

        offset += header.width + header.height;
        ImGui::TableNextRow();
    }

    ImGui::EndTable();
}

void CApexLegendsBsp::DrawLumpInspectWindow( int index ) {
    switch( index ) {
        case (int)eApexLegendsLumps::MESHES:
            CApexLegendsBsp::DrawWindow_Meshes();
            break;
        case (int)eApexLegendsLumps::LIGHTMAP_HEADERS:
            CApexLegendsBsp::DrawWindow_LightmapHeaders();
            break;
    }
}