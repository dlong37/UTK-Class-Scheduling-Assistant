#ifndef SUPPORT_H
#define SUPPORT_H
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <set>
#include <utility>
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

void calc_distance(vector<vector<float> > &distance_vector);
void print_error(string r, string s, int i);
int read_file(ifstream &file, vector<course> &course_vector);
void expand_vector(vector<string> &taken_vector, vector<course> &course_vector);
void remove_duplicates(set<string> &taken_set, vector<string> &taken_vector, vector<string> &major_vector);
int open_file(string file_name, ifstream &file, string args);
void read_file2(vector<string> &vector, ifstream &file);
int error_check(string s, int argc, int i);
void find_next_courses(vector<string> &needed, vector<course> course_vector, set<string> taken_set, vector<string> major_vector, vector<vector<float> > distance_vector, string s, int hours);
bool get_prereqs(course c, vector<vector<string> > &temppre);
bool check_prereqs(set<string> taken_set, vector<vector<string> > temppre);
int get_flag(string s);

#endif