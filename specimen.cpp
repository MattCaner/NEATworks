#include"specimen.hpp"



Specimen::Specimen(int inputs, int outputs, bool fullconnect, int innovation): _inSize(inputs), _outSize(outputs) {
    if(fullconnect){
        //creates a node and link table:
        int innovationCounter = innovation;
        for(int i = 0; i<inputs; i++){
            _nodes.push_back(new NodeGene(i,innovationCounter));
        }
        for(int i=inputs; i<inputs+outputs;i++){
            _nodes.push_back(new NodeGene(i,innovationCounter));
        }
        //create a suitable link table
        for(int i = 0; i< inputs; i++){
            for(int j = inputs; j< outputs + inputs; j++){
                _connections.push_back(new ConnectionGene(i,j,randomDouble(0,1.0),innovationCounter));
            }
        }
    }
}

Specimen::Specimen(const Specimen& s): _largestNodeIndex(s._largestNodeIndex), _inSize(s._inSize), _outSize(s._outSize){
    for(auto& i : s._nodes){
        _nodes.push_back(i);
    }
    for(auto& i : s._connections){
        _connections.push_back(i);
    }
}

Specimen::Specimen(const Specimen& s1, const Specimen& s2){
    *this = NEATbreeding(s1,s2);
}

Specimen::~Specimen(){
    for(auto& i : _nodes) delete i;
    for(auto& i : _connections) delete i;
}

Specimen& Specimen::mutateNode(int innovation){
    int cutLink = randomInt(0,_connections.size());
    NodeGene* tmp = new NodeGene(++_largestNodeIndex,innovation);
    _nodes.push_back(tmp);
    int thisID = _nodes.size();
    int back = _connections[cutLink]->getIn();
    int forward = _connections[cutLink]->getOut();
    _connections.erase(_connections.begin()+cutLink);
    _connections.push_back(new ConnectionGene(back,thisID,1.0,innovation+1));
    _connections.push_back(new ConnectionGene(thisID,forward,1.0,innovation+2));
    return *this;
}

Specimen& Specimen::mutateLink(int innovation){
    for(int i = 0; i<10; i++){      //test the arbitrary value of tries (10?)
        int newBack = randomInt(0,_nodes.size()+_inSize);   //all neurons excluding outputs (outputs cannot push additional outputs (or can they?))
        int newForward = randomInt(_inSize,_nodes.size()+_outSize); //all neurons excluding inputs (inputs cannot receive output)
        if(newBack==newForward) continue;       //just try again
        for(uint i = 0; i<_connections.size(); i++){ //check if exactly same link does not exists
            if(_connections[i]->getIn()==newBack && _connections[i]->getOut()==newForward) continue;    //if so, try again
        }
        //eventually, if no such link exists, add it (ugh, finally!)
        ConnectionGene* newGene = new ConnectionGene(newBack,newForward,randomDouble(-1.0,1.0),innovation);
        _connections.push_back(newGene);
        break;  //if no continue was fired, the loop will break.
    }
    return *this;
}

Specimen& Specimen::operator=(const Specimen& s){
    _largestNodeIndex = s._largestNodeIndex;
    for(auto& i : s._nodes){
        _nodes.push_back(new NodeGene(*i));
    }
    for(auto& i : s._connections){
        _connections.push_back(new ConnectionGene(*i));
    }
    return *this;
}

Specimen::operator UnLayeredNet(){
    UnLayeredNet tmp = UnLayeredNet(_inSize, _outSize,true,/*CHANGE!:::*/TanSig);

    for(uint i = 0; i<_nodes.size(); i++){
        tmp.getFreeLayer().AddNode();
    }
    //cout << endl << tmp.getNumberOfInputs() << endl << tmp.getNumberOfOutputs() << endl ;
    for(uint i = 0; i<_connections.size(); i++){
       // cout << endl << i << endl;
        tmp.AddConnection(_connections[i]->getIn(),_connections[i]->getOut(),_connections[i]->getWeight());
    }
    return tmp;
}




Specimen NEATbreeding(const Specimen& s1, const Specimen& s2){
    Specimen tmp = Specimen(s1._inSize,s2._outSize);

    uint iterator1, iterator2 = 0;
    //create a unified node table:
    while(iterator1<s1._nodes.size() && iterator2<s2._nodes.size()){
        int i1 = s1._nodes.at(iterator1)->getInnovation();
        int i2 = s2._nodes.at(iterator2)->getInnovation();
        if(i1<i2){
            tmp._nodes.push_back(new NodeGene(*(s1._nodes.at(iterator1))));
            iterator1++;
        }
        else
        {
            if(i1>i2){
                tmp._nodes.push_back(new NodeGene(*(s2._nodes.at(iterator2))));
                iterator2++;                
            }
            else{
                if(randomDouble(0,1)>0.5){
                    tmp._nodes.push_back(new NodeGene(*(s1._nodes.at(iterator1))));                 
                }
                else{
                    tmp._nodes.push_back(new NodeGene(*(s2._nodes.at(iterator2))));                       
                }
                iterator1++;
                iterator2++;
            }
        }
        
    }

    iterator1 = 0; 
    iterator2 = 0;
    //create a unified connections table:
    while(iterator1<s1._connections.size() && iterator2<s2._connections.size()){
        int i1 = s1._connections.at(iterator1)->getInnovation();
        int i2 = s2._connections.at(iterator2)->getInnovation();
        if(i1<i2){
            tmp._connections.push_back(new ConnectionGene(*(s1._connections.at(iterator1))));
            iterator1++;
        }
        else
        {
            if(i1>i2){
                tmp._connections.push_back(new ConnectionGene(*(s2._connections.at(iterator2))));
                iterator2++;                
            }
            else{
                if(randomDouble(0,1)>0.5){
                    tmp._connections.push_back(new ConnectionGene(*(s1._connections.at(iterator1))));                 
                }
                else{
                    tmp._connections.push_back(new ConnectionGene(*(s2._connections.at(iterator2))));                       
                }
                iterator1++;
                iterator2++;
            }
        }
    }

    return tmp;

}

