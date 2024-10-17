#include "Support.h"
using namespace std;

int main(int argc, char** argv) {

    // argument checking
    if(error_check(argv[0], argc, 4)) { return 1; }

    // files streams
    ifstream file; 

    // open the available_courses file and error check opening
    if(open_file(argv[1], file, argv[0])) { return 1; }

    // make vector that can hold class type course
    vector<course> course_vector;
    if(read_file(file, course_vector)) { return 1; }

    // open the major_courses file and error check opening
    if(open_file(argv[2], file, argv[0])) { return 1; }

    // reads from the major courses into a vector that holds the strings
    vector<string> major_vector;
    read_file2(major_vector, file);

    for(int i = 0; i < (int)major_vector.size(); i++) {
        cout << major_vector[i] << endl;
    }
    cout << endl;

    // open the taken_courses file and error check opening
    if(open_file(argv[3], file, argv[0])) { return 1; }

    // reads from the taken_courses file and saves them to a vector
    vector<string> taken_vector;
    read_file2(taken_vector, file);

    for(int i = 0; i < (int)taken_vector.size(); i++) {
        cout << taken_vector[i] << endl;
    }
    cout << endl;

    // expands the taken_courses vector to include all the pre reqs that are needed to get to a class in the taken_courses vector
    expand_vector(taken_vector, course_vector);

    for(int i = 0; i < (int)taken_vector.size(); i++) {
        cout << taken_vector[i] << endl;
    }
    cout << endl;

    // create a set so duplicates are removed and classes are sorted alphabetically
    set<string> taken_set;
    remove_duplicates(taken_set, taken_vector, major_vector);
    for(set<string>::iterator it = taken_set.begin(); it != taken_set.end(); ++it) {
        cout << *it << std::endl;
    }
    cout << endl;

    vector<vector<float>> distance_vector;
    calc_distance(distance_vector);

    for(int i = 0; i < 19; i++) {
        for(int j = 0; j < 19; j++) {
            printf("%f ", distance_vector[i][j]);
        }
        printf("\n");
    }
    
}