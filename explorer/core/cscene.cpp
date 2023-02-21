#include "cscene.hpp"


CScene::CScene(const char *filename) {
    fs::path filePath = fs::path(filename);

    LOG_FILESYSTEM_INFO("Opening: {}", filename)

    if(!fs::exists(filePath)) {
        ERROR("Couldn't find selected file!")
        this->m_bValid = false;
        return;
    }

    // This should never happen
    if(fs::is_directory(filePath)) {
        ERROR("Selected file is a directory!")
        this->m_bValid = false;
        return;
    }


    // We filter to only .bsp files so at this point we can read it fine
    this->m_szName = filePath.filename();
    this->m_bOpen = true;
    this->m_bValid = true;
    if( g_vecpScenes.size() != 0 ) {
        this->m_iID = g_vecpScenes.back()->ID() + 1;
    } else {
        this->m_iID = 0;
    }

    // Check version
    Header_t header;

    std::ifstream file( filename, std::ios::in | std::ios::binary );

    file.read((char*)&header, sizeof(header));
    file.close();

    if( strncmp(header.ident, "rBSP", 4) != 0 ) {
        LOG_EXPLORER_ERROR("Unknown BSP ident: {}", header.ident)
        ERROR("Unknown BSP ident!")
        this->m_bValid = false;
        return;
    }

    if( header.version == 29 ) {
        LOG_EXPLORER_INFO("BSP Game: Titanfall 1")
        this->m_pBsp = std::make_unique<CTitanfallBsp>(filename);
    } else if( header.version == 37 ) {
        LOG_EXPLORER_INFO("BSP Game: Titanfall 2")
        this->m_pBsp = std::make_unique<CTitanfallBsp>(filename);
    } else if( header.version == 47 ) {
        LOG_EXPLORER_INFO("BSP Game: Apex Legends")
        this->m_pBsp = std::make_unique<CApexLegendsBsp>(filename);
    } else {
        LOG_EXPLORER_ERROR("Unknown BSP version: {}", header.version)
        ERROR("Unknown BSP version!")
        this->m_bValid = false;
    }

    this->m_pCamera = std::make_shared<CCamera>();
    this->m_bCullBackFaces = true;
    this->m_bDrawUnlit     = true;
    this->m_bDrawLitFlat   = true;
    this->m_bDrawLitBump   = true;
    this->m_bDrawUnlitTS   = true;
}

CScene::~CScene() {

}

void CScene::Remove() {
    std::erase_if( g_vecpScenes, [this](std::shared_ptr<CScene> pScene) { return this->ID() == pScene->ID(); } );

    if( g_pScene->ID() == this->ID() ) {
        g_pScene = NULL;
        if( g_vecpScenes.size() > 0 ) {
            g_pScene = g_vecpScenes.front();
        }
    }
}

bool *CScene::IsOpen() {
    return &(this->m_bOpen);
}

bool CScene::IsValid() {
    return this->m_bValid;
}

int CScene::ID() {
    return this->m_iID;
}

std::string CScene::Name() {
    return this->m_szName;
}

std::string CScene::GetGameName() {
    return this->m_pBsp->GetGameName();
}

int CScene::GetBspVersion() {
    return this->m_pBsp->GetBspVersion();
}

void CScene::DrawLumpsList( bool hideUnused ) {
    ImGui::BeginTable( "Lumps", 5, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg );
    ImGui::TableSetupColumn( "Index" );
    ImGui::TableSetupColumn( "Name" );
    ImGui::TableSetupColumn( "Version" );
    ImGui::TableSetupColumn( "Size" );
    ImGui::TableSetupColumn( "Inspect" );
    ImGui::TableHeadersRow();

    int i = 0;
    for( LumpDef_t &lump : this->m_pBsp->GetLumps() ) {
        if( lump.gameVersion != -1 && this->m_pBsp->GetBspVersion() != lump.gameVersion ) {
            lump.name = "Unused";
            lump.version = -1;
        }
        
        if( hideUnused && lump.version == -1 ) {
            i++;
            continue;
        }

        ImGui::TableNextColumn();
        ImGui::Text( "%i", i);
        ImGui::TableNextColumn();
        ImGui::Text( "%s", lump.name );
        ImGui::TableNextColumn();
        ImGui::Text( "%i", lump.version );
        ImGui::TableNextColumn();
        ImGui::Text( "%i", lump.size );
        ImGui::TableNextColumn();
        if( !lump.canInspect ) { ImGui::BeginDisabled(); }
        ImGui::PushID(i);
        ImGui::Button( "Inspect" );
        ImGui::PopID();
        if( !lump.canInspect ) { ImGui::EndDisabled(); }
        ImGui::TableNextRow();

        i++;
    }
    ImGui::EndTable();
}

void CScene::DrawViewportOptions() {
    static int id = 0;
    static int lastID = -1;
    for( DrawableType_t &type : this->m_pBsp->GetDrawableTypes() ) {
        ImGui::RadioButton( type.name, &id, type.id );
    }

    if( lastID != id ) {
        this->UpdateRenderMeshes( id );
    }

    lastID = id;

    ImGui::Checkbox("Cull back faces", &this->m_bCullBackFaces);

    if(this->m_bCullBackFaces) {
        glEnable( GL_CULL_FACE );
    } else {
        glDisable( GL_CULL_FACE );
    }

    ImGui::Separator();
    
    g_iRenderFlags = 0;
    ImGui::Checkbox( "Draw Unlit", &m_bDrawUnlit );
    ImGui::Checkbox( "Draw Lit Flat", &m_bDrawLitFlat );
    ImGui::Checkbox( "Draw Lit Bump", &m_bDrawLitBump );
    ImGui::Checkbox( "Draw Unlit TS", &m_bDrawUnlitTS );

    if( m_bDrawUnlit )   { g_iRenderFlags |= RENDER_FLAG_UNLIT; }
    if( m_bDrawLitFlat ) { g_iRenderFlags |= RENDER_FLAG_LITFLAT; }
    if( m_bDrawLitBump ) { g_iRenderFlags |= RENDER_FLAG_LITBUMP; }
    if( m_bDrawUnlitTS ) { g_iRenderFlags |= RENDER_FLAG_UNLITTS; }
}

void CScene::UpdateRenderMeshes( int id ) {
    m_pBsp->SetRendererMeshes( id );
    g_pRenderer->Update();
    g_pCamera = this->m_pCamera;
}