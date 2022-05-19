#ifndef TEXTURE_GENERATOR_2D_HPP
#define TEXTURE_GENERATOR_2D_HPP 1

#include "TextureGenerator.hpp"

namespace EngineSpace
{
    class TextureGenerator2D : public TextureGenerator
    {
    public:
        virtual void generate(Texture& texture, const TextureGenerateMethod& method, const unsigned& width, const unsigned& height, const unsigned& depth = 1);
        void bindTexture(Texture& texture, const unsigned& width, const unsigned& height, const unsigned& size);
        void changePointHeight(unsigned index, unsigned value);
    };
}
#endif
