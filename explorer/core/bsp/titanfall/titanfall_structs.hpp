/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#pragma once

#include "../../../utils/math.hpp"
#undef PLANES
namespace Titanfall {
    struct VertexUnlit_t {
        uint32_t  vertexIndex;
        uint32_t  normalIndex;
        Vector2f  uv0;
        uint32_t  unknown;
    };

    // 0x48
    struct VertexLitFlat_t {
        uint32_t  vertexIndex;
        uint32_t  normalIndex;
        Vector2f  uv0;
        uint32_t  unknown0;
        uint32_t  unknown1;
        uint32_t  unknown2;
        uint32_t  unknown3;
        uint32_t  unknown4;
    };

    // 0x49
    struct VertexLitBump_t {
        uint32_t  vertexIndex;
        uint32_t  normalIndex;
        Vector2f  uv0;
        int32_t   negativeOne;
        Vector2f  uv1;
        uint32_t  unk[4];
    };

    // 0x4A
    struct VertexUnlitTS_t {
        uint32_t  vertexIndex;
        uint32_t  normalIndex;
        Vector2f  uv0;
        uint32_t  unknown0;
        uint32_t  unknown1;
        uint32_t  unknown2;
    };

    // 0x50
    struct Mesh_t {
        uint32_t  triOffset;
        uint16_t  triCount;
        uint16_t  vertexOffset;
        uint16_t  vertexCount;
        uint8_t   vertexType;
        uint8_t   unused;
        uint32_t  const0;
        uint16_t  unk1;
        uint16_t  unk2;
        uint16_t  unk3;
        uint16_t  materialOffset;
        uint32_t  flags;
    };

    struct MaterialSort_t {
        int16_t  textureData;
        int16_t  lightmapHeader;
        int16_t  cubemap;
        int16_t  unk;
        int32_t  vertexOffset;
    };

    // 0x53
    struct LightmapHeader_t {
        int32_t type;
        int16_t width;
        int16_t height;
    };

    // 0x55
    struct CMGrid_t {
        float     scale;
        int32_t   xOffset;
        int32_t   yOffset;
        int32_t   xCount;
        int32_t   yCount;
        int32_t   straddleGroupCount;
        uint32_t  brushSidePlaneOffset;
    };
}

enum class eTitanfallLumps : int {
    ENTITIES                        = 0,
    PLANES                          = 1,
    TEXTURE_DATA                    = 2,
    VERTICES                        = 3,
    MODELS                          = 14,
    ENTITY_PARTITIONS               = 24,
    PHYSICS_COLLIDE                 = 29,
    VERTEX_NORMALS                  = 30,
    GAME_LUMP                       = 35,
    LEAF_WATER_DATA                 = 36,
    PAKFILE                         = 40,
    CUBEMAPS                        = 42,
    TEXTURE_DATA_STRING_DATA        = 43,
    TEXTURE_DATA_STRING_TABLE       = 44,
    WORLD_LIGHTS                    = 54,
    PHYSICS_LEVEL                   = 62,
    TRICOLL_TRIANGLES               = 66,
    TRICOLL_NODES                   = 68,
    TRICOLL_HEADERS                 = 69,
    PHYSICS_TRIANGLES               = 70,
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
    CM_GRID                         = 85,
    CM_GRID_CELLS                   = 86,
    CM_GEO_SETS                     = 87,
    CM_GEO_SET_BOUNDS               = 88,
    CM_PRIMITIVES                   = 89,
    CM_PRIMITIVE_BOUNDS             = 90,
    CM_UNIQUE_CONTENTS              = 91,
    CM_BRUSHES                      = 92,
    CM_BRUSH_SIDE_PLANE_OFFSETS     = 93,
    CM_BRUSH_SIDE_PROPERTIES        = 94,
    CM_BRUSH_SIDE_TEXTURE_VECTORS   = 95,
    TRICOLL_BEVEL_STARTS            = 96,
    TRICOLL_BEVEL_INDICES           = 97,
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
    PORTAL_EDGE_INTERSECT_HEADER    = 116,
    OCCLUSION_MESH_VERTICES         = 117,
    OCCLUSION_MESH_INDICES          = 118,
    CELL_AABB_NODES                 = 119,
    OBJ_REFERENCES                  = 120,
    OBJ_REFERENCE_BOUNDS            = 121,
    LEVEL_INFO                      = 123,
    SHADOW_MESH_OPAQUE_VERTICES     = 124,
    SHADOW_MESH_ALPHA_VERTICES      = 125,
    SHADOW_MESH_INDICES             = 126,
    SHADOW_MESHES                   = 127
};
