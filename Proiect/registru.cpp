#include <algorithm>
#include "registru.h"

void registru::print()
{
    std::cout << "Registru: " << this->memory << std::endl;
}

void registru::change_memory(const std::string memory_)
{
    if(!this->enable)
    {
        if(this->reset == 1)
        {
            std::cout << "Setati reset-ul pe 0." << std::endl;
            this->memory.replace(0, 8, "00000000");
            this->print(); 
        }
        else
        {
            if(memory_.size() != 8)
            {
                this->memory.replace(0, 8, "00000000");
                this->memory.replace(8 - memory_.size(), memory_.size(), memory_);
            }
            else
            {
                this->memory = memory_;
            }
        }
    }
}

registru& registru::operator=(const std::string memory_)
{
    this->change_memory(memory_);
    
    return *this;
}

void registru::rotate_data(size_t shift)
{
    std::rotate(this->memory.begin(), this->memory.end() - shift, this->memory.end());
}
