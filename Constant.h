/* 
 * File:   Constant.h
 * Author: amin
 *
 * Created on March 8, 2016, 5:33 PM
 */

#ifndef CONSTANT_H
#define	CONSTANT_H
#include "Vector.h"
#include    "Configure.h"

template <class T>
class Constant {
public:
    T dt;
    T KB;
    T dtLambda;
    
    Vector<T> box;
    
    Constant(const Configure *conf);
    Constant(const Constant& orig);
    virtual ~Constant();
private:

};


#define CONSTANT_FUNCTION
#include "Constant.cpp"

#endif	/* CONSTANT_H */

