/* Quite an imporant note:
 * This is an implementation of modified NEAT evolutionary algorithm aimed to train in simple board games. 
 * NEAT algorithm is  primarly created and developed by Ken Stanley (The University of Texas at Austin).
 * This particular approach uses 2048 game to test its efficiency, which is created by Gabriele Cirulli 
 * and distributed under MIT license. As MIT licence requires the mentioning of the author, here it is.
 * 
 * Feel free to use this particular approach, as long as you mention me.
 * 
 * Praise Omnissiah.
 */

#include"neuralib.hpp"
#include"neat.hpp"
#include"G2048.hpp"
#include<iostream>

using std::cout;
using std::endl;

vector<Specimen*> NumericalRoulette2048(vector<Specimen*> specimens,double){
    vector<Specimen*> target;
    vector<int> evals;
    for(auto& i : specimens){
        Game2048 game(4);
        UnLayeredNet net = (UnLayeredNet)(*i);

        for(int iter = 0; iter<10; iter++){         //1000 = max allowed iterations, for sake of safety
            cout << endl << "ITER" << iter << endl;

            vector<int> board = game.getGameState();
            vector<double> dboard;
            for(auto& j : board) dboard.push_back((double)j);
            vector<double> out = net.calculateOutput(dboard);
            int maxIndex = 0;
            for(uint j = 0; j<out.size(); j++) if(out[j]>out[maxIndex]) maxIndex = j;
            if(!game.move(maxIndex)) break;
            game.printBoard();
        }
        int eval = game.evaluate() + 1;     //+1 is to eliminate zeros
        evals.push_back(eval);
    }

    int sum = 0;
    for(auto& i : evals) sum+=i;

    //actual roulette wheel:
    for(uint i = 0; i<specimens.size(); i++){
        int random = randomInt(0,sum);
        int check = 0;
        int currentPlace = 0;
        while(check<random){
            check+=evals[currentPlace];
            currentPlace++;
        }
        target.push_back(new Specimen(*(specimens[currentPlace])));
    }
    return target;
}


int main(){

    srand(time(NULL));

    cout << "- - - - - - - - - - - - -" << endl << "! PROGRAM STARTED SUCCESFULLY !" << endl << "- - - - - - - - - - - - -" << endl;

    Population pop(50,100,16,4,NumericalRoulette2048);
    //pop.Step();

//GAME TEST!!!!
    Game2048 test (4);
    test.printBoard();
    while(true){
        int c;
        cin >> c;
        test.move(c);
        test.printBoard();
    }
//END GAME TEST
    cout << "- - - - - - - - - - - - -" << endl << "! PROGRAM REACHED THE END !" << endl << "- - - - - - - - - - - - -" << endl;

    return 0;
};