#include<bits/stdc++.h>
using namespace std;

bool sudoko(int ** a, int x, int y) {
    if(x == 9 ) {
        return true;
    }
    if(y == 9) {
        return sudoko(a, x + 1, 0);
    }
    if(a[x][y] != 0) {
        return sudoko(a, x, y + 1);
    }
    bool *visited = new bool[10];
    for(int i = 0; i< 10; i++) {
        visited[i] = false;
    }
    for(int i = 0; i < 9; i++) {
        if(a[x][i] != 0) {
            visited[a[x][i]] = true;
        }
        if(a[i][y] != 0) {
            visited[a[i][y]] = true;
        }
    }
    int c = x % 3;
    int b = y % 3;

    for(int i = x - c; i < x - c + 3; i++) {
        for(int j = y - b ; j< y -b +3; j++) {
            if(a[i][j] != 0) {
                visited[a[i][j]] = true;
            }
        }
    }
    bool check = false;
    for(int i = 1; i < 10; i++) {
        if (!visited[i]) {
            a[x][y] = i;
            check = sudoko(a, x, y + 1);
            if (check) {
                break;
            }
            a[x][y] = 0;
        }
        
    }
    return check;
}

bool rightcrossword(vector<vector<char>> &v, string word, int row, int col, int size){
    int n = word.size();
    bool canfit = true;
    int j, k ;
    for( j = col, k = 0; k < n && j < size; k++,j++) {
        if(v[row][j] == '+' || (v[row][j] != '-' && v[row][j] != word[k])) {
            canfit = false;
            break;
        }
    }
    if(k < n) {
        canfit = false;
    }
    if (canfit) {
        for(int j = col, k = 0; k <  n; k++, j++) {
            v[row][j] = word[k]; 
        }
        return true;
    } else {
        return false;
    }
}
bool downcrossword(vector<vector<char>> &v, string word, int row, int col, int size) {
    int n = word.size();
    bool canfit = true;
    int i, k ;
    for(i = row, k = 0;k < n && i < size; k++,i++) {
        if(v[i][col] == '+' || (v[i][col] != '-' && v[i][col] != word[k])) {
            canfit = false;
            break;
        }
    }
    if( k < n ) {
        canfit = false;
    }
    if (canfit) {
        for(int i = row, k = 0; k < n; k++, i++) {
            v[i][col] = word[k]; 
        }
        return true;
    } else {
        return false;
    }
}
void makeminus(vector<vector<char>> &v, string word, bool right, int row, int col) {
    int n = word.size();
    if(right) {
        for(int j = col; j < col + n; j++) {
            v[row][j] = '-';
        }
    } else {
        for(int i = row; i < row + n; i++) {
            v[i][col] = '-';
        }
    }
    return;
}
bool fillcrossword(vector<vector<char>> &v, vector<string> &words, int k, int size) {
    if(k == words.size()) {
        return true;
    }
    bool rightfitted = false, downfitted = false, next = false;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(v[i][j] == '-' || v[i][j] == words[k][0]) {
                rightfitted = rightcrossword(v, words[k], i, j, size);
                if(!rightfitted) {
                    downfitted = downcrossword(v, words[k], i, j, size);
                }
                if(rightfitted || downfitted)  {
                    next = fillcrossword(v, words, k + 1, size);
                    if(next){
                        return true;
                    } else {
                        makeminus(v, words[k], rightfitted, i, j);
                        rightfitted = false;
                        downfitted = false;
                    }
                }
            }
        }
    }
    return false;
}

int main(){
    
    cout<<"Hello! Welcome to Puzzle Solver"<<endl;
    cout<<"*************MENU*************"<<endl;
    cout<<"To solve SUDOKU -> ENTER 1"<<endl;
    cout<<"To solve CROSSWORD PUZZLE -> ENTER 2"<<endl;
    cout<<"To EXIT! -> ENTER 0"<<endl;

    int choice;
    cin>>choice;

    if(choice == 2) {
        cout<<"Enter The size of the CrossWord Grid(square martix)"<<endl;
        int size;
        cin>>size;
            vector<vector<char>> v(size);
            char c;
            vector<char> v1;
            cout<<"Now Enter the puzzle grid (Enter Blank spaces as '+' and solution spaces as '-')"<<endl;
            for(int i = 0; i < size; i++) {
                for(int j = 0; j < size; j++) {
                    cin>>c;
                    v1.push_back(c);
                }
                v[i] = v1;
                v1.clear();
            }
            cout<<"Now enter the number of words to be filled "<<endl;
            int n;
            cin>>n;
            string s = "";
            vector<string> words;
            for(int i = 0; i < n; i++) {
                cout<<"word"<<i+1<<":";
                cin>>s;
                words.push_back(s);
                s = "";
            }
            bool use = fillcrossword(v, words, 0, size);
                if(use){
                    cout<<"HURREH! solved!\nHere is your solution\n";
                    for(int i = 0 ; i < size; i++) {
                        for(int j = 0 ; j < size; j++){
                            cout<<v[i][j];
                        }
                        cout<<endl;
                    }
                } else {
                    cout<<"Entered crossword puzzle cannot be solved for the given set of words";
                }
    }
    else if(choice == 1){
        cout<<"Let's Solve Sudoku"<<endl;
        cout<<"****INSTRUCTIONS***"<<endl;
        cout<<"\t> Sudoku must be 9*9 matrix"<<endl;
        cout<<"\t> All the blank spaces must replaced by '0'"<<endl;
            int** a = new int*[9];
            for(int i = 0; i< 9; i++) {
                a[i] = new int[9];
                for(int j = 0; j< 9; j++) {
                    cin>>a[i][j];
                }
            }
            bool shouldprint = sudoko(a,0,0);
            if(shouldprint) {
                cout<<"Hurreh! Solved \nHere is you're solution\n";
                for(int i = 0; i< 9; i++) {
                    for(int j = 0; j< 9; j++) {
                        cout<<a[i][j]<<" ";
                    }
                    cout<<endl;
                }   
            } else {
                cout<<"The given SUDOKU can not be solved";
            }
    }
    return 0;
}