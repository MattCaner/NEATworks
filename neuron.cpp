#include"neuron.hpp"


Neuron::Neuron(double (*transferFcn)(double)): _transferFcn(transferFcn){ }

Neuron::Neuron(double (*transferFcn)(double),vector<Neuron*>& inputingNeurons, vector<double> inputingWeights, double bias): awaiting(0), _transferFcn(transferFcn), _bias(bias){
    for(unsigned int i = 0; i<inputingNeurons.size(); i++){
        Link tmpLink = Link(inputingNeurons[i],inputingWeights[i]);
        _inputs.push_back(tmpLink);
    }
}

void Neuron::overWriteWeights(vector<double> newWeights){
    for(unsigned int i = 0; i<_inputs.size(); i++){
        _inputs[i]._weight = newWeights[i];
    }
    _bias = newWeights[_inputs.size()];
}

void Neuron::calculateOutput(){
    double sum = 0;
    for(unsigned int i = 0; i<_inputs.size(); i++){
        sum += _inputs[i]._to->_output * _inputs[i]._weight;
    }
    sum+= _bias;
    _output = _transferFcn(sum);
}

void Neuron::connectBack(Neuron& to, double weight){
    Link tmpLink = Link(&to,weight);
    _inputs.push_back(tmpLink);
}

void Neuron::connectForward(Neuron& to, double weight){
    to.connectBack(*this,weight);
}

void Neuron::deleteLink(Neuron& to){
    for(unsigned int i=_inputs.size()-1; i>=0; i++){
        if(_inputs[i]._to==&to){
            _inputs.erase(_inputs.begin()+i);
        }
    }
}

void Neuron::setOutput(double value){
    _output = value;
}

bool Neuron::awaitingPrevious(){
    for(uint i = 0; i< _inputs.size(); i++){
        if(_inputs[i]._to->awaiting==true) return true;
    }
    return false;
}

Neuron::~Neuron(){
    //left non-default for any future changes
}