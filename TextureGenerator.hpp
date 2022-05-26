#ifndef TEXTURE_GENERATOR_HPP
#define TEXTURE_GENERATOR_HPP 1

#include "Texture.hpp"

namespace EngineSpace
{
    class TextureGenerateMethod
    {
    public:
        virtual void fillData(std::vector<GLubyte>& map, std::vector<double>& points, const unsigned& width, const unsigned& height, const unsigned& depth) const = 0;
    };

    class TextureGenerator
    {
    protected:
        std::vector<GLubyte> map;
        std::vector<double> points;
    public:
        virtual void generate(Texture& texture, const TextureGenerateMethod& method, const unsigned& width, const unsigned& height, const unsigned& depth) {}
        virtual ~TextureGenerator() {}

        const std::vector<GLubyte>& getHeightMap() const { return map; }
        const std::vector<double>& getPoints() const { return points; }
    };
}
#endif
