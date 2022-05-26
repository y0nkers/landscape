#include "PerlinNoise2D.hpp"

namespace EngineSpace
{
	PerlinNoise2D::PerlinNoise2D(const double& pFrequency, const double& pAmplitude, const double& pPersistance, const unsigned& pOctaves, const double& pMulitplier, const unsigned& pOffsetX, const unsigned& pOffsetY)
		: frequency(pFrequency), amplitude(pAmplitude), persistence(pPersistance), octaves(pOctaves), multiplier(pMulitplier), offsetX(pOffsetX), offsetY(pOffsetY) {
		;
	}

	double PerlinNoise2D::octavePerlin(const double& x, const double& z) const // Расчёт значения шумовой функции
	{
		double total = 0;
		double freq = frequency;
		double amp = amplitude;
		double maxValue = 0;
		if (amp == 0) return 0;

		for (unsigned i = 0; i < octaves; ++i)
		{
			glm::vec2 p((x * freq + offsetX) * multiplier, (z * freq + offsetY) * multiplier);

			total += ((glm::perlin(p) + 1.0) / 2.0) * amp;
			maxValue += amp;
			amp *= persistence;
			freq *= 2;
		}
		return total / maxValue;
	}

	void PerlinNoise2D::fillData(std::vector<GLubyte>& map, std::vector<double>& points, const unsigned& width, const unsigned& height, const unsigned& depth) const
	{
		double xFactor = 1.0 / (width - 1);
		double zFactor = 1.0 / (height - 1);

		for (size_t h = 0; h < height; ++h)
		{
			double dz = zFactor * h;
			for (size_t w = 0; w < width; ++w)
			{
				double dx = xFactor * w;
				double x = dx - 0.5;
				double y = octavePerlin(dx, dz);
				double z = 0.5 - dz;

				size_t pIdx = (w * width + h) * 3;
				points[pIdx] = x;
				points[pIdx + 1] = y;
				points[pIdx + 2] = z;

				size_t mIdx = (w * width + h) * 4;
				map[mIdx] = (GLubyte)(255 * x);
				map[mIdx + 1] = (GLubyte)(255 * y);
				map[mIdx + 2] = (GLubyte)(255 * z);
				map[mIdx + 3] = (GLubyte)255;
			}
		}
	}
}
