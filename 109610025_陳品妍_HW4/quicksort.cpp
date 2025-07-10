#include <bits/stdc++.h>
#include <time.h>
#include <cstdlib>
using namespace std;

//hw4 the comparison of insertion sort/merge sort/heap sort/quicksort 


int partition(int a[], int p, int r){

    //randomized partition start
    int random = p+rand()%(r-p+1);
    int key = a[random];
    a[random] = a[r];
    a[r] = key; //randomly choose a number as a[r]
    //randomized partition end

    int x = a[r];
    int i = p-1;
    for(int j = p;j<=r-1;j++){
        if (a[j]<=x){
            i++;
            key = a[j];
            a[j] = a[i];
            a[i] = key;
        }
    }
    key = a[i+1];
    a[i+1] = a[r];
    a[r] = key;
    return i+1;
}
void quicksort(int a[], int p, int r){
    
    if (p<r){
        int q; 
        q = partition(a,p,r);
        quicksort(a,p,q-1);
        quicksort(a,q+1,r);
    }
    
}

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

void max_heapify(int a[], int i, int heap_size){
    int l = 2*i+1;
    int r = 2*i+2;
    int largest;
    int change;
    if (l<=heap_size-1 && a[l]>a[i]){
        largest = l;
    }else{
        largest = i;
    }
    if (r<=heap_size-1 && a[r]>a[largest]){
        largest = r;
    }
    if (largest != i){
        change = a[largest];
        a[largest] = a[i];
        a[i] = change;
        max_heapify(a,largest,heap_size); //continue to check downward to form a max-heapify
    }
}
void built_max_heap(int a[], int length){
    int heap_size = length;
    for(int i=(length-1)/2; i>=0; i--){
        max_heapify(a,i,heap_size);
    }
}
void heap_sort(int a[], int length, int heap_size, int d[]){
    built_max_heap(a,length); //first of all, build a max-heapify
    int change;
    int index = 0;
    for(int i = length-1 ; i>=1 ; i-- ){
        change = a[0];
        a[0] = a[i];
        a[i] = change;
        heap_size--;        
        d[index] = change; //remove the max of the max-heapify
        index++;
        max_heapify(a,0,heap_size);   
    }
    d[index] = a[0]; //the last one also has to be added into the result
}

int main(int argc,char** argv){

    
    srand(time(NULL));
    int *a;
    int a_length;
    int *b;
    int *c;
    int *d;
    int *e;

    cout<<"please enter array size: ";
    cin>>a_length;
    int b_length=a_length;
    int c_length = a_length;
    int d_length = a_length;
    int e_length = a_length;

    c = new int [c_length];
    b=new int [b_length];
    a=new int [a_length];
    d = new int [d_length];
    e = new int [e_length];
    
    int time;
    
    cout<<"before sorting: "<<endl;
    for (int i=0;i<a_length;i++){
        a[i]=rand()%10000000;
        b[i]=a[i];
        c[i]=a[i];
        e[i] = a[i];        
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
    //built_max_heap(c,c_length);

    tstart=clock(); //start to sort
    heap_sort(c,c_length,c_length,d);
    tend=clock(); //end the sort

    //cout<<"this is c : \n";
    //for (int i=0;i<c_length;i++){
        //cout<<c[i]<<"\t";
    //}//check whether c is max heapify 
    cout<<"\n";

    cout<<"after heap sort: \n";   
    for (int i=0;i<c_length;i++){
        //cout<<d[i]<<"\t"; //can test the correctness of the heap sort
    }   
    cout<<"\nTime is measured by heap sort: "<<(double)(tend-tstart)/CLOCKS_PER_SEC<<"s";

    int p = 0;
    int r = e_length-1;

    tstart = clock();
    quicksort(e,p,r);
    tend = clock();
    cout<<"\n";

    cout<<"after randomized quick sort: \n";   
    for (int i=0;i<c_length;i++){
        //cout<<e[i]<<"\t"; //can test the correctness of the quick sort
    }

    cout<<"\nTime is measured by randomized quick sort: "<<(double)(tend-tstart)/CLOCKS_PER_SEC<<"s";
    delete []e;
    delete[] b;
    delete []c;
    delete[]d;
}