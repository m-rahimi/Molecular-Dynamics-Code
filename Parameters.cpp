/* 
 * File:   Parameters.cpp
 * Author: amin
 * 
 * Created on February 29, 2016, 5:16 PM
 */

#include "Parameters.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <algorithm>
#include "Parameters.h"
#include "Configure.h"

using namespace std;

Parameters::Parameters(const Configure *conf) {

    read_params(conf->parname);
}

void Parameters::read_params(const char *filename){
    string str;
    size_t found;
    if (ifstream(filename)) {
    ifstream infile;
    infile.open(filename);
    while(!infile.eof()) {
	getline(infile, str);
        if (str != ""){
            found=str.find("BOND");
            if (found!=std::string::npos) {
                str.replace(found,4,""); //remove first column  
                bond_str.push_back(str);
            }
            found=str.find("ANGLE");
            if (found!=std::string::npos) {
                str.replace(found,5,""); //remove first column
                angle_str.push_back(str);
            }
            found=str.find("VDW");
            if (found!=std::string::npos) {
                str.replace(found,3,""); //remove first column
                vdw_str.push_back(str);
            }
            found=str.find("DPD");
            if (found!=std::string::npos) {
                str.replace(found,3,""); //remove first column
                dpd_str.push_back(str);
            }
        }
    }
    } else {
        cout << "Parameters file is not exist" << endl;
        exit(1);
    }
}

Parameters::Parameters(const Parameters& orig) {
}

Parameters::~Parameters() {
}

