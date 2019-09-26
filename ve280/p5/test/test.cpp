#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }
    int testNum = atoi(argv[1]);
    if (testNum < 1) {
        return 0;
    }
    cout << "Testcase ";
    if (testNum < 10) {
	cout << " ";
    }
    cout << testNum << ": ";

    string answerFilename = argv[1];
    answerFilename = "answer-" + answerFilename;
    string outputFilename = argv[1];
    outputFilename = "output-" + outputFilename;
    string answerString, outputString;
    ifstream finAnswer, finOutput;
    finAnswer.open(answerFilename.c_str());
    finOutput.open(outputFilename.c_str());
    while (!finAnswer.eof() && !finOutput.eof()) {
        getline(finAnswer, answerString);
        getline(finOutput, outputString);
        if (answerString != outputString) {
            cout << "fail." << endl;
            return 0;
        }
    }
    if (finAnswer.eof() && finOutput.eof()) {
        cout << "pass." << endl;
    } else {
        cout << "fail." << endl;
    }
    return 0;
}
