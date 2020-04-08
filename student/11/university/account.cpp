#include "account.hh"

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

Account::~Account()
{
    for(auto instance : current_)
    {
        delete instance;
    }
    for(auto course : completed_)
    {
        delete course;
    }
}


void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email()
{
    return email_;
}

void Account::add_instance(Instance* instance)
{
    current_.push_back(instance);
    std::cout << SIGNED_UP << std::endl;
}

void Account::complete_course(Instance* instance, Course* course)
{
    completed_.push_back(course);
    auto instance_index = find(current_.begin(), current_.end(), instance);
    current_.erase(instance_index);
    std::cout << COMPLETED << std::endl;
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

bool Account::is_attending(Instance* the_instance, bool print_error)
{
    for(auto instance : current_) {
        if(instance == the_instance) {
            return true;
        }
    }
    // if the_instance not in current_
    if(print_error == true) {
        std::cout << NO_SIGNUPS << std::endl;
    }
    return false;
}








