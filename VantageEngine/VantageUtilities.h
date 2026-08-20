
#ifndef VANTAGE_UTILITIES_H
#define VANTAGE_UTILITIES_H

#pragma once
#include "../shader.h"
#include <vector>
#include "../VantageMath/Vertex.h"
#include "Model.h"

class VantageUtilities
{
public:
    static unsigned int loadImage(const char *imagePath);
    static Shader loadShader(const char *vertShaderPath, const char *fragShaderPath);
    static Model loadModel(const char *filePath, const char *name);
private:
    static Model loadModelFromVerticies(float modelData[], size_t size, size_t vertexCount, const char *name);
    static bool loadObjAsTriangles(const std::string& filepath, std::vector<Vertex>& outVertices);
};

#endif