#pragma once

#include "../../../utils/math.hpp"

namespace ApexLegends {
    struct VertexUnlit_t {
        uint32_t  vertexIndex;
        uint32_t  normalIndex;
        Vector2f  uv0;
        int32_t   negativeOne;
    };

    // 0x48
    struct VertexLitFlat_t {
        uint32_t  vertexIndex;
        uint32_t  normalIndex;
        Vector2f  uv0;
        int32_t   unknown0;
    };

    // 0x49
    struct VertexLitBump_t {
        uint32_t  vertexIndex;
        uint32_t  normalIndex;
        Vector2f  uv0;
        int32_t   negativeOne;
        Vector2f  uv1;
        uint8_t   color[4];
    };

    // 0x4A
    struct VertexUnlitTS_t {
        uint32_t  vertexIndex;
        uint32_t  normalIndex;
        Vector2f  uv0;
        int32_t   unknown0;
        int32_t   unknown1;
    };

    struct Mesh_t {
        uint32_t  triOffset;
        uint16_t  triCount;
        uint16_t  unknown[8];
        uint16_t  materialOffset;
        uint32_t  flags;
    };

    struct MaterialSort_t {
        uint16_t  textureData;
        int16_t  lightmapIndex;
        uint16_t  unknown0;
        uint16_t  unknown1;
        uint32_t  vertexOffset;
    };
}