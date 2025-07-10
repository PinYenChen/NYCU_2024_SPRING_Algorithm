#include <bits/stdc++.h>
#include <time.h>
#include <cstdlib>
using namespace std;
void lcslength(vector<vector<vector<int>>>& b, vector<vector<vector<int>>>& c, double x[], double y[],double z[],int x_length,int y_length,int z_length){
    for (int i = 0; i <= x_length; i++) { //initialization of the c plane
        for (int j = 0; j <= y_length; j++) {
            for (int k = 0; k <= z_length; k++) {
                if (i == 0 || j == 0 || k == 0) {
                    c[i][j][k] = 0;
                }
            }
        }
    }
    for (int i=1;i<=x_length;i++){
        for (int j=1;j<=y_length;j++){
            for (int k=1;k<=z_length;k++){ //check every element of x,y,z
                if (x[i] == y[j] && x[i] == z[k]){
                    c[i][j][k] = c[i-1][j-1][k-1]+1;
                    b[i][j][k] = 1; //1 represent up-left-back
                }
                else if(c[i-1][j][k]>=c[i][j-1][k] && c[i-1][j][k]>=c[i][j][k-1]){
                    c[i][j][k] = c[i-1][j][k];
                    b[i][j][k] = 2; //2 represent answer from up(i-1)
                }
                else if (c[i][j-1][k]>=c[i-1][j][k] && c[i][j-1][k]>=c[i][j][k-1]){
                    c[i][j][k] = c[i][j-1][k];
                    b[i][j][k] = 3; //3 represent answer from up(j-1)
                }
                else if (c[i][j][k-1]>=c[i-1][j][k] && c[i][j][k-1]>=c[i][j-1][k]){
                    c[i][j][k] = c[i][j][k-1];
                    b[i][j][k] = 4; //3 represent answer from up(k-1)
                }
            }
        }
    }    
}
void printlcs(vector<vector<vector<int>>>& b,double x[], int i,int j,int k){
    if (i == 0 or j == 0 or k == 0){
        return;
    }
    if (b[i][j][k] == 1){ //print the lcs sequence
        printlcs(b,x,i-1,j-1,k-1);
        cout<<x[i]<<"\t";
    }
    else if (b[i][j][k] == 2){
        printlcs(b,x,i-1,j,k);
    }
    else if (b[i][j][k] == 3){
        printlcs(b,x,i,j-1,k);
    }
    else if (b[i][j][k] == 4){
        printlcs(b,x,i,j,k-1);
    }
}

int main(int argc,char** argv){
    double *x;
    int x_length;
    cout<<"please enter array size of x : ";
    cin>>x_length;
    cout<<"please input a sequence x : ";
    x =new double [x_length+1];
    
    for (int i=1;i<=x_length;i++){
        cin>>x[i];
    }
    
    // cout<<"this is a for check : \n";
    // for (int i=0;i<x_length;i++){
    //     cout<<x[i]<<"\t";
    // }

    double *y;
    int y_length;
    cout<<"please enter array size of y : ";
    cin>>y_length;
    cout<<"please input a sequence y : ";
    y =new double [y_length+1];
    
    for (int i=1;i<=y_length;i++){
        cin>>y[i];
    }

    double *z;
    int z_length;
    cout<<"please enter array size of z : ";
    cin>>z_length;
    cout<<"please input a sequence z : ";
    z =new double [z_length+1];
    
    for (int i=1;i<=z_length;i++){
        cin>>z[i];
    }
    //construct the vector of b and c
    vector<vector<vector<int>>> b(x_length+1, vector<vector<int>>(y_length+1, vector<int>(z_length+1)));
    vector<vector<vector<int>>> c(x_length+1, vector<vector<int>>(y_length+1, vector<int>(z_length+1)));

    lcslength(b,c,x,y,z,x_length,y_length,z_length);
    cout << "The length of the LCS is: " << c[x_length][y_length][z_length] << endl;
    cout<<"sequence w is: "<<endl;
    printlcs(b,x,x_length,y_length,z_length);
    

    delete[] x;
    delete[] y;
    delete[] z;
    //delete the dynamic array
}