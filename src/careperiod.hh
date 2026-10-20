/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2024
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>

class CarePeriod
{
public:
    /**
      * @brief CarePeriod
      * @param start date given as a string (ddmmyyyy)
      * @param patient whose care period will be created
      */
    CarePeriod(const std::string& start, Person* patient);

    /**
      * @brief CarePeriod
      * @param start date given as a Date object
      * @param patient whose care period will be created
      */
    CarePeriod(const Date& start, Person* patient);

    /**
      * @brief destructor
      */
    ~CarePeriod();

    //add staff to care period
    void add_staff(const std::string& staff_id, Person* staff);

    void set_end_date(const Date& end_date);

    //checks if care period is active or not
    bool is_active() const;

    //prints care periods info
    void print_period_info() const;

    //finds the patients id
    std::string get_patient_id() const{
        return patient_->get_id();
    }

    //has staff member worked
    bool has_staff_member(const std::string& staff_id) const{
        return staff_.find(staff_id) != staff_.end();
    }

    //start date for care period
    Date get_start() const { return start_; }

    //end date for care period
    Date get_end() const { return end_; }

    //print patients staff
    void print_assigned_staff() const;


private:
    Person* patient_;
    Date start_;
    Date end_;

    std::map<std::string, Person*> staff_;

};

#endif // CAREPERIOD_HH
