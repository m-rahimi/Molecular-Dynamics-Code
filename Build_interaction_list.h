/* 
 * File:   Build_interaction_list.h
 * Author: amin
 *
 * Created on March 2, 2016, 3:29 PM
 */

#ifndef BUILD_INTERACTION_LIST_H
#define	BUILD_INTERACTION_LIST_H
#define PI 3.14159265

#include "Configure.h"
#include "Molecule.h"
#include "vector"
#include "Parameters.h"

struct BondElem {
  int atom1, atom2;
  float x0;
  float k;
};

struct AngleElem {
  int atom1, atom2, atom3;
  float k, theta0;
  bool ub;
};

struct VdwElem {
    float epsi, rmin;
    float charge;
    int *exclist;
    int numexc;
    int type;
};

struct DpdElem {
    int *exclist;
    int numexc;
    int type;
};

class Build_interaction_list {
public:

    BondElem *bonds;
    AngleElem *angles;
    VdwElem *vdw;
    DpdElem *dpd;

    float **aij; // for DPD simulation
    int ntype;

    bool exclude(const int iatom, const int jatom) const;
    void build_bondlist(const Configure *conf, const Molecule *mol, const Parameters *params);
    void build_anglelist(const Configure *conf, const Molecule *mol, const Parameters *params);
    void build_dpdlist(const Configure *conf, const Molecule *mol, const Parameters *params);

    Build_interaction_list(const Configure *conf, const Molecule *mol, const Parameters *params);
    Build_interaction_list(const Build_interaction_list& orig);
    virtual ~Build_interaction_list();
private:

};

#endif	/* BUILD_INTERACTION_LIST_H */

