#ifndef SHADERS_MANAGER_HPP
#define SHADERS_MANAGER_HPP 1

#include "Program.hpp"

namespace EngineSpace
{
    class ShadersManager
    {
        Program skybox;
        Program terrain;

    public:
        void setSkyboxProgram(const Program& prog) { skybox = prog; }
        void setTerrainProgram(const Program& prog) { terrain = prog; }

        Program& getSkyboxProgram() { return skybox; }
        Program& getTerrainProgram() { return terrain; }
    };
}
#endif
