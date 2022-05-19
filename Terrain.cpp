#include "Terrain.hpp"

namespace EngineSpace
{
    Terrain::Terrain()
    {
        glGenVertexArrays(1, &VAO);
        amount = new unsigned;
        *amount = 1;
    }

    Terrain::Terrain(const Terrain& terrain) { swap(terrain); }

    Terrain& Terrain::operator=(const Terrain& terrain)
    {
        swap(terrain);
        return *this;
    }

    void Terrain::swap(const Terrain& terrain)
    {
        textureStone = terrain.textureStone;
        textureGrass = terrain.textureGrass;
        textureHeight = terrain.textureHeight;
        textureNormal = terrain.textureNormal;
        depth = terrain.depth;
        tesselationLevel = terrain.tesselationLevel;
        VAO = terrain.VAO;
        amount = terrain.amount;
        *amount = *amount + 1;
    }

    Terrain::~Terrain() { clear(); }

    void Terrain::clear()
    {
        *amount = *amount - 1;
        if (*amount == 0)
        {
            delete amount;
            glDeleteVertexArrays(1, &VAO);
        }
    }

    void Terrain::render(Program& program)
    {
        glDisable(GL_CULL_FACE);

        Transformationable::render(program);
        program.setFloat("depth", depth);
        program.setInt("tesselationLevel", tesselationLevel);

        Texture::active(0);
        program.setInt("heightMap", 0);
        textureHeight.bind(GL_TEXTURE_2D);

        Texture::active(1);
        program.setInt("normalMap", 1);
        textureNormal.bind(GL_TEXTURE_2D);

        Texture::active(2);
        program.setInt("stoneTex", 2);
        textureStone.bind(GL_TEXTURE_2D);

        Texture::active(3);
        program.setInt("grassTex", 3);
        textureGrass.bind(GL_TEXTURE_2D);

        glBindVertexArray(VAO);
        glPatchParameteri(GL_PATCH_VERTICES, 4); // Устанавливаем количество вершин на патч
        glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64); // отрисовываем сразу несколько экземпляров одного патча
        glBindVertexArray(0);
        Texture::unbind(GL_TEXTURE_2D);
        glEnable(GL_CULL_FACE);
    }
}
