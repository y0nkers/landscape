﻿#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP 1

#include <iostream>
#include <stdexcept>
#include <vector>
#include <glew/include/GL/glew.h>
#include "stb_image.h"
#include "Config.hpp"

namespace EngineSpace
{
    class TextureLoader
    {
        static std::string getError(const std::string& fileName);
        static GLenum getFormat(const unsigned& nrChannels);

    public:
        static void loadTexture(unsigned& textureId, const std::string& fileName, GLenum type);
        static void loadTexture2D(unsigned& textureId, const std::string& fileName);
        static void loadCubeMapTexture(unsigned& textureId, const std::vector<std::string>& fileNames);
    };
}
#endif
