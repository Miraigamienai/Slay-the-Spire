#pragma once

#include <memory>

//fwd decl
namespace Core{
    class Program;
}

class Programs
{
public:
    Programs()=delete;~Programs()=delete;Programs(const Programs &) = delete;Programs(Programs &&) = delete;Programs &operator=(const Programs &) = delete;Programs &operator=(Programs &&) = delete;
    static const std::shared_ptr<Core::Program> &DefaultProgram();
    static const std::shared_ptr<Core::Program> &GrayScaleProgram();
};