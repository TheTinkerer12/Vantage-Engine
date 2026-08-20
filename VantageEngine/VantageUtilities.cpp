
#include "VantageUtilities.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "../tiny_obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

unsigned int VantageUtilities::loadImage(const char *imagePath)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return texture;
}

Shader VantageUtilities::loadShader(const char *vertShaderPath, const char *fragShaderPath)
{
    Shader shader(vertShaderPath, fragShaderPath);
    shader.use();
    return shader;
}

bool VantageUtilities::loadObjAsTriangles(const std::string& filepath, std::vector<Vertex>& outVertices) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    // Enable triangulation (last parameter = true)
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str(), nullptr, true);

    if (!warn.empty()) std::cout << "WARN: " << warn << std::endl;
    if (!err.empty()) std::cerr << "ERR: " << err << std::endl;
    if (!ret) return false;

    // Iterate over shapes/objects in the obj file
    for (size_t s = 0; s < shapes.size(); s++) {
        size_t index_offset = 0;
        // Iterate over faces (each polygon is triangulated into 3 indices)
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f]; // Will be 3 due to triangulation

            for (size_t v = 0; v < fv; v++) {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                Vertex vertex = {};

                // Extract Position (3 floats per vertex)
                vertex.position[0] = attrib.vertices[3 * idx.vertex_index + 0];
                vertex.position[1] = attrib.vertices[3 * idx.vertex_index + 1];
                vertex.position[2] = attrib.vertices[3 * idx.vertex_index + 2];

                // Extract Texture Coordinate / UV (2 floats per vertex)
                if (idx.texcoord_index >= 0) {
                    vertex.texcoord[0] = attrib.texcoords[2 * idx.texcoord_index + 0];
                    vertex.texcoord[1] = attrib.texcoords[2 * idx.texcoord_index + 1]; // Flip if needed: 1.0f - ...
                }

                outVertices.push_back(vertex);
            }
            index_offset += fv;
        }
    }
    return true;
}

Model VantageUtilities::loadModelFromVerticies(float modelData[], size_t size, size_t vertexCount, const char *name)
{
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, modelData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    return Model(VAO, VBO, vertexCount, name);
}

Model VantageUtilities::loadModel(const char *filePath, const char *name)
{
    std::vector<Vertex> vertices;
    vertices = std::vector<Vertex>();
    loadObjAsTriangles(filePath, vertices);

    float modelData[vertices.size() * 5];

    for (int i = 0; i < vertices.size(); i++)
    {
        Vertex v;
        v = vertices[i];
        modelData[(i * 5) + 0] = v.position[0];
        modelData[(i * 5) + 1] = v.position[1];
        modelData[(i * 5) + 2] = v.position[2];
        modelData[(i * 5) + 3] = v.texcoord[0];
        modelData[(i * 5) + 4] = v.texcoord[1];
    }

    return loadModelFromVerticies(modelData, sizeof(modelData), vertices.size(), name);
}