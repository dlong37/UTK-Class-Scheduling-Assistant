#include "Support.h"
using namespace std;

// eecs_courses.csv + major_courses.csv + taken_courses.csv

int user_hour = 0;
int user_min = 0;
int gap = 0;
int credit_hours = 0;
vector<course> scheduled_courses;
vector<course> perm_courses;

int main(int argc, char** argv) {
    // argument checking
    if(error_check(argv[0], argc, 5)) {
        return 1;
    }

    int flag = get_flag(argv[argc-1]);

    // files streams
    ifstream file; 

    // open the available_courses file and error check opening
    if(open_file(argv[1], file, argv[0])) {
        return 1;
    }

    // make vector that can hold class type course
    vector<course> course_vector;
    if(read_file(file, course_vector)) {
        return 1;
    }

    // open the major_courses file and error check opening
    if(open_file(argv[2], file, argv[0])) {
        return 1;
    }

    // reads from the major courses into a vector that holds the strings
    vector<string> major_vector;
    read_file2(major_vector, file);

    // open the taken_courses file and error check opening
    if(open_file(argv[3], file, argv[0])) {
        return 1;
    }

    // reads from the taken_courses file and saves them to a vector
    vector<string> taken_vector;
    read_file2(taken_vector, file);

    // expands the taken_courses vector to include all the pre reqs that are needed to get to a class in the taken_courses vector
    expand_vector(taken_vector, course_vector);

    // create a set so duplicates are removed and classes are sorted alphabetically
    set<string> taken_set;
    remove_duplicates(taken_set, taken_vector, major_vector);

    if (flag == 1) { // gaps program
        if (open_time_file(file, credit_hours, gap, user_min, user_hour) == false) {
            return 1;
        }

        // Create the 2D matrix for the course scheduler
        vector<vector<int>> schedule(60*24, vector<int>(5, 0));

        // create schedule
        create_schedule(schedule, course_vector, taken_vector, major_vector, credit_hours, scheduled_courses, perm_courses, user_hour, user_min, gap);

        // print schedule
        print_ids(perm_courses, course_vector);
        //print_array(schedule);
    }

    if (flag == 2) {
        vector<vector<float> > distance_vector;
        calc_distance(distance_vector);
        bool running = true;

        while(running) {
            vector<string> needed;
            find_next_courses(needed, course_vector, taken_set, major_vector, distance_vector, argv[1], 12);

            vector<course> next_courses;
            if(schedule_next_courses(next_courses, needed, course_vector) == needed.size()) {
                for(int i = 0; i < next_courses.size(); i++) {
                    for(int j = 0; j < course_vector.size(); j++) {
                        if(next_courses[i] == course_vector[j]) {
                            cout << j+1 << endl;
                            break;
                        }
                    }
                }
                // for(int i = 0; i < next_courses.size(); i++) {
                //     cout << next_courses[i].abbrv + " " + to_string(next_courses[i].num) << " @ " << next_courses[i].lec_time << endl;
                // }
                running = false;
            }
        }
    }
}