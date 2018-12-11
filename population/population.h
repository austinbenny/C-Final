
#include<iostream>
#include<vector>
#include<random>
#include<string>


#include "person.h"

using namespace std;

class population : public person{
    public:
        int num_people, sick_number, rand_person, people_contacted, next_position, innoculated_number,
        recovered_number, susceptible_number, days, contact;
        float probability, perc;
        vector<int> position_of_infected, people_to_innoculate;
        vector<person> v_persons;

        population(vector<person> men){
            v_persons = men;
            num_people = v_persons.size();
            update_pop();
        }
        void random_infection(){

            int healed, total = 0;
            for (auto &e: v_persons){
                if (e.get_status() == "recovered" || e.get_status() == "innoculated"){
                    healed++;
                }
            }
            total = num_people - healed;//if total = 0 the everyone ie recovered
            rand_person = (int)(rand()%num_people) + 1;//random int person in vector
            if (total == 0){
                cout << "No more people to infect " << endl;
            }
            else if (v_persons[rand_person].get_status() == "susceptible"){
                v_persons[rand_person].infect();
            }
            else{
                random_infection();//call function till someone is infected
            }
        }
        int count_infected(){
            sick_number = 0;
            for (auto &a: v_persons){
                if (a.get_status() == "sick"){
                    sick_number++;
                }
            }
            return sick_number;
        }

        int count_inoculated(){
            innoculated_number = 0;
            for (auto &b: v_persons){
                if (b.get_status() == "innoculated"){
                    innoculated_number++;
                }
            }
            return innoculated_number;
        }

        int count_recovered(){
            recovered_number = 0;
            for (auto &c: v_persons){
                if (c.get_status() == "recovered"){
                    recovered_number++;
                }
            }
            return recovered_number;
        }
        int count_susceptible(){
           susceptible_number = 0;
           for (auto &g: v_persons){
                if(g.get_status() == "susceptible"){
                    susceptible_number++;
                }
            }
            return susceptible_number;
        }

        void update_pop(){//update whole pop till nobody is sick
             
            probability = 0.8;//probability of transfer
            perc = 0.5;//percentage of population to innoculate
            people_contacted = 6; // number of people contacted
            next_position = 0;

            cout << " The probability is: " << probability << endl;
            cout << " The percentage of population to innoculate is : " << perc << endl;
            cout << " The population size is: " << num_people << endl;

            if (perc <= 1 && perc >= 0){
                int rand_person_innoculate, num_to_innoculate;
                    if (perc == 1){
                        num_to_innoculate = num_people;
                    }
                    else if (perc == 0){
                        num_to_innoculate = 0;
                    }
                    else{
                        num_to_innoculate = perc * num_people;
                    }
                for (int k = 0; k < num_to_innoculate; k++){
                    rand_person_innoculate = (int)(rand()%num_people) + 1;
                    people_to_innoculate.push_back(rand_person_innoculate);
                }
                for (auto g: people_to_innoculate){
                    if (v_persons[g].get_status() == "susceptible"){//assuming sick people can only be recovered not innoculated
                        v_persons[g].set_status("innoculated");
                    }
                }
            }
            else{
                cout << "Please enter a valid percentage [0,1] " << endl;
            }

            random_infection();
            int days = 1;
            int contact = 0
            while (count_infected() != 0){
                cout << " ______________________________________________________ " << endl;
                cout << " Day: " << days << endl;
                cout << " Infected: " << count_infected() << endl;
                cout << " Recovered: " << count_recovered() << endl;
                cout << " Susceptible: " << count_susceptible() << endl;
                days++;
                for (int j = 1; j < people_contacted; j++){//number of people contacted/day
                    contact++;
                    for (int index = 0; index < num_people; index++){//find position of infected person in vector
                        if (v_persons[index].get_status() == "sick"){
                            position_of_infected.push_back(index);
                        }
                    }
                    float tolerance = (float) rand()/(float)RAND_MAX; //random tolerance [0,1]
                    if (probability > tolerance){
                        for (auto f: position_of_infected){//checking bounds
                            if (f == 0){
                                next_position = 1;//move right
                                if (v_persons[next_position].get_status() == "susceptible"){
                                    v_persons[next_position].infect();
                                }
                            }
                            else if (f == num_people - 1){
                                next_position = f - 1;//move to the left
                                if (v_persons[next_position].get_status() == "susceptible"){
                                    v_persons[next_position].infect();
                                }
                            }
                            else{//infect neighbors 
                                if (v_persons[f - 1].get_status() == "susceptible"){
                                    v_persons[f - 1].infect();
                                }
                                if (v_persons[f + 1].get_status() == "susceptible"){
                                    v_persons[f + 1].infect();

                                }
                            }
                        }
                    }
                }
                for (auto &e: v_persons){//update everybody
                    e.update();
                }
            }
            if (count_infected() == 0){
                cout << "Disease ran its course in the " << days << " day " << endl;
            }
        }
};
