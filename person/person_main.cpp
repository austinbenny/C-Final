/*
Author Name: Austin Benny
Program Name: Final Project
Create Date: 21/11/2018
*/

#include<iostream>
#include<vector>
#include<random>
#include<string>

#include "person.h"//header files for class person and population
#include "population.h"

using namespace std;

int main(){

    float tolerance = .95;//probability Joe will be infected
    cout << "Default probability of infection is " << tolerance << endl;
    int day = 0;

    person joe;
    joe = person();
    
    while(joe.is_stable() != true){
        day++;
        joe.update();
        float bad_luck = (float) rand()/(float)RAND_MAX; 
        cout << " Random probability is " << bad_luck << endl;
            if (bad_luck > tolerance){
                joe.infect();
                cout << " Joe on day, " << day << " "; joe.status_string();
                cout << endl;
            }
            else{
                cout << "Joe on day, " << day << " "; joe.status_string();
                cout << endl;
            }
    }
return 0;
}
