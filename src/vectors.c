#include "vectors.h"

Vector3 addv3(Vector3 v1, Vector3 v2) {
    Vector3 result = v1;
    result.x += v2.x;
    result.y += v2.y;
    result.z += v2.z;
    return result;
}

Vector3 smul(float s, Vector3 v) {
    Vector3 result = v;
    result.x *= s;
    result.y *= s;
    result.z *= s;
    return result;
}

float dot(Vector3 v1, Vector3 v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vector3 cross(Vector3 v1, Vector3 v2) {
    Vector3 result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;

    return result;
}

Quaternion multQ(Quaternion q1, Quaternion q2) {
    Quaternion result;
    result.scalar = q1.scalar * q2.scalar - dot(q1.vector, q2.vector);
    result.vector = addv3(cross(q1.vector, q2.vector), addv3(smul(q1.scalar, q2.vector), smul(q2.scalar, q1.vector)));

    return result;
}

Vector3 rotation(Vector3 v, Quaternion rot) {
    Quaternion tmp = {0, v};
    tmp = multQ(rot, tmp);
    rot.vector = smul(-1, rot.vector);
    tmp = multQ(tmp, rot);
    return tmp.vector;
}
