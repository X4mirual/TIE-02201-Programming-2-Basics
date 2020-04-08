#include "instance.hh"

using namespace std;

Instance::Instance(std::string instance_code, Date starting_date):
    instance_code_(instance_code),
    starting_date_(starting_date)
{
}

Instance::~Instance()
{
    for(auto account : attendees_) {
        delete account;
    }
}

bool Instance::is_named(std::string name) {
    if(name == instance_code_) {
        return true;
    }
    else {
    return false;
    }
}

void Instance::print() {
    cout << instance_code_ << endl;
    cout << INDENT << "Starting date: ";
    starting_date_.print();
    cout << endl;
    cout << INDENT << "Amount of students: " << attendees_.size() << endl;
}

void Instance::print_students() {
    for(auto attendee : attendees_) {
        cout << INDENT;
        attendee->print();
    }
}

void Instance::add_attendee(Account* attendee) {
    attendees_.push_back(attendee);
}

void Instance::remove_attendee(Account* attendee) {
    attendees_.erase(find(attendees_.begin(), attendees_.end(), attendee));
}

bool Instance::is_attending(Account* attendee)
{
    if(find(attendees_.begin(), attendees_.end(), attendee) != attendees_.end()) {
        std::cout << ALREADY_REGISTERED << std::endl;
        return true;
    }
    return false;
}

std::string Instance::get_name() {
    return instance_code_;
}

bool Instance::can_be_singned_up_on(Date Uni_today) {
    if(Uni_today == starting_date_) {
        return true;
    }
    cout << LATE << endl;
    return false;
}




