#include <iostream>
#include <optional>

using namespace std;

optional<std::string> create0(bool b) {
  if (b) {
    return "Godzilla";
  } else {
    return {};
  }
}

std::optional<std::string> create1(bool b) {
    if (b)
        return "Godzilla";
    return {};
}
 
// std::nullopt can be used to create any (empty) std::optional
auto create2(bool b) {
    return b ? std::optional<std::string>{"Godzilla"} : std::nullopt;
}
 
// std::reference_wrapper may be used to return a reference
auto create_ref(bool b) {
    static std::string value = "Godzilla";
    return b ? std::optional<std::reference_wrapper<std::string>>{value}
             : std::nullopt;
}

auto iref(int x)
{
    static int val = x;
    return optional<reference_wrapper<int>>(val);
}

auto createInt(bool b) {
    if(b) return optional<int>(1);
    return optional<int>(nullopt);
}

void doOption() {
    cout << "createInt(true): " << createInt(true).value() << endl;
    cout << "createInt(false): " << createInt(false).value_or(100) << endl;
    if(!createInt(false)) cout << "MADE 1\n";

    cout<< create0(false).value_or("empty") << endl; // == "empty"
    cout << create0(true).value() << endl; // == "Godzilla"
    // optional-returning factory functions are usable as conditions of while and if
    if (auto str = create0(true)) { cout << "true true true\n"; }

    cout << "create1(false) returned " << create1(false).value_or("empty") << '\n';
 
    // optional-returning factory functions are usable as conditions of while and if
    if (auto str = create2(true)) {
        cout << "create2(true) returned " << *str << '\n';
    }
 
    if (auto str = create_ref(true)) {
        // using get() to access the reference_wrapper's value
        cout << "create_ref(true) returned " << str->get() << '\n';
        str->get() = "Mothra";
        cout << "modifying it changed it to " << str->get() << '\n';
    }

    auto str2 = create_ref(true);
    cout << "has value? " <<  str2.has_value() << endl;
    str2->get() = "Mothra";
    cout << str2->get() << endl;
    return;
}