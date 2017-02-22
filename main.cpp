/* 
 * File:   main.cpp
 * Author: amin
 *
 * Created on February 25, 2016, 3:14 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <new>
#include "Configure.h"
#include "Molecule.h"
#include "Parameters.h"
#include "Build_interaction_list.h"
#include "Initial.h"
#include "Integrator.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    time_t t0 = time(0);
    char* cht = ctime(&t0);
    cout << "The local date and time is: " << cht ;
    
    ifstream infile(argv[1]);
    if (argc != 2 || !infile){
        cout << "Error: Enter Input file" << endl;
        exit(1);
    } 

    Configure conf(argv[1]);  // Read Configure file   
    Molecule *pMol = new Molecule(&conf); // Read PSF and PDB files
    Parameters *pPar = new Parameters(&conf); // Read Parameter file
    
    Build_interaction_list *pInteraction = new Build_interaction_list(&conf, pMol, pPar);
  
    Integrator run(&conf, pMol, pInteraction);
    run.Loop(&conf, pMol, pInteraction);
    delete pMol; delete pPar;
    
    
    // Simulation Time
    time_t t1 = time(0);
    cht = ctime(&t1);
    cout << "The local date and time is: " << cht ;
    time_t t2 = t1 - t0;
    cout << "Simulation Time: " << t2 << " seconds" << endl;
    struct tm *tt = gmtime ( &t2 );
    printf ("Simulation Time:  %2d:%02d:%02d\n", (tt->tm_hour)%24, tt->tm_min, tt->tm_sec);
    cout << "END PROGRAM" << endl;   
    

    return 0;
}

