#include "TextureGenerator2D.hpp"

namespace EngineSpace
{
    void TextureGenerator2D::generate(Texture& texture, const TextureGenerateMethod& method, const unsigned& width, const unsigned& height, const unsigned& depth)
    {
        const unsigned size = width * height * 4;
        data.clear();
        data.resize(size);
        method.fillData(data, width, height, depth);

        bindTexture(texture, width, height, size);
    }

    void TextureGenerator2D::bindTexture(Texture& texture, const unsigned& width, const unsigned& height, const unsigned& size)
    {
        if (texture.isNotCreated())
        {
            texture.create();
            texture.bind(GL_TEXTURE_2D);
            glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Config::get().getAnisotropy());
        }

        GLubyte* inputData = new GLubyte[size];
        for (unsigned i = 0; i < size; ++i) 
            inputData[i] = data[i];

        texture.bind(GL_TEXTURE_2D);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, inputData);
        Texture::unbind(GL_TEXTURE_2D);
        delete[] inputData;
    }

    void TextureGenerator2D::changePointHeight(unsigned index, unsigned value)
    {
        int val = data[index + 1] + value;
        val = std::min(std::max(0, val), 255);
        data[index + 1] = val;
        //data[index] = val;
        //data[index + 2] = val;
        //data[index + 3] = val;
    }
}
