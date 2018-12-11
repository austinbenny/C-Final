#include<iostream>
#include<vector>
#include<random>
#include<string>

#include "person.h"//header files
#include "population.h"

using namespace std;



int main(){

    int pop_size = 100; //size of population
    vector<person> group(pop_size, person());
    population pop(group);

    return 0;
}
