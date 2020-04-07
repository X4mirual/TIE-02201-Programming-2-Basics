#include "university.hh"

University::University():running_number_(111111)
{
}

University::~University()
{
    for ( auto course : courses_ ){
        delete course.second;
    }

    for ( auto account : accounts_ ){
        delete account.second;
    }

}

void University::print_courses(Params)
{
    for ( auto course : courses_ ){
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }

    courses_.at(params.at(0))->print_long_info();
}

void University::add_account(Params params)
{
    for( std::map<int, Account*>::iterator iter = accounts_.begin(); iter != accounts_.end(); ++iter ) {
        if( iter->second->get_email() == params.at(1) ) {
            std::cout << ALREADY_EXISTS << std::endl;
            return;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(params.at(0), params.at(1), account_number);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ ){
        account.second->print();
    }
}

void University::print_account_info(Params params)
{
    std::map<int, Account*>::iterator iter = accounts_.find(std::stoi(params.at(0)));
    if ( iter == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    iter->second->print();
}

void University::add_staff_to_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    if ( accounts_.find(std::stoi(params.at(1))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }

    courses_.at(params.at(0))->add_staff(accounts_.at(std::stoi(params.at(1))));
}

void University::add_course(Params params) // TIE-02200 "Ohjelmointi 2" - kurssitunnus kurssinimi
{
    if ( courses_.find(params.at(0)) != courses_.end() ){
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    } else {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(params.at(0), params.at(1));
    courses_.insert({n_course->get_code(), n_course});
}



//Itse tehdyt alkavat


// Virhetapaukset: jos instanssi ON jo olemassa? DONE
// Virhetapaukset: jos opintojaksoa ei ole olemassa? DONE
void University::add_instance(Params params) { // TIE-02200 K2020
    if(not is_valid_course(params.at(0))) {
        return;
    }
    Course* the_course = courses_.at(params.at(0)); //pointteri haluttuun kurssiin
    if(the_course->has_instance(params.at(1)))
    {
        std::cout << INSTANCE_EXISTS << std::endl;
        return;
    }
    Instance* n_instance = new Instance(params.at(1), utils::today);
    the_course->new_instance(n_instance);
}

//Virhetapaukset: if attendee already attending DONE
//Virhetapaukset: opiskelija ei löydy (opiskelijatunnuksellaan) DONE
//Virhetapaukset: kurssi ei löydy DONE
//Virhetapaukset: toteutuskerta ei löydy DONE
//Virhetapaukset: Today is after instance starting date DONE
void University::sign_up_on_course(Params params) { // TIE-02200 K2020 111111
    if(not is_valid_parameters3(params)) {
        return;
    }
    Course* the_course = courses_.at(params.at(0));
    Instance* the_instance = the_course->get_instance(params.at(1));
    if(not the_instance->can_be_singned_up_on(utils::today)) {
        return;
    }
    Account* the_attendee = accounts_.at(stoi(params.at(2)));

    // Checking if student is attending instance is done on instance side,
    // because otherwise student could enroll and complete same instance
    // multiple times
    if(the_instance->is_attending(the_attendee)) {
        return;
    }
    the_instance->add_attendee(the_attendee);

    // also prints confirmation of sign up
    the_attendee->add_instance(the_instance);
}

// Virhetapaukset: kurssi, toteutus, käyttäjä eivät ole olemassa DONE
void University::complete_course(Params params) { // TIE-02200 S2019 111112
    if(not is_valid_parameters3(params)) {
        return;
    }
    Course* the_course = courses_.at(params.at(0));
    Instance* the_instance = the_course->get_instance(params.at(1));
    int student_id = stoi(params.at(2));

    Account* the_attendee = accounts_.at(student_id);
    if(the_attendee->is_not_attending(the_instance)) {
        return;
    }

    //Complete course in Account
    the_attendee->complete_course(the_instance, the_course);
}

// Virhetapaukset: kurssi ei ole olemassa DONE
void University::print_signups(Params params) { // TIE-02200
    if(not is_valid_course(params.at(0))) {
        return;
    }
    Course* the_course = courses_.at(params.at(0));
    the_course->print_signups();
}

// Virhetapaukset: käyttäjä ei ole olemassa DONE
void University::print_study_state(Params params) // 111113
{
    if(not is_valid_account(stoi(params.at(0)))) {
        return;
    }
    Account* attendee = accounts_.at(stoi(params.at(0)));
    std::map<std::string, Course*>::iterator course_itr = courses_.begin();

    std::cout << "Current:" << std::endl;
    while(course_itr != courses_.end()) {
        course_itr->second->print_attended(attendee);
        ++course_itr;
    }

    std::cout << "Completed:" << std::endl;
    attendee->print_completed();
}

// Virhetapaukset: käyttäjä ei ole olemassa DONE
void University::print_completed(Params params) // 111113
{
    if(not is_valid_account(stoi(params.at(0)))) {
        return;
    }
    Account* the_student = accounts_.at(stoi(params.at(0)));
    the_student->print_completed();
}

//Itse tehdyt loppuvat (+4)

void University::set_date(Params params)
{
    utils::today = Date(std::stoi(params.at(0)), std::stoi(params.at(1)), std::stoi(params.at(2)));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_date(Params params)
{
    utils::today.advance_by(std::stoi(params.at(0)));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_by_period(Params)
{
    utils::today.advance_by_period_length();
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

// Omatekoiset
bool University::is_valid_parameters3(Params params) // TIE-02200 S2019 111112
{
    if(not is_valid_course(params.at(0))) {
        return false;
    }
    else if(not is_valid_instance(params.at(1), params.at(0))) {
        return false;
    }
    else if(not is_valid_account(stoi(params.at(2)))) {
        return false;
    }
    return true;
}

bool University::is_valid_account(int student_id) //priority 1
{
    if(accounts_.find(student_id) == accounts_.end()) {
        std::cout << CANT_FIND << student_id << std::endl;
        return false;
    }
    return true;
}

bool University::is_valid_instance(std::string instance_name, std::string course_name) //priority 3
{
    Course* the_course = courses_.at(course_name);
    if(not the_course->has_instance(instance_name)) {
        std::cout << CANT_FIND << instance_name << std::endl;
        return false;
    }
    return true;
}

bool University::is_valid_course(std::string course_name) //priority 2
{
    if(courses_.find(course_name) == courses_.end()) {
        std::cout << CANT_FIND << course_name << std::endl;
        return false;
    }
    return true;
}
