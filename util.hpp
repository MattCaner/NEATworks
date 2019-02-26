#pragma once
#include<vector>
#include<cmath>
#include<cstdlib>
using namespace std;


//UTILITY FUNCTIONs:

inline double randomDouble(double lowlimit,double uplimit);
inline int randomInt(int lowlimit, int uplimit);

//TRANSFER FCNs:

double HardLim(double input);       //Hardlim transfer function
double LogSig(double input);        //Logsig transfer function
double TanSig(double input);        //Tansig transfer function

