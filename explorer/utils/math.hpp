/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#pragma once

template<typename T>
struct Vector3 {
    T vec[3];

    Vector3() :
        vec(0) {}

    Vector3( float _x, float _y, float _z ) :
        vec(_x, _y, _z) {}

    T x() {
        return vec[0];
    }

    T y() {
        return vec[1];
    }

    T z() {
        return vec[2];
    }
};

template<typename T>
struct Vector2 {
    T vec[2];

    T x() {
        return vec[0];
    }

    T y() {
        return vec[1];
    }
};

using Vector3f = Vector3<float>;
using Vector2f = Vector2<float>;

template<typename T>
struct AABB {
    Vector3<T> mins;
    Vector3<T> maxs;
};