/* 
 * File:   Integrator.cpp
 * Author: amin
 * 
 * Created on March 8, 2016, 4:29 PM
 */

#include <fstream>
#include <string.h>
#include <iostream>
#include "Integrator.h"
#include "Constant.h"

using namespace std;

Integrator::Integrator(const Configure *conf, const Molecule *mol, const Build_interaction_list *interaction){
    
    pos = new Vector<float>[conf->numAtoms]; // allocate memory for coordinate
    for (int ii=0; ii<conf->numAtoms; ii++){
        pos[ii].x = mol->atoms[ii].coorx;
        pos[ii].y = mol->atoms[ii].coory;
        pos[ii].z = mol->atoms[ii].coorz;
    }
    
    rmass = new float[conf->numAtoms];  // allocate memory for 1/mass
    for (int ii=0; ii<conf->numAtoms; ii++){
        rmass[ii] = 1.0f/mol->atoms[ii].mass;
    }
    // allocate memory for velocity 
    vel = new Vector<float>[conf->numAtoms]; // allocate memory for velocity at dt
    vel2 = new Vector<float>[conf->numAtoms]; // allocate memory for velocity at dt/2
    memset((void *)vel, 0, conf->numAtoms*sizeof(Vector<float>));
    memset((void *)vel2, 0, conf->numAtoms*sizeof(Vector<float>));
    
}

void Integrator::Loop(const Configure *conf, const Molecule *mol, const Build_interaction_list *interaction){
 
    Constant<float> constant(conf);
    
    
    cout << constant.box << endl;
    

}

Integrator::Integrator(const Integrator& orig) {
}

Integrator::~Integrator() {
}

