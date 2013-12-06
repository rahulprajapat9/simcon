#ifndef MDP_H
#define MDP_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <pthread.h>
#include "algo.h"
#include "simdata.h"
#include "config.h"
#include "stateIterator.h"
#include "policy.h"
using namespace std;

class Mdp : public Policy
{
	long int num_states;
	vector< vector<int> > optimal_policy;
	vector< vector<int> > mig_list;

	float getISUV(int phase, int* vm_to_pm_map1, int* vm_to_pm_map2, int* perm_map);
	float getSUV(int phase, int* vm_to_pm_map);

  public:
	Mdp(SimData *s_data);
	float compareState(int phase, int* vm_to_pm_map1, int* vm_to_pm_map2, int *best_perm_map);
	void run(int phases);
	void getMapping(int phase_number, vector<int>* mapping);
	void getMigrationList(int phase_number, vector<int>* mapping);
};

struct ThreadData
{
   int num_vms;
   int p;
   int state_no;
   int* state_array;
   Matrix<int*>* mig_table;
   Matrix<float>* trans_table;
   Mdp *mdp;

   ThreadData(int n, int phaseno, int sno, int* sarray, Matrix<int*>* mtable, Matrix<float>* ttable, Mdp* m)
   : num_vms(n), p(phaseno), state_no(sno), mig_table(mtable), trans_table(ttable), mdp(m)
   {
        state_array = new int[n];
        for(int j=0; j<n; j++)
            state_array[j] = sarray[j];
   }

   ~ThreadData()
   {
        delete state_array;
   }
};

#endif
