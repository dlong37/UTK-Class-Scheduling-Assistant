#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <set>
#include <utility>
#include <time.h>
#include <stdlib.h>
#include "Support.h"
using namespace std;

vector<pair<double, double>> coordinates = { APBcoord, AYRcoord, BECcoord, BEOcoord, DOUcoord, HBBcoord, HPRcoord, HSScoord, JHBcoord, LIBcoord, MKBcoord, MOScoord, PERcoord, PHYcoord, SRFcoord, STRcoord, TICcoord, WABcoord, ZECcoord };

void calc_distance(vector<vector<float> > &distance_vector) {
    distance_vector.resize(19);
    for(int i = 0; i < 19; i++) {
        distance_vector[i].resize(19);
    }

    for(int i = 0; i < 19; i++) {
        for(int j = 0; j <= i; j++) {
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
    ferr << "usage: " << r << " available_courses_file.csv major_courses_file.csv taken_courses_file.csv" << endl;
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
        vector.push_back(course);
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

void optimize_loc(vector<course> course_vector, set<string> taken_set, vector<string> major_vector, vector<vector<float>> distance_vector, string s, int hours) {
    int t = 0;
    vector<string> jaibesoin;
    srand (time(NULL));
    while(t < hours) {
        int i = rand() % major_vector.size();
        for(int j = 0; j < (int)course_vector.size(); j++) {
            string tempTitle = course_vector[j].abbrv + " " + to_string(course_vector[j].num);
            if(tempTitle == major_vector[i]) {
                vector<vector<string>> temppre(5, vector<string>(5, "NULL"));
                if(get_prereqs(course_vector[j], temppre)) {
                    if(check_prereqs(taken_set, temppre)) {
                        jaibesoin.push_back(tempTitle);
                        major_vector.erase(major_vector.begin()+i);
                        t += course_vector[j].hours;
                    }
                    else {
                        major_vector.erase(major_vector.begin()+i);
                    }
                }
                else {
                    jaibesoin.push_back(tempTitle);
                    major_vector.erase(major_vector.begin()+i);
                    t += course_vector[j].hours;
                }
                break;
            }
        }
    }

    for(int i = 0; i < jaibesoin.size(); i++) {
        cout << jaibesoin[i] << endl;
    }
}

bool get_prereqs(course c, vector<vector<string>> &temppre) {
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

bool check_prereqs(set<string> taken_set, vector<vector<string>> temppre) {
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