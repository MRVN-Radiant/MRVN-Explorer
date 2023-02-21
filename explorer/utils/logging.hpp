#pragma once

#include <memory>
#include <vector>
#include <sstream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/ostream_sink.h"

#include "cfilesink.hpp"

class CLogger {
    private:
        std::shared_ptr<CFileSink_st> m_pSink;
        std::shared_ptr<std::ostringstream> m_pStringStream;
        std::shared_ptr<spdlog::sinks::ostream_sink_st> m_pStringStreamSink;

#ifdef _WIN32
        std::shared_ptr<spdlog::sinks::wincolor_stdout_sink_st> m_pConsoleSink;
#else
        std::shared_ptr<spdlog::sinks::ansicolor_stdout_sink_st> m_pConsoleSink;
#endif


        std::shared_ptr<spdlog::logger> m_pExplorerLogger;
        std::shared_ptr<spdlog::logger> m_pFilesystemLogger;
        std::shared_ptr<spdlog::logger> m_pOpenGLLogger;
        std::shared_ptr<spdlog::logger> m_pGUILogger;
    public:
        CLogger();
        std::shared_ptr<spdlog::logger> Explorer();
        std::shared_ptr<spdlog::logger> Filesystem();
        std::shared_ptr<spdlog::logger> OpenGL();
        std::shared_ptr<spdlog::logger> GUI();

        std::shared_ptr<std::ostringstream> StringStream();
};

inline std::unique_ptr<CLogger> g_pLogger;

#define LOG_EXPLORER_INFO(...)    g_pLogger->Explorer()->info(__VA_ARGS__);
#define LOG_EXPLORER_WARN(...)    g_pLogger->Explorer()->warn(__VA_ARGS__);
#define LOG_EXPLORER_ERROR(...)   g_pLogger->Explorer()->error(__VA_ARGS__);

#define LOG_FILESYSTEM_INFO(...)  g_pLogger->Filesystem()->info(__VA_ARGS__);
#define LOG_FILESYSTEM_WARN(...)  g_pLogger->Filesystem()->warn(__VA_ARGS__);
#define LOG_FILESYSTEM_ERROR(...) g_pLogger->Filesystem()->error(__VA_ARGS__);

#define LOG_OPENGL_INFO(...)      g_pLogger->OpenGL()->info(__VA_ARGS__);
#define LOG_OPENGL_WARN(...)      g_pLogger->OpenGL()->warn(__VA_ARGS__);
#define LOG_OPENGL_ERROR(...)     g_pLogger->OpenGL()->error(__VA_ARGS__);

#define LOG_GUI_INFO(...)         g_pLogger->GUI()->info(__VA_ARGS__);
#define LOG_GUI_WARN(...)         g_pLogger->GUI()->warn(__VA_ARGS__);
#define LOG_GUI_ERROR(...)        g_pLogger->GUI()->error(__VA_ARGS__);