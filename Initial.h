/* 
 * File:   Initial.h
 * Author: amin
 *
 * Created on March 3, 2016, 2:49 PM
 */

#ifndef INITIAL_H
#define	INITIAL_H

#include "Vector.h"
#include "Configure.h"
#include "Molecule.h"
#include "Parameters.h"

template<class T>
class Initial {
public:
    
    Vector<T> *pos;
    T *mass;
    
    T box[3];
    
    int *residue;
    int nresidue;
    
    T gamma, sigma;
    
    Initial() {
    
    std::cout << "FFFFF";
    nresidue = 1000;
    }
    Initial(T a);
    Initial(const Initial& orig);
    virtual ~Initial();
private:

};

#endif	/* INITIAL_H */

