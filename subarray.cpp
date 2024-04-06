#include <bits/stdc++.h>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;



struct subarray_info{
    int low; //
    int high;
    float sum=0;
};

subarray_info cross_subarray(const vector<float> &a, int low,int mid, int high){
    float left_sum=-FLT_MAX;
    float sum=0;
    int right_index;
    int left_index;

    for (int i=mid;i>=low;i--){
        sum = sum + a[i];
        if (sum>left_sum){
            left_sum=sum;
            left_index=i;
        }
    }
    float right_sum=-FLT_MAX;
    sum=0;
    for(int i=mid+1;i<=high;i++){
        sum = sum+a[i];
        if(sum>right_sum){
            right_sum = sum;
            right_index = i;
        }
    }
    subarray_info cross_result;
    cross_result.low = left_index;
    cross_result.high = right_index;
    cross_result.sum = right_sum + left_sum;
    return cross_result;
}

subarray_info max_subarray(const vector<float> &a, int low, int high, vector<subarray_info> &record){
    /*
        record is a vector which is a struct of subarray_info, for purpose of 
        recording the local maxima
    */

    if(high == low){
        subarray_info result;
        result.low = low;
        result.high = high;
        result.sum = a[low];
        return result;
    }
    else{
        int mid;

        mid=(low+high)/2;
        subarray_info left_max = max_subarray(a,low,mid,record);
        subarray_info right_max = max_subarray(a, mid+1, high,record);
        subarray_info cross_max = cross_subarray(a,low,mid,high);
        
        /*there are seven cases overall, whether the max has only one(*3)
        or the max has two(*3) or all three(left, right, cross) are all max
        */
        if (left_max.sum>cross_max.sum && left_max.sum>right_max.sum){

            record.push_back({left_max.low, left_max.high, left_max.sum});
            return left_max;

        }//should record the site of max
        else if (cross_max.sum>left_max.sum && cross_max.sum>right_max.sum){
            
            record.push_back({cross_max.low, cross_max.high, cross_max.sum});
            return cross_max;

        }//cross>left and cross>right
        else if (right_max.sum>left_max.sum && right_max.sum>cross_max.sum){
            
            record.push_back({right_max.low, right_max.high, right_max.sum});
            return right_max;
        }
        else if (left_max.sum == cross_max.sum && left_max.sum>right_max.sum){
           
            record.push_back({left_max.low, left_max.high, left_max.sum});
            record.push_back({cross_max.low, cross_max.high, cross_max.sum});
            return left_max;
        }
        else if (left_max.sum == right_max.sum && left_max.sum>cross_max.sum){
            
            record.push_back({left_max.low, left_max.high, left_max.sum});
            record.push_back({right_max.low, right_max.high, right_max.sum});
            return left_max;
        }
        else if (cross_max.sum == right_max.sum && cross_max.sum>left_max.sum){

            record.push_back({cross_max.low, cross_max.high, cross_max.sum});
            record.push_back({right_max.low, right_max.high, right_max.sum});   
            return cross_max;

        }else{

            record.push_back({cross_max.low, cross_max.high, cross_max.sum});
            record.push_back({right_max.low, right_max.high, right_max.sum});
            record.push_back({left_max.low, left_max.high, left_max.sum});  
            return cross_max;

        }//3 筆資料都一樣大所以都要記起來
        
    }//end of else now we have record all the possible maximum in the vector
    //now we want to compare the value

}


int main(int argc,char** argv){
    int i=0;
    vector<subarray_info> record;
    ifstream inStream;
    inStream.open("data.txt");

    vector<float> a;
    int a_length = 0;
    int index;
    float value;

    while(inStream>>index>>value){
        a_length++;
        a.push_back(value);
        //cout<<num<<"\t";
    }
    
    inStream.close();
    //cout<<a_length;
    max_subarray(a,0,a_length-1,record);
    
    
    //found the max, next to find the minimun distance
    float max = record[0].sum;
    int max_spacing = record[0].high - record[0].low;
    int max_high;
    int max_low;

    //cout<<record.size()<<"\n"; //for testing 
    for (int i=1;i<record.size();i++){
        
        if (record[i].sum>max){

            max = record[i].sum;
            max_spacing = record[i].high - record[i].low;
            max_high = record[i].high;
            max_low = record[i].low;

        }//如果存在一數大於原始直則會被replace meanwile renew the max spacing

    }//after for i found a max of the record
    
    //then find the minima spacing of the max value
    for(int i=0;i<record.size();i++){

        if (record[i].sum == max){
            //cout<<"in "<<record[i].high-record[i].low<<"\n";

            if (record[i].high - record[i].low < max_spacing){
            
            max_spacing = record[i].high - record[i].low;
            
            }//find the minimal spacing
        }
    }
    cout<<"The max is: "<<max<<"\n";

    vector <subarray_info> already; //record the information that has been displayed

    for(int i=0;i<record.size();i++){
        
        if (record[i].sum == max && max_spacing == record[i].high - record[i].low){ //print max whose space is equal to minimal space
            bool repeat= 0;//avoid the case that has same high and low and sum
            for(int j=0;j<already.size();j++){
                if (record[i].high == already[j].high && record[i].low == already[j].low){//已經記錄了(有被print過)
                    repeat = 1;
                    break;
                }
            }
            if(!repeat){
                already.push_back({record[i].low, record[i].high, record[i].sum});
                cout<<"from "<<record[i].low + 1<<" to "<<record[i].high + 1<<endl;
            }
        }//end of first if
    }//end of for
}