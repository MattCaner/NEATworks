#pragma once
#include"gene.hpp"
#include"neuralib.hpp"

class Specimen{         //Class for a single 1-chromosome NEAT specimen that consists of node and connection genes.
public:
    Specimen(int inputs, int outputs, bool fullconnect = false, int innovation = 0);      //general use constructor. If fullconnect is true, creates a dense link net between in and out.
    Specimen(const Specimen& s);                                                          //copy construcotr
    Specimen(const Specimen& s1, const Specimen& s2);                                     //breeding constructor
    ~Specimen();
    Specimen& operator=(const Specimen& s);                                              //assignment operator
    

    explicit operator UnLayeredNet();       //conversion to UnLayered Neural Network

    Specimen& mutateNode(int innovation);   //adds 3 to innovation number
    Specimen& mutateLink(int innovation);   //adds 1 to innovation number

    Specimen& addNode(int prev, int next);                              //adds a node between two other nodes
    Specimen& addConnection(int nodeFrom, int nodeTo, double weight);   //adds a connection between two given nodes
    Specimen& switchConnection(int nodeFrom, int nodeTo, bool state);   //enables/disables connection

    int getLowestInnovation() const;                //returns the oldest innovation number
    int getHighestInnovation() const;               //returns the newest innovation number

    friend Specimen NEATbreeding(const Specimen& s1, const Specimen& s2);

protected:
    int _largestNodeIndex;
    int _inSize;
    int _outSize;
    vector<NodeGene*> _nodes;
    vector<ConnectionGene*> _connections;
};

Specimen NEATbreeding(const Specimen& s1, const Specimen& s2); 