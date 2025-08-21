#include <bits/stdc++.h>
#include <time.h>
#include <cstdlib>
using namespace std;

//hw1 the comparison of insertion sort and merge sort 

void Merge(int b[],int p, int q, int r){
    int n1=q-p+1;
    int n2=r-q;

    int *L;
    int *R;
    L=new int [n1+1];
    R=new int [n2+1];

    //cout<<endl;
    for (int i=0;i<n1;i++){
        L[i]=b[p+i];
        
        //cout<<"this is L["<<i<<"]: "<<L[i]<<"\t";
    }
    //cout<<endl;
    for (int i=0;i<n2;i++){
        R[i]=b[q+i+1];
        //cout<<"this is R["<<i<<"]: "<<R[i]<<"\t";
    }
    //cout<<endl;

    L[n1]=INT_MAX;
    R[n2]=INT_MAX;
    int i=0;
    int j=0;
    for (int k=p;k<=r;k++){
        if(L[i]<=R[j]){
            b[k]=L[i];
            i++;
        }else{
            b[k]=R[j];
            j++;
        }
    }
    delete[] L;
    delete[] R;
}
void Merge_sort(int b[], int p, int r){
    if(p<r){
        int q=(p+r)/2;
        Merge_sort(b,p,q);
        Merge_sort(b,q+1,r);
        Merge(b,p,q,r);
    }
}

int main(int argc,char** argv){

    
    srand(time(NULL));
    int *a;
    int a_length;
    int *b;
    
    cout<<"please enter array size: ";
    cin>>a_length;
    int b_length=a_length;
    b=new int [b_length];
    a=new int [a_length];
    
    int time;
    
    cout<<"before sorting: "<<endl;
    for (int i=0;i<a_length;i++){
        a[i]=rand()%10000000;
        b[i]=a[i];
        //cout<<a[i]<<"\t";
    }

    //for test
    //for (int i=0;i<b_length;i++){
    //    cout<<"\ntest b array: "<<b[i]<<"\t";
    //}
    

    cout<<endl;
    cout<<"after insertion sort: ";
    cout<<endl;

    clock_t tstart=clock();
    for (int j=1;j<a_length;j++){
        int key=a[j];
        int i=j-1;
        while(i>=0 && a[i]>key){
            a[i+1]=a[i];
            i=i-1;
        }
        a[i+1]=key;
    }
    clock_t tend=clock();
    
    for (int i=0;i<a_length;i++){
        //cout<<a[i]<<"\t";
    }
    cout<<"\nTime is measured by insertion sort: "<<(double)(tend-tstart)/CLOCKS_PER_SEC<<"s";
    delete[] a;

    tstart=clock();
    Merge_sort(b,0,b_length-1);
    tend=clock();
    cout<<endl;
    cout<<"after merge sort: ";
    cout<<endl;

    for (int i=0;i<b_length;i++){
        //cout<<b[i]<<"\t";
    }
    cout<<"\nTime is measured by merge sort: "<<(double)(tend-tstart)/CLOCKS_PER_SEC<<"s";
    delete[] b;

}
