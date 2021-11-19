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

std::optional<std::string> create(bool b) {
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

void doOption() {
    cout<< create0(false).value_or("empty") << endl; // == "empty"
    cout << create0(true).value() << endl; // == "Godzilla"
    // optional-returning factory functions are usable as conditions of while and if
    if (auto str = create0(true)) { cout << "true true true\n"; }

    cout << "create(false) returned " << create(false).value_or("empty") << '\n';
 
    // optional-returning factory functions are usable as conditions of while and if
    if (auto str = create2(true)) {
        cout << "create2(true) returned " << *str << '\n';
    }
 
    if (auto str = create_ref(false)) {
        // using get() to access the reference_wrapper's value
        cout << "create_ref(true) returned " << str->get() << '\n';
        str->get() = "Mothra";
        cout << "modifying it changed it to " << str->get() << '\n';
    }

    auto str2 = create_ref(false);
    cout << "has value? " <<  str2.has_value() << endl;
    // str2->get() = "Mothra";
    return;
}