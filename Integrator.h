/* 
 * File:   Integrator.h
 * Author: amin
 *
 * Created on March 8, 2016, 4:29 PM
 */

#ifndef INTEGRATOR_H
#define	INTEGRATOR_H
#include "Configure.h"
#include "Molecule.h"
#include "Build_interaction_list.h"
#include "Vector.h"
#include "Constant.h"

class Integrator {
public:
    Vector<float> *pos;
    Vector<float> *vel;
    Vector<float> *vel2;
    Vector<float> *ff;
    
    float *rmass;
    
    double Etot = 0.0, Ebond = 0.0, Eangle = 0.0, Evdw = 0.0, Eelec = 0.0, Ekin = 0.0;
    
    Integrator(const Configure *conf, const Molecule *mol, const Build_interaction_list *interaction);
    void Loop(const Configure *conf, const Molecule *mol, const Build_interaction_list *interaction);
    Integrator(const Integrator& orig);
    virtual ~Integrator();
private:

};

#endif	/* INTEGRATOR_H */

