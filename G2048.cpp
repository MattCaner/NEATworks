#include"G2048.hpp"


Game2048::Game2048(int boardSize): _bsize(boardSize){
    for(int i = 0; i<_bsize*_bsize; i++){
        _board.push_back(0);
    }
    int rand1 = randomInt(0,_bsize*_bsize-1);
    int rand2 = randomInt(0,_bsize*_bsize-2);
    if(randomDouble(0.0,1.0)>0.75) _board[rand1] = 2;
    else _board[rand1] = 4;
    _board[this->emptyFieldNumbers()[rand2]] = 2;
}

vector<int> Game2048::emptyFieldNumbers(){
    vector<int> tmp;
    for(int i = 0; i<_bsize*_bsize; i++){
        if(_board[i]==0) tmp.push_back(i);
    }
    return tmp;
}

bool Game2048::move(int m){
    switch(m)
    {
        case 0:                     
        cout << "CASE0" << endl;
        for(int i = 0; i<_bsize*_bsize; i++){
            if(i<_bsize) continue;
            if(_board[i-_bsize]==0){    // target field is empty -> move this block
                _board[i-_bsize]=_board[i];
                _board[i] = 0;
            }
            if(_board[i-_bsize]==_board[i]){        // target field has the same number then -> consolidate blocks
                _board[i-_bsize]=_board[i]*2;
                _board[i] = 0;
                _points += _board[i-_bsize];
            }
            if(_board[i-_bsize]!=_board[i]&&_board[i-_bsize]!=0){       //target field cannot be moved
                //?
            }
        }
        break;
        case 1:
        cout << "CASE1" << endl;
        for(int i = 0; i<_bsize*_bsize; i++){
            if(i>=_bsize*(_bsize-1)) continue;
            if(_board[i+_bsize]==0){    // target field is empty -> move this block
                _board[i+_bsize]=_board[i];
                _board[i] = 0;
            }
            if(_board[i+_bsize]==_board[i]){        // target field has the same number then -> consolidate blocks
                _board[i+_bsize]=_board[i]*2;
                _board[i] = 0;
                _points += _board[i+_bsize];
            }
            if(_board[i+_bsize]!=_board[i]&&_board[i+_bsize]!=0){       //target field cannot be moved
                //?
            }
        }
        break;
        case 2:
        cout << "CASE2" << endl;
        for(int i = 0; i<_bsize*_bsize; i++){
            if(i%_bsize==_bsize-1) continue;
            if(_board[i-_bsize]==0){    // target field is empty -> move this block
                _board[i+1]=_board[i];
                _board[i] = 0;
            }
            if(_board[i+1]==_board[i]){        // target field has the same number then -> consolidate blocks
                _board[i+1]=_board[i]*2;
                _board[i] = 0;
                _points += _board[i+1];
            }
            if(_board[i+1]!=_board[i]&&_board[i+1]!=0){       //target field cannot be moved
                //?
            }
        }
        break;
        case 3:
        cout << "CASE3" << endl;
        for(int i = 0; i<_bsize*_bsize; i++){
            if(i%_bsize==0) continue;
            if(_board[i-1]==0){    // target field is empty -> move this block
                _board[i-1]=_board[i];
                _board[i] = 0;
            }
            if(_board[i-1]==_board[i]){        // target field has the same number then -> consolidate blocks
                _board[i-1]=_board[i]*2;
                _board[i] = 0;
                _points += _board[i-1];
            }
            if(_board[i-1]!=_board[i]&&_board[i-1]!=0){       //target field cannot be moved
                //?
            }
        }
        break;
    }
    //Check empty fields
    vector<int> tmp = emptyFieldNumbers();
    if(tmp.size()<2) return false;  // game over!
    else{
        cout << "size:" <<  tmp.size() << endl;
        int rand = randomInt(0,tmp.size()-1);
        cout << "rand:" << rand << endl;
        if(randomDouble(0.0,1.0)>0.75) _board[tmp[rand]] = 2;
        else _board[rand] = 4;
        tmp = emptyFieldNumbers();
        rand = randomInt(0,tmp.size()-1);
        _board[tmp[rand]] = 2;
        return true;
    }
}

void Game2048::printBoard(){
    for(int i = 0; i<_bsize; i++){
        for(int j = 0; j<_bsize; j++) cout << " " << _board[i*_bsize+j] << " ";
        cout << endl;
    }
    cout << endl;
}