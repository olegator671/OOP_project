#include <iostream>
#include <string>

class Expression{
    private:
        char variables[3];
        int results[8];

    public:
        void setVariables(char input[3]){
            for (int i = 0; i < 3; i++){
                variables[i] = input[i];
            }
        }

        void setResults(int input[8]){
            for (int i = 0; i < 8; i++){
                results[i] = input[i];
            }
        }
        

        const int combinations3[8][3] = {
            {0,0,0},
            {0,0,1},
            {0,1,0},
            {0,1,1},
            {1,0,0},
            {1,0,1},
            {1,1,0},
            {1,1,1}
        };
        const int combinations2[4][2] = {
            {0,0},
            {0,1},
            {1,0},
            {1,1}
        };
        const int combinations3[2] = {
            0,
            1
        };
};

class Operator{
    protected:
        int variables[2];
        int result;
        int priority;

    public:

        
};

class And: public Operator{
    
};

class Or: public Operator{

};

class Not: public Operator{
    
};

class Xor: public Operator{

};

class Nand: public Operator{

};

class Nor: public Operator{

};

int main(){
    std::string expression;
    std::cin>>expression;
    for (int i = 0; i < expression.length(); i++){
        
    }
    return 0;
}