/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#include "logging.hpp"



CLogger::CLogger() {
    this->m_pSink             = std::make_shared<CFileSink_st>();
    this->m_pStringStream     = std::make_shared<std::ostringstream>();
    this->m_pStringStreamSink = std::make_shared<spdlog::sinks::ostream_sink_st> (*m_pStringStream);

#ifdef _WIN32
    this->m_pConsoleSink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_st>(); 
#else
    this->m_pConsoleSink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_st>(); 
#endif


    this->m_pSink->set_pattern("[%n] [%l] %v");
    this->m_pConsoleSink->set_pattern("[%n] [%l] %v");
    this->m_pStringStreamSink->set_pattern("[%n] [%l] %v");

    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back( this->m_pSink );
    sinks.push_back( this->m_pConsoleSink );
    sinks.push_back( this->m_pStringStreamSink );

    this->m_pExplorerLogger   = std::make_shared<spdlog::logger>("EXPLRER", sinks.begin(), sinks.end() );
    this->m_pFilesystemLogger = std::make_shared<spdlog::logger>("FILESYS", sinks.begin(), sinks.end() );
    this->m_pOpenGLLogger     = std::make_shared<spdlog::logger>("OPEN_GL", sinks.begin(), sinks.end() );
    this->m_pGUILogger        = std::make_shared<spdlog::logger>("GRAPHUI", sinks.begin(), sinks.end() );

    spdlog::register_logger( this->m_pExplorerLogger );
    spdlog::register_logger( this->m_pFilesystemLogger );
    spdlog::register_logger( this->m_pOpenGLLogger );
    spdlog::register_logger( this->m_pGUILogger );
}

std::shared_ptr<spdlog::logger> CLogger::Explorer() {
    return this->m_pExplorerLogger;
}

std::shared_ptr<spdlog::logger> CLogger::Filesystem() {
    return this->m_pFilesystemLogger;
}

std::shared_ptr<spdlog::logger> CLogger::OpenGL() {
    return this->m_pOpenGLLogger;
}

std::shared_ptr<spdlog::logger> CLogger::GUI() {
    return this->m_pGUILogger;
}

std::shared_ptr<std::ostringstream> CLogger::StringStream() {
    return this->m_pStringStream;
}