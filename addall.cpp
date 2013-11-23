/* 
 * File:   addall.cpp
 * Author: shijiex
 *
 * Created on November 23, 2013, 1:04 AM
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char** argv) {
     
    int node =0 ;
     while (scanf("%d\n", &node) != EOF){
         if(node ==0) break;
         priority_queue<int, vector<int>, greater<int> > costTree;
         
         for (int i = 0; i < node; i++) {
             int digit = 0;
            scanf("%d", &digit);
            costTree.push(digit);
        }
         int cost = 0;
         while(!costTree.empty()){
             int sum = 0;
             int a = costTree.top();
             costTree.pop();
             if(!costTree.empty()){
                 int b = costTree.top();
                 costTree.pop();
                 sum = a+b;
                 cost+=sum;
                 costTree.push(sum);
             }else{
                 sum = a;
             }
             
         }
         
         cout<<cost<<endl;
     }
   
    return 0;
}

