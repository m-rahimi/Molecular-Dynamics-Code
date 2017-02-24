/* 
 * File:   Parameters.h
 * Author: amin
 *
 * Created on February 29, 2016, 5:16 PM
 */

#ifndef PARAMETERS_H
#define	PARAMETERS_H

#include <vector>
#include <string>
#include "Configure.h"

using namespace std;

class Parameters {
public:

    vector<string> bond_str;
    vector<string> angle_str;
    vector<string> vdw_str;
    vector<string> dpd_str;
        
    void read_params(const char *filename);
    
    Parameters(const Configure *conf);
    Parameters(const Parameters& orig);
    virtual ~Parameters();
private:

};

#endif	/* PARAMETERS_H */

