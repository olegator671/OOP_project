#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const string FILE_NAME = "truth_table.txt";

void saveTestTable() {
    ofstream file(FILE_NAME);

    if (!file) {
        cout << "Error: could not open file.\n";
        return;
    }

    string expression = "A AND B";

    string table =
        "|  A |  B | RESULT |\n"
        "|-----|-----|--------|\n"
        "|  0 |  0 |   0    |\n"
        "|  0 |  1 |   0    |\n"
        "|  1 |  0 |   0    |\n"
        "|  1 |  1 |   1    |\n";

    file << "*** BOOLEAN TRUTH TABLE SIMULATOR ***\n\n";
    file << "Expression:\n";
    file << expression << "\n\n";

    file << "Operators Detected and Explained:\n";
    file << "- AND: Returns true only when both inputs are true.\n\n";

    file << "Truth Table:\n";
    file << table;

    file.close();

    cout << "fart\n";
}

int main() {

    saveTestTable();

    cout << "Check file: truth_table.txt\n";

    return 0;
}