#include <iostream>
#include <fstream>
using namespace std;

int getRow(string line) {
    int row = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '\n') {
            row++;
        }
    }
    return row;
}

int getColumns(string line) {
    int columns = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ' ' || line[i] == '\n') {
            columns++;
        }
    }
    return columns/getRow(line);
}

int main() {
    // Open file
    string filename;

    cout << "Enter filename (without .txt): ";
    cin >> filename;

    ifstream readFile("../test/" + filename + ".txt");

    // Iterate every line to puzzle variable
    string puzzle;
    string line;
    while(getline (readFile, line) && line != "") {
        puzzle += line + "\n";
    }

    // Get answers
    int answerSize = 0;
    string answers;
    while(getline (readFile, line) && line != "") {
        answerSize++;
        answers += line + "\n";
    }

    // Make list of answers
    string answerList[answerSize];
    int i,j,k;
    for(i=0; i<answerSize; i++) {
        answerList[i] = answers.substr(0, answers.find('\n'));
        answers = answers.substr(answers.find('\n')+1);
    }

    // // Print each answers
    // for(i=0; i<answerSize; i++) {
    //     cout << answerList[i] << endl;
    // }

    // Get rows and columns
    int col = getColumns(puzzle);
    // cout << "coloumns: " << col << endl;

    int row = getRow(puzzle);
    // cout << "rows: " << row << endl;

    // Covert puzzle to matrix
    char matrix[row][col];

    k=0;
    for(i=0;i<row;i++) {
        for(j=0;j<col;j++) {
            while(puzzle[k] != ' ' && puzzle[k] != '\n') {
                matrix[i][j] = puzzle[k];
                k++;
            }
            k++;
        }
    }

    // Iterate through matrix
    for(k=0;k<answerSize;k++) {
        cout << "Answer " << k+1 << ": " << endl;
        for(i=0;i<row;i++) {
            for(j=0;j<col;j++) {
                if(answerList[k][0] == matrix[i][j]) {
                    cout << "(" << i << "," << j << ")" << endl;
                }
            }
        }
    }
    
    readFile.close();
}
