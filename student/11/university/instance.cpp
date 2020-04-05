#include "instance.hh" // kaikki omia lisäyksiä
#include "course.hh"
#include <iostream>

using namespace std;

Instance::Instance(std::string toteutusaika):
    toteutusaika_(toteutusaika)
{
    //starting_date_ = utils::today;
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
    cout << "Starting date: ";
    utils::today.print();
    cout << endl;
    cout << "Amount of students: " << attendees_.size() << endl;
}

void Instance::print_students() {
    for(auto attendee : attendees_) {
        attendee->print();
    }
}

void Instance::add_attendee(string id) {

}
