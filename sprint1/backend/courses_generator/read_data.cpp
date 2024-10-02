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
        cerr << "usage: " << argv[0] << " available_courses_file.csv major_courses_file.csv taken_courses_file.csv" << endl;
        return 1;
    }

    ifstream file; 
    string line;

    // make vector that can hold class type course
    vector<course> course_vector;
    course my_course;

    string available_courses_file = argv[1];
    file.open(available_courses_file);
    if(!file.is_open()) {
        cerr << "error: cannot open " << available_courses_file << endl;
        cerr << "usage: " << argv[0] << " available_courses_file.csv major_courses_file.csv taken_courses_file.csv" << endl;
        return 1;
    }

    // Skip formatting string
    getline(file, line);
    while (getline(file, line)) { // get whole line
        int i = 0;
        stringstream ss(line);
        while (getline(ss, line, ',')) { // separate by commas
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

    string major_courses_file = argv[2];
    file.open(major_courses_file);
    if(!file.is_open()) {
        cerr << "error: cannot open " << major_courses_file << endl;
        cerr << "usage: " << argv[0] << " available_courses_file.csv major_courses_file.csv taken_courses_file.csv" << endl;
        return 1;
    }

    vector<string> major_vector;
    string major_course;
    while(getline(file, line)) {
        major_course = line;
        major_vector.push_back(major_course);
    }
    file.close();

    string taken_courses_file = argv[3];
    file.open(taken_courses_file);
    if(!file.is_open()) {
        cerr << "error: cannot open " << taken_courses_file << endl;
        cerr << "usage: " << argv[0] << " available_courses_file.csv major_courses_file.csv taken_courses_file.csv" << endl;
        return 1;
    }

    vector<string> taken_vector;
    string taken_course;
    while(getline(file, line)) {
        taken_course = line;
        taken_vector.push_back(taken_course);
    }
    file.close();

    for(int i = 0; i < taken_vector.size(); i++) {
        string c = "";
        for(int j = 0; j < course_vector.size(); j++) {
            c = course_vector[j].abbrv + " " + to_string(course_vector[j].num);
            if(c == taken_vector[i]) {
                string cc = course_vector[j].pre_req;
                string ccc = "";
                for(int k = 0; k < cc.size(); k++) {
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

    // create a set so duplicates are remoced and classes are sorted
    set<string> taken_set;
    for(int i = 0; i < taken_vector.size(); i++) {
        taken_set.insert(taken_vector[i]);
    }

    // print set
    set<string>::iterator it = taken_set.begin();
    while (it != taken_set.end()) {
        if (*it == "none") {
            it = taken_set.erase(it);
        } 
        else {
            cout << *it << endl;
            ++it;
        }
    }
}