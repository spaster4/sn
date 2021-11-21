#include <iostream>
#include <vector>
#include <list>
#include <c17.h> 
#include <c17Config.h>
// #include <GLFW/glfw3.h>
using namespace std;


void doList() {
    vector<int>vi({1,2,3,4,5});
    list<int>il(5, 20);
    for( auto x : il) { cout << x << ' '; }
    cout << endl;    
    list<int>il1{9,8,6,8};
    for( auto x : il1) { cout << x << ' '; }
    cout << endl;    
    list<int>il2(vi.begin(), vi.end());
    for( auto x : il2) { cout << x << ' '; }
    cout << endl;    
    return;
}

int main(int argc, char *argv[]) {
    cout << argv[0] << " Version " << c17_VERSION_MAJOR << '.' << c17_VERSION_MINOR << endl;
    doOption();
    // doList();
}



