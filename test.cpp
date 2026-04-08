#include <iostream>
#include <string>

class Person{
    protected:
        std::string address;
        std::string name;
    public:
        void setAddress(std::string value){
            address = value;
        }
        void setName(std::string value){
            name = value;
        }
        std::string getAddress(){
            return address;
        }
        std::string getName(){
            return name;
        }
};

class Employee: public Person{
    private:
        int salary;
    public:
        void setSalary(int value){
            salary = value;
        }
        int getSalary(){
            return salary;
        }
};

int main(){
    Employee accountant;
    accountant.setSalary(20000);
    std::cout<<accountant.getSalary();
    accountant.setName("Maria");
    std::cout<<accountant.getName(); 
    std::cout<<accountant.getName();
    return 0;
}