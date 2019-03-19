#pragma once
#include"specimen.hpp"


/*
 * Selection methods:
 *      NumericalRoulette - breeding is based on numerical function
 *      NumericalTournament - breeding is tournament based, evaluation of winners is based on numerical functions
 *      BooleanTournamend - breeding is tournament based, evaluation of winners is boolean based (winner/loser)
 */



class Population{
public:
    Population(int size, int epochs, int inSize, int outSize,vector<Specimen*> (*SelectionFunction)(vector<Specimen*>, double));
    ~Population();     
    void Step();                                                    //step by one epoch
    Specimen Evaluate();                                            //return best specimen

    int getEpoch() const {return _epoch;}                           //return number of epoch
    
protected:
    
    //selection function must take specimen vector and breeding coefficient d in form of double.
    //it has to return specimen vector with at least d*(original size) unique parents to breed.
    //d is a number between 0 and 1. Returned value must be the sime as original size.
    vector<Specimen*> (*_SelectionFunction)(vector<Specimen*>, double);

    //breeding function takes two specimens and returns their offspring.
    Specimen Breed(const Specimen& s1, const Specimen& s2);

    //general variables:
    int _popsize;
    int _epoch;
    int _maxepochs;
    double _breedingCoefficient;
    double _nodeMutation;
    double _connectionMutation;

    //specimen specification
    int _inSpecimenSize;
    int _outSpecimenSize;

    //innovation counter, a key element in NEAT network:
    int _innovationCounter;

    //holding space for population and best specimens:
    vector<Specimen*> _popTable;
    vector<Specimen*> _winnerTable;
};