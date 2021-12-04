#include <iostream>
#include <thread>

using namespace std;

void thread_function()
{
    for(int i = 0; i < 100; i++)
        std::cout<<"thread function Executing"<<std::endl;
}
 
void thread_function2()
{
    for(int i = 0; i < 10; i++)
        std::cout<<"thread function2 Executing"<<std::endl;
}

void do_threads()  
{
    std::thread threadObj(thread_function);
    for(int i = 0; i < 100; i++)
        std::cout<<"Display From MainThread"<<std::endl;
    threadObj.join();    
    [](){ thread threadObj2(thread_function2); threadObj2.join(); }();
    std::cout<<"Exit of Main function"<<std::endl;

    return;
}
