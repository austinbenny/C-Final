

#include<iostream>
#include<vector>
#include<random>
#include<string>

using namespace std;


class person{
    protected://should i make these public?
        int infect_days, age;
        string status;
    public:
        person(){
            status = "susceptible";
            age = 0;
        }
        string get_status(){
            return status;
        }
        void set_status(string condition){
            status = condition;
        }
        void infect(){
            if (status == "susceptible"){
                status = "sick";
                infect_days = 5;//default 5 days
            }
        }
        void update(){
            age++;
            if (status == "sick" && infect_days != 1){
                infect_days --;
            }
            else if(status == "sick" && infect_days == 1){
                status = "recovered";
            }
        }
        void status_string(){
            if (status == "sick"){
                cout << " is sick and will be for " << infect_days << " more days" << endl;
            }
            else{
                cout << " is " << status << endl;
            }
        }
        bool is_stable(){
            if (status == "recovered" || status == "innoculated"){
                return true;
            }
            else{
                return false;
            }
        }
};

