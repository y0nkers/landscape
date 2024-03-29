﻿#ifndef CONVERTER_TO_NORMAL_MAP_HPP
#define CONVERTER_TO_NORMAL_MAP_HPP 1

#include "Texture.hpp"

namespace EngineSpace
{
    class ConverterToNormalMap
    {
        GLubyte toRGB(const float& pixel);
        int clamp(const int& value, const int& max);
        void prepareData(GLubyte* inputData, const std::vector<GLubyte>& data, const unsigned& width, const unsigned& height);
        glm::vec3 calculateNormal(const std::vector<GLubyte>& data, const unsigned& width, const unsigned& height, const int& row, const int& column);
        float getHeight(const std::vector<GLubyte>& data, const unsigned& width, const unsigned& height, int row, int column);

    public:
        void convert(const std::vector<GLubyte>& data, Texture& textureDestination, const unsigned& width, const unsigned& height);
    };
}
#endif
