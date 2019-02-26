#pragma once
#include"layer.hpp"

using namespace std;

class NeuralNet{            //abstract class for handling basic net behaviour.
public:
    NeuralNet(int inSize, int outSize, double (*transferFcn)(double));      //creates a net of given number of inputs and outputs, without any additional neurons.
    virtual vector<double> calculateOutput(vector<double> input) = 0;       //virtualised, abstract function that calculates output based on input.
protected:
    InputLayer _input;
    OutputLayer _output;
};

class FeedForwardNet: public NeuralNet{     //class for handling feed-forward type neural networks.
public:
    FeedForwardNet(int inSize, int OutSize, vector<int> hiddenLayers,double (*transferFcn)(double));  //creates a basic net with given set of neurons in each hidden layer.
    vector<double> calculateOutput(vector<double> input);                                             //takes input, performs calculations, returns output.
    inline Layer* getLayer(unsigned int number);                                                               //returns pointer to requested layer. 
    Layer* getOutputLayer() {return &_output;}                                                        //returns pointer to output.
protected:
    vector<Layer*> _hiddenLayers;
};

class UnLayeredNet: public NeuralNet{       //class for handling neural networks with more advanced topologies than feed-forward.
public:
    UnLayeredNet(int inSize, int OutSize);
    UnLayeredNet(int inSize, int OutSize, int hidden);
    vector<double> calculateOutput(vector<double> input);
protected:
    Layer _hiddenLayer;
};