#include "Programs.hpp"

#include "Core/Program.hpp"

const std::shared_ptr<Core::Program> &Programs::DefaultProgram(){
    static auto program=std::make_shared<Core::Program>(
        RESOURCE_DIR "/shader/default/default.vert",
        RESOURCE_DIR "/shader/default/default.frag");
    return program;
}
const std::shared_ptr<Core::Program> &Programs::GrayScaleProgram(){
    static auto program=std::make_shared<Core::Program>(
        RESOURCE_DIR "/shader/default/default.vert",
        RESOURCE_DIR "/shader/grayscale/grayscale.frag");
    return program;
}