/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#pragma once

#include <memory>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

#define HAS_FLAG( value, flag ) (value & flag) == flag

// ImGui requiers the call to open the popup and the call to draw the popup
// to be in the same "context", this is why we're doing this.
// TODO: Make a better system
inline std::string g_szErrorModal = "";
inline bool        g_bOpenErrorModal = false;

#define SHOW_ERROR( str ) g_bOpenErrorModal = true; g_szErrorModal = str;

//
inline std::string g_szFileChooserModal = "";
inline bool        g_bOpenFileChooseModal = false;

#define OPEN_FILE_CHOOSER() g_bOpenFileChooseModal = true; g_szFileChooserModal = std::getenv("HOME");