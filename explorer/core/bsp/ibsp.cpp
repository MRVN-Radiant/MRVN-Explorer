#include "ibsp.hpp"

IBsp::IBsp(const char *filename) {
    LOG_EXPLORER_INFO("IBSP Constructor: {}", filename)


    m_file = std::ifstream( filename, std::ios::in | std::ios::binary );

    m_file.read((char*)&m_header, sizeof(m_header));
}

IBsp::~IBsp() {
}

int IBsp::GetBspVersion() {
    return this->m_header.version;
}

/*template<typename T>
void IBsp::CopyLump( int lump, std::vector<T> &data ) {
    if ( m_header.lumps[lump].length % sizeof(T) != 0 ) {
        printf( "Length mismatch! Lump: %i\n", lump );
        return;
    }
    
    data.clear();

    m_file.seekg( m_header.lumps[lump].offset );

    data.resize( m_header.lumps[lump].length / sizeof(T) );
    m_file.read( (char*)&data[0], m_header.lumps[lump].length );
}*/

void IBsp::CloseFile() {
    m_file.close();
}