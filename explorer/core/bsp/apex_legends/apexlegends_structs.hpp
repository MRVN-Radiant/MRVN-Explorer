/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#pragma once

#include "../titanfall/titanfall_structs.hpp"
#include "../../../utils/math.hpp"
#undef PLANES
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

enum class eApexLegendsLumps : int {
    ENTITIES                        = 0,
    PLANES                          = 1,
    TEXTURE_DATA                    = 2,
    VERTICES                        = 3,
    LIGHTPROBE_PARENT_INFOS         = 4,
    SHADOW_ENVIRONMENTS             = 5,
    MODELS                          = 14,
    SURFACE_NAMES                   = 15,
    CONTENTS_MASKS                  = 16,
    SURFACE_PROPERTIES              = 17,
    BVH_NODES                       = 18,
    BVH_LEAF_DATA                   = 19,
    PACKED_VERTICES                 = 20,
    ENTITY_PARTITIONS               = 24,
    VERTEX_NORMALS                  = 30,
    GAME_LUMP                       = 35,
    UNKNOWN_37                      = 37,
    UNKNOWN_38                      = 38,
    UNKNOWN_39                      = 39,
    PAKFILE                         = 40,
    CUBEMAPS                        = 42,
    UNKNOWN_43                      = 43,
    WORLD_LIGHTS                    = 54,
    WORLD_LIGHT_PARENT_INFOS        = 55,
    VERTEX_UNLIT                    = 71,
    VERTEX_LIT_FLAT                 = 72,
    VERTEX_LIT_BUMP                 = 73,
    VERTEX_UNLIT_TS                 = 74,
    VERTEX_BLINN_PHONG              = 75,
    VERTEX_RESERVED_5               = 76,
    VERTEX_RESERVED_6               = 77,
    VERTEX_RESERVED_7               = 78,
    MESH_INDICES                    = 79,
    MESHES                          = 80,
    MESH_BOUNDS                     = 81,
    MATERIAL_SORT                   = 82,
    LIGHTMAP_HEADERS                = 83,
    TWEAK_LIGHTS                    = 85,
    UNKNOWN_97                      = 97,
    LIGHTMAP_DATA_SKY               = 98,
    CSM_AABB_NODES                  = 99,
    CSM_OBJ_REFERENCES              = 100,
    LIGHTPROBES                     = 101,
    STATIC_PROP_LIGHTPROBE_INDICES  = 102,
    LIGHTPROBE_TREE                 = 103,
    LIGHTPROBE_REFERENCES           = 104,
    LIGHTMAP_DATA_REAL_TIME_LIGHTS  = 105,
    CELL_BSP_NODES                  = 106,
    CELLS                           = 107,
    PORTALS                         = 108,
    PORTAL_VERTICES                 = 109,
    PORTAL_EDGES                    = 110,
    PORTAL_VERTEX_EDGES             = 111,
    PORTAL_VERTEX_REFERENCES        = 112,
    PORTAL_EDGE_REFERENCES          = 113,
    PORTAL_EDGE_INTERSECT_AT_EDGE   = 114,
    PORTAL_EDGE_INTERSECT_AT_VERTEX = 115,
    PORTAL_EDGE_INTERSECT_HEADER     = 116,
    OCCLUSION_MESH_VERTICES         = 117,
    OCCLUSION_MESH_INDICES          = 118,
    CELL_AABB_NODES                 = 119,
    OBJ_REFERENCES                  = 120,
    OBJ_REFERENCE_BOUNDS            = 121,
    LIGHTMAP_DATA_RTL_PAGE          = 122,
    LEVEL_INFO                      = 123,
    SHADOW_MESH_OPAQUE_VERTICES     = 124,
    SHADOW_MESH_ALPHA_VERTICES      = 125,
    SHADOW_MESH_INDICES             = 126,
    SHADOW_MESHES                   = 127
};
