#include "cmainwindow.hpp"


CMainWindow::CMainWindow() {
    // Init GLFW
    if (!glfwInit())
        exit(-1);
    
    LOG_GUI_INFO("GLFW Initilazed")
    
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window
    m_bShouldClose = false;
    this->m_pWindow = glfwCreateWindow(1400, 800, "Explorer", NULL, NULL);
    if (!this->m_pWindow) {
        glfwTerminate();
        LOG_GUI_ERROR("Failed to create window! Shutting down")
        exit(-1);
    }

    LOG_GUI_INFO("Created window")

    // Make context current
    glfwMakeContextCurrent(this->m_pWindow);

    // ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Set default ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(this->m_pWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    LOG_GUI_INFO("ImGui Initilazed")

    this->m_pRenderer = std::make_unique<CRenderer>();
}

CMainWindow::~CMainWindow() {
    LOG_GUI_INFO("Shutting down ImGui")
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    LOG_GUI_INFO("Shutting down GLFW")
    glfwTerminate();
}

void CMainWindow::Loop() {
    while (!glfwWindowShouldClose(this->m_pWindow) && !this->m_bShouldClose) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        this->DrawMenuBar();
        this->DrawFileInfo();
        this->DrawViewportControl();
        this->DrawConsole();

        this->DrawDebugOverlay();

        if( g_bDrawAboutModal ) { ImGui::OpenPopup("About"); g_bDrawAboutModal = false; }
        this->DrawAboutModal();

        if( g_bOpenFileChooseModal ) { ImGui::OpenPopup("File Chooser"); g_bOpenFileChooseModal = false; };
        this->DrawFileChooserModal();

        if( g_bOpenErrorModal ) { ImGui::OpenPopup("Error"); g_bOpenErrorModal = false; };
        this->DrawErrorModal();


        if( g_bDrawDemoWindow )
            ImGui::ShowDemoWindow( &g_bDrawDemoWindow );

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(this->m_pWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_pRenderer->Update(this->m_pWindow);

        glfwSwapBuffers(this->m_pWindow);

        glfwPollEvents();
    }
}

void CMainWindow::Close() {
    m_bShouldClose = true;
    //glfwDestroyWindow(this->window);
}

void CMainWindow::DrawMenuBar() {
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if( ImGui::MenuItem("Open File", NULL) ) { OPEN_FILE_CHOOSER() }
            ImGui::Separator();
            if( ImGui::MenuItem("Exit") ) { this->Close(); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if( ImGui::BeginMenu( "Theme" ) ) {
                if( ImGui::MenuItem( "Dark" ) ) { ImGui::StyleColorsDark(); }
                if( ImGui::MenuItem( "Light" ) ) { ImGui::StyleColorsLight(); }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem( "File Information", NULL, &g_bDrawFileInformationWindow );
            ImGui::MenuItem( "Viewport control", NULL, &g_bDrawViewportControlWindow );
            ImGui::MenuItem( "Console", NULL, &g_bDrawConsoleWindow );
            ImGui::MenuItem( "Debug Overlay", NULL, &g_bDrawDebugOverlay );
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem( "About", NULL, &g_bDrawAboutModal );
            ImGui::Separator();
            if( ImGui::MenuItem("Error test") ) { ERROR( "Test error modal\nSecond line!" ) }
            ImGui::Separator();
            ImGui::MenuItem( "Demo window", NULL, &g_bDrawDemoWindow );
            ImGui::EndMenu();
        }

        ImGui::Separator();

        if (ImGui::BeginTabBar("OpenFilesTabBar", ImGuiTabBarFlags_None)) {
            // Set scene if NULL
            if( g_pScene == NULL && g_vecpScenes.size() != 0 ) {
                g_pScene = g_vecpScenes.front();
            }

            std::shared_ptr<CScene> pSceneToRemove;

            for( std::shared_ptr<CScene> &scene : g_vecpScenes ) {
                ImGui::PushID(scene->ID());
                if( ImGui::BeginTabItem(scene->Name().c_str(), scene->IsOpen() ) ) {
                    g_pScene = scene;
                    ImGui::EndTabItem();
                }

                if( !(*scene->IsOpen()) ) {
                    pSceneToRemove = scene;
                    LOG_EXPLORER_INFO("Remove scene with id: {}", scene->ID())
                    //scene->Remove();
                }
                
                ImGui::PopID();
            }

            // Need to remove the scene outside the loop
            if( pSceneToRemove ) {
                pSceneToRemove->Remove();
            }

            ImGui::EndTabBar();
        }

        ImGui::EndMainMenuBar();
    }
}

void CMainWindow::DrawFileInfo() {
    if( !g_bDrawFileInformationWindow )
        return;

    ImGui::Begin( "File Information", &g_bDrawFileInformationWindow );

    if( g_pScene ) {
        ImGui::Text("Name: %s", g_pScene->Name().c_str());
        ImGui::Text("Game: %s", g_pScene->GetGameName().c_str());
        ImGui::SameLine(200);
        ImGui::Text("Version: %i", g_pScene->GetBspVersion());

        static bool hideUnused = true;
        ImGui::Checkbox("Hide Unused", &hideUnused);

        g_pScene->DrawLumpsList( hideUnused );
    } else {
        ImGui::Text("No file open!");
    }

    ImGui::End();
}

void CMainWindow::DrawViewportControl() {
    if ( !g_bDrawViewportControlWindow )
        return;
    
    ImGui::Begin( "Viewport Control", &g_bDrawViewportControlWindow );
    if( g_pScene ) {
        g_pScene->DrawViewportOptions();
    } else {
        ImGui::Text("No file open!");
    }
    ImGui::End();
}

void CMainWindow::DrawConsole() {
    if( !g_bDrawConsoleWindow )
        return;
    
    static bool bAutoScroll = true;
    static int  iTestLogCount = 314;
    
    ImGui::Begin( "Console", &g_bDrawConsoleWindow, ImGuiWindowFlags_MenuBar );

    if (ImGui::BeginMenuBar()) {
        ImGui::Checkbox( "Auto-Scroll", &bAutoScroll );
        if( ImGui::Button("Test log (Info)") )  { iTestLogCount += 271; LOG_EXPLORER_INFO("Test log: {}", iTestLogCount ) }
        if( ImGui::Button("Test log (Warn)") )  { iTestLogCount += 271; LOG_EXPLORER_WARN("Test log: {}", iTestLogCount ) }
        if( ImGui::Button("Test log (Error)") ) { iTestLogCount += 271; LOG_EXPLORER_ERROR("Test log: {}", iTestLogCount ) }

        ImGui::EndMenuBar();
    }

    ImGui::BeginChild("console", ImVec2(0, 0), true);

    ImGui::Text(g_pLogger->StringStream()->str().c_str());

    if( bAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);
    
    ImGui::EndChild();

    ImGui::End();
}

void CMainWindow::DrawDebugOverlay() {
    if( !g_bDrawDebugOverlay )
        return;

    ImGuiIO& io = ImGui::GetIO();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    
    const float PAD = 10.0f;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
    ImVec2 work_size = viewport->WorkSize;
    ImVec2 window_pos, window_pos_pivot;
    window_pos.x = (work_pos.x + PAD);
    window_pos.y = (work_pos.y + PAD);
    window_pos_pivot.x = 0.0f;
    window_pos_pivot.y = 0.0f;
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    window_flags |= ImGuiWindowFlags_NoMove;
    

    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (ImGui::Begin("Debug Overlay", NULL, window_flags))
    {
        ImGui::Text("Open scenes: %i", g_vecpScenes.size());
        if( g_pScene != NULL ) {
            ImGui::Text("Scene name: %s", g_pScene->Name().c_str());
            ImGui::Text("Scene id: %i", g_pScene->ID());
        } else {
            ImGui::Text("No scenes open!");
        }
    }
    ImGui::End();
}

void CMainWindow::DrawAboutModal() {
    if (ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("MRVN-Explorer");
        ImGui::Text("0.0.0");
        ImGui::Spacing();
        ImGui::AlignTextToFramePadding();
        ImGui::Text("A respawn .bsp OpenGL explorer.");

        if( ImGui::Button("Ok") ) { ImGui::CloseCurrentPopup(); }
        
        ImGui::EndPopup();
    }
}

void CMainWindow::DrawFileChooserModal() {
    static bool bHideHidden = true;

    ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_FirstUseEver);
    if (ImGui::BeginPopupModal("File Chooser", NULL, 0)) {
        ImVec2 size = ImGui::GetWindowSize();
        size.x -= 17.0;
        size.y -= 82.0;

        fs::path path( g_szFileChooserModal.c_str() );
        fs::path homePath( std::getenv("HOME") );

        // Current path
        if( g_szFileChooserModal.empty() )
            g_szFileChooserModal = "/";

        // Current path split into buttons
        fs::path tempPath;
        for( auto it = path.begin(); it != path.end(); it++ ) {
            tempPath = tempPath / *it;

            ImGui::SameLine();
            if( ImGui::Button(it->string().c_str()) ) {
                g_szFileChooserModal = tempPath.string().c_str();
            }
        }
        //ImGui::Button( g_szFileChooserModal.c_str() );


        // Left-pane
        static int selected = 0;
        {
            ImGui::BeginChild("left-pane", ImVec2(200, size.y), true);
            for( auto const &dir : fs::directory_iterator{homePath}) {
                std::string d = dir.path().string().substr(homePath.string().length() + 1);

                // Skip hidden files
                if(d.starts_with("."))
                    continue;
                
                // Skip files
                if(!fs::is_directory(dir))
                    continue;

                if( ImGui::Button(d.c_str()) ) {
                    g_szFileChooserModal = dir.path();
                }
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();

        static int iSelectedIndex = -1;
        static std::string szSelectedFile;

        // Right-pane
        {
            ImGui::BeginChild("right-pane",ImVec2(0, size.y), true);

            if( ImGui::Selectable("..") ) {
                g_szFileChooserModal = path.parent_path();
            }

            int i = 0;
            for( auto const &dir : fs::directory_iterator{path}) {
                int prefix = path.string().length();
                
                if( path.parent_path() != path )
                    prefix++;

                std::string d = dir.path().string().substr(prefix);

                // Skip hidden files and non bsp files
                if( d.starts_with(".") && bHideHidden || !fs::is_directory(dir) && dir.path().extension() != ".bsp" )
                    continue;
                
                std::string name;
                if(fs::is_directory(dir))
                    name = "[dir] ";
                
                name += d.c_str();

                if( ImGui::Selectable(name.c_str(), iSelectedIndex == i ) ) {
                    iSelectedIndex = i;
                    if(fs::is_directory(dir)) {
                        g_szFileChooserModal = dir.path();
                        iSelectedIndex = -1;
                    } else {
                        szSelectedFile = dir.path().string();
                        LOG_FILESYSTEM_INFO("Selected: {}", szSelectedFile.c_str())
                    }
                }

                i++;
            }
            ImGui::EndChild();
        }



        //ImGui::Separator();
        ImGui::Checkbox("Hide hidden", &bHideHidden);
        ImGui::SameLine();
        if( ImGui::Button("Cancel") ) { ImGui::CloseCurrentPopup(); }
        ImGui::SameLine();
        if( iSelectedIndex == -1 ) { ImGui::BeginDisabled(); }
        if( ImGui::Button("Open") ) {
            std::shared_ptr<CScene> pTempScene = std::make_shared<CScene>(szSelectedFile.c_str());
            if( pTempScene->IsValid() )
                g_vecpScenes.emplace_back( pTempScene );
            
            ImGui::CloseCurrentPopup();
        }
        if( iSelectedIndex == -1 ) { ImGui::EndDisabled(); }
        ImGui::EndPopup();
    }
}

void CMainWindow::DrawErrorModal() {
    if (ImGui::BeginPopupModal("Error", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text( g_szErrorModal.c_str() );
        ImGui::Separator();
        if( ImGui::Button("Ok") ) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }
}