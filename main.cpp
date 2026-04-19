#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

const string FILE_NAME = "truth_table.txt";

// base class for all operators
class BooleanOperator {
public:
    virtual string getName() = 0;
    virtual int getPrecedence() = 0;
    virtual int getOperands() = 0;
    virtual bool apply(bool a, bool b = false) = 0;
    virtual string getExplanation() = 0;
    virtual ~BooleanOperator() {}
};

// and operator
class AndOperator : public BooleanOperator {
public:
    string getName() { return "AND"; }
    int getPrecedence() { return 2; }
    int getOperands() { return 2; }
    bool apply(bool a, bool b = false) { return a && b; }
    string getExplanation() {
        return "AND: Returns true only when both inputs are true. Example: 1 AND 1 = 1, 1 AND 0 = 0.";
    }
};

// or operator
class OrOperator : public BooleanOperator {
public:
    string getName() { return "OR"; }
    int getPrecedence() { return 1; }
    int getOperands() { return 2; }
    bool apply(bool a, bool b = false) { return a || b; }
    string getExplanation() {
        return "OR: Returns true if at least one input is true. Example: 1 OR 0 = 1, 0 OR 0 = 0.";
    }
};

// not operator
class NotOperator : public BooleanOperator {
public:
    string getName() { return "NOT"; }
    int getPrecedence() { return 3; }
    int getOperands() { return 1; }
    bool apply(bool a, bool b = false) { return !a; }
    string getExplanation() {
        return "NOT: Reverses the input. Example: NOT 1 = 0, NOT 0 = 1.";
    }
};

// xor operator
class XorOperator : public BooleanOperator {
public:
    string getName() { return "XOR"; }
    int getPrecedence() { return 1; }
    int getOperands() { return 2; }
    bool apply(bool a, bool b = false) { return a != b; }
    string getExplanation() {
        return "XOR: Returns true when inputs are different. Example: 1 XOR 0 = 1, 1 XOR 1 = 0.";
    }
};

// nand operator
class NandOperator : public BooleanOperator {
public:
    string getName() { return "NAND"; }
    int getPrecedence() { return 2; }
    int getOperands() { return 2; }
    bool apply(bool a, bool b = false) { return !(a && b); }
    string getExplanation() {
        return "NAND: Opposite of AND. Example: 1 NAND 1 = 0, 1 NAND 0 = 1.";
    }
};

// nor operator
class NorOperator : public BooleanOperator {
public:
    string getName() { return "NOR"; }
    int getPrecedence() { return 1; }
    int getOperands() { return 2; }
    bool apply(bool a, bool b = false) { return !(a || b); }
    string getExplanation() {
        return "NOR: Opposite of OR. Example: 0 NOR 0 = 1, 1 NOR 0 = 0.";
    }
};

// this class works with the expression
class BooleanExpression {
private:
    map<string, BooleanOperator*> ops;

public:
    BooleanExpression() {
        ops["AND"] = new AndOperator();
        ops["OR"] = new OrOperator();
        ops["NOT"] = new NotOperator();
        ops["XOR"] = new XorOperator();
        ops["NAND"] = new NandOperator();
        ops["NOR"] = new NorOperator();
    }

    ~BooleanExpression() {
        for (auto x : ops) {
            delete x.second;
        }
    }

    string upper(string s) {
        for (int i = 0; i < (int)s.size(); i++) {
            s[i] = toupper(s[i]);
        }
        return s;
    }

    bool isVar(string s) {
        return s == "A" || s == "B" || s == "C";
    }

    bool isOp(string s) {
        return ops.find(s) != ops.end();
    }

    // split expression into pieces
    vector<string> tokenize(string exp) {
        exp = upper(exp);
        vector<string> t;
        string cur = "";

        for (int i = 0; i < (int)exp.size(); i++) {
            char ch = exp[i];

            if (ch == ' ') {
                if (!cur.empty()) {
                    t.push_back(cur);
                    cur = "";
                }
            }
            else if (ch == '(' || ch == ')') {
                if (!cur.empty()) {
                    t.push_back(cur);
                    cur = "";
                }
                string a = "";
                a += ch;
                t.push_back(a);
            }
            else {
                cur += ch;
            }
        }

        if (!cur.empty()) {
            t.push_back(cur);
        }

        return t;
    }

    // check if expression is okay
    void validate(vector<string> t) {
        if (t.empty()) {
            throw runtime_error("Expression cannot be empty.");
        }

        int brackets = 0;
        int opCount = 0;
        set<string> vars;

        for (int i = 0; i < (int)t.size(); i++) {
            string x = t[i];

            if (!(isVar(x) || isOp(x) || x == "(" || x == ")")) {
                throw runtime_error("Invalid token: " + x);
            }

            if (x == "(") brackets++;
            if (x == ")") brackets--;
            if (brackets < 0) throw runtime_error("Wrong parentheses.");

            if (isOp(x)) opCount++;
            if (isVar(x)) vars.insert(x);
        }

        if (brackets != 0) throw runtime_error("Wrong parentheses.");
        if (opCount > 3) throw runtime_error("Maximum 3 operators are allowed.");
        if (vars.size() > 3) throw runtime_error("Only variables A, B and C are allowed.");

        if (isOp(t[0]) && t[0] != "NOT") {
            throw runtime_error("Expression cannot start with a binary operator.");
        }
        if (isOp(t[t.size() - 1])) {
            throw runtime_error("Expression cannot end with an operator.");
        }
    }

    // convert to postfix
    vector<string> toPostfix(vector<string> t) {
        vector<string> out;
        stack<string> st;

        for (int i = 0; i < (int)t.size(); i++) {
            string x = t[i];

            if (isVar(x)) {
                out.push_back(x);
            }
            else if (isOp(x)) {
                while (!st.empty() && isOp(st.top())) {
                    if (ops[st.top()]->getPrecedence() >= ops[x]->getPrecedence() && x != "NOT") {
                        out.push_back(st.top());
                        st.pop();
                    }
                    else if (ops[st.top()]->getPrecedence() > ops[x]->getPrecedence() && x == "NOT") {
                        out.push_back(st.top());
                        st.pop();
                    }
                    else {
                        break;
                    }
                }
                st.push(x);
            }
            else if (x == "(") {
                st.push(x);
            }
            else if (x == ")") {
                while (!st.empty() && st.top() != "(") {
                    out.push_back(st.top());
                    st.pop();
                }
                if (st.empty()) throw runtime_error("Wrong parentheses.");
                st.pop();
            }
        }

        while (!st.empty()) {
            if (st.top() == "(") throw runtime_error("Wrong parentheses.");
            out.push_back(st.top());
            st.pop();
        }

        return out;
    }

    // solve postfix expression
    bool eval(vector<string> post, map<string, bool> vals) {
        stack<bool> st;

        for (int i = 0; i < (int)post.size(); i++) {
            string x = post[i];

            if (isVar(x)) {
                st.push(vals[x]);
            }
            else if (isOp(x)) {
                if (ops[x]->getOperands() == 1) {
                    if (st.empty()) throw runtime_error("Invalid expression.");
                    bool a = st.top();
                    st.pop();
                    st.push(ops[x]->apply(a));
                }
                else {
                    if (st.size() < 2) throw runtime_error("Invalid expression.");
                    bool b = st.top(); st.pop();
                    bool a = st.top(); st.pop();
                    st.push(ops[x]->apply(a, b));
                }
            }
        }

        if (st.size() != 1) throw runtime_error("Invalid expression.");
        return st.top();
    }

    // variables used in expression
    vector<string> getVars(vector<string> t) {
        vector<string> v;
        set<string> seen;

        for (int i = 0; i < (int)t.size(); i++) {
            if (isVar(t[i]) && seen.find(t[i]) == seen.end()) {
                v.push_back(t[i]);
                seen.insert(t[i]);
            }
        }

        return v;
    }

    // operators used in expression
    vector<string> getOps(vector<string> t) {
        vector<string> v;
        set<string> seen;

        for (int i = 0; i < (int)t.size(); i++) {
            if (isOp(t[i]) && seen.find(t[i]) == seen.end()) {
                v.push_back(t[i]);
                seen.insert(t[i]);
            }
        }

        return v;
    }

    string getExp(string op) {
        return ops[op]->getExplanation();
    }
};

// makes the truth table
class TruthTable {
public:
    string generate(BooleanExpression& be, string exp, vector<string>& vars, vector<string>& usedOps) {
        vector<string> t = be.tokenize(exp);
        be.validate(t);
        vector<string> post = be.toPostfix(t);

        vars = be.getVars(t);
        usedOps = be.getOps(t);

        stringstream out;

        out << "|";
        for (int i = 0; i < (int)vars.size(); i++) {
            out << " " << setw(3) << vars[i] << " |";
        }
        out << " " << setw(6) << "RESULT" << " |\n";

        out << "|";
        for (int i = 0; i < (int)vars.size(); i++) {
            out << "-----|";
        }
        out << "--------|\n";

        int rows = 1 << vars.size();

        for (int mask = 0; mask < rows; mask++) {
            map<string, bool> vals;
            out << "|";

            for (int i = 0; i < (int)vars.size(); i++) {
                int bit = (mask >> (vars.size() - 1 - i)) & 1;
                vals[vars[i]] = bit;
                out << " " << setw(3) << bit << " |";
            }

            bool ans = be.eval(post, vals);
            out << " " << setw(6) << ans << " |\n";
        }

        return out.str();
    }
};

// save and load file
class FileManager {
public:
    void saveToFile(string exp, vector<string> exps, string table) {
        ofstream file(FILE_NAME);

        file << "*** BOOLEAN TRUTH TABLE SIMULATOR ***\n\n";
        file << "Expression:\n";
        file << exp << "\n\n";

        file << "Operators Detected and Explained:\n";
        for (int i = 0; i < (int)exps.size(); i++) {
            file << "- " << exps[i] << "\n";
        }

        file << "\nTruth Table:\n";
        file << table;
    }

    bool loadExpression(string& exp) {
        ifstream file(FILE_NAME);
        if (!file) return false;

        string line;
        while (getline(file, line)) {
            if (line == "Expression:") {
                if (getline(file, exp)) {
                    return !exp.empty();
                }
            }
        }
        return false;
    }
};

int main() {
    BooleanExpression be;
    TruthTable tt;
    FileManager fm;

    while (true) {
        try {
            cout << "\n*** BOOLEAN TRUTH TABLE SIMULATOR ***\n";
            cout << "1) Load previously saved expression\n";
            cout << "2) Enter new expression\n";
            cout << "Choose option: ";

            int ch;
            cin >> ch;
            cin.ignore();

            string exp;

            if (ch == 1) {
                if (!fm.loadExpression(exp)) {
                    cout << "No saved expression found in file \"truth_table\".\n";
                    continue;
                }
                cout << "Loaded expression: " << exp << "\n";
            }
            else if (ch == 2) {
                cout << "Enter Boolean expression (max 3 operators, variables A, B, C): ";
                getline(cin, exp);
            }
            else {
                cout << "Invalid option.\n";
                continue;
            }

            vector<string> vars;
            vector<string> usedOps;
            string table = tt.generate(be, exp, vars, usedOps);

            cout << "\nExpression: " << exp << "\n\n";
            cout << "Operators Detected and Explained:\n";

            vector<string> exps;
            for (int i = 0; i < (int)usedOps.size(); i++) {
                string s = be.getExp(usedOps[i]);
                exps.push_back(s);
                cout << "- " << s << "\n";
            }

            cout << "\nGenerated Truth Table:\n";
            cout << table << "\n";

            cout << "1) Repeat the process\n";
            cout << "2) Save the table and repeat the process (this will override the old one)\n";
            cout << "Choose option: ";

            int ch2;
            cin >> ch2;
            cin.ignore();

            if (ch2 == 2) {
                fm.saveToFile(exp, exps, table);
                cout << "Saved to file \"truth_table\" successfully. Old saved table was overridden.\n";
            }
        }
        catch (exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
