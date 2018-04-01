#ifndef VECTORS_H_
#define VECTORS_H_

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    union {
        float x;
        float r;
    };
    union {
        float y;
        float g;
    };
    union {
        float z;
        float b;
    };
    union {
        float w;
        float a;
    };
} Vector4;

typedef Vector4 Color;

typedef struct {
    float scalar;
    Vector3 vector;
} Quaternion;

Vector3 smul(float, Vector3);
float dot(Vector3, Vector3);
Vector3 cross(Vector3, Vector3);
Quaternion multQ(Quaternion, Quaternion);
Vector3 rotate(Vector3, Quaternion);

#endif

