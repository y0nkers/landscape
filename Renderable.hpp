#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP 1

#include "Program.hpp"

namespace EngineSpace
{
    class Renderable
    {
    public:
        virtual void render(Program& program) = 0;
        virtual unsigned getVAO() const { return 0; }
        virtual ~Renderable() { ; }
    };
}
#endif
