#ifndef MODEL_H_
#define MODEL_H_

#include "vectors.h"

typedef struct {
    Vector3* vertices;
    Color* vColors;
    int triCount;

    float position[3];
    float rotation[3];
    float scale;
} Model;

#endif

