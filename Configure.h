/* 
 * File:   Configure.h
 * Author: amin
 *
 * Created on February 25, 2016, 3:55 PM
 */

#ifndef CONFIGURE_H
#define	CONFIGURE_H

class Configure {
public:
    char pdbname[80];
    char psfname[80];
    char parname[80];
    char outname[80];
    char dcdname[80];
    char enename[80];
    char resname[80];
    char inname[80];

    char mode[4];

    char   thermostat[3];
    double temp;
    char   initialtemp[3];
    double lambda = 0.5;
    double gamma  = 0.0;

    double timestep;   // in fs
    double box[3][3];

    double cutoff;
    double switchdist;
    double pairlistdist;
    double celldist;
    int pairlistFreq;
    int nonbondedFreq;
    int seed;

    char rigidBonds[3];
  
    int restartFreq;
    int wrapFreq;
    int dcdFreq;
    int energyFreq;

    int fstep;
    int nsteps;
    
    int numAtoms;
    int numBonds;
    int numAngles;
    
    Configure(char *input);
    Configure(const Configure& orig);
    virtual ~Configure();
private:

};

#endif	/* CONFIGURE_H */

