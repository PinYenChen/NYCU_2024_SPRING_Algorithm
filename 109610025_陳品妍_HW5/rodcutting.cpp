#include <bits/stdc++.h>
#include <time.h>
#include <cstdlib>
using namespace std;
int memoCutRodAux(int p[],int n,int r[],int s[]){
    if (r[n] >=0){
        return r[n];
    }
    else{
        int q;
        q = INT_MIN; // initialize q
        for (int i=1;i<=n;i++){
            if (q<p[i]+memoCutRodAux(p,n-i,r,s)){
                q = p[i]+memoCutRodAux(p,n-i,r,s);
                s[n] = i;
            }
        }
        r[n] = q; // find the max revenue for length n
        return q; // the maximum prices
    }
}
int memoCutRod(int p[], int n,int s[]){
    int r[n+1]; //ri is max revenure for a rod i
    r[0] = 0;
    for (int i=1;i<=n; i++){
        r[i] = INT_MIN; //original with very tiny price
    }
    return memoCutRodAux(p,n,r,s); // return the max prices
}

int memoCutRodAux_min(int p[],int n,int r1[],int s[]){
    if (r1[n] >=0){
        return r1[n];
    }
    else{
        int q;
        q = INT_MAX;
        for (int i=1;i<=n;i++){
            if (p[i]+memoCutRodAux_min(p,n-i,r1,s)<q){
                q = memoCutRodAux_min(p,n-i,r1,s)+p[i];
                s[n] = i;
            }
            
        }
        r1[n] = q;
        return q;
    }
}
int memoCutRod_min(int p[], int n,int s[]){
    int r1[n+1];
    r1[0] = 0;
    for (int i=1;i<=n; i++){
        r1[i] = INT_MIN;
    }
    return memoCutRodAux_min(p,n,r1,s);
}
int bottomup_max(int p[], int n, int s[]){
    int r[n+1];
    r[0] = 0; //ri = optimal price of the length = i 
    int q;
    for (int j=1; j<=n;j++){
        q = INT_MIN;
        for (int i=1; i<=j;i++){
            if (q<p[i]+r[j-i]){
                q= p[i]+r[j-i];
                s[j] = i; // record the sublength of the cutting
            }
        }
        r[j] = q;
    }
    return r[n];
}
int bottomup_min(int p[], int n, int s[]){
    int r[n+1];
    r[0] = 0;
    int q;
    for (int j=1; j<=n;j++){
        q = INT_MAX;
        for (int i=1; i<=j;i++){
            if (q>p[i]+r[j-i]){
                q= p[i]+r[j-i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
    return r[n];
}

int main(int argc,char** argv){
    int n;
    int n1;
    cout<<"please input the length of rod :";
    cin>>n;
    n1= n;
    int p[11]; //price of the rod
    int s[11]; //load the pieces of the rod
    int s1[11];
    int max_val; //max_price
    int min_val; //min_price
    p[0] = 0;
    
    for (int i=1;i<11;i++){
        cout<<"input the price of the "<<i<<" cutted rod : ";
        cin>>p[i]; // input the prices of the rod
    }
    //cout<<n<<"\n";
    //for (int i=0;i<11;i++){
        //cout<<p[i]<<"\t";
    //}
    max_val = memoCutRod(p,n,s);
    min_val = memoCutRod_min(p,n,s1);
    int num = 0;
    cout<<"----------------------------------------------------------------------\n";
    cout<<"TOP DOWN: \nTotal length: "<<n<<"\n"<<"maximum price: "<<max_val<<"\n";
    while (n>0){
        cout<<s[n]<<"\t";
        n = n-s[n];
        num++;
    }
    n = n1; // n unchanged
    cout<<"\nnumbers of pieces: "<<num<<endl<<endl;
    num = 0; 
    cout<<"minimum price: "<<min_val<<"\n";
    while (n>0){
        cout<<s1[n]<<"\t";
        n = n-s1[n];
        num++;
    }
    n = n1; // n unchanged
    cout<<"\nnumber of pieces: "<<num<<endl;
    num = 0;
    cout<<"----------------------------------------------------------------------\n";
    int s3[11];
    int s4[11];
    max_val = bottomup_max(p,n,s3);
    min_val = bottomup_min(p,n,s4);    
    cout<<"BOTTOM UP: \nTotal length: "<<n<<"\n"<<"maximum price: "<<max_val<<"\n";
    while (n>0){
        cout<<s3[n]<<"\t";
        n = n-s[n];
        num++;
    }
    n = n1; // n unchanged
    cout<<"\nnumbers of pieces: "<<num<<endl<<endl;
    num = 0; 
    cout<<"minimum price: "<<min_val<<"\n";
    while (n>0){
        cout<<s4[n]<<"\t";
        n = n-s4[n];
        num++;
    }
    n = n1; // n umchanged
    cout<<"\nnumber of pieces: "<<num<<endl;


}