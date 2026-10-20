#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::set_end_date(const Date &end_date)
{
    //sets end date
    end_ = end_date;
}

bool CarePeriod::is_active() const
{
    //checks wheter care period is active or not
    return end_.is_default();
}

void CarePeriod::print_period_info() const
{
    //prints care periods information (dates, staff)
    start_.print();
    std::cout << " - ";

    if (!is_active()) {
        end_.print();
    }
    std::cout << std::endl;

    std::cout << "  - Staff: ";

    if (staff_.empty()) {
        std::cout << "None" << std::endl;
    } else {
        for (const auto& [staff_id, staff_person] : staff_) {
            std::cout << staff_person->get_id() << " ";
        }
        std::cout << std::endl;
    }
}

void CarePeriod::add_staff(const std::string& staff_id, Person* staff)
{
    //check is staff already assigned
    if (staff_.find(staff_id) != staff_.end()) {
        return;
    }

    // add staff to patient
    staff_[staff_id] = staff;
}

void CarePeriod::print_assigned_staff() const
{
    if (staff_.empty()) {
        std::cout << "None" << std::endl;
    } else {
        for (const auto& [staff_id, staff_person] : staff_) {
            std::cout << staff_person->get_id();
        }

        std::cout << std::endl;
    }
}
