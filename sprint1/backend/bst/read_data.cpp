#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

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

int main(int argc, char** argv) {
    string file_name = "eecs_courses.csv";
    ifstream file; 
    string line;

    // make vector that can hold class type course
    vector<course> course_vector;
    course my_course;

    file.open(file_name);

    if(!file.is_open()) {
        cerr << "file could not be opened" << endl;
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
                    my_course.co_req = line;
                    break;
                case(6):
                    my_course.pre_req = line;
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

    // for loop to show that course attributes were stored
    for (int k = 0; k < course_vector.size(); k++) {
        cout << course_vector[k].title << endl;
    }
}
