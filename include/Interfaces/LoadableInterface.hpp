#pragma once

#include "Context.hpp"
#include <sstream>
#include <string>
#include <fstream>

namespace interfaces {

    template <typename T>
    class Loadable {
        public:
            Loadable() { }

            static T load(std::string filename, game_engine::Context* context) {
                std::ifstream load_file{filename};
                if (!load_file.is_open())
                    throw std::runtime_error("Can not open file " + filename + " to save\n");
                
                std::stringstream file_content_ss;
                file_content_ss << load_file.rdbuf();
                
                return deserialize(std::move(file_content_ss), context);
            }

            static T deserialize(std::stringstream file_content, game_engine::Context* context) {
                T::deserialize(file_content, context);
            };

    };
}