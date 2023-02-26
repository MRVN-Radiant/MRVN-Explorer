/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/

#include <iostream>

#include "ui/cmainwindow.hpp"
#include "utils/logging.hpp"
#include "utils/globals.hpp"

int main( int argc, char *argv[] ) {
    // Set working path to exe directory no matter where we're being ran from
    fs::current_path(fs::path(argv[0]).parent_path());

    g_pLogger = std::make_unique<CLogger>();

    LOG_EXPLORER_INFO("                   __                    ")
    LOG_EXPLORER_INFO("  ___  _  ______  / /___  ________  _____")
    LOG_EXPLORER_INFO(" / _ \\| |/_/ __ \\/ / __ \\/ ___/ _ \\/ ___/")
    LOG_EXPLORER_INFO("/  __/>  </ /_/ / / /_/ / /  /  __/ /    ")
    LOG_EXPLORER_INFO("\\___/_/|_/ .___/_/\\____/_/   \\___/_/     ")
    LOG_EXPLORER_INFO("        /_/                              ")

    LOG_EXPLORER_INFO("Path: {}", fs::current_path().c_str());

    g_pMainWindow = std::make_unique<CMainWindow>();

    g_pMainWindow->Loop();

    return 0;
}