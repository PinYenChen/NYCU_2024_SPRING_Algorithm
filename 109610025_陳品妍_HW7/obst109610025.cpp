#include <bits/stdc++.h>
#include <time.h>
#include <cstdlib>
using namespace std;

void obst(vector<vector<float>>& e, vector<vector<float>>& w, vector<vector<int>>& root, int n, float p[], float q[]){
    for(int i=1;i<=n+1;i++){
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }
    for (int l=1;l<=n;l++){
        for (int i=1;i<=n-l+1;i++){
            int j = i+l-1;
            e[i][j] = FLT_MAX;
            w[i][j] = w[i][j-1] +p[j] +q[j];
            for (int r = i ;r<=j;r++){
                float t = e[i][r-1]+e[r+1][j]+w[i][j];
                if (t<e[i][j]){
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
}

void printOBST(vector<vector<int>>& root, int i, int j, int depth=0, char indication='R') {
    if (i<=j) { //if i==j stop the recursion
    
        for (int k=0;k<depth; k++){
            cout << "   "; // with depth increasing, display more space
        } 
        cout << indication << "-" << root[i][j] << endl; //represent from i to j optimal solution(cut site)
        //以root為分界，個別處理左邊以及右邊 先顯示左邊
        printOBST(root,i,root[i][j]-1,depth+1,'L'); //address the left side node from i to root[i][j]-1
        printOBST(root,root[i][j]+1,j,depth+1,'R'); //address the right side node from root[i][j] to j
    }
}

int main(int argc, char** argv){

    int n ;
    cout<<"please input the n : "; // n is the length of the elements
    cin>>n;
    
    float *p;
    float *q;
    p = new float [n+1];
    q = new float [n+1];
    cout<<"please input the p (p1,p2,p3...pn): ";

    for (int i=1;i<=n;i++){
        cin>>p[i];
    }
    // cout<<endl<<"the p are : "<<endl;
    // for (int i=1;i<n;i++){
    //     cout<<p[i]<<"\t";
    // }

    cout<<"please input the q (q0,q1,q2...qn): ";
    for (int i=0;i<=n;i++){
        cin>>q[i];
    }    
    vector<vector<float>> e(n + 2, vector<float>(n+1,0));
    vector<vector<float>> w(n + 2, vector<float>(n+1,0));
    vector<vector<int>> root(n + 1, vector<int>(n+1,0));

    obst(e,w,root,n,p,q);

    cout<<"the smallest cost is: "<<e[1][n]<<endl;
    cout<<"root is : "<<root[1][n]<<endl;
    printOBST(root,1,n); //印出1到n的optimal binary search tree
    delete[]p;
    delete[]q;

}