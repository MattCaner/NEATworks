#include"neuralib.hpp"

class Population{
public:
    Population(int size, int epochs, int inSize, int outSize);
    void Step();
    Specimen Evaluate();
    
protected:
    int _popsize;
    int _epoch;
    int _maxepochs;
    void Select();
    void Breed();
    void Mutate();
    double _breedingCoefficient;
    double _nodeMutation;
    double _connectionMutation;

    int innovationMeter_;

    vector<Specimen*> _popTable;
    vector<Specimen*> _winnerTable;
};


class Specimen{         //Class for a single 1-chromosome NEAT specimen that consists of node and connection genes.
public:
    Specimen(int inputs, int outputs);
    explicit operator UnLayeredNet();

    Specimen& mutateNode(int innovation);   //adds 3 to innovation number
    Specimen& mutateLink(int innovation);   //adds 1 to innovation number

    Specimen& addNode(int prev, int next);
    Specimen& addConnection(int nodeFrom, int nodeTo, double weight);
    Specimen& switchConnection(int nodeFrom, int nodeTo, bool state);
    
    int getLowestInnovation() const;
    int getHighestInnovation() const;


    friend Specimen NEATbreeding(Specimen& s1, Specimen& s2);

protected:
    int _largestNodeIndex;
    int _inSize;
    int _outSize;
    vector<NodeGene*> _nodes;
    vector<ConnectionGene*> _connections;
};


Specimen NEATbreeding(Specimen& s1, Specimen& s2);


class NodeGene{
public:
    NodeGene(int identifier, int innovation);
    NodeGene() = default;
    int getInnovation() const {return _innovation;}

protected:
    int _identification;
    int _innovation;
};

class ConnectionGene{
public:
    ConnectionGene(int inID, int outID, double weight, int innovation);
    ConnectionGene() = default;
    int getInnovation() const {return _innovation;}
    int getIn() const {return _inID;}
    int getOut() const {return _outID;}
protected:
    int _inID;
    int _outID;
    double _weight;
    bool _enabled;
    int _innovation;
};

