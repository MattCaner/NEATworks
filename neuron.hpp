#pragma once
#include"util.hpp"

//Forward declarations for use in neuron
struct Link;
class Layer;

class Neuron{
public:    void setWeitghts(vector<double> weightsAndBiases);      //set all weights and biases to values given in vector.
    vector<double> getWeights();                            //get all weights and biases as a single double vector.
    Neuron(double (*transferFcn)(double));      //creates a neuron without any inputing weights (in most common case such neuron is an input neuron)
    Neuron(double (*transferFcn)(double), vector<Neuron*>& inputingNeurons);
    Neuron(double (*transferFcn)(double),vector<Neuron*>& inputingNeurons, vector<double> inputingWeights, double bias);     //

    int getNumberOfInputs() const {return _inputs.size();}  //returns number of inputs given neuron has.  

    void connectBack(Neuron& to, double weight = 1);   //make connection between this neuron and other neuron (data flows towards this neuron)
    void connectForward(Neuron& to, double weight = 1);    //make connection between this neuron and other neuron (data flows towards the other neuron)

    void deleteLink(Neuron& to);            //deletes all back links to given neuron

    void clearConnections();                //clears all back links of given neuron

    void setOutput(double value);           //forcibly sets output to given value. Used in debugging and input layers.

    bool awaiting;                          //a single byte wasted for purpose of UnLayered Nets - this bool indicates if this particular neuron has its output ready to be processed by other neurons. Defaults to 0 in feed-forward
    bool awaitingPrevious();                //returns true if there are any awaiting neurons in inputs.

    double getOutput() const {return _output;}

    void overWriteWeights(vector<double> newWeights);

    virtual void calculateOutput();

    friend Layer;

protected:
    double (*_transferFcn)(double);
    bool _receivesInput;
    vector<Link> _inputs;
    double _bias;

    double _output;
};

struct Link{            //a reversed arrow pointer, also functions as a link between two neurons.
    Link(Neuron* to, double weight): _weight(weight), _to(to) {}
    double _weight;
    Neuron* _to;
};