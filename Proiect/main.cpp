#include <string>
#include <thread>
#include <chrono>
#include "registru.h"

void rotate_values(registru& reg, const bool& start, const bool& stop)
{
    while(!stop)
    {
        if(start && !reg.enable)
        {
            reg.rotate_data();            
            reg.print();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

int main()
{
    bool valid_option = true;
    bool stop = 0;
    bool start = 0;

    std::cout << "By default, registrul este in paralel (functionare = 0)." << std::endl
        << "Pentru a introduce starea initiala a registrului in inel, setati intai enable-ul pe high." << std::endl
    << std::endl;

    std::string x;
    std::cout 
        << "sir de 0 sau 1 - introducere valoare in registru" << std::endl 
        << "2 sau 3 - functionare = 0 sau 1" << std::endl 
        << "4 sau 5 - reset = 0 sau 1" << std::endl 
        << "6 sau 7 - enable = 0 sau 1 (activ pe low) " << std::endl
    << std::endl;

    registru reg;
    std::thread inel(rotate_values, std::cref(reg), std::cref(start), std::cref(stop));

    while(valid_option)
    {
        getline(std::cin, x);
        start = 0;
        if(x.size() == 1 && x.front() > '1')
        {
            char a = x.front();
            switch(a)
            {

                case '2':
                    reg.functionare = 0;
                    std::cout << "Registru in paralel." << std::endl;
                    break;
                case '3':
                    reg.functionare = 1;
                    std::cout << "Registru in inel" << std::endl;
                    start = 1;
                    break;
                case '4':
                    std::cout << "Reset setat pe 0" << std::endl;
                    reg.reset = 0;
                    break;
                case '5':
                    if(!reg.enable)
                    {
                        reg.reset = 1;
                        std::cout << "Resetat valori registru." << std::endl;
                        reg.change_memory();
                    }
                    break;
                case '6':
                    reg.enable = 0;
                    std::cout << "Enable setat pe 0." << std::endl;
                    reg.change_memory(reg.get_memory());
                    break;
                case '7':
                    reg.enable = 1;
                    std::cout << "Enable setat pe 1." << std::endl;
                    break;
                default:
                    valid_option = false;
                    std::cout << "Invalid option. Program ended by user being an idiot." << std::endl;
                    break;
            }       
        }
        if(x.size() > 1 || reg.enable == 0)
        {
            bool data_only = true;
            for(int i = 0; i < x.size(); i ++)
            {
                if(x.at(i) != '1' && x.at(i) != '0')
                {
                    data_only = false;
                    break;
                }
            }
            if(data_only && (!reg.functionare || reg.enable == 1))
            {
                reg = x;           
            }

            reg.print();

            if(reg.functionare)
            {
                start = 1;
            }


        }

    }

    stop = 1;
    if(inel.joinable())
    {
        inel.join();        
    }

    return 0;
}