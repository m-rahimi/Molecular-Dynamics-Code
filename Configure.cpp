/* 
 * File:   Configure.cpp
 * Author: amin
 * 
 * Created on February 25, 2016, 3:55 PM
 */

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Configure.h"

using namespace std;

Configure::Configure(char *input) {
    string str;
    char   seg[256];
    char  *pch;
    ifstream infile;
    infile.open(input);
    while(!infile.eof()) {
	getline(infile, str);
	if (str!="") {
            strncpy(seg, str.c_str(), sizeof(seg));
            seg[sizeof(seg) - 1] = 0;
            pch = strtok (seg," ,:=");
            string word(pch);
	    if (word == "structure") {
                char *pch = strtok (NULL, " ,:=");
                strcpy(psfname,pch);
            }
            else if (word == "coordinates") {
                char *pch = strtok (NULL, " ,:=");
                strcpy(pdbname,pch);
            }
            else if (word == "parameters") {
                char *pch = strtok (NULL, " ,:=");
                strcpy(parname,pch);
            }
            else if (word == "outputName") {
                char *pch = strtok (NULL, " ,:=");
                strcpy(outname,pch);
                sprintf(dcdname,"%s.dcd",outname);
                sprintf(resname,"%s.res",outname);
                sprintf(enename,"%s.ene",outname);
            }
            else if (word == "inputName") {
                char *pch = strtok (NULL, " ,:=");
                strcpy(inname,pch);
            }
            else if (word == "mode") {
                char *pch = strtok (NULL, " ,:=");
                strcpy(mode,pch);
            }
            else if (word == "thermostat") {
                char *pch = strtok (NULL, " ,:=");
                strcpy(thermostat,pch);
            }
            else if (word == "temperature") {
                char *pch = strtok (NULL, " ,:=");
                temp = stof(pch);
            }
            else if (word == "initialtemp") {
                char *pch = strtok (NULL, " ,:=");
                strcpy(initialtemp,pch);
            }
            else if (word == "lambda") {
                char *pch = strtok (NULL, " ,:=");
                lambda = stof(pch);
            }
            else if (word == "friction") {
                char *pch = strtok (NULL, " ,:=");
                gamma = stof(pch);
            }
            else if (word == "seed") {
                char *pch = strtok (NULL, " ,:=");
                seed = stoi(pch);
            }
            else if (word == "timestep") {
                char *pch = strtok (NULL, " ,:=");
                timestep = stof(pch);
            }
            else if (word == "cutoff"){
                char *pch = strtok (NULL, " ,:=");
                cutoff = stof(pch);
            }
            else if (word == "switchdist"){
                char *pch = strtok (NULL, " ,:=");
                switchdist = stof(pch);
                if (switchdist>cutoff) {
                    cout << "ERROR: switchdist must be <= cutoff" <<endl;
                    exit(1);
                }
            }
            else if (word == "pairlistdist"){
                char *pch = strtok (NULL, " ,:=");
                pairlistdist = stof(pch);
                if (pairlistdist<cutoff) {
                    cout << "ERROR: pairlistdist must be >= cutoff" <<endl;
                    exit(1);
                }
            }
            else if (word == "celldist"){
                char *pch = strtok (NULL, " ,:=");
                celldist = stof(pch);
                if (celldist<pairlistdist){
                    cout << "ERROR: celldist must be >= pairlistdist" <<endl;
                    exit(1);
                }

            }
            else if (word == "pairlistFreq"){
                char *pch = strtok (NULL, " ,:=");
                pairlistFreq = stoi(pch);
            }
            else if (word == "nonbondedFreq"){
                char *pch = strtok (NULL, " ,:=");
                nonbondedFreq = stoi(pch);
            }
            else if (word == "rigidBonds") {
                char *pch = strtok (NULL, " ,:=");
                strcpy(rigidBonds,pch);
            }
            else if (word == "boxx"){
                for (int ii=0; ii<3; ii++){
                    char *pch = strtok (NULL, " ,:=");
                    box[0][ii] = stof(pch);
                }
            }
            else if (word == "boxy"){
                for (int ii=0; ii<3; ii++){
                    char *pch = strtok (NULL, " ,:=");
                    box[1][ii] = stof(pch);
                }
            }
            else if (word == "boxz"){
                for (int ii=0; ii<3; ii++){
                    char *pch = strtok (NULL, " ,:=");
                    box[2][ii] = stof(pch);
                }
            }
            else if (word == "wrapFreq"){
                char *pch = strtok (NULL, " ,:=");
                wrapFreq = stoi(pch);
            }
            else if (word == "restartFreq"){
                char *pch = strtok (NULL, " ,:=");
                restartFreq = stoi(pch);
            }
            else if (word == "dcdFreq"){
                char *pch = strtok (NULL, " ,:=");
                dcdFreq = stoi(pch);
            }
            else if (word == "energyFreq"){
                char *pch = strtok (NULL, " ,:=");
                energyFreq = stoi(pch);
            }
            else if (word == "firsttimestep"){
                char *pch = strtok (NULL, " ,:=");
                fstep = stoi(pch);
            }
            else if (word == "run"){
                char *pch = strtok (NULL, " ,:=");
                nsteps = stoi(pch);
            }

        }
    }
    infile.close();
    
    cout << "Input files : " << pdbname << "  " << psfname << "  " << parname << endl;
    // Check the input files
    ifstream infile_psf(psfname);
    if (!infile_psf){
        cout << "Error: The PSF file is not exist" << endl;
        exit(1);
    }
    ifstream infile_pdb(pdbname);
    if (!infile_pdb){
        cout << "Error: The PDB file is not exist" << endl;
        exit(1);
    }
    ifstream infile_par(parname);
    if (!infile_par){
        cout << "Error: The Parameter file is not exist" << endl;
        exit(1);
    }
    
    // Read the number of atoms, bonds, angles from psf file
    infile.open(psfname);
    size_t found;
    while(!infile.eof()) {
	getline(infile, str);

        found=str.find("NATOM");
        if (found!=std::string::npos) {
            strncpy(seg, str.c_str(), sizeof(seg));
            seg[sizeof(seg) - 1] = 0;
            pch = strtok (seg," ,:=");
            numAtoms = stoi(pch);
        }

        found=str.find("NBOND");
        if (found!=std::string::npos) {
            strncpy(seg, str.c_str(), sizeof(seg));
            seg[sizeof(seg) - 1] = 0;
            pch = strtok (seg," ,:=");
            numBonds = stoi(pch);
        }

        found=str.find("NTHETA");
        if (found!=std::string::npos) {
            strncpy(seg, str.c_str(), sizeof(seg));
            seg[sizeof(seg) - 1] = 0;
            pch = strtok (seg," ,:=");
            numAngles = stoi(pch);
        }

    }
    infile.close();
    
    cout << "SIMULATION INFORMATION:" << endl;
    cout << "Number of Atoms   = " << numAtoms << endl;
    cout << "Number of bonds   = " << numBonds << endl;
    cout << "Number of Angles  = " << numAngles << endl;
}

Configure::Configure(const Configure& orig) {
}

Configure::~Configure() {
}

