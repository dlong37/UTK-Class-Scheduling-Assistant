#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

#define MINS_PER_HOUR 60

class course {
    public:
        string abbrv;
        int num;
        string title;
        int hours;
        string attributes;
        string pre_req;
        string co_req;
        string lec_time;
        string lec_date;
        string lec_loc;
        string lab_time;
        string lab_date;
        string lab_loc;
        int priority = 0;

    // bool operator==(const course *mc) const {
    //     return ((this->abbrv == mc->abbrv) && (this->num == mc->num));
    // }
};

int user_hour = 0;
int user_min = 0;
int gap = 0;
int credit_hours = 0;
vector<course> scheduled_courses;
vector<course> perm_courses;

// Custom comparator for min-heap
struct CompareCourse {
    bool operator()(const course& c1, const course& c2) {
        return c1.priority > c2.priority;  // Min-heap: closer to 0 = higher priority
    }
};

priority_queue<course, vector<course>, CompareCourse> create_pq(vector<course> remaining_vector, vector<vector<int>> schedule) {
    priority_queue<course, vector<course>, CompareCourse> pq;
    for (int i = 0; i < (int)remaining_vector.size(); i++) {
        // calculate start time in minutes
        // only based on lecture days! I would love to do labs as well, but that would require deep structural changes
        string lec_days = remaining_vector[i].lec_date;
        // find the last minute that a course is scheduled for:
        int rows = schedule.size();
        int cols = schedule[0].size();
        int startx = 0;
        for (int j = 0; j < rows; ++j) {
            for (int k = 0; k < lec_days.size(); k++) {
                if (schedule[j][0] == 1 && lec_days[k] == 'M') {
                    startx = j;
                }
                if (schedule[j][1] == 1 && lec_days[k] == 'T') {
                    startx = j;
                }
                if (schedule[j][2] == 1 && lec_days[k] == 'W') {
                    startx = j;
                }
                if (schedule[j][3] == 1 && lec_days[k] == 'R') {
                    startx = j;
                }
                if (schedule[j][4] == 1 && lec_days[k] == 'F') {
                    startx = j;
                }
            }
        }
        // if nothing was scheduled for any time, make startx the global variable start time
        if (startx == 0) {
            startx = user_hour * MINS_PER_HOUR + user_min;
        }
        int course_hour = stoi(remaining_vector[i].lec_time.substr(0, 2));
        int course_min = stoi(remaining_vector[i].lec_time.substr(2, 2));
        int endx = course_hour * MINS_PER_HOUR + course_min;
        int duration = endx - startx;
        int priority = duration - gap;
        if (priority < 0) {
            priority *= -1;
        }
        remaining_vector[i].priority = priority;
        pq.push(remaining_vector[i]);
    }
    return pq;
};

void print_pq(priority_queue<course, vector<course>, CompareCourse> pq) {
    priority_queue<course, vector<course>, CompareCourse> print = pq;
    cout << "\nPriority Queue: " << endl;
    while (!print.empty()) {
        cout << print.top().abbrv << " " << print.top().num << " : " << print.top().title << " at " << print.top().lec_time << " (" << print.top().priority << ")" << endl;
        print.pop(); 
    }
    cout << endl;
};

void print_array( vector<vector<int>> arr) {
    // Get number of rows
    int rows = arr.size();
    // Check if the matrix is non-empty and get the number of columns from the first row
    if (rows > 0) {
        int cols = arr[0].size();

        // Nested for loops to print the matrix
        for (int i = 0; i < cols; ++i) {
            for (int j = 0; j < rows; ++j) {
                if (arr[j][i] == 1) { // Access elements by index
                    // print by day + min
                    if (i == 0) {
                        cout << "M at " << j << endl;
                    }
                    else if (i == 1) {
                        cout << "T at " << j << endl;
                    }
                    else if (i == 2) {
                        cout << "W at " << j << endl;
                    }
                    else if (i == 3) {
                        cout << "R at " << j << endl;
                    }
                    else if (i == 4) {
                        cout << "F at " << j << endl;
                    }
                }
            }
        }
    }
};

// pops a course off a PQ if it does not meet the pre-reqs, or leaves the course on the top of the PQ if it does meet the prs
bool check_pr(vector<string> taken_vector, priority_queue<course, vector<course>, CompareCourse> &pq) {
    // create OR vector to cross compare with taken vector.
    vector<string> or_vector;
    // check that course meets pre-reqs
    bool schedule = true;
    while (schedule) {
        int index = 0;
        // check for empty pq
        if (pq.size() == 0) {
            return false;
        }
        course scheduled_class = pq.top();
        string pre_req = scheduled_class.pre_req;
        string pr;

        // check for multiple pre-reqs
        for (int i = 0; i < (int)pre_req.size(); i++) {
            // hit an OR sign
            if (pre_req[i] == '|') { // add to OR vector only
                // just push
                pr = pre_req.substr(index, i-index);
                or_vector.push_back(pr);
                index = i+1;
            }
            // hit an AND sign
            if (pre_req[i] == '&') { // check OR vector + clear / break
                // push class onto the OR vector
                pr = pre_req.substr(index, i-index);
                or_vector.push_back(pr);
                // then check + clear
                for (int j = 0; j < (int)taken_vector.size(); j++) {
                    for (int k = 0; k < (int)or_vector.size(); k++) {
                        if (taken_vector[j] == or_vector[k]) {
                            or_vector.clear();
                            break;
                        }
                    }
                    if (or_vector.size() == 0) { break; }
                }
                // if we checked, but weren't able to match, this class is unabled to be scheduled
                if (or_vector.size() != 0) {
                    pq.pop();
                    break;
                }
                index = i+1;
            }
            // grabs last class
            if (i == (int)pre_req.size()-1) { // grab the last course / the only course if no other pre-reqs
                // push
                pr = pre_req.substr(index, pre_req.size() - index);
                or_vector.push_back(pr);
                // final check
                for (int j = 0; j < (int)taken_vector.size(); j++) {
                    for (int k = 0; k < (int)or_vector.size(); k++) {
                        if (taken_vector[j] == or_vector[k]) {
                            or_vector.clear();
                            break;
                        }
                    }
                    if (or_vector.size() == 0) { break; }
                }
                // if we checked, but weren't able to match, this class is unabled to be scheduled
                if (or_vector.size() != 0) {
                    pq.pop();
                    break;
                }
                else { // otherwise, we can schedule this class!
                    schedule = false;
                }
            }
        }
    }
    return true;
};

bool check_conflicts(vector<vector<int>> schedule, course course) {
    int lec_start_time = stoi(course.lec_time.substr(0, 2)) * MINS_PER_HOUR + stoi(course.lec_time.substr(2, 2));
        cout << "lec start time: " << lec_start_time << endl;
    int lec_end_time = stoi(course.lec_time.substr(5, 2)) * MINS_PER_HOUR + stoi(course.lec_time.substr(7, 2));
        cout << "lec end time: " << lec_end_time << endl;
    int lab_start_time = 0;
        cout << "lab start time: " << lab_start_time << endl;
    int lab_end_time = 0;
        cout << "lab start time: " << lab_end_time << endl;

    if (course.lab_time != "none") {
        lab_start_time = stoi(course.lab_time.substr(0, 2)) * MINS_PER_HOUR + stoi(course.lab_time.substr(2, 2));
        lab_end_time = stoi(course.lab_time.substr(5, 2)) * MINS_PER_HOUR + stoi(course.lab_time.substr(7, 2));
    }

    string lec_days = course.lec_date;
    string lab_days = course.lab_date;

    // check lecture first
    for (int i = 0; i < (int)lec_days.length(); i++) {
        for (int j = lec_start_time; j < lec_end_time; j++) {
            if (lec_days[i] == 'M') {
                if (schedule[j][0] == 1) {
                    return true;
                }
            }
            else if (lec_days[i] == 'T') {
                if (schedule[j][1] == 1) {
                    return true;
                }
            }
            else if (lec_days[i] == 'W') {
                if (schedule[j][2] == 1) {
                    return true;
                }
            }
            else if (lec_days[i] == 'R') {
                if (schedule[j][3] == 1) {
                    return true;
                }
            }
            else if (lec_days[i] == 'F') {
                if (schedule[j][4] == 1) {
                    return true;
                }
            }
        }
    }
    // then, check lab
    if (lab_days == "none") {
        return false;
    }
    else {
        for (int i = 0; i < (int)lab_days.length(); i++) {
            for (int j = lab_start_time; j < lab_end_time; j++) {
                if (lab_days[i] == 'M') {
                    if (schedule[j][0] == 1) {
                        return true;
                    }
                }
                else if (lab_days[i] == 'T') {
                    if (schedule[j][1] == 1) {
                        return true;
                    }
                }
                else if (lab_days[i] == 'W') {
                    if (schedule[j][2] == 1) {
                        return true;
                    }
                }
                else if (lab_days[i] == 'R') {
                    if (schedule[j][3] == 1) {
                        return true;
                    }
                }
                else if (lab_days[i] == 'F') {
                    if (schedule[j][4] == 1) {
                        return true;
                    }
                }
            }
        }
    }

    // if we got here, the time is free!
    return false;
};

void add_to_schedule(vector<vector<int>> &schedule, course course) {
    scheduled_courses.push_back(course);

    int lec_start_time = stoi(course.lec_time.substr(0, 2)) * MINS_PER_HOUR + stoi(course.lec_time.substr(2, 2));
    int lec_end_time = stoi(course.lec_time.substr(5, 2)) * MINS_PER_HOUR + stoi(course.lec_time.substr(7, 2));
    int lab_start_time = 0;
    int lab_end_time = 0;

    if (course.lab_time != "none") {
        lab_start_time = stoi(course.lab_time.substr(0, 2)) * MINS_PER_HOUR + stoi(course.lab_time.substr(2, 2));
        lab_end_time = stoi(course.lab_time.substr(5, 2)) * MINS_PER_HOUR + stoi(course.lab_time.substr(7, 2));
    }

    string lec_days = course.lec_date;
    string lab_days = course.lab_date;

    // add lecture first
    for (int i = 0; i < (int)lec_days.length(); i++) {
        for (int j = lec_start_time; j < lec_end_time; j++) {
            if (lec_days[i] == 'M') {
                schedule[j][0] = 1;
            }
            else if (lec_days[i] == 'T') {
                schedule[j][1] = 1;
            }
            else if (lec_days[i] == 'W') {
                schedule[j][2] = 1;
            }
            else if (lec_days[i] == 'R') {
                schedule[j][3] = 1;
            }
            else if (lec_days[i] == 'F') {
                schedule[j][4] = 1;
            }
        }
    }

    // then add lab
    if (lab_days == "none") {
        return;
    }
    for (int i = 0; i < (int)lab_days.length(); i++) {
        for (int j = lab_start_time; j < lab_end_time; j++) {
            if (lab_days[i] == 'M') {
                schedule[j][0] = 1;
            }
            else if (lab_days[i] == 'T') {
                schedule[j][1] = 1;
            }
            else if (lab_days[i] == 'W') {
                schedule[j][2] = 1;
            }
            else if (lab_days[i] == 'R') {
                schedule[j][3] = 1;
            }
            else if (lab_days[i] == 'F') {
                schedule[j][4] = 1;
            }
        }
    }
};

vector<course> create_remaining_vector(vector<course> course_vector, vector<string> string_vector) {
    vector<course> remaining_vector;
    for (int i = 0; i < (int)course_vector.size(); i++) {
        for (int j = 0; j < (int)string_vector.size(); j++) {
            string name = course_vector[i].abbrv + " " + to_string(course_vector[i].num);
            if (string_vector[j] == name) {
                remaining_vector.push_back(course_vector[i]);
            }
        }
    }
    return remaining_vector;
};

bool check_crs(course c, vector<vector<int>> &temp_schedule, vector<course> course_vector, vector<string> taken_vector) {
    vector<course> scheduled_cr;
    bool cr_scheduled = true;
    // check for co-reqs
    if (c.co_req != "none") {
        int index = 0;
        vector<string> or_vector;
        string cr;
        vector<vector<int>> cr_schedule = temp_schedule;

        // start filtering out the co-req courses
        for (int i = 0; i < (int)c.co_req.size(); i++) {

            // hit an OR sign: add to OR vector
            if (c.co_req[i] == '|') { // add to OR vector only
                cr = c.co_req.substr(index, i-index);
                or_vector.push_back(cr);
                index = i+1;
            }

            // hit an AND sign: check OR vector + attempt to schedule
            if (c.co_req[i] == '&') {
                // push class onto the OR vector
                cr = c.co_req.substr(index, i-index);
                or_vector.push_back(cr);

                /* attempt to schedule one of the co-reqs */
                bool taken;
                for (int j = 0; j < (int)taken_vector.size(); j++) {
                    for (int k = 0; k < (int)or_vector.size(); k++) {
                        if (taken_vector[j] == or_vector[k]) {
                            taken = true;
                            or_vector.clear();
                        }
                    }
                }
                // check taken vector first
                for (int j = 0; j < (int)perm_courses.size(); j++) {
                    string name = perm_courses[j].abbrv + " " + to_string(perm_courses[j].num);
                    for (int k = 0; k < (int)or_vector.size(); k++) {
                        if (name == or_vector[k]) {
                            taken = true;
                            or_vector.clear();
                        }
                    }
                }
                if (taken == false) {
                    // create a vector of courses from the or_vector
                    vector<course> remaining_crs = create_remaining_vector(course_vector, or_vector);
                    // create a new priority queue for just the co-reqs
                    priority_queue<course, vector<course>, CompareCourse> cr_pq = create_pq(remaining_crs, temp_schedule);
                    // check pre-reqs
                    while(1) {
                        if (check_pr(taken_vector, cr_pq) == true) {
                            // check conflicts
                            if (check_conflicts(cr_schedule, cr_pq.top()) == false) {
                                // schedule
                                add_to_schedule(cr_schedule, cr_pq.top());
                                scheduled_cr.push_back(cr_pq.top());
                                or_vector.clear();
                                break;
                            }
                            // if this doesn't work, pop the queue + try again
                            cr_pq.pop();
                        }
                        else { 
                            cout << "failed to schedule a co-req" << endl;
                            cr_scheduled = false;
                            scheduled_cr.clear();
                            break;
                        }
                    }
                }
                // if we checked, but weren't able to match, this class is unabled to be scheduled
                if (or_vector.size() != 0) {
                    cr_scheduled = false;
                    break;
                }
                // increment index
                index = i+1;
            }

            // grab last course + check
            if (i == (int)c.co_req.size()-1) {
                // push
                cr = c.co_req.substr(index, c.co_req.size() - index);
                or_vector.push_back(cr);

                /* final attempt to schedule */
                bool taken;
                for (int j = 0; j < (int)taken_vector.size(); j++) {
                    for (int k = 0; k < (int)or_vector.size(); k++) {
                        if (taken_vector[j] == or_vector[k]) {
                            taken = true;
                            or_vector.clear();
                        }
                    }
                }
                // check taken vector first
                for (int j = 0; j < (int)perm_courses.size(); j++) {
                    string name = perm_courses[j].abbrv + " " + to_string(perm_courses[j].num);
                    for (int k = 0; k < (int)or_vector.size(); k++) {
                        if (name == or_vector[k]) {
                            taken = true;
                            or_vector.clear();
                        }
                    }
                }
                if (taken == false) {
                    // create a vector of courses from the or_vector
                    vector<course> remaining_crs = create_remaining_vector(course_vector, or_vector);
                    // create a new priority queue for just the co-reqs
                    priority_queue<course, vector<course>, CompareCourse> cr_pq = create_pq(remaining_crs, temp_schedule);
                    // check pre-reqs
                    while(1) {
                        if (check_pr(taken_vector, cr_pq) == true) {
                            // check conflicts
                            if (check_conflicts(cr_schedule, cr_pq.top()) == false) {
                                // schedule
                                add_to_schedule(cr_schedule, cr_pq.top());
                                scheduled_cr.push_back(cr_pq.top());
                                or_vector.clear();
                                break;
                            }
                            // if this doesn't work, pop the queue + try again
                            cr_pq.pop();
                        }
                        else { 
                            cout << "failed to schedule a co-req" << endl;
                            cr_scheduled = false;
                            scheduled_cr.clear();
                            break;
                        }
                    }
                }
                // if we checked, but weren't able to match, this class is unabled to be scheduled
                if (or_vector.size() != 0) {
                    cr_scheduled = false;
                    scheduled_cr.clear();
                    break;
                }
                else {
                    cout << "all co-reqs successfully scheduled" << endl;
                    for (int j = 0; j < (int)scheduled_cr.size(); j++) {
                        scheduled_courses.push_back(scheduled_cr[j]);
                    }
                    temp_schedule = cr_schedule;
                }
            }
        }
    }
    return cr_scheduled;
};

void create_schedule(vector<vector<int>> &schedule, vector<course> course_vector, vector<string> taken_vector, vector<string> major_vector) {
    ofstream appendfile("lexy_schedule.csv");
    // loop here until credit hours are met
    int total_hours = 0;
    int passes = 0;
    bool scheduled_success;
    vector<course> remaining_vector;
    priority_queue<course, vector<course>, CompareCourse> pq;

    while (total_hours < credit_hours) {
        if (passes == 0 || scheduled_success == true) {
            // Create a remaining courses vector to pull ALL reamining courses from the database.
            remaining_vector = create_remaining_vector(course_vector, major_vector);
            // Create min heap priority queue
            pq = create_pq(remaining_vector, schedule);
            // print pq
            print_pq(pq);
            // reset
            scheduled_success = false;
        }
        passes++;

        if (check_pr(taken_vector, pq) == true) {
            cout << "Passed PRs - " << pq.top().abbrv << " " << pq.top().num << " : " << pq.top().title << " at " << pq.top().lec_time << endl;

            // attempt to schedule the first class
            course c = pq.top();

            // create a temp schedule to hold old values - but as to not destroy the previous schedule in case there are conflicts! only in use with co-reqs
            vector<vector<int>> temp_schedule = schedule;

            // check for conflicts
            if (check_conflicts(schedule, c) == false) {
                cout << "No time conflicts" << endl;

                // schedule (tentatively)
                add_to_schedule(temp_schedule, c);

                // check + schedule co-reqs
                if (check_crs(c, temp_schedule, course_vector, taken_vector) == true) {
                    // we scheduled a class!
                    cout << "Scheduled CRs" << endl;
                    schedule = temp_schedule;
                    scheduled_success = true;

                    // remove scheduled courses from major_vector
                    for (int i = 0; i < (int)major_vector.size(); i++) {
                        for (int j = 0; j < (int)scheduled_courses.size(); j++) {
                            string name = scheduled_courses[j].abbrv + " " + to_string(scheduled_courses[j].num);
                            if (major_vector[i] == name) {
                                major_vector.erase(major_vector.begin() + i);
                            }
                        }
                    }
                    // determine number of credit hours + write to file
                    if (appendfile.is_open()) {
                        for (int i = 0; i < (int)scheduled_courses.size(); i++) {
                            total_hours += scheduled_courses[i].hours;
                            perm_courses.push_back(scheduled_courses[i]);
                            cout << "SCHEDULED " << scheduled_courses[i].abbrv << " " << scheduled_courses[i].num << endl;
                            // Abbreviation,Number,Title,Hours,Attributes,LcTime,LcDate,LcLocation,LaTime,LaDate,LaLocation
                            appendfile << 
                            scheduled_courses[i].abbrv << "," << 
                            scheduled_courses[i].num << "," <<
                            scheduled_courses[i].title << "," <<
                            scheduled_courses[i].hours << "," <<
                            scheduled_courses[i].attributes << "," <<
                            scheduled_courses[i].lec_time << "," <<
                            scheduled_courses[i].lec_date << "," <<
                            scheduled_courses[i].lec_loc << "," <<
                            scheduled_courses[i].lab_time << "," <<
                            scheduled_courses[i].lab_date << "," <<
                            scheduled_courses[i].lab_loc << endl;
                        }
                    }
                    else {
                        cerr << "Unable to open file." << endl;
                    }
                    scheduled_courses.clear();
                }
                else {
                    // pop the queue + try again
                    pq.pop();
                }
            }
            else {
                cout << "Time Conflicts!" << endl;
                pq.pop();
            }
        }
        else {
            pq.pop();
        }
    }
    appendfile.close();
};

// coordinates for class locations
const pair<double, double> APBcoord(35.95716565313402, -83.92699933505531);
const pair<double, double> AYRcoord(35.95743065274119, -83.92592513641416);
const pair<double, double> BECcoord(35.954316260640674, -83.92782712008297);
const pair<double, double> BEOcoord(35.9481784481985, -83.94013149194797);
const pair<double, double> DOUcoord(35.95775693538045, -83.92407556241893);
const pair<double, double> HBBcoord(35.95573323240885, -83.928646419472);
const pair<double, double> HPRcoord(35.95188743870127, -83.93253301808525);
const pair<double, double> HSScoord(35.953522436651596, -83.92881407748088);
const pair<double, double> JHBcoord(35.95919575620802, -83.92617622801401);
const pair<double, double> LIBcoord(35.95511512399242, -83.92976548040959);
const pair<double, double> MKBcoord(35.95863732223823, -83.92463257032564);
const pair<double, double> MOScoord(35.9588754345924, -83.92702442104134);
const pair<double, double> PERcoord(35.95668833001991, -83.92406905123228);
const pair<double, double> PHYcoord(35.95656376894459, -83.92551827131747);
const pair<double, double> SRFcoord(35.95730762715489, -83.92475009354663);
const pair<double, double> STRcoord(35.95768764248766, -83.93108382310751);
const pair<double, double> TICcoord(35.95577153518418, -83.9226653536677);
const pair<double, double> WABcoord(35.95693990352076, -83.92768208583665);
const pair<double, double> ZECcoord(35.95569385908873, -83.92376342399506);

int main(int argc, char** argv) {
    // argument checking
    bool failed = false;
    if(argc != 4) {
        failed = true;
    }
    if(failed) {
        ofstream ferr("error.txt");
        ferr << "usage: " << argv[0] << " available_courses_file.csv major_courses_file.csv taken_courses_file.csv" << endl;
        // Lexy added this command line argument back because she can't remember how to use the darn program, we can take this out, though.
            cout << "usage: " << argv[0] << " + eecs_courses.csv + major_courses.csv + taken_courses.csv" << endl;
        ferr.close();
        return 1;
    }

    // files streams + string buffer
    ifstream file; 
    string line;

    // make vector that can hold class type course
    vector<course> course_vector;
    course my_course;

    // open the available_courses file and error check opening
    string available_courses_file = argv[1];
    file.open(available_courses_file);
    if(!file.is_open()) {
        ofstream ferr("error.txt");
        ferr << "error: cannot open " << available_courses_file << endl;
        ferr << "usage: " << argv[0] << " available_courses_file.csv major_courses_file.csv taken_courses_file.csv" << endl;
        ferr.close();
        return 1;
    }

    // Skip formatting string
    getline(file, line);
    while (getline(file, line)) { // get whole line
        int i = 0;
        stringstream ss(line);
        while (getline(ss, line, ',')) { // separate by commas
            // using i to keep track of the number of attributes we've read in,
            // switch to read into the right properties
            switch (i) {
                case(0):
                    my_course.abbrv = line;
                    break;
                case(1):
                    my_course.num = stoi(line);
                    break;
                case(2):
                    my_course.title = line;
                    break;
                case(3):
                    my_course.hours = stoi(line);
                    break;
                case(4):
                    my_course.attributes = line;
                    break;
                case(5):
                    my_course.pre_req = line;
                    break;
                case(6):
                    my_course.co_req = line;
                    break;
                case(7):
                    my_course.lec_time = line;
                    break;
                case(8):
                    my_course.lec_date = line;
                    break;
                case(9):
                    my_course.lec_loc = line;
                    break;
                case(10):
                    my_course.lab_time = line;
                    break;
                case(11):
                    my_course.lab_date = line;
                    break;
                case(12):
                    my_course.lab_loc = line;
                    break;
                default:
                    cout << "error" << endl;
                    return 1;
            }
            i++; 
            if (i == 13) {
                course_vector.push_back(my_course);
                i = 0;
            }
        }
    }
    file.close();

    // open the major_courses file and error check opening
    string major_courses_file = argv[2];
    file.open(major_courses_file);
    if(!file.is_open()) {
        ofstream ferr("error.txt");
        ferr << "error: cannot open " << major_courses_file << endl;
        ferr << "usage: " << argv[0] << " available_courses_file.csv major_courses_file.csv taken_courses_file.csv" << endl;
        ferr.close();
        return 1;
    }

    // reads from the major courses into a vector that holds the strings
    vector<string> major_vector;
    string major_course;
    while(getline(file, line)) {
        major_course = line;
        major_vector.push_back(major_course);
    }
    file.close();

    // open the taken_courses file and error check opening
    string taken_courses_file = argv[3];
    file.open(taken_courses_file);
    if(!file.is_open()) {
        ofstream ferr("error.txt");
        ferr << "error: cannot open " << taken_courses_file << endl;
        ferr << "usage: " << argv[0] << " available_courses_file.csv major_courses_file.csv taken_courses_file.csv" << endl;
        ferr.close();
        return 1;
    }

    // reads from the taken_courses file and saves them to a vector
    vector<string> taken_vector;
    string taken_course;
    while(getline(file, line)) {
        taken_course = line;
        taken_vector.push_back(taken_course);
    }
    file.close();

    // expands the taken_courses vector to include all the pre reqs that are needed to get to a class in the taken_courses vector
    for(int i = 0; i < (int)taken_vector.size(); i++) {
        string c = "";
        for(int j = 0; j < (int)course_vector.size(); j++) {
            c = course_vector[j].abbrv + " " + to_string(course_vector[j].num);
            if(c == taken_vector[i]) {
                string cc = course_vector[j].pre_req;
                string ccc = "";
                for(int k = 0; k < (int)cc.size(); k++) {
                    if (cc[k] == '|' || cc[k] == '&') {
                        taken_vector.push_back(ccc);
                        ccc.clear();
                    }
                    if (cc[k] != '|' && cc[k] != '&') {
                        ccc.push_back(cc[k]);
                    }
                }
                taken_vector.push_back(ccc);
                break;
            }
        }
    }

    // create a set so duplicates are removed and classes are sorted alphabetically
    set<string> taken_set;
    for(int i = 0; i < (int)taken_vector.size(); i++) {
        taken_set.insert(taken_vector[i]);
    }

    // print inside the set
    set<string>::iterator it = taken_set.begin();
    while (it != taken_set.end()) {
        if (*it == "none") {
            it = taken_set.erase(it);
        } 
        else {
            //cout << *it << endl;
            ++it;
        }
    }

    for(int i = 0; i < (int)major_vector.size(); i++) {
        set<string>::iterator it = taken_set.begin();
        while(it != taken_set.end()) {
            if(*it == major_vector[i]) { major_vector.erase(major_vector.begin()+i); i--; }
            else { ++it; }
        }    
    }

    cout << "Remaining Courses:" << endl;
    for(int i = 0; i < (int)major_vector.size(); i++) {
        cout << major_vector[i] << endl;
    }
    cout << endl;

    // START OF THE GAPS PROGRAM
    // NOTE:    add a flag at the start of the program when this is done!!

    string input;
    cout << "What time would you like to start your classes?\nPlease enter in 24-hour time (0000-2359): ";
    while (1) {
        cin >> input;
        if (input.length() == 4) { // check string length
            user_hour = stoi(input.substr(0,2));
            user_min = stoi(input.substr(2,2));
            if (user_hour >= 0 && user_hour < 24 && user_min >= 0 && user_min < 60) {
                break;
            }
        }
        cout << "Please enter a valid time (0000-2359): ";
    }

    cout << "How many minutes would you like between classes?: ";
    while (1) {
        cin >> gap;
        if (gap >= 0 && gap < 1440) {
            break;
        }
        cout << "Please enter a valid number of minutes (0-1439): ";
    }

    cout << "How many credit hours would you like to take next semester?: ";
    while (1) {
        cin >> credit_hours;
        if (credit_hours > 0) {
            break;
        }
        cout << "Please enter a valid number of credit hours (>0): ";
    }

    // Create the 2D matrix for the course scheduler
    vector<vector<int>> schedule(60*24, vector<int>(5, 0));

    create_schedule(schedule, course_vector, taken_vector, major_vector);

    print_array(schedule);
}