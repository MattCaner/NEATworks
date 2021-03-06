#include"layer.hpp"

Layer::Layer(double (*transferFcn)(double),int size,Layer* prevLayer,Layer* nextLayer): _prevLayer(prevLayer),_nextLayer(nextLayer){
    for(int i = 0; i<size; i++){
        Neuron* tmpNeuron = new Neuron(transferFcn);
        _neurons.push_back(tmpNeuron);
    }
}

void Layer::runCalculations(){
    for(unsigned int i = 0; i<_neurons.size(); i++){
        _neurons[i]->calculateOutput();
    }
}

void Layer::connectLayers(Layer& to, bool back){
    if(back){
        for(unsigned int i = 0; i<_neurons.size(); i++){
            for(int j = 0; j<to.getSize(); j++){
                _neurons[i]->connectBack(to[j]);
            }
        }
    }
}

int Layer::getNumberOfWeights(){
    if(_neurons.empty()){
        return 0;
    }
    int counter = 0;
    for(auto& i : _neurons){
        counter++;      //bias
        if(!(i->_inputs.empty())){
            counter+=i->_inputs.size();
        }
    }
    return counter;
}

void Layer::setWeitghts(vector<double> weightsAndBiases){
    int iterator = 0;
    for(auto& i : _neurons){
        i->_bias = weightsAndBiases[iterator];
        iterator++;
        for(auto& j : (i->_inputs)){
            j._weight = weightsAndBiases[iterator];
            iterator++;
        }
    }
}

vector<double> Layer::getWeights(){
    vector<double> tmp;
    for(uint i = 0; i<_neurons.size(); i++){
        for(uint j = 0; j<_neurons[i]->_inputs.size(); j++){
            tmp.push_back(_neurons[i]->_inputs[j]._weight);
        }
    }
    return tmp;
}

inline bool Layer::anyAwaiting(){
    for(uint i = 0; i<_neurons.size(); i++){
        if(_neurons[i]->awaiting==true) return true;
    }
    return false;
}

Layer::~Layer(){
    for(auto& i : _neurons){
        delete i;
    }
}

FreeLayer::FreeLayer(double (*transferFcn)(double),int size): Layer(transferFcn,size) {
    //turns awaiting state in all neurons:
    for(uint i = 0; i<_neurons.size(); i++){
        _neurons[i]->awaiting=true;
    }
}


void FreeLayer::runCalculations(){
    while(anyAwaiting()){
        for(unsigned int i = 0; i<_neurons.size(); i++){
            if(_neurons[i]->awaitingPrevious()==false){
                _neurons[i]->calculateOutput();
                _neurons[i]->awaiting=false;
            }
        }
    }
}

void FreeLayer::AddNode(){
    _neurons.push_back(new Neuron(TanSig));
}



InputLayer::InputLayer(int size): Layer(nullptr,size,nullptr,nullptr){ }

OutputLayer::OutputLayer(double (*transferFcn)(double), int size,Layer* prevLayer): Layer(transferFcn,size,prevLayer,nullptr){ }

void InputLayer::Feed(vector<double> input){
    for(unsigned int i = 0; i<_neurons.size(); i++){
        _neurons[i]->setOutput(input[i]);
    }
}

vector<double> OutputLayer::getOutput(){
    vector<double> tmp;
    for(unsigned int i = 0; i<_neurons.size(); i++){
        tmp.push_back(_neurons[i]->getOutput());
    }
    return tmp;
}
