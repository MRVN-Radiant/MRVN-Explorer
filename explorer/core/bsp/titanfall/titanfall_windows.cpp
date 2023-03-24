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

void CTitanfallBsp::DrawLumpInspectWindow( int index ) {
    switch( index ) {
        case (int)eTitanfallLumps::MESHES:
            DrawWindow_Meshes();
            break;
    }
}