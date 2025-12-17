#include <iostream>
#include <string>
#include <unistd.h>

static int functionare = 0;
static int reset = 0;
static int registru[] = {0, 0, 0, 0, 0, 0, 0, 0};

void printRegistry()
{
    std::cout << "Registru: ";
    for(size_t i = 0; i < 8; i ++)
    {
        std::cout << registru[i];
    }
    std::cout << std::endl;
}

void resetReg()
{
    for(size_t i = 0; i < 8; i ++)
    {
        registru[i] = 0;
    }
    printRegistry();
}

void changeMemory(std::string x)
{
    if(reset == 1)
    {
        std::cout << "Setati reset-ul pe 0." << std::endl;
        resetReg();
    }
    else
    {
        switch(functionare)
        {
            case 0:
                //Registru in inel
                for(int j = 8; j > 0; j --)
                {
                    for(int i = 6; i >= 0; i --)
                    {
                        registru[i+1] = registru[i];
                    }
                    if(!x.empty())
                    {
                        registru[0] = x.back() - '0';
                        x.pop_back();                    
                    }
                    else
                    {
                        registru[0] = 0;
                    }
                    printRegistry();
                    sleep(1);
                }
                break;
            case 1:
                for(int i = 7; i >= 0; i --)
                {
                    if(!x.empty())
                    {
                        registru[i] = x.back() - '0';
                        x.pop_back();
                    }
                    else
                    {
                        registru[i] = 0;
                    }
                }
                printRegistry();
                break;
            default:
                break;                
        }
    }
}

int main()
{
    bool valid_option = true;
    std::string x;
    std::cout << "sir de 0 sau 1 - introducere valoare in registru" << std::endl << "2 sau 3 - functionare = 0 sau 1" << std::endl << "4 sau 5 - reset = 0 sau 1" << std::endl << std::endl;
    while(valid_option)
    {
        getline(std::cin, x);
        if(x.length() == 1)
        {
            int a = x.front() - '0';
            switch(a)
            {
                case 2:
                    functionare = 0;
                    std::cout << "Registru in inel." << std::endl;
                    break;
            
                case 3:
                    functionare = 1;
                    std::cout << "Registru in paralel" << std::endl;
                    break;
                case 4:
                    std::cout << "Reset setat pe 0" << std::endl;
                    reset = 0;
                    break;
                case 5:
                    reset = 1;
                    std::cout << "Resetat valori registru." << std::endl;
                    resetReg();
                    break;
                default:
                    valid_option = false;
                    std::cout << "Invalid option. Program ended by user." << std::endl;
                    break;
            }       
        }
        else
        {
            for(int i = 0; i < x.length(); i ++)
            {
                if(x.at(i) != '1' && x.at(i) != '0')
                {
                    valid_option = false;
                    std::cout << "Invalid option. Program ended by user." << std::endl;
                    break;
                }
            }
            if(valid_option && !x.empty())
            {
                changeMemory(x);                
            }

        }

    }
    return 0;
}