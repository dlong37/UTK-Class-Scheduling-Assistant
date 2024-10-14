#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

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
        float priority = 0;

        // Define operator< for comparison (for use in std::set)
        // NOTE: increase to encompass every course
        bool operator<(const course& other) const {
            return tie(abbrv, num, title) < tie(other.abbrv, other.num, other.title);
        }
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
    set<course> course_set;
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
                course_set.insert(my_course);
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
                    if(cc[k] == '-') {
                        taken_vector.push_back(ccc);
                        ccc.clear();
                    }
                    if(cc[k] != '-') {
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
    int user_hour;
    int user_min;
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

    int gap;
    cout << "How many minutes would you like between classes?: ";
    while (1) {
        cin >> gap;
        if (gap > 0) {
            break;
        }
    }

    // Ok! Now, assign a priority to the courses in major_vector by using the equation priority = time_between_classes - gap;

    // Create a remaining courses set to assign priorites.
    set<course> remaining_set;
    cout << "\nAll courses available from database:" << endl;
    set<course>::iterator it_course = course_set.begin();
    while (it_course != course_set.end()) {
        for (int j = 0; j < (int)major_vector.size(); j++) {
            string name = it_course->abbrv + " " + to_string(it_course->num);
            if (major_vector[j] == name) {
                cout << name << " : " << it_course->priority << endl;
                remaining_set.insert(*it_course);
            }
        }
        it_course++;
    }

    // Calculate priority of remaining_courses.

    // Once a class has been matched, remove from the remaining_set.
}