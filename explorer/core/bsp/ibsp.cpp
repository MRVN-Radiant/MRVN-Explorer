#include "ibsp.hpp"

IBsp::IBsp(const char *filename) {
    LOG_EXPLORER_INFO("IBSP Constructor: {}", filename)


    std::ifstream file( filename, std::ios::in | std::ios::binary );

    file.read((char*)&m_header, sizeof(m_header));
    file.close();
}

IBsp::~IBsp() {

}

int IBsp::GetBspVersion() {
    return this->m_header.version;
}