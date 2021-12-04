#include <iostream>
#include <map>
#include <tuple>
#include <cstdio>
#include <string>

using namespace std;

map<string, tuple<int,int,int>>student;

struct A{
    string s;
    A() { cout << "A()\n";}
    A(string t): s(t) { cout << "A(" << t << ")\n"; }
};

struct B: virtual public A{
    B(): A("BBB"){ cout << "B()\n";}
};
struct C: virtual public A { };
struct D: public B, public C { };
struct E: public C, public B { };
struct F: public B {  };

void list_students(map<string, tuple<int,int,int>>&student) {
    for(auto x : student) {
        tuple<int,int,int>t = x.second;
        cout << x.first  << endl;
        cout << "   scores: " << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;
    }

}

void changeScores(string name, int x1, int x2, int x3) {
    if(auto it = student.find(name); it != student.end() ) {
        student[name] = make_tuple(x1,x2,x3);
    }
    else cout << "student not found\n";

}

void deleteStudent(string name) {
    if(auto it = student.find(name); it != student.end() ) {
        student.erase(name);
    }
}

void do_map() {
    /*
    A a1;
    A a2("a2");
    cout << "-------B------\n";
    B b;
    cout << "-------C------\n";
    C c;
    cout << "-------D------\n";
    D d;
    cout << "-------E------\n";
    E e;
    cout << "-------F------\n";
    F f;
    printf("D \"%s\"\n",d.s.c_str());
    printf("E \"%s\"\n",e.s.c_str());
    printf("F \"%s\"\n",f.s.c_str());
    printf("B \"%s\"\n",b.s.c_str());
    cout << "B " << '"' << b.s << '"' << endl;
*/

    student.insert(make_pair<string, tuple<int,int,int>>("Bob", make_tuple(1,2,3)));
    student.insert(make_pair<string, tuple<int,int,int>>("Mary", make_tuple(4,4,4)));
    student.insert(make_pair<string, tuple<int,int,int>>("Mike", make_tuple(3,4,5)));
    changeScores("Mike", 5,5,5);
    list_students(student);
    student.erase("Mike");
    student.insert(make_pair<string, tuple<int,int,int>>("Alma", make_tuple(3,4,5)));
    for(auto it = student.rbegin(); it != student.rend(); it++) {
        cout << it->first << " ";
    }
    cout << endl;
    return;    
}