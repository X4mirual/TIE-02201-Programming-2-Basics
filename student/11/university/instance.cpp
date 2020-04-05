#include "instance.hh" // kaikki omia lisäyksiä
#include "course.hh"
#include <iostream>

using namespace std;

Instance::Instance(std::string toteutusaika):toteutusaika_(utils::today)
{
}

bool Instance::is_named(std::string name) {
    if(name == toteutusaika_) {
        return true;
    }
    else {
    return false;
    }
}

void Instance::print() {
    cout << toteutusaika_ << endl;

}
