

#ifndef MODEL_H
#define MODEL_H

#pragma once
#include <cstddef>

class Model
{
public:
    unsigned int VAO;
    unsigned int VBO;
    size_t vertexCount;
    const char *name;

    Model(unsigned int VAO, unsigned int VBO, size_t vertexCount, const char *name)
    {
        this -> VAO = VAO;
        this -> VBO = VBO;
        this -> name = name;
        this -> vertexCount = vertexCount;
    }
};
#endif