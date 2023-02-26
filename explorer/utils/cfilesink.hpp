/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#pragma once

#include <fstream>

#include "spdlog/sinks/base_sink.h"

#include "globals.hpp"


template<typename Mutex>
class CFileSink : public spdlog::sinks::base_sink <Mutex> {
    private:
        std::ofstream m_stream;
    
    public:
        CFileSink() {
            fs::path l_logFile = fs::path("./explorer.txt");
            if( fs::exists(l_logFile) )
                fs::remove( l_logFile );

            m_stream = std::ofstream("explorer.txt");
        }

        ~CFileSink() {
            m_stream.close();
        }
    
    protected:
        void sink_it_(const spdlog::details::log_msg& msg) override {
            spdlog::memory_buf_t formatted;
            spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
            m_stream << fmt::to_string(formatted) << std::flush;
        }

        void flush_() override {
            m_stream << std::flush;
        }
};

#include "spdlog/details/null_mutex.h"
#include <mutex>
using CFileSink_mt = CFileSink<std::mutex>;
using CFileSink_st = CFileSink<spdlog::details::null_mutex>;