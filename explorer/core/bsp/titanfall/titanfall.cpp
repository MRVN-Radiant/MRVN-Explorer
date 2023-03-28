/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#include "titanfall.hpp"

#include "../../../utils/logging.hpp"

/*CTitanfallBsp::CTitanfallBsp( const char *filename ) : IBsp(filename) {
    LOG_EXPLORER_INFO("Titanfall BSP: {}", filename)
}*/

std::string CTitanfallBsp::GetGameName() {
    return this->GetBspVersion() == 29 ? "Titanfall 1" : "Titanfall 2";
}

std::vector<LumpDef_t> CTitanfallBsp::GetLumps() {
    return  {
                //                             name,                       size, entries,  version,   gameVersion, canInspect
                {                        "Entities", m_header.lumps[  0].length,       0,        0,            -1,      false },
                {                          "Planes", m_header.lumps[  1].length,       0,        0,            -1,      false },
                {                    "Texture Data", m_header.lumps[  2].length,       0,        0,            -1,      false },
                {                        "Vertices", m_header.lumps[  3].length,       0,        0,            -1,      false },
                {         "Lightprobe Parent Infos", m_header.lumps[  4].length,       0,        0,            37,      false },
                {             "Shadow Environments", m_header.lumps[  5].length,       0,        0,            37,      false },
                {            "Lightprobe BSP Nodes", m_header.lumps[  6].length,       0,        0,            37,      false },
                {          "Lightprobe BSP Ref Ids", m_header.lumps[  7].length,       0,        0,            37,      false },
                {                          "Unused", m_header.lumps[  8].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[  9].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 10].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 11].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 12].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 13].length,       0,       -1,            -1,      false },
                {                          "Models", m_header.lumps[ 14].length,       0,        0,            -1,      false },
                {                          "Unused", m_header.lumps[ 15].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 16].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 17].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 18].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 19].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 20].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 21].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 22].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 23].length,       0,       -1,            -1,      false },
                {               "Entity Partitions", m_header.lumps[ 24].length,       0,        0,            -1,      false },
                {                          "Unused", m_header.lumps[ 25].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 26].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 27].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 28].length,       0,       -1,            -1,      false },
                {                 "Physics Collide", m_header.lumps[ 29].length,       0,        0,            -1,      false },
                {                  "Vertex Normals", m_header.lumps[ 30].length,       0,        0,            -1,      false },
                {                          "Unused", m_header.lumps[ 31].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 32].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 33].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 34].length,       0,       -1,            -1,      false },
                {                       "Game Lump", m_header.lumps[ 35].length,       0,        0,            -1,      false },
                {                 "Leaf Water Data", m_header.lumps[ 36].length,       0,        0,            -1,      false },
                {                          "Unused", m_header.lumps[ 37].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 38].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 39].length,       0,       -1,            -1,      false },
                {                         "PakFile", m_header.lumps[ 40].length,       0,        0,            -1,      false },
                {                          "Unused", m_header.lumps[ 41].length,       0,       -1,            -1,      false },
                {                        "CubeMaps", m_header.lumps[ 42].length,       0,        0,            -1,      false },
                {        "Texture Data String Data", m_header.lumps[ 43].length,       0,        0,            -1,      false },
                {       "Texture Data String Table", m_header.lumps[ 44].length,       0,        0,            -1,      false },
                {                          "Unused", m_header.lumps[ 45].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 46].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 47].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 48].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 49].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 50].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 51].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 52].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 53].length,       0,       -1,            -1,      false },
                {                    "World Lights", m_header.lumps[ 54].length,       0,        0,            -1,      false },
                {        "World Light Parent Infos", m_header.lumps[ 55].length,       0,        0,            37,      false },
                {                          "Unused", m_header.lumps[ 56].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 57].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 58].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 59].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 60].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 61].length,       0,       -1,            -1,      false },
                {                   "Physics Level", m_header.lumps[ 62].length,       0,        0,            -1,      false },
                {                          "Unused", m_header.lumps[ 63].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 64].length,       0,       -1,            -1,      false },
                {                          "Unused", m_header.lumps[ 65].length,       0,       -1,            -1,      false },
                {               "Tricoll Triangles", m_header.lumps[ 66].length,       0,        0,            -1,      false },
                {                          "Unused", m_header.lumps[ 67].length,       0,       -1,            -1,      false },
                {                   "Tricoll Nodes", m_header.lumps[ 68].length,       0,        0,            -1,      false },
                {                 "Tricoll Headers", m_header.lumps[ 69].length,       0,        0,            -1,      false },
                {               "Physics Triangles", m_header.lumps[ 70].length,       0,        0,            -1,      false },
                {                    "Vertex Unlit", m_header.lumps[ 71].length,       0,        0,            -1,      false },
                {                 "Vertex Lit Flat", m_header.lumps[ 72].length,       0,        0,            -1,      false },
                {                 "Vertex Lit Bump", m_header.lumps[ 73].length,       0,        0,            -1,      false },
                {                 "Vertex Unlit TS", m_header.lumps[ 74].length,       0,        0,            -1,      false },
                {              "Vertex Blinn Phong", m_header.lumps[ 75].length,       0,        0,            -1,      false },
                {               "Vertex Reserved 5", m_header.lumps[ 76].length,       0,        0,            -1,      false },
                {               "Vertex Reserved 6", m_header.lumps[ 77].length,       0,        0,            -1,      false },
                {               "Vertex Reserved 7", m_header.lumps[ 78].length,       0,        0,            -1,      false },
                {                    "Mesh Indices", m_header.lumps[ 79].length,       0,        0,            -1,      false },
                {                          "Meshes", m_header.lumps[ 80].length,       0,        0,            -1,       true },
                {                     "Mesh Bounds", m_header.lumps[ 81].length,       0,        0,            -1,      false },
                {                   "Material Sort", m_header.lumps[ 82].length,       0,        0,            -1,      false },
                {                "Lightmap Headers", m_header.lumps[ 83].length,       0,        0,            -1,       true },
                {                          "Unused", m_header.lumps[ 84].length,       0,        0,            -1,      false },
                {                         "CM Grid", m_header.lumps[ 85].length,       0,        0,            -1,      false },
                {                   "CM Grid Cells", m_header.lumps[ 86].length,       0,        0,            -1,      false },
                {                     "CM Geo Sets", m_header.lumps[ 87].length,       0,        0,            -1,      false },
                {               "CM Geo Set Bounds", m_header.lumps[ 88].length,       0,        0,            -1,      false },
                {                   "CM Primitives", m_header.lumps[ 89].length,       0,        0,            -1,      false },
                {             "CM Primitive Bounds", m_header.lumps[ 90].length,       0,        0,            -1,      false },
                {              "CM Unique Contents", m_header.lumps[ 91].length,       0,        0,            -1,      false },
                {                      "CM Brushes", m_header.lumps[ 92].length,       0,        0,            -1,      false },
                {     "CM Brush Side Plane Offsets", m_header.lumps[ 93].length,       0,        0,            -1,      false },
                {        "CM Brush Side Properties", m_header.lumps[ 94].length,       0,        0,            -1,      false },
                {   "CM Brush Side Texture Vectors", m_header.lumps[ 95].length,       0,        0,            -1,      false },
                {            "Tricoll Bevel Starts", m_header.lumps[ 96].length,       0,        0,            -1,      false },
                {           "Tricoll Bevel Indices", m_header.lumps[ 97].length,       0,        0,            -1,      false },
                {               "Lightmap Data Sky", m_header.lumps[ 98].length,       0,        0,            -1,      false },
                {                  "CSM AABB Nodes", m_header.lumps[ 99].length,       0,        0,            -1,      false },
                {              "CSM Obj References", m_header.lumps[100].length,       0,        0,            -1,      false },
                {                     "Lightprobes", m_header.lumps[101].length,       0,        0,            -1,      false },
                {  "Static Prop Lightprobe Indices", m_header.lumps[102].length,       0,        0,            -1,      false },
                {                 "Lightprobe Tree", m_header.lumps[103].length,       0,        0,            -1,      false },
                {           "Lightprobe References", m_header.lumps[104].length,       0,        0,            -1,      false },
                {  "Lightmap Data Real Time Lights", m_header.lumps[105].length,       0,        0,            -1,      false },
                {                  "Cell BSP Nodes", m_header.lumps[106].length,       0,        0,            -1,      false },
                {                           "Cells", m_header.lumps[107].length,       0,        0,            -1,      false },
                {                         "Portals", m_header.lumps[108].length,       0,        0,            -1,      false },
                {                 "Portal Vertices", m_header.lumps[109].length,       0,        0,            -1,      false },
                {                    "Portal Edges", m_header.lumps[110].length,       0,        0,            -1,      false },
                {             "Portal Vertex Edges", m_header.lumps[111].length,       0,        0,            -1,      false },
                {        "Portal Vertex References", m_header.lumps[112].length,       0,        0,            -1,      false },
                {          "Portal Edge References", m_header.lumps[113].length,       0,        0,            -1,      false },
                {   "Portal Edge Intersect At Edge", m_header.lumps[114].length,       0,        0,            -1,      false },
                { "Portal Edge Intersect At Vertex", m_header.lumps[115].length,       0,        0,            -1,      false },
                {    "Portal Edge Intersect Header", m_header.lumps[116].length,       0,        0,            -1,      false },
                {         "Occlusion Mesh Vertices", m_header.lumps[117].length,       0,        0,            -1,      false },
                {          "Occlusion Mesh Indices", m_header.lumps[118].length,       0,        0,            -1,      false },
                {                 "Cell AABB Nodes", m_header.lumps[119].length,       0,        0,            -1,      false },
                {                  "Obj References", m_header.lumps[120].length,       0,        0,            -1,      false },
                {            "Obj Reference Bounds", m_header.lumps[121].length,       0,        0,            -1,      false },
                {          "Lightmap Data RTL Page", m_header.lumps[122].length,       0,        0,            37,      false },
                {                      "Level Info", m_header.lumps[123].length,       0,        0,            -1,      false },
                {     "Shadow Mesh Opaque Vertices", m_header.lumps[124].length,       0,        0,            -1,      false },
                {      "Shadow Mesh Alpha Vertices", m_header.lumps[125].length,       0,        0,            -1,      false },
                {             "Shadow Mesh Indices", m_header.lumps[126].length,       0,        0,            -1,      false },
                {                   "Shadow Meshes", m_header.lumps[127].length,       0,        0,            -1,      false },
            };
}

std::vector<DrawableType_t> CTitanfallBsp::GetDrawableTypes() {
    return {
        //    name, id
        { "Meshes",  (int)eTitanfallLumps::MESHES },
    };
}
