#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <algorithm>
#include <utility>
#include <time.h>
#include <stdlib.h>
#include "Support.h"
#define MINS_PER_HOUR 60
using namespace std;

vector<pair<double, double> > coordinates = { APBcoord, AYRcoord, BECcoord, BEOcoord, DOUcoord, HBBcoord, HPRcoord, HSScoord, JHBcoord, LIBcoord, MKBcoord, MOScoord, PERcoord, PHYcoord, SRFcoord, STRcoord, TICcoord, WABcoord, ZECcoord };

void calc_distance(vector<vector<float> > &distance_vector) {
    distance_vector.resize(19);
    for(int i = 0; i < 19; i++) {
        distance_vector[i].resize(19);
    }

    for(int i = 0; i < 19; i++) {
        for(int j = 0; j < 19; j++) {
            float la1 = coordinates[i].first*(M_PI/180.0);
            float la2 = coordinates[j].first*(M_PI/180.0);
            float lo1 = coordinates[i].second*(M_PI/180.0);
            float lo2 = coordinates[j].second*(M_PI/180.0);
            float temp1 = ((la2 - la1)/2);
            float temp2 = ((lo2 - lo1)/2);

            float temp3 = (sin(temp1))*(sin(temp1));
            float temp4 = cos(la1);
            float temp5 = cos(la2);
            float temp6 = (sin(temp2))*(sin(temp2));

            float temp7 = temp3 + (temp4*temp5*temp6);

            float temp8 = sqrt(temp7);

            float distance = 2*(3963.0)*(asin(temp8));

            distance = 0.001*round(distance/0.001);

            distance_vector[i][j] = distance;
        }
    }
}

void print_error(string r, string s, int i) {
    ofstream ferr("error.txt");
    if(i == 1) { ferr << "error: cannot open " << s << endl; }
    ferr << "usage: " << r << " available_courses_file.csv major_courses_file.csv taken_courses_file.csv location|time" << endl;
    ferr.close();
}

int read_file(ifstream &file, vector<course> &course_vector) {
    course my_course;
    string line;
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
                    cerr << "error" << endl;
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
    return 0;
}

void expand_vector(vector<string> &taken_vector, vector<course> &course_vector) {
    for(int i = 0; i < taken_vector.size(); i++) {
        string c = "";
        for(int j = 0; j < course_vector.size(); j++) {
            c = course_vector[j].abbrv + " " + to_string(course_vector[j].num);
            if(c == taken_vector[i]) {
                string cc = course_vector[j].pre_req;
                string ccc = "";
                for(int k = 0; k < cc.size(); k++) {
                    if(cc[k] == '&' || cc[k] == '|') {
                        taken_vector.push_back(ccc);
                        ccc.clear();
                    }
                    if(cc[k] != '&' && cc[k] != '|') {
                        ccc.push_back(cc[k]);
                    }
                }
                taken_vector.push_back(ccc);
                break;
            }
        }
    }
}

void remove_duplicates(set<string> &taken_set, vector<string> &taken_vector, vector<string> &major_vector) {
    for(int i = 0; i < taken_vector.size(); i++) {
        taken_set.insert(taken_vector[i]);
    }

    // print inside the set
    set<string>::iterator it = taken_set.begin();
    while (it != taken_set.end()) {
        if (*it == "none") {
            it = taken_set.erase(it);
        } 
        else {
            ++it;
        }
    }

    for(int i = 0; i < major_vector.size(); i++) {
        for(set<string>::iterator it = taken_set.begin(); it != taken_set.end(); ++it) {
            if(major_vector[i] == *it) {
                major_vector.erase(major_vector.begin()+i);
                i--;
                break;
            }
        }   
    }
}

int open_file(string file_name, ifstream &file, string args) {
    file.open(file_name);
    if(!file.is_open()) {
        print_error(args, file_name, 1);
        return 1;
    }
    return 0;
}

void read_file2(vector<string> &vector, ifstream &file) {
    string line;
    string course;
    while(getline(file, line)) {
        course = line;
        if(line != "\n") {
            vector.push_back(course);
        }
    }
    file.close();
}

int error_check(string s, int argc, int i) {
    bool failed = false;
    if(argc != i) {
        failed = true;
    }
    if(failed) {
        print_error(s, "no", 0);
        return 1;
    }
    return 0;
}

void find_next_courses(vector<string> &needed, vector<course> course_vector, set<string> taken_set, vector<string> major_vector, vector<vector<float> > distance_vector, string s, int hours) {
    int t = 0;
    srand(time(NULL));
    while(t < hours) {
        if(major_vector.size() == 0) { break; }
        int i = rand() % major_vector.size();
        for(int j = 0; j < (int)course_vector.size(); j++) {
            string tempTitle = course_vector[j].abbrv + " " + to_string(course_vector[j].num);
            if(tempTitle == major_vector[i]) {
                vector<vector<string> > temppre(5, vector<string>(5, "NULL"));
                if(get_prereqs(course_vector[j], temppre)) {
                    if(check_prereqs(taken_set, temppre)) {
                        //cout << "scheduled: " << tempTitle << endl;
                        needed.push_back(tempTitle);
                        major_vector.erase(major_vector.begin()+i);
                        t += course_vector[j].hours;
                    }
                    else {
                        //cout << "did not schedule: " << tempTitle << endl;
                        major_vector.erase(major_vector.begin()+i);
                    }
                }
                else {
                    //cout << "scheduled: " << tempTitle << endl;
                    needed.push_back(tempTitle);
                    major_vector.erase(major_vector.begin()+i);
                    t += course_vector[j].hours;
                }
                break;
            }
        }
    }
}

bool get_prereqs(course c, vector<vector<string> > &temppre) {
    string cc = c.pre_req;
    string ccc = "";
    int loc = 0;
    int locloc = 0;
    int pushedback = 0;
    for(int i = 0; i < cc.size(); i++) {
        if(cc[i] == '&' || cc[i] == '|') {
            if(cc[i] == '&') { temppre[loc][locloc] = ccc; loc++; locloc = 0; pushedback++; }
            else { temppre[loc][locloc] = ccc; locloc++; pushedback++; }
            ccc.clear();
        }
        if(cc[i] != '&' && cc[i] != '|') {
            ccc.push_back(cc[i]);
        }
    }
    temppre[loc][locloc] = ccc;
    if(ccc != "none") { pushedback++; }
    else { temppre[loc][locloc] = "NULL"; }
    if(pushedback > 0) { return true; }
    else { return false; }
}

bool check_prereqs(set<string> taken_set, vector<vector<string> > temppre) {
    int needed = 0;
    for(int i = 0; i < temppre.size(); i++) {
        if(temppre[i][0] != "NULL") {
            needed++;
        }
    }
    for(int i = 0; i < temppre.size(); i++) {
        for(int j = 0; j < temppre[i].size(); j++) {
            if(taken_set.find(temppre[i][j]) != taken_set.end()) {
                needed--;
                break;
            }
        }
    }
    if(needed == 0) { return true; }
    else { return false; }
}

int get_flag(string s) {
    if(s == "time") { return 1; }
    if(s == "location") { return 2; }
    return 0;
}

// Lexy's Functions

priority_queue<course, vector<course>, CompareCourse> create_pq(vector<course> remaining_vector, vector<vector<int>> schedule, int user_hour, int user_min, int gap) {
    priority_queue<course, vector<course>, CompareCourse> pq;
    for (int i = 0; i < (int)remaining_vector.size(); i++) {
        // calculate start time in minutes
        // only based on lecture days! I would love to do labs as well, but that would require deep structural changes
        string lec_days = remaining_vector[i].lec_date;
        // find the last minute that a course is scheduled for:
        int rows = schedule.size();
        int startx = 0;
        for (int j = 0; j < rows; ++j) {
            for (int k = 0; k < (int)lec_days.size(); k++) {
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
    // cout << "\nPriority Queue: " << endl;
    while (!print.empty()) {
        // cout << print.top().abbrv << " " << print.top().num << " : " << print.top().title << " at " << print.top().lec_time << " (" << print.top().priority << ")" << endl;
        print.pop(); 
    }
    // cout << endl;
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
        // cout << "lec start time: " << lec_start_time << endl;
    int lec_end_time = stoi(course.lec_time.substr(5, 2)) * MINS_PER_HOUR + stoi(course.lec_time.substr(7, 2));
        // cout << "lec end time: " << lec_end_time << endl;
    int lab_start_time = 0;
        // cout << "lab start time: " << lab_start_time << endl;
    int lab_end_time = 0;
        // cout << "lab start time: " << lab_end_time << endl;

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

void add_to_schedule(vector<vector<int>> &schedule, course course_c, vector<course> &scheduled_courses) {
    scheduled_courses.push_back(course_c);

    int lec_start_time = stoi(course_c.lec_time.substr(0, 2)) * MINS_PER_HOUR + stoi(course_c.lec_time.substr(2, 2));
    int lec_end_time = stoi(course_c.lec_time.substr(5, 2)) * MINS_PER_HOUR + stoi(course_c.lec_time.substr(7, 2));
    int lab_start_time = 0;
    int lab_end_time = 0;

    if (course_c.lab_time != "none") {
        lab_start_time = stoi(course_c.lab_time.substr(0, 2)) * MINS_PER_HOUR + stoi(course_c.lab_time.substr(2, 2));
        lab_end_time = stoi(course_c.lab_time.substr(5, 2)) * MINS_PER_HOUR + stoi(course_c.lab_time.substr(7, 2));
    }

    string lec_days = course_c.lec_date;
    string lab_days = course_c.lab_date;

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

bool check_crs(course c, vector<vector<int>> &temp_schedule, vector<course> course_vector, vector<string> taken_vector, vector<course> &perm_courses, int user_hour, int user_min, int gap, vector<course> &scheduled_courses) {
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
                // cout << "push " << cr << endl;
            }

            // hit an AND sign: check OR vector + attempt to schedule
            if (c.co_req[i] == '&') {
                // push class onto the OR vector
                cr = c.co_req.substr(index, i-index);
                or_vector.push_back(cr);
                // cout << "push " << cr << endl;

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
                    priority_queue<course, vector<course>, CompareCourse> cr_pq = create_pq(remaining_crs, temp_schedule, user_hour, user_min, gap);
                    // check pre-reqs
                    while(1) {
                        if (check_pr(taken_vector, cr_pq) == true) {
                            // check conflicts
                            if (check_conflicts(cr_schedule, cr_pq.top()) == false) {
                                // schedule
                                add_to_schedule(cr_schedule, cr_pq.top(), scheduled_courses);
                                scheduled_cr.push_back(cr_pq.top());
                                or_vector.clear();
                                break;
                            }
                            // if this doesn't work, pop the queue + try again
                            cr_pq.pop();
                        }
                        else { 
                            // cout << "failed to schedule a co-req" << endl;
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
                // cout << "push last class " << cr << endl;

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
                    priority_queue<course, vector<course>, CompareCourse> cr_pq = create_pq(remaining_crs, temp_schedule, user_hour, user_min, gap);
                    // check pre-reqs
                    while(1) {
                        if (check_pr(taken_vector, cr_pq) == true) {
                            // check conflicts
                            if (check_conflicts(cr_schedule, cr_pq.top()) == false) {
                                // schedule
                                add_to_schedule(cr_schedule, cr_pq.top(), scheduled_courses);
                                scheduled_cr.push_back(cr_pq.top());
                                or_vector.clear();
                                break;
                            }
                            // if this doesn't work, pop the queue + try again
                            cr_pq.pop();
                        }
                        else { 
                            // cout << "failed to schedule a co-req" << endl;
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
                    // cout << "all co-reqs successfully scheduled" << endl;
                    temp_schedule = cr_schedule;
                }
            }
        }
    }
    return cr_scheduled;
};

void create_schedule(vector<vector<int>> &schedule, vector<course> course_vector, vector<string> taken_vector, vector<string> major_vector, int credit_hours, vector<course> &scheduled_courses, vector<course> &perm_courses, int user_hour, int user_min, int gap) {
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
            pq = create_pq(remaining_vector, schedule, user_hour, user_min, gap);
            // print pq
            print_pq(pq);
            // reset
            scheduled_success = false;
        }
        passes++;

        if (check_pr(taken_vector, pq) == true && check_dup(perm_courses, pq.top()) == true) {
            // cout << "Passed PRs - " << pq.top().abbrv << " " << pq.top().num << " : " << pq.top().title << " at " << pq.top().lec_time << endl;

            // attempt to schedule the first class
            course c = pq.top();

            // create a temp schedule to hold old values - but as to not destroy the previous schedule in case there are conflicts! only in use with co-reqs
            vector<vector<int>> temp_schedule = schedule;

            // check for conflicts
            if (check_conflicts(schedule, c) == false) {
                // cout << "No time conflicts" << endl;

                // schedule (tentatively)
                add_to_schedule(temp_schedule, c, scheduled_courses);

                // check + schedule co-reqs
                if (check_crs(c, temp_schedule, course_vector, taken_vector, perm_courses, user_hour, user_min, gap, scheduled_courses) == true) {
                    // we scheduled a class!
                    // cout << "Scheduled CRs" << endl;
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

                            // cout << "SCHEDULED " << scheduled_courses[i].abbrv << " " << scheduled_courses[i].num << endl;

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
                // cout << "Time Conflicts!" << endl;
                pq.pop();
            }
        }
        else if (pq.empty()) {
            // cout << "No more schedulable classes." << endl;
            break;
        }
        else {
            pq.pop();
        }
    }
    appendfile.close();
};

int schedule_next_courses(vector<course> &next_courses, vector<string> &needed, vector<course> &course_vector) {
    int scheduled = 0;
    vector<vector<course> > twodvec;
    twodvec.resize(needed.size());
    for(int i = 0; i < needed.size(); i++) {
        for(int j = 0; j < course_vector.size(); j++) {
            if(needed[i] == (course_vector[j].abbrv + " " + to_string(course_vector[j].num))) {
                twodvec[i].push_back(course_vector[j]);
            }
        }
    }

    sort(twodvec.begin(), twodvec.end(), [](const std::vector<course>& a, const std::vector<course>& b) { return a.size() < b.size(); });

    for(int i = 0; i < twodvec.size(); i++) {
        if(i == 0) { next_courses.push_back(twodvec[i][0]); scheduled++; }
        else {
            for(int j = 0; j < twodvec[i].size(); j++) {
                bool canschedule = true;
                for(int k = 0; k < next_courses.size(); k++) {
                    if((next_courses[k].lec_time == twodvec[i][j].lec_time && twodvec[i][j].lec_time != "none") || (next_courses[k].lab_time == twodvec[i][j].lab_time && twodvec[i][j].lab_time != "none") || (next_courses[k].lec_time == twodvec[i][j].lab_time && twodvec[i][j].lab_time != "none") || (next_courses[k].lab_time == twodvec[i][j].lec_time && twodvec[i][j].lec_time != "none")) {
                        canschedule = false;
                    }
                }
                if(canschedule) {
                    next_courses.push_back(twodvec[i][j]);
                    scheduled++;
                    break;
                }
            }
        }
    }
    return scheduled;
}

bool course::operator==(course rhs) {
    bool same = true;
    if(abbrv != rhs.abbrv) { same = false; }
    if(num != rhs.num) { same = false; }
    if(lec_time != rhs.lec_time) { same = false; }
    if(lec_loc != rhs.lec_loc) { same = false; }
    if(lab_time != rhs.lab_time) { same = false; }
    if(lab_loc != rhs.lab_loc) { same = false; }
    return same;
}

void print_ids(vector<course> v1, vector<course> v2) {
    for (int i = 0; i < v1.size(); i++) {
        for (int j = 0; j < v2.size(); j++) {
            if (v1[i] == v2[j]) {
                cout << j+1 << endl;
                break;
            }
        }
    }
}

bool check_dup(vector<course> perm_courses, course c) {
    for (int j = 0; j < (int)perm_courses.size(); j++) {
        string perm_name = perm_courses[j].abbrv + " " + to_string(perm_courses[j].num);
        string c_name = c.abbrv + " " + to_string(c.num);
        if (perm_name == c_name) {
            return false;
        }
    }
    return true;
}