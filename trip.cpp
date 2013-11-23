/* 
 * File:   main.cpp
 * Author: shijiex
 *
 * Created on November 7, 2013, 2:17 PM
 */
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>


using namespace std;

int main(int argc, const char * argv[]) {
    int numStudents = 0;
    while (scanf("%d\n", &numStudents) != EOF) {
        if (numStudents == 0) break;

        vector<double> students;

        double total = 0;

        for (int i = 0; i < numStudents; i++) {
            double money = 0;
            scanf("%lf\n", &money);
            students.push_back(money);
            total += students.at(i);
        }

        double average = total / numStudents;
        double pos = 0, neg = 0;

        for (vector<double>::iterator iter = students.begin(); iter != students.end(); iter++) {
            // Force cast to int so that all digits after 0.01 would be removed
            double dis = (int) (((double) (*iter) - average)*100) / 100.0;
            if (dis < 0) neg += dis;
            else pos += dis;
        }
        double exchange = (-neg > pos) ? -neg : pos;
        cout.precision(2);
        cout <<std::fixed<<"$"<<exchange << endl;

    }

    return 0;
}
