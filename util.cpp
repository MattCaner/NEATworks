#include"util.hpp"

double HardLim(double input){
    if(input>0) return 1;
    else return 0;
}

double LogSig(double input){
    return 1/(1+exp(-1*input));
}

double TanSig(double input){
    return 2/(1+exp(-2*input))-1;
}

double randomDouble(double lowlimit,double uplimit){
    double f = (double)rand() / RAND_MAX;
    return lowlimit+f*(uplimit - lowlimit);
}

int randomInt(int lowlimit, int uplimit){
    return rand()%(uplimit-lowlimit)+lowlimit;
}