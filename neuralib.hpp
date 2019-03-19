#pragma once
#include"layer.hpp"

using namespace std;

class NeuralNet{            //abstract class for handling basic net behaviour.
public:
    NeuralNet(int inSize, int outSize, double (*transferFcn)(double));      //creates a net of given number of inputs and outputs, without any additional neurons.
    virtual vector<double> calculateOutput(vector<double> input) = 0;       //virtualised, abstract function that calculates output based on input.
    virtual ~NeuralNet() = default;
    int getNumberOfInputs() const {return _input.getSize();}
    int getNumberOfOutputs() const {return _output.getSize();}
protected:
    InputLayer _input;
    OutputLayer _output;
};

class FeedForwardNet: public NeuralNet{     //class for handling feed-forward type neural networks.
public:
    FeedForwardNet(int inSize, int OutSize, vector<int> hiddenLayers,double (*transferFcn)(double));  //creates a basic net with given set of neurons in each hidden layer.
    ~FeedForwardNet();                                                                                //destructor
    vector<double> calculateOutput(vector<double> input);                                             //takes input, performs calculations, returns output.
    inline Layer* getLayer(unsigned int number);                                                      //returns pointer to requested layer. 
    Layer* getOutputLayer() {return &_output;}                                                        //returns pointer to output.
protected:
    vector<Layer*> _hiddenLayers;
};

class UnLayeredNet: public NeuralNet{       //class for handling neural networks with more advanced topologies than feed-forward.
public:
    UnLayeredNet(int inSize, int outSize, bool connected, double (*transferFcn)(double));                         //creates an unlayered net with 0 neurons in hidden layer. Connected determines if there exists connection net between in and out
    UnLayeredNet(int inSize, int outSize, bool connected, double (*transferFcn)(double), int hidden);             //creates an unlayered net with hidden neurons. Connected determines if there exist dense connection net.
    ~UnLayeredNet();                                                                                              //destructor
    FreeLayer& getFreeLayer() {return _hiddenLayer;}                // returns reference to the free layer.
    vector<double> calculateOutput(vector<double> input);     // calculates output (inherited virtual method)
    void AddConnection(int from, int to, double weight);            // adds connection between two given neurons.

    Neuron& operator[](int identifier);     // access to neuron at identifier. This is a correct way of accessing neuron.
protected:
    FreeLayer _hiddenLayer;
};