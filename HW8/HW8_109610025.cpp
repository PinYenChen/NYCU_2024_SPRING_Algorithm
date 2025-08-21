#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <deque>
#include <queue>

using namespace std;

int number = 0;

struct Node {
    int x;
    int y;
    int value; //0 wall, 1 road, 2 trap
    int color; //3 white, 4 gray, 5 black
    Node* parent = nullptr; //establish a pointer toward parent
    int distance = INT_MAX;
    Node(int x=0, int y=0 , int val=0, int color=0,int dis = INT_MAX) : x(x), y(y), value(val), color(color), distance(dis) {}
    //the initialization of a Node
};

void print_path(ofstream& outfile, Node s, Node v, int step,int step_on_2){
    if (s.x == v.x && v.y == s.y){  //represent v go to s
        outfile<<"step="<<step<<endl;
        outfile<<"("<<s.x<<","<<s.y<<")"<<endl;
    }
    else if (v.parent == nullptr){
        outfile<<"there is no road!"<<endl;
    }
    else{
        if (v.value==2) step_on_2++;
        step+=v.value; //確定可以走再加上步數
        print_path(outfile,s,*(v.parent),step,step_on_2);
        outfile<<"("<<v.x<<","<<v.y<<")"<<endl;
    } 
}

void bfs(vector<vector<int>>& matrix, ofstream &outfile){
    vector<vector<Node>> map(19, vector<Node>(19)); //such that the point start from (1,1) and end of (17,17)
    for (int i=0;i<19;i++){
        for (int j=0;j<19;j++){
            if (i==0 || j==0 || i==18 ||j==18){ 
                map [i][j] = Node(i,j,0,5,INT_MAX);
            }
            else{
                map[i][j] = Node(i,j,matrix[i-1][j-1],3,INT_MAX);
            }
        }
    }
    //end of initialize of the matrix

    map[1][1].color = 4;
    map[1][1].distance = 0;

    queue <Node> nodequeue; //establish a queue that is like Node
    nodequeue.push(map[1][1]); //把第一點放進去

    while(!nodequeue.empty()){ //while nodequeue is not empty, exploit further
        //implement the action of deque
        Node discover = nodequeue.front();
        nodequeue.pop();

        //start to find up down left right possible road
        Node transient = Node(discover.x-1,discover.y,map[discover.x-1][discover.y].value, map[discover.x-1][discover.y].color, INT_MAX);
        if (transient.value!=0 &&  transient.color==3){ //能加進去只能在該點為有效範圍內以及不是牆以及沒被探索過
            map[discover.x-1][discover.y].color = 4;
            map[discover.x-1][discover.y].distance = discover.distance+1;
            map[discover.x-1][discover.y].parent = &map[discover.x][discover.y];
            nodequeue.push(map[discover.x-1][discover.y]);
        }//up
        transient = Node(discover.x+1,discover.y,map[discover.x+1][discover.y].value, map[discover.x+1][discover.y].color, INT_MAX);
        if (transient.value!=0 &&  transient.color==3){ //能加進去只能在該點為有效範圍內以及不是牆以及沒被探索過
            map[discover.x+1][discover.y].color = 4;
            map[discover.x+1][discover.y].distance = discover.distance+1;
            map[discover.x+1][discover.y].parent = &map[discover.x][discover.y];
            nodequeue.push(map[discover.x+1][discover.y]);
        }//down
        transient = Node(discover.x,discover.y+1,map[discover.x][discover.y+1].value, map[discover.x][discover.y+1].color, INT_MAX);
        if (transient.value!=0 &&  transient.color==3){ //能加進去只能在該點為有效範圍內以及不是牆以及沒被探索過
            map[discover.x][discover.y+1].color = 4;
            map[discover.x][discover.y+1].distance = discover.distance+1;
            map[discover.x][discover.y+1].parent = &map[discover.x][discover.y];
            nodequeue.push(map[discover.x][discover.y+1]);
        }//right
        transient = Node(discover.x, discover.y-1, map[discover.x][discover.y-1].value, map[discover.x][discover.y-1].color, INT_MAX);
        //cout<<transient.value<<" and "<< transient.color<<endl;
        if (transient.value!=0 &&  transient.color==3){ //能加進去只能在該點為有效範圍內以及不是牆以及沒被探索過
            map[discover.x][discover.y-1].color = 4;
            map[discover.x][discover.y-1].distance = discover.distance+1;
            map[discover.x][discover.y-1].parent = &map[discover.x][discover.y];
            nodequeue.push(map[discover.x][discover.y-1]);
        }//left
        map[discover.x][discover.y].color = 5; //end of discovery            
    }
    int step = 0; //每點要開始記步之前先設為零
    int step_on_2 = 0; //計算trap的數量
    print_path(outfile,map[1][1],map[17][17],step,step_on_2);
    outfile<<endl; //換下一個迷宮
}

void readMatrix(const string &filename, ofstream &outfile) {
    ifstream infile(filename);
    if (!infile) {
        cerr<<"cannot read the input file "<<filename<<endl;
        return;
    }
    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue; // 跳過空行

        vector<vector<int>> matrix(17, vector<int>(17));
        bool error=false;
        for (int i=0; i<17; i++) {
            if (i > 0) {
                if (!getline(infile, line) || line.empty()) {
                    error = true;
                    break;
                }
            }
            stringstream ss(line);
            for (int j=0; j<17; j++) {
                if (!(ss >> matrix[i][j])) {
                    error = true;
                    break;
                }
            }
        }
        if (error) {
            cerr<< "error while reading the input file" << endl;
            return;
        }
        number++;
        //for check
        /*
        cout<<pattern<<endl;
        for (int i=0;i<17;i++){
            for (int j=0;j<17;j++){
                cout<<matrix[i][j]<<"\t";
            }
            cout<<endl;
        }*/
        outfile<<"pattern "<<number<<endl;
        //進入迷宮演算法
        bfs(matrix, outfile);

        // Skip the empty line after the matrix 要不然會讀到空格 所以先讀一行空格
        getline(infile, line);
    }
    infile.close();
}

int main() {
    string filename = "input.txt"; // Replace with your filename
    // Create and open the output file stream
    ofstream outfile("109610025_output.txt", ios_base::app);
    if (!outfile) {
        cerr<< "cannot open output file" << endl;
        return 1;
    }
    readMatrix(filename, outfile);
    outfile.close();

    return 0;
}