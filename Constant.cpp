/* 
 * File:   Constant.cpp
 * Author: amin
 * 
 * Created on March 8, 2016, 5:33 PM
 */

#ifdef CONSTANT_FUNCTION
#include "Constant.h"



template<class T>
Constant<T>::Constant(const Configure *conf) {
    dt = conf->timestep;
    dtLambda = dt * conf->lambda;
    KB = 1.0f;
    
    box.x = conf->box[0][0];
    box.y = conf->box[1][1];
    box.z = conf->box[2][2];
    
}
template<class T>
Constant<T>::Constant(const Constant& orig) {
}
template<class T>
Constant<T>::~Constant() {
}

#endif