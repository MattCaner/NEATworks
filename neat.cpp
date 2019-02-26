#include"neat.hpp"

//0->X - inputy, X+1 -> X+Y - outputy


Specimen::Specimen(int inputs, int outputs): _inSize(inputs), _outSize(outputs) { }

Specimen& Specimen::mutateNode(int innovation){
    int cutLink = randomInt(0,_connections.size());
    NodeGene* tmp = new NodeGene(++_largestNodeIndex,innovation);
    _nodes.push_back(tmp);
    int thisID;
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
        for(int i = 0; i<_connections.size(); i++){ //check if exactly same link does not exists
            if(_connections[i]->getIn()==newBack && _connections[i]->getOut()==newForward) continue;    //if so, try again
        }
        //eventually, if no such link exists, add it (ugh, finally!)
        ConnectionGene* newGene = new ConnectionGene(newBack,newForward,randomDouble(-1.0,1.0),innovation);
        _connections.push_back(newGene);
        break;  //if no continue was fired, the loop will break.
    }
    return *this;
}

explicit Specimen::operator UnLayeredNet(){

    

}




Specimen NEATbreeding(Specimen& s1, Specimen& s2){
    Specimen tmp = Specimen(s1._inSize,s2._outSize);

    int iterator1, iterator2 = 0;
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

    iterator1, iterator2 = 0;
    //create a unified connections table:
    while(iterator1<s1._connections.size() && iterator2<s2._connections.size()){
        int i1 = s1._connections.at(iterator1)->getInnovation();
        int i2 = s2._connections.at(iterator2)->getInnovation();
        if(i1<i2){
            tmp._connections.push_back(new NodeGene(*(s1._connections.at(iterator1))));
            iterator1++;
        }
        else
        {
            if(i1>i2){
                tmp._connections.push_back(new NodeGene(*(s2._connections.at(iterator2))));
                iterator2++;                
            }
            else{
                if(randomDouble(0,1)>0.5){
                    tmp._connections.push_back(new NodeGene(*(s1._connections.at(iterator1))));                 
                }
                else{
                    tmp._connections.push_back(new NodeGene(*(s2._connections.at(iterator2))));                       
                }
                iterator1++;
                iterator2++;
            }
        }
    }

    return tmp;

}

