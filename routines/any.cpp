#include <iostream>
#include <exception>
#include <any>

using namespace std;

void do_any() {
    cout << "\n--------- do_any -----------\n";
    string str = "one hundred";
    any a;
    a = 100;
    a = str;
    cout << "a.has_value: " << a.has_value() << endl;
    try 
    {
        cout << "\tANY CAST STRING: " << any_cast<string>(a) << '\n'; 
        a = 200;
        cout << "\tANY CAST INT: " << any_cast<int>(a) << '\n'; 
    }
    catch(...) 
    {
        std::cout << "Caught one" << '\n';
    }

    cout << "done\n\n";
    // cout << "x = " << x.has_value() << endl;
    // cout << any_cast<double>x << endl;
    // cout << any_cast<int32_t>x << endl;

}
