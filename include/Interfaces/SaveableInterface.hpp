#pragma once

#include "Context.hpp"
#include <sstream>
#include <string>
#include <fstream>

namespace interfaces {

    template <typename T>
    class Saveable {
        public:
            Saveable() { }
            
            void save(std::string filename) const {
                std::ofstream save_file{filename};
                if (!save_file.is_open())
                    throw std::runtime_error("Can not open file " + filename + " to save\n");
                
                save_file << serialize();
            }
            
            std::string serialize() const {
                static_cast<T>(*this)->serialize();
            };
    };
}