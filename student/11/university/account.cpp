#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"

Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    account_number_(account_number)
{
    std::vector<std::string> name = utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();
}

// TO DO: Destructor?


void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email() {
    return email_;
}

void Account::add_instance(Instance* instance) {
    current_.push_back(instance);
    std::cout << SIGNED_UP << std::endl;
}

void Account::print_completed()
{
    int tot_credits = 0;
    for(Course* course : completed_) {
        course->print_info(true);
        tot_credits += course->get_credits();
    }
    std::cout << "Total credits: " << tot_credits << std::endl;
}

bool Account::is_not_attending(Instance* the_instance)
{
    if(find(current_.begin(), current_.end(), the_instance) == current_.end()) {
        std::cout << NO_SIGNUPS << std::endl;
        return true;
    }
    return false;
}

bool Account::is_attending(Instance* the_instance)
{
    for(auto instance : current_) {
        if(instance == the_instance) {
            return true;
        }
    }
    return false;
}

void Account::complete_course(Instance* instance, Course* course) {
    completed_.push_back(course);
    auto instance_index = find(current_.begin(), current_.end(), instance);
    current_.erase(instance_index);
    std::cout << COMPLETED << std::endl;
}









