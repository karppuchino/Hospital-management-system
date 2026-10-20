#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>
#include <algorithm>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Deallocating staff
    for( std::map<std::string, Person*>::iterator
             iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Remember to deallocate patients also
}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
        patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
        patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::enter(Params params)
{
    std::string patient_id = params.at(0);


    //patient already has a care period -> error
    if ( current_patients_.find(patient_id) != current_patients_.end())
    {
        //error message, cant find patient
        std::cout << ALREADY_EXISTS << patient_id << std::endl;
        return;
    }

    //checks if patient has a previous care period in hospital
    // if not, adds patient
    if ( all_patients_.find(patient_id) == all_patients_.end())
    {
        all_patients_[patient_id] = new Person(patient_id);
    }

    //new/old patient same functions
    // adds to current patients and creates new care period
    Person* new_patient =  all_patients_.find(patient_id)->second;
    current_patients_[patient_id] = new_patient;

    CarePeriod* care_period = new CarePeriod(utils::today, new_patient);
    care_periods_.push_back(care_period);

    //print message
    std::cout << PATIENT_ENTERED << std::endl;

}

void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);

    //is patient currently in hospital
    auto patient_iter = current_patients_.find(patient_id);

    if (patient_iter == current_patients_.end())
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    //patients care period at the moment
    CarePeriod* current_care_period = care_periods_.back();

    //remove patient from current patients
    current_patients_.erase(patient_id);

    //end care period for patient
    current_care_period->set_end_date(utils::today);

    std::cout << PATIENT_LEFT << std::endl;
}

void Hospital::assign_staff(Params params)
{
    std::string staff_id = params.at(0);
    std::string patient_id = params.at(1);

    // check that patient and staff exist
    if (staff_.find(staff_id) == staff_.end()) {
        std::cout << CANT_FIND << staff_id << std::endl;
        return;
    }
    if (current_patients_.find(patient_id) == current_patients_.end()) {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    // find patients current care period
    CarePeriod* current_care_period = nullptr;
    for (auto& care_period : care_periods_) {
        if (care_period->get_patient_id() == patient_id &&
            care_period->is_active()) {
            current_care_period = care_period;
            break;
        }
    }

    // if no care period, create new and add staff
    if (!current_care_period) {
        Person* patient = current_patients_[patient_id];
        current_care_period = new CarePeriod(utils::today, patient);
        care_periods_.push_back(current_care_period);
    }

    // add staff to care period
    current_care_period->add_staff(staff_id, staff_[staff_id]);

    std::cout << STAFF_ASSIGNED << patient_id << std::endl;
}

void Hospital::print_patient_info(Params params)
{
    std::string patient_id = params.at(0);

    // check that the patient exists
    auto patient_iter = all_patients_.find(patient_id);
    if (patient_iter == all_patients_.end()) {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    bool has_care_periods = false;

    // find all care periods for patient
    for (auto& care_period : care_periods_) {
        if (care_period->get_patient_id() == patient_id) {
            // print care periods info
            std::cout << "* Care period: ";
            care_period->print_period_info();
            has_care_periods = true;
        }
    }

    if (has_care_periods) {
        // print medicines given to patient
        std::cout << "* Medicines:";
        patient_iter->second->print_medicines(" - ");
    }
}

void Hospital::print_care_periods(Params params)
{
    std::string staff_id = params.at(0);

    // check that staff exists
    if (staff_.find(staff_id) == staff_.end()) {
        std::cout << CANT_FIND << staff_id << std::endl;
        return;
    }

    bool found_periods = false;

    // vector to store care periods
    std::vector<CarePeriod*> sorted_care_periods;

    // find care periods for the staff member
    for (auto& care_period : care_periods_) {
        if (care_period->has_staff_member(staff_id) ||
            care_period->is_active()) {
            sorted_care_periods.push_back(care_period);
            found_periods = true;
        }
    }

    // sort care periods based on start date
    std::sort(sorted_care_periods.begin(), sorted_care_periods.end(),
              [](CarePeriod* a, CarePeriod* b) {
                  return a->get_start() < b->get_start();
              });

    // print sorted care periods
    for (auto& care_period : sorted_care_periods) {
        care_period->get_start().print();
        std::cout << " - ";
        if (!care_period->is_active()) {
            care_period->get_end().print();
        }
        std::cout << std::endl;
        std::cout << " * Patient: " << care_period->get_patient_id()
                  << std::endl;
    }

    // no care periods for staff member
    if (!found_periods) {
        std::cout << "None" << std::endl;
    }
}

void Hospital::print_all_medicines(Params)
{
    //map to store meidicines(key) and the patients(value)
    std::map<std::string, std::set<std::string>> medicines;

    //go through all patients
    for (const auto& patient_pair : all_patients_){
        const Person* patient = patient_pair.second;

        //find corresponding medicines for patient
        std::vector<std::string> patient_medicines = patient->get_medicines();

        //add meidicne to map
        for (const auto& medicine : patient_medicines){
            medicines[medicine].insert(patient->get_id());
        }
    }

    //check patients medicines
    if(medicines.empty()){
        std::cout << "None" << std::endl;
    }

    //print meidicine and patient
    for (auto it = medicines.begin(); it != medicines.end(); ++it) {
        std::cout << it->first << " prescribed for " << std::endl;
        const auto& patients = it->second;
        for (auto patient_it = patients.begin(); patient_it !=
                                                 patients.end(); ++patient_it) {
            std::cout << "* " << *patient_it << std::endl;
        }
    }
}

void Hospital::print_all_patients(Params)
{
    // check if there are any patients
    if (all_patients_.empty()) {
        std::cout << "None" << std::endl;
        return;
    }

    // vector to store patient ids for sorting
    std::vector<std::string> patient_ids;
    for (const auto& patient_pair : all_patients_) {
        patient_ids.push_back(patient_pair.first);
    }

    // sort patient ids alphabetically
    std::sort(patient_ids.begin(), patient_ids.end());

    // print patient information
    for (const auto& patient_id : patient_ids) {
        std::cout << patient_id << std::endl;
        print_patient_info({patient_id});
    }
}

void Hospital::print_current_patients(Params)
{
    // check current patients exist
    if (current_patients_.empty()) {
        std::cout << "None" << std::endl;
        return;
    }

    // go through all current patients
    for (const auto& patient_pair : current_patients_) {
        std::string patient_name = patient_pair.first;

        // print patient name
        std::cout << patient_name << std::endl;

        // print patients info
        print_patient_info({patient_name});
    }
}
