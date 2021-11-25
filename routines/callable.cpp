#include <iostream>
#include <tuple>

using namespace std;

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
    return;
}


