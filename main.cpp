#include"neuralib.hpp"
#include<iostream>


int main(){
    vector<double> w {2.2,0.3};
    vector<double> g {1,0.2,1.5,1,1,1};
    vector<int> emptyVector;

    FeedForwardNet net = FeedForwardNet(2,2,emptyVector,TanSig);
    net.getOutputLayer()->setWeitghts(g);

    vector<double> wynik = net.calculateOutput(w);
    cout<<wynik[0]<<"  "<<wynik[1]<<endl;

    std::cout<<"\\o/ Program runs! \\o/\n";
    return 0;
};