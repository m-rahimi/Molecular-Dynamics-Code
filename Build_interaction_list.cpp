/* 
 * File:   Build_interaction_list.cpp
 * Author: amin
 * 
 * Created on March 2, 2016, 3:29 PM
 */

#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include "Configure.h"
#include "Molecule.h"
#include "Parameters.h"
#include "Build_interaction_list.h"

Build_interaction_list::Build_interaction_list(const Configure *conf, const Molecule *mol, const Parameters *params) {
    
    bonds = new BondElem[conf->numBonds];
    memset((void *)bonds, 0, conf->numBonds*sizeof(BondElem));
    build_bondlist(conf,mol,params);
    
    angles = new AngleElem[conf->numAngles];
    memset((void *)angles, 0, conf->numAngles*sizeof(AngleElem));
    build_anglelist(conf,mol,params);

 //   connections = new Connections[conf->numAtoms];
 //   memset((void *)connections, 0, conf->numAtoms*sizeof(Connections));

    dpd = new DpdElem[conf->numAtoms];
    memset((void *)dpd, 0, conf->numAtoms*sizeof(DpdElem));
    build_dpdlist(conf,mol,params);
}

void Build_interaction_list::build_bondlist(const Configure *conf, const Molecule *mol, const Parameters *params){
    string str;
    char   seg[256];
    char  *pch;
    size_t found1, found2;

    for (int ii=0; ii<conf->numBonds; ii++){
        bonds[ii].atom1 = mol->bonds[ii].atom1;
        bonds[ii].atom2 = mol->bonds[ii].atom2;

        string atype1(mol->atoms[bonds[ii].atom1].atomtype); // Atom1 type
        string atype2(mol->atoms[bonds[ii].atom2].atomtype); // Atom2 type
        for (int jj=0; jj < params->bond_str.size(); jj++){

            str = params->bond_str[jj];
            found1=str.find(atype1); //find atom1 in the str
            if (found1!=std::string::npos) {
                str.replace(found1,atype1.length(),""); //remove the atom1 from str
                found2=str.find(atype2); //find atom2 in the str
                if (found2!=std::string::npos) {
                    strncpy(seg, str.c_str(), sizeof(seg));
                    seg[sizeof(seg) - 1] = 0;
                    pch = strtok (seg," ,:=");//pch = strtok (NULL," ,:="); // Jumb two columns
                    bonds[ii].k = stof(strtok (NULL," ,:="));
                    bonds[ii].x0 = stof(strtok (NULL," ,:="));
                }
            }
        } // Loops over all bonds parameters
        if (bonds[ii].k==0 && bonds[ii].x0==0) {
            cout << "ERROR : NO BOND PARAMETER FOR BOND BETWEEN ATOM " << bonds[ii].atom1+1 << " AND " << bonds[ii].atom2+1 << endl;
            exit(1);
        }

    } // Loops over all bonds
    
}

void Build_interaction_list::build_anglelist(const Configure *conf, const Molecule *mol, const Parameters *params){
    string str;
    char   seg[256];
    char  *pch1, *pch2, *pch3, *pch4;
    size_t found;

    for (int ii=0; ii<conf->numAngles; ii++){
        angles[ii].atom1 = mol->angles[ii].atom1;
        angles[ii].atom2 = mol->angles[ii].atom2;
        angles[ii].atom3 = mol->angles[ii].atom3;

        char *atype1 = mol->atoms[angles[ii].atom1].atomtype; // Atom1 type
        char *atype2 = mol->atoms[angles[ii].atom2].atomtype; // Atom2 type
        char *atype3 = mol->atoms[angles[ii].atom3].atomtype; // Atom3 type

        for (int jj=0; jj < params->angle_str.size(); jj++){
            str = params->angle_str[jj];
            strncpy(seg, str.c_str(), sizeof(seg));
            seg[sizeof(seg) - 1] = 0;
            pch1 = strtok (seg," ,:=");
            pch2 = strtok (NULL," ,:=");
            pch3 = strtok (NULL," ,:=");
         

            if (strcmp(atype2,pch2)==0){
                if ((strcmp(atype1,pch1)==0 && strcmp(atype3,pch3)==0)||(strcmp(atype1,pch3)==0 && strcmp(atype3,pch1)==0)){
                    angles[ii].k = stof(strtok (NULL," ,:="));
                    angles[ii].theta0 = stof(strtok (NULL," ,:=")); // * PI / 180.0 ;
                    
                    found=str.find("UB");
                    if (found==std::string::npos) {
                        angles[ii].theta0 = angles[ii].theta0 * PI / 180.0f; 
                        angles[ii].ub = false;
                    } else {
                        angles[ii].ub = true;
                    }
                       
                }
            }
        }
        if (angles[ii].k==0 && angles[ii].theta0==0) {
            cout << "ERROR : NO ANGLE PARAMETER FOR ANGLE BETWEEN ATOM " << angles[ii].atom1+1 << " AND "
                                                                         << angles[ii].atom2+1 << " AND "
                                                                         << angles[ii].atom3+1 << endl;
            exit(1);
        }
    }
}

void Build_interaction_list::build_dpdlist(const Configure *conf, const Molecule *mol, const Parameters *params){
    string str;
    char   seg[256];
    char  *pch;
    size_t found1, found2;
    vector<string> list_type;

    // Convert string type to int type
    string atype(mol->atoms[0].atomtype);
    list_type.push_back(atype);
    for (int ii=1; ii<conf->numAtoms; ii++){
        bool flag = true;
        string atype(mol->atoms[ii].atomtype);
        for (int jj=0; jj<list_type.size(); jj++) {
            if (atype==list_type[jj]) {
                dpd[ii].type = jj;
                flag = false;
                break;
            }
        }
        if (flag) { // add new type to list type
            dpd[ii].type = list_type.size();
            list_type.push_back(atype);
        }
    }
    ntype = list_type.size();
    
    // generate N*N array to store interaction parameters
    aij = new float*[ntype];
    for (int ii=0; ii<ntype; ii++) {
        aij[ii] = new float[ntype];
        memset((void *)aij[ii], 0, ntype*sizeof(ntype));
    }


    // Obtain aij from params
    for (int ii=0; ii<ntype; ii++){
        string atype1(list_type[ii]);
        for (int line=0; line<params->dpd_str.size(); line++){
            str = params->dpd_str[line];
            found1=str.find(atype1);
            if (found1!=std::string::npos) {
                str.replace(found1,atype1.length(),""); //remove the atom1 from str
                for (int jj=0; jj<ntype; jj++) {
                    string atype2(list_type[jj]);
                    found2=str.find(atype2);
                    if (found2!=std::string::npos) {
                        strncpy(seg, str.c_str(), sizeof(seg));
                        seg[sizeof(seg) - 1] = 0;
                        pch = strtok (seg," ,:="); // Jump one column
                        aij[ii][jj] = stof(strtok (NULL," ,:="));
                    }
                }
            }
        }
    }

    for (int ii=0; ii<ntype; ii++){
        for (int jj=0; jj<ntype; jj++) {
            if (aij[ii][jj]==0) {
                cout << "There is no interaction parameter between atom type " << list_type[ii] << " and " << list_type[jj] << endl;
                exit(1);
            }
        }
    }

    // find excluded atoms for intermolecular interactions
    int a1, a2, a3;
    const int Max = 15;
    int connections[conf->numAtoms][Max]; // Using array insted of vector to optimize memory
    memset((void *)connections, -1, sizeof connections); 
    int nconnections[conf->numAtoms];     // Save the number of connections
    memset(nconnections, 0, sizeof nconnections);

    for (int ii=0; ii<conf->numAtoms; ii++){
        connections[ii][nconnections[ii]] = ii; nconnections[ii]++; // exclude itself
    }

    for (int ii=0; ii<conf->numBonds; ii++){ // Loop over all bonds
        a1 = bonds[ii].atom1;
        a2 = bonds[ii].atom2;
        
        connections[a1][nconnections[a1]] = a2; nconnections[a1]++; // Save the connection for atom1
        connections[a2][nconnections[a2]] = a1; nconnections[a2]++;
    }
    for (int ii=0; ii<conf->numAngles; ii++){ //Loop over all angles
        a1 = angles[ii].atom1;
        a2 = angles[ii].atom2;
        a3 = angles[ii].atom3;
        // No need to save atom2 since the bond connections for atom2 was saved in bond section
        connections[a1][nconnections[a1]] = a3; nconnections[a1]++; // Save the connection for atom1
        connections[a3][nconnections[a3]] = a1; nconnections[a3]++; // Save the connection for atom1
    }

    for (int ii=0; ii<conf->numAtoms; ii++){ // Loop over all atoms to save connections
        vector<int> temp;
        for (int jj=0; jj<Max; jj++){
            if (connections[ii][jj]>=0) temp.push_back(connections[ii][jj]);
        }

        sort(temp.begin(),temp.end()); // Sort connections
        dpd[ii].exclist = new int[nconnections[ii]]; // Allocate memory to save all connections

        dpd[ii].numexc = nconnections[ii];
        for (int jj=0; jj<nconnections[ii]; jj++){
            dpd[ii].exclist[jj] = temp[jj];
        }
    }
}
bool Build_interaction_list::exclude(const int iatom, const int jatom) const {
    int jj=0;
    bool flag = false;
    while (dpd[iatom].exclist[jj]<=jatom && jj<dpd[iatom].numexc){
        if (dpd[iatom].exclist[jj++] == jatom){
            flag = true;
        }
    }
    return flag;
}


Build_interaction_list::Build_interaction_list(const Build_interaction_list& orig) {
}

Build_interaction_list::~Build_interaction_list() {
}

