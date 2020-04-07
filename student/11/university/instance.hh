/* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single instance.
 *
 * Note: Students should make changes to this class, and add their info and
 * specifics of the class to this comment.
 * */
#ifndef INSTANCE_HH
#define INSTANCE_HH

#include "account.hh"
#include "date.hh"
#include "course.hh" // oma lisäys
#include "date.hh" // oma lisäys
#include "utils.hh" // oma lisäys
#include <map> // oma lisäys
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
    Instance(std::string instance_code, Date starting_date);

    /** TO DO
     * @brief
     * @param params:
     *
     */
    bool is_named(std::string name);

    /** TO DO
     * @brief
     * @param params:
     *
     */
    void print();

    /** TO DO
     * @brief
     * @param params:
     *
     */
    void print_students();

    /** TO DO
     * @brief
     * @param params:
     *
     */
    void add_attendee(Account* attendee);

    /** TO DO
     * @brief
     * @param params:
     *
     */
    void remove_attendee(Account* attendee);

    /** TO DO
     * @brief
     * @param params:
     *
     */
    bool is_attending(Account* account);


    std::string get_name();


    bool can_be_singned_up_on(Date Uni_today);


private:
    std::string instance_code_;
    Date starting_date_;
    std::vector<Account*> attendees_;

};

#endif // INSTANCE_HH
