#include<bits/stdc++.h>
using namespace std;

void printVec(vector<vector<char> >& board);

void playerMove(vector<vector<char> >& board, bool played);

bool legalMove(vector<vector<char> >& board, int y, int x);

int computerMove(vector<vector<char> >& board, char c, int& goodY, int& goodX);

int getRandom(int except);

bool isTie(vector<vector<char> >& board);

bool findStrike(vector<vector<char> >& board, int& chekStrikeY, int& chekStrikeX);

void tie(vector<vector<char> >& board);

void lose(vector<vector<char> >& board);

void game(vector<vector<char> >& board);

int main(){
    vector<vector<char> > board;

    //filling playing board with dots
    for(int i = 0; i < 3; i++){
        vector<char> curRow;
        for (int j = 0; j < 3; j++){
            curRow.push_back('.');
        }
        board.push_back(curRow);      
    }

    cout << "this is tic-tac-toe game" << endl;
    cout << "please fill in first, or second" << endl;
    string s;
    /*s must be "first" or "second" 
    fill in "first" to make first move, "second" to make second move */
    cin >> s;

    while (s != "first" && s != "second")
    {
        cout << "invalid text" << endl;
        cin >> s;
    }

    cout << "this is starting board";    printVec(board);

    if(s == "first"){
        playerMove(board, false);
        bool isX = false;

        for(int i = 0; i <= 2; i += 2){
            for(int j = 0; j <= 2; j += 2){
                if(board[i][j] == 'X'){
                    board[1][1] = 'O';
                    isX = true;
                    break;
                }
            }
        }

        if(!isX){

            if(board[1][1] == 'X'){
                int row, col;
                row = getRandom(1);
                col = getRandom(1);

                board[row][col] = 'O'; 
                isX = true;
            }
            if(!isX){
                //if x = 1
                if(board[0][1] == 'X' || board[2][1] == 'X'){
                    int y1 = board[0][1] == 'X'? 0 : 2;

                    int y = getRandom(-1), x;

                    if(y == y1)x = getRandom(1);
                    else x = 1;
                    board[y][x] = 'O';
                }
                //if y = 1
                else if(board[1][0] == 'X' || board[1][2] == 'X'){
                    int x1 = board[1][0] == 'X'? 0 : 2;

                    int x = getRandom(-1), y;

                    if(x == x1)y = getRandom(1);
                    else y = 1;
                    board[y][x] = 'O';
                }
            }
        }
        playerMove(board, true);
    }
    else{
        int row, col;
        row = getRandom(-1);
        col = getRandom(-1);
       
        board[row][col] = 'O';
        playerMove(board, true); 
    }

    game(board);
    
}


void printVec(vector<vector<char> >& board){
    cout << endl;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

void playerMove(vector<vector<char> >& board, bool played){
    if(played){
        cout << endl << "board after computers move is:";    
        printVec(board);
    }

    cout << "make a move" << endl;
    /* to make a move you need to fill int row first and colum secondly */
    int row, col;
    cin >> row >> col;

    bool isLegal = legalMove(board, row, col);

    while(!isLegal){
        cout << "it is illegal move" << endl  << "repeat again" << endl;
        cin >> row >> col;

        bool isLegal = legalMove(board, row, col);
        if(isLegal)break;
    }

    board[row][col] = 'X';
    cout << "board after your move is:";    printVec(board);
}

bool legalMove(vector<vector<char> >& board, int y, int x){
    bool isLegal = false;

    if(x >= 0 && x < 3 && y >= 0 && y < 3 && board[y][x] == '.')isLegal = true;

    return isLegal;
}

int getRandom(int except){

    int r;
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist6(0,2);
    
    r = dist6(rng);

    while(r == except){
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<std::mt19937::result_type> dist6(0,2);
    
        r = dist6(rng);
    }
    return r;
}

int computerMove(vector<vector<char> >& board, char c, int& goodY, int& goodX){
    if(isTie(board))return 0;

    int y = -1, x = -1;
    char nextC = c == 'O'? 'X': 'O';
    if(findStrike(board, y, x)){
        if(board[y][x] == nextC)return -1;
        if(board[y][x] == c)return 1;
    }
    int ans = -1;
    int ry, ry1, ry2, rx, rx1, rx2;

    ry = getRandom(-1);
    ry1 = getRandom(ry);
    ry2 = 3 - ry1 - ry;

    stack<int> itrY;  
    itrY.push(ry); itrY.push(ry1); itrY.push(ry2);

    while(!itrY.empty()){
        int tmpY = itrY.top();   itrY.pop();

        rx = getRandom(-1);
        rx1 = getRandom(rx);
        rx2 = 3 - rx1 - rx;

        stack<int> itrX;  
        itrX.push(rx); itrX.push(rx1); itrX.push(rx2);
        
        while(!itrX.empty()){
            int tmpX = itrX.top();     itrX.pop();
            if( legalMove (board, tmpY, tmpX) ){
                board[tmpY][tmpX] = c;
                y = x = -1;
                int preAns = computerMove(board, nextC, y, x);

                if(preAns == 0){
                    goodY = tmpY;
                    goodX = tmpX;
                    ans = 0;
                } 
                else if(preAns == -1){
                    goodY = tmpY;
                    goodX = tmpX;
                    board[tmpY][tmpX] = '.';
                    return 1;
                } 
                board[tmpY][tmpX] = '.';   
            }
        }
    }
    return ans;
}

bool findStrike(vector<vector<char> >& board, int& chekStrikeY, int& chekStrikeX){

    for(int i = 0; i < 3; i++){
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
            if(board[i][1] != '.'){
                chekStrikeY = i;  chekStrikeX = 1;
                return true;
            }
        }
    }
    
    for(int i = 0; i < 3; i++){
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i]){
            if(board[1][i] != '.'){
                chekStrikeY = 1;  chekStrikeX = i;
                return true;
            }
        }
    }
    

    if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        if(board[1][1] != '.'){
            chekStrikeX = chekStrikeY = 1;
            return true;
        }
    }

    if(board[2][0] == board[1][1] && board[1][1] == board[0][2]){
        if(board[1][1] != '.'){
            chekStrikeX = chekStrikeY = 1;
            return true; 
        }
    }

    return false;
}

bool isTie(vector<vector<char> >& board){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == '.'){
                return false;
            }
        }
    }
    return true;
}

void tie(vector<vector<char> >& board){
    cout << "Game is finished" << endl << "this is how board looks like:" << endl;
    printVec(board);
    cout << "Good Game <3" << endl << "you manage to make tie  (: " << endl;
    exit(0);
}

void lose(vector<vector<char> >& board){
    cout << "Game is finished" << endl << "this is how board looks like" << endl; 
    printVec(board);
    cout <<  "Good Game <3, but..." << endl <<"YOU LOSE" << endl;
    exit(0);
}

void game(vector<vector<char> >& board){
    int goodY = -1, goodX = -1;
    while(!isTie(board)){
        computerMove(board, 'O', goodY, goodX);
        board[goodY][goodX] = 'O';

        if(isTie(board)){
            tie(board);
        }

        int chekStrikeY = -1, chekStrikeX = -1;
        if(findStrike(board, chekStrikeY, chekStrikeX)){
            lose(board);
        }

        playerMove(board, true);
        if(isTie(board)){
            tie(board);
        }
    }
}


