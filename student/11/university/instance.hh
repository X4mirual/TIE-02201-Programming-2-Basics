/* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single instance with a name, starting date and
 * attendees.
 *
 * Program author
 * Name: Lauri Hiltunen
 * Student number: 274422
 * UserID: hiltunen
 * E-Mail: lauri.hiltunen@tuni.fi
 * */
#ifndef INSTANCE_HH
#define INSTANCE_HH
#include "account.hh"
#include "date.hh"
#include "course.hh"
#include "date.hh"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using Params = const std::vector<std::string>&;

// Forward-declaration of Course, so that instance can point to the course it belongs to.
class Course;

const std::string ALREADY_REGISTERED = "Error: Student has already registered on this course.";
const std::string LATE = "Error: Can't sign up on instance after the starting date.";
const std::string INDENT = "    ";

class Instance
{
public:

    /**
     * @brief Instance constructor
     * @param instance_code
     * @param starting_date
     */
    Instance(std::string instance_code, Date starting_date);

    /**
     * @brief is_named
     * @param name
     * @return true if Instance code is name, false otherwise
     */
    bool is_named(std::string name);

    /**
     * @brief print
     * Print instance info
     */
    void print();

    /**
     * @brief print_students
     * Print students attending this instance
     */
    void print_students();

    /**
     * @brief add_attendee
     * @param attendee
     * Add pointer to attendee in attendees_
     */
    void add_attendee(Account* attendee);

    /**
     * @brief remove_attendee
     * @param attendee
     * Remove pointer to attendee from attendees_
     */
    void remove_attendee(Account* attendee);

    /**
     * @brief is_attending
     * @param attendee
     * @return true if attendee is attending instance, false otherwise
     */
    bool is_attending(Account* attendee);

    /**
     * @brief get_name
     * @return name of instance
     */
    std::string get_name();

    /**
     * @brief can_be_singned_up_on
     * @param Uni_today
     * @return true if instance starting date is today(in University),
     * otherwise false
     * Print error if it's too late to sign up on instance
     */
    bool can_be_singned_up_on(Date Uni_today);

private:
    std::string instance_code_;
    Date starting_date_;
    std::vector<Account*> attendees_;
};

#endif // INSTANCE_HH
