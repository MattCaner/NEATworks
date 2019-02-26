#pragma once
#include"neuron.hpp"

class Layer{            //general-use layer and mother class for all layer-type classes. Supports basic functions for controlling and managing neuron layer.
public:
    Layer(double (*transferFcn)(double),int size,Layer* prevLayer,Layer* nextLayer);    //general constructor.
    void changeTransferFcn(double (*transferFcn)(double));                              //changes transfer function for all neurons in this layer.

    void connectLayers(Layer& to, bool back = true);        //connects this layer with another one. By default this layer is treated as the one closer to output.

    int getSize() const {return _neurons.size();}           //returns number of neurons in layer.
    Layer& getPrevLayer() const {return *_prevLayer;}       //returns previous layer this layer is connected to
    Layer& getNextLater() const {return *_nextLayer;};      //returns next layer this layer is connected to.
    
    void setPrevLayer(Layer* pl) {_prevLayer = pl;}         //set pointer to previous layer
    void setNextLayer(Layer* nl) {_nextLayer = nl;}         //set pointer to next layer (yet unused)

    Neuron& operator[](int n) {return *(_neurons[n]);}      //returns reference to nth neuron in the layer.

    virtual void runCalculations();                         //runs calculations through this layer (virtualised for use in FreeLayer)

    int getNumberOfWeights();                               //returns how many weights and biases are inputing this layer.
    void setWeitghts(vector<double> weightsAndBiases);      //set all weights and biases to values given in vector.
    vector<double> getWeights();                            //get all weights and biases as a single double vector.

protected:
    vector<Neuron*> _neurons;
    Layer* _prevLayer;
    Layer* _nextLayer;
};

class FreeLayer: public Layer{
public:
    FreeLayer(double (*transferFcn)(double),int size,Layer* in, Layer* out);    //general-use constructor that have similar functionality to Layer base class constructor
    void runCalculations();         //runs calculations through the layer (takes all the inputs and returns all the outputs

};


class InputLayer: public Layer{                             //special class for input-type layer. Allows data feeding.
public:
    InputLayer(int size);                   //general-use constructor. Input requires nothing more than size to be specified.
    void Feed(vector<double> input);        //feeds data to neurons so that they can be processed by other layers.
};

class OutputLayer: public Layer{                            //special class for output-type layer. Allows easy gathering of output data in form of a vector.
public:
    OutputLayer(double (*transferFcn)(double), int size,Layer* prevLayer);      //general-use constructor.
    vector<double> getOutput();                                                 //return all neuron outputs in form of std::vector<double>
};