#include <iostream>
#include <tuple>
#include <list>
#include <vector>
#include <map>
#include <initializer_list>
#include <type_traits>

using namespace std;

class BB {
public:
    BB(int x = 100) { cout << x << endl;} 
};

auto halfAgain = [](int x) { return (x + x/2); };
auto tripleAdd = [](int x, int y, int z) { return (x+y+z); };


void overloaded( int const &arg ) { std::cout << "by lvalue\n"; }
void overloaded( int && arg ) { std::cout << "by rvalue\n"; }
// void overloaded( const int arg ) { std::cout << "by anything\n"; }
 
template< typename t >
/* "t &&" with "t" being template param is special, and  adjusts "t" to be
   (for example) "int &" or non-ref "int" so std::forward knows what to do. */
void forwarding( t && arg ) {
    std::cout << "via std::forward: ";
    overloaded( std::forward< t >( arg ) );
    std::cout << "via std::move: ";
    overloaded( std::move( arg ) ); // conceptually this would invalidate arg
    std::cout << "by simple passing: ";
    overloaded( arg );
}

template <class T>
void func2( std::initializer_list<T> list )
{
    for( auto elem : list )
    {
        cout << elem << endl ;
    }
}

template <class T>
list<T> func(initializer_list<T> list )
{
    return list;
}



void do_callable() {
    int w = 5;
    int&& x=5;
    int& y=x;
    int z = x;
    overloaded(forward<int>(w));   // rvalue
    overloaded(forward<int&>(w));  // lvalue
    overloaded(w);                 // lvalue
    overloaded(move(w));           // rvalue -- w no longer valid
    cout << "------5-----\n";
    overloaded(forward<int>(5));   // rvalue
    // overloaded(forward<int&>(5));  // cant pass this as an lvalue
    overloaded(5);                 // rvalue
    overloaded(move(5));           // rvalue 
    cout << "------x-----\n";
    overloaded(forward<int>(x));   // rvalue
    overloaded(forward<int&>(x));  // lvalue
    overloaded(x);                 // lvalue
    overloaded(move(x));           // rvalue -- x no longer valid
    cout << "------y-----\n";
    overloaded(forward<int>(y));   // rvalue
    overloaded(forward<int&>(y));  // lvalue
    overloaded(y);                 // lvalue
    overloaded(move(y));           // rvalue -- y no longer valid
    cout << "------w-----\n";
    overloaded(forward<int>(z));   // rvalue
    overloaded(forward<int&>(z));  // lvalue
    overloaded(z);                 // lvalue
    overloaded(move(z));           // rvalue -- z no longer valid

    cout << "\n-----------\n";
    auto tup = make_tuple(30);
    auto tup2 = make_tuple(10,20,30);
    cout << "get<0>(tup2) = " << get<0>(tup2) << "  << get<1>(tup2) = " << get<1>(tup2) << endl;
    cout << apply(halfAgain, tup) << endl;
    cout << apply(tripleAdd, tup2) << endl;
    // forwarding(5);
    // func(5,6,7);
    string str1 = "abc";
    string str2 = "def";
    func2( {10, 20, 30, 40 }) ;
    auto il = func<int>( {10, 20, 30, 40 }) ;
    for ( auto x : il) { cout << x << endl; }
    func2({str1, str2});
    auto sl = func({str1, str2});
    for ( auto x : sl) { cout << x << endl; }
    list<char> cl = initializer_list<char>{'a','b','c', 'd'};
    vector<char> cv = initializer_list<char>{'a','b','c', 'd'};
    cout << "cv[2]: " << cv[2] << endl;
    for ( auto x : cl) { cout << x << endl; }
    list<BB> classList = initializer_list<BB>{BB(1), BB(2), BB(3), BB(4)};
    for(auto x : classList)  { cout << "WWWW" << endl; }
    map<string,string>fav_lang = {{"A", "B"},{"C","D"},{"E", "F"}};

    for (const auto & [ name, language ] : fav_lang) {   
        cout << name << ":" << language << endl;
    }


    for (const auto &c : cl) { cout << c; }; cout << endl;
    list<byte>bl = initializer_list<byte>{byte('a'), byte('b')};
    list<byte>bl2 = { byte('a'), byte('b'), byte('c')};
    for(auto i : bl) {cout << char(i); } ; cout << endl;
    for(auto i : bl2) {cout << char(i); } ; cout << endl;
    if(int u=5; u%2 == 0) { 
        cout << "true" << endl; 
    } 
    else { 
        cout << "false" << endl; 
    }
    return;
}


