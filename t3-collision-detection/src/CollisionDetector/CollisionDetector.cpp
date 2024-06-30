#include "CollisionDetector.h"

namespace cd {
bool isSameSide(const vec3 &p1, const vec3 &p2, const vec3 &a, const vec3 &b) {
    auto ba = b - a;
    auto cp1 = cross(ba, p1 - a);
    auto cp2 = cross(ba, p2 - a);
    return dot(cp1, cp2) >= 0;
}

bool isInside(const vec2 &p, const triangle &t) {
    return isSameSide(p, t[2], t[0], t[1]) &&
           isSameSide(p, t[1], t[0], t[2]) &&
           isSameSide(p, t[0], t[1], t[2]);
}

bool isColliding(const triangle &t1, const triangle &t2) {
    // returns true if triangles do not intersect
    auto checkTriangle = [](const triangle &base, const triangle &p) {
        // returns true if all points of the triangle `p`
        // lie on the same side of the edge `ba` and the
        // point `c` lies on the other side
        auto checkEdge = [&p](const vec2 &a, const vec2 &b, const vec2 &c) {
            return isSameSide(p[0], p[1], a, b) &&
                   isSameSide(p[0], p[2], a, b) &&
                   !isSameSide(p[0], c, a, b);
        };

        return checkEdge(base[0], base[1], base[2]) ||
               checkEdge(base[0], base[2], base[1]) ||
               checkEdge(base[1], base[2], base[0]);
    };

    return !(checkTriangle(t1, t2) || checkTriangle(t2, t1));
}
}