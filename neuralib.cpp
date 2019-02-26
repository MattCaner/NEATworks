#include"neuralib.hpp"

NeuralNet::NeuralNet(int inSize, int outSize, double (*transferFcn)(double)): _input(InputLayer(inSize)), _output(OutputLayer(transferFcn,outSize,nullptr)) {}

FeedForwardNet::FeedForwardNet(int inSize, int outSize, vector<int> hiddenLayers,double (*transferFcn)(double)): NeuralNet(inSize,outSize,transferFcn){
    //creating layers
    if(!hiddenLayers.empty()){
        for(unsigned int i = 0; i<hiddenLayers.size(); i++){
            Layer* tmpLayer = new Layer(transferFcn,hiddenLayers[i],nullptr,nullptr);
            _hiddenLayers.push_back(tmpLayer);
        }
    }

    //interconnecting layers
    if(!(_hiddenLayers.empty())){       //a case of non-zero hidden layers
        _input.setNextLayer(_hiddenLayers[0]);
        _hiddenLayers[0]->setPrevLayer(&_input);
        _hiddenLayers[0]->connectLayers(_input);   

        for(unsigned int i = 1; i<=_hiddenLayers.size(); i++){
            _hiddenLayers[i]->setPrevLayer(_hiddenLayers[i-1]);
            _hiddenLayers[i-1]->setPrevLayer(_hiddenLayers[i]);
            _hiddenLayers[i]->connectLayers(*(_hiddenLayers[i-1]));
        }

        _output.setPrevLayer(_hiddenLayers.back());
        _hiddenLayers.back()->setNextLayer(&_output);
        _output.connectLayers(*(_hiddenLayers.back()));  
    }
    else{   //case of zero hidden layers: just connects in with out and finish
        _input.setNextLayer(&_output);
        _output.setPrevLayer(&_input);
        _output.connectLayers(_input);
    }

}

vector<double> FeedForwardNet::calculateOutput(vector<double> input){
    _input.Feed(input);
    for(unsigned int i = 1; i<_hiddenLayers.size(); i++){
        _hiddenLayers[i]->runCalculations();
    }
    _output.runCalculations();
    return _output.getOutput();
}

inline Layer* FeedForwardNet::getLayer(unsigned int number) {
    return number==_hiddenLayers.size()||_hiddenLayers.empty()?&_output:_hiddenLayers[number];
}

