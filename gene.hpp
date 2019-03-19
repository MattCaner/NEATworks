#pragma once
#include"util.hpp"

class NodeGene{
public:
    NodeGene(int identifier, int innovation): _identification(identifier), _innovation(innovation) { }
    NodeGene() = default;
    ~NodeGene() = default;
    NodeGene(const NodeGene& ng) = default;
    int getInnovation() const {return _innovation;}
protected:
    int _identification;
    int _innovation;
};

class ConnectionGene{
public:
    ConnectionGene(int inID, int outID, double weight, int innovation): _inID(inID), _outID(outID), _weight(weight), _enabled(true), _innovation(innovation) {}
    ConnectionGene() = default;
    ~ConnectionGene() = default;
    ConnectionGene(const ConnectionGene& cg) = default;
    int getInnovation() const {return _innovation;}
    int getIn() const {return _inID;}
    int getOut() const {return _outID;}
    double getWeight() const {return _weight;}
protected:
    int _inID;
    int _outID;
    double _weight;
    bool _enabled;
    int _innovation;
};

