#pragma once 

#include "Interfaces/LoadableInterface.hpp"
#include "Interfaces/SaveableInterface.hpp"
#include "States/State.hpp"
#include <sstream>
#include <string>
namespace states_engine {
    class SaveableLoadableState: virtual public State {
    
    public:
        // Given class may implement Saveable and Loadable CRTP interfaces, 
        // but that requires more complicated code, so I decided to make SaveableLoadableState
        // independent 
        SaveableLoadableState() { }
        virtual ~SaveableLoadableState() = default;

        virtual std::string serialize() const = 0;

        virtual void save_state(std::string file_name) const {
                std::ofstream save_file{file_name};
                if (!save_file.is_open())
                    throw std::runtime_error("Can not open file " + file_name + " to save\n");
                
                save_file << serialize();
        }
        
        virtual void deserialize(std::stringstream file_content) = 0;

        virtual void load_state(std::string file_name) {
            std::ifstream load_file{file_name};
            if (!load_file.is_open())
                throw std::runtime_error("Can not open file " + file_name + " to save\n");
            
            std::stringstream file_content_ss;
            file_content_ss << load_file.rdbuf();
                
            deserialize(std::move(file_content_ss));
        }

    };
}