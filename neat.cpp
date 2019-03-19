#include"neat.hpp"

//0->X - inputy, X+1 -> X+Y - outputy

Population::Population(int size, int epochs, int inSize, int outSize,vector<Specimen*> (*SelectionFunction)(vector<Specimen*>, double)):
    _SelectionFunction(SelectionFunction), _popsize(size), _epoch(0), _maxepochs(epochs), _inSpecimenSize(inSize), _outSpecimenSize(outSize) {
    
    //generation of first specimens:
    for(int i = 0; i<_popsize; i++){
        Specimen* tmp = new Specimen(_inSpecimenSize,_outSpecimenSize,true,i);
        _popTable.push_back(tmp);
    }
}

Population::~Population(){
    for(auto& i : _popTable) delete i;
}

void Population::Step(){
    //choosing parents
    vector<Specimen*> tmp = _SelectionFunction(_popTable,_breedingCoefficient);
    //creating new population
    for(auto& i : _popTable){
        i = new Specimen(*tmp[randomInt(0,tmp.size())],*tmp[randomInt(0,tmp.size())]);
    }
    //randomly mutating
    for(auto& i : _popTable){
        if(randomDouble(0.,1.)<_nodeMutation){
            i->mutateNode(_innovationCounter);
            _innovationCounter += 3;
        }
        if(randomDouble(0.,1.)<_connectionMutation){
            i->mutateLink(_innovationCounter);
            _innovationCounter += 1;
        }
    }
}

