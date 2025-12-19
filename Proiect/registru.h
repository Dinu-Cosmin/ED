#pragma once
#include <iostream>

class registru
{
    private:
        std::string memory;
        std::string temp_memory;
    public:
        bool reset;
        bool functionare;
        bool enable;

        registru(std::string memory_="00000000", bool reset_=0, bool funcitonare_=0, bool enable_=0) 
            : memory(std::move(memory_)), reset(reset_), functionare(funcitonare_), enable(enable_)
        {};
        ~registru()
        {
            this->memory.clear();
        }

        std::string get_memory();

        void rotate_data(const size_t shift=1);
        void change_memory(const std::string memory_="00000000");
        registru& operator=(const std::string);
        void print();

};