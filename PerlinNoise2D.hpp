﻿#ifndef PERLIN_NOISE_2D_HPP
#define PERLIN_NOISE_2D_HPP 1

// https://habr.com/ru/post/142592/
#include <glm/gtc/noise.hpp>
#include "TextureGenerator.hpp"

namespace EngineSpace
{
    class PerlinNoise2D : public TextureGenerateMethod
    {
        double frequency; // частота (1/длина_волны => больше частота - меньше длина) (2^i)
        double amplitude; // разница между минимальным и максимальным значениями (persistence ^ i)
        double persistence; // Стойкость
        double multiplier;
        unsigned offsetX;
        unsigned offsetY;
        unsigned octaves; // количество шумовых функций

        double octavePerlin(const double& x, const double& y) const;

    public:
        PerlinNoise2D(const double& pFrequency = 1, const double& pAmplitude = 1, const double& pPersistance = 1, const unsigned& pOctaves = 4, const double& pMulitplier = 1, const unsigned& pOffsetX = 0, const unsigned& pOffsetY = 0);
        virtual void fillData(std::vector<GLubyte>& data, const unsigned& width, const unsigned& height, const unsigned& depth) const;
    };
}
#endif
