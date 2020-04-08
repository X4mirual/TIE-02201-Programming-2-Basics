/* Class: Account
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Defines a student or a staff account in the university system. Keeps track
 * of current and completed studies and person information.
 *
 * Program author
 * Name: Lauri Hiltunen
 * Student number: 274422
 * UserID: hiltunen
 * E-Mail: lauri.hiltunen@tuni.fi
 * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH
#include "instance.hh"
#include "course.hh"
#include "utils.hh"
#include <string>
#include <vector>
#include <iostream>

// Foreward declarations
class Instance;
class Course;

const std::string NO_SIGNUPS = "No signups found on this instance.";
const std::string SIGNED_UP = "Signed up on the course instance.";
const std::string COMPLETED = "Course completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "frontname lastname"
     * @param email
     * @param account_number
     */
    Account(std::string full_name, std::string email, int account_number);

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief print
     * Print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email();

    /**
     * @brief add_instance
     * @param instance
     * Adds instance to accounts current studies
     */
    void add_instance(Instance* instance);

    /**
     * @brief complete_course
     * @param instance
     * @param course
     * Remove instance from current studies and add course to completed
     */
    void complete_course(Instance* instance, Course* course);

    /**
     * @brief print_completed
     * Print completed courses
     */
    void print_completed();

    /**
     * @brief is_attending
     * @param the_instance
     * @param print_error will message be printed if not attending
     * @return true if account attending the_instance, false oterwise
     */
    bool is_attending(Instance* the_instance, bool print_error = false);


private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;
    std::vector<Instance*> current_;
    std::vector<Course*> completed_;
};

#endif // ACCOUNT_HH
