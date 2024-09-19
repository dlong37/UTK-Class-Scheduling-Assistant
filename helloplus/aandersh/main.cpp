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
        string cat;
        string title;
        string pre_req;
        string co_req;
        int diff;
};


int main(int argc, char** argv) {
    string file_name = "major_courses.csv";
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
                    cout << line << endl;
                    break;
                case(3):
                    my_course.cat = line;
                    break;
                case(4):
                    my_course.co_req = line;
                    break;
                case(5):
                    my_course.pre_req = line;
                    break;
                default:
                    cout << "error" << endl;
                    return 1;
            }
            i++; 
            if (i == 6) {
                course_vector.push_back(my_course);
                i = 0;
            }
        }
    }

    for (int k = 0; k < course_vector.size(); k++) {
        cout << course_vector[k].title << endl;
    }

    file.close();
}