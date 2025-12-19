#include <algorithm>
#include "registru.h"

void registru::print()
{
    std::cout << "Registru: " << this->memory << std::endl;
}

std::string registru::get_memory()
{
    return this->memory;
}

void registru::change_memory(const std::string memory_)
{
    if(this->reset && !this->enable)
    {
        std::cout << "Setati reset-ul pe 0." << std::endl;
        this->memory = "00000000";
        return;
    }

    std::string& alias = this->enable ? this->temp_memory : this->memory;

    if(!this->enable && !this->temp_memory.empty())
    {
        this->memory = this->temp_memory;
        this->temp_memory.clear();
        return;
    }

    if(memory_.size() != 8)
    {
        alias = "00000000";
        alias.replace(8 - memory_.size(), memory_.size(), memory_);
    }
    else
    {
        alias = memory_;
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
