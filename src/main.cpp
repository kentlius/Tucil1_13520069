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

string displayAnswerMatrix(int row, int col, int rowStart, int colStart, int rowEnd, int colEnd, string answerList) {
    int i,j,k;
    char matrix[row][col];
    string answerMatrix = "";

    for(i=0;i<row;i++) {
        for(j=0;j<col;j++) {
            matrix[i][j] = '-';
        }
    }

    if(rowStart == rowEnd && colStart > colEnd){ //kiri ke kanan
        for(j=colStart,k=0;j>=colEnd,k<answerList.length();j--,k++) {
            matrix[rowStart][j] = answerList[k];
        }
    }

    if(rowStart == rowEnd && colStart < colEnd){ //kanan ke kiri
        for(j=colStart,k=0;j<=colEnd,k<answerList.length();j++,k++) {
            matrix[rowStart][j] = answerList[k];
        }
    }

    if(colStart == colEnd && rowStart > rowEnd){ //atas ke bawah
        for(i=rowStart,k=0;i>=rowEnd,k<answerList.length();i--,k++) {
            matrix[i][colStart] = answerList[k];
        }
    }

    if(colStart == colEnd && rowStart < rowEnd){ //bawah ke atas
        for(i=rowStart,k=0;i<=rowEnd,k<answerList.length();i++,k++) {
            matrix[i][colStart] = answerList[k];
        }
    }


    //diagonal atas kiri ke bawah kanan
    if(rowStart < rowEnd && colStart < colEnd) {
        for(i=rowStart,j=colStart,k=0;i<=rowEnd,j<=colEnd,k<answerList.length();i++,j++,k++) {
            matrix[i][j] = answerList[k];
        }
    }

    //diagonal atas kanan ke bawah kiri
    if(rowStart < rowEnd && colStart > colEnd) {
        for(i=rowStart,j=colStart,k=0;i<=rowEnd,j>=colEnd,k<answerList.length();i++,j--,k++) {
            matrix[i][j] = answerList[k];
        }
    }

    //diagonal bawah kiri ke atas kanan
    if(rowStart > rowEnd && colStart < colEnd) {
        for(i=rowStart,j=colStart,k=0;i>=rowEnd,j<=colEnd,k<answerList.length();i--,j++,k++) {
            matrix[i][j] = answerList[k];
        }
    }

    //diagonal bawah kanan ke atas kiri
    if(rowStart > rowEnd && colStart > colEnd) {
        for(i=rowStart,j=colStart,k=0;i>=rowEnd,j>=colEnd,k<answerList.length();i--,j--,k++) {
            matrix[i][j] = answerList[k];
        }
    }

    for(i=0;i<row;i++) {
        for(j=0;j<col;j++) {
            answerMatrix += matrix[i][j];
        }
        answerMatrix += '\n';
    }

    return answerMatrix;
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
    int i,j,k,direction,letter,n,o;
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
        cout << "\n" << "Answer " << k+1 << ": " << endl;
        bool found = false;
        i=0;
        while(i<row && !found) {
            // cout<<"Row "<<i<<endl;
            j=0;
            while(j<col && !found) {
                // cout<<"Col "<<j<<endl;
                if(answerList[k][0] == matrix[i][j] && found != true) {
                    // cout<<"Found!"<<"("<<i<<","<<j<<")"<<endl;
                    direction=0;
                    while(direction<8 && found != true) {
                        // cout<<"Direction "<<direction<<endl;
                        if(direction == 0) { //atas
                            letter=1;
                            n=i;
                            while(letter<answerList[k].length() && n>=0 && found != true) {
                                if(answerList[k][letter] != matrix[n-1][j]) {
                                    break;
                                }
                                else if(letter == answerList[k].length()-1) {
                                    found = true;
                                    cout << "(" << i << "," << j << ")" << "to" << "(" << n-1 << "," << j << ")" << endl;
                                    cout << "Atas" << endl;
                                    cout << displayAnswerMatrix(row, col, i, j, n-1, j, answerList[k]) << endl;
                                    break;
                                }
                                letter++;
                                n--;
                            }
                            direction++;
                        }
                        else if(direction == 1) { //kanan atas
                            letter=1;
                            n=i;
                            o=j;
                            while(letter<answerList[k].length() && n>=0 && o<col && found != true) {
                                if(answerList[k][letter] != matrix[n-1][o+1]) {
                                    break;
                                }
                                else if(letter == answerList[k].length()-1) {
                                    found = true;
                                    cout << "(" << i << "," << j << ")" << "to" << "(" << n-1 << "," << o+1 << ")" << endl;
                                    cout << "Kanan Atas" << endl;
                                    cout << displayAnswerMatrix(row, col, i, j, n-1, o+1, answerList[k]) << endl;
                                    break;
                                }
                                letter++;
                                n--;
                                o++;
                            }
                            direction++;
                        }
                        else if(direction == 2) { //kanan
                            letter=1;
                            o=j;
                            while(letter<answerList[k].length() && o<col && found != true) {
                                if(answerList[k][letter] != matrix[i][o+1]) {
                                    break;
                                }
                                else if(letter == answerList[k].length()-1) {
                                    found = true;
                                    cout << "(" << i << "," << j << ")" << "to" << "(" << i << "," << o+1 << ")" << endl;
                                    cout << "Kanan" << endl;
                                    cout << displayAnswerMatrix(row, col, i, j, i, o+1, answerList[k]) << endl;
                                    break;
                                }
                                letter++;
                                o++;
                            }
                            direction++;
                        }
                        else if(direction == 3) { //kanan bawah
                            letter=1;
                            n=i;
                            o=j;
                            while(letter<answerList[k].length() && n<row && o<col && found != true) {
                                if(answerList[k][letter] != matrix[n+1][o+1]) {
                                    break;
                                }
                                else if(letter == answerList[k].length()-1) {
                                    found = true;
                                    cout << "(" << i << "," << j << ")" << "to" << "(" << n+1 << "," << o+1 << ")" << endl;
                                    cout << "Kanan Bawah" << endl;
                                    cout << displayAnswerMatrix(row, col, i, j, n+1, o+1, answerList[k]) << endl;
                                    break;
                                }
                                letter++;
                                n++;
                                o++;
                            }
                            direction++;
                        }
                        else if(direction == 4) { //bawah
                            letter=1;
                            n=i;
                            while(letter<answerList[k].length() && n<row && found != true) {
                                if(answerList[k][letter] != matrix[n+1][j]) {
                                    break;
                                }
                                else if(letter == answerList[k].length()-1) {
                                    found = true;
                                    cout << "(" << i << "," << j << ")" << "to" << "(" << n+1 << "," << j << ")" << endl;
                                    cout << "Bawah" << endl;
                                    cout << displayAnswerMatrix(row, col, i, j, n+1, j, answerList[k]) << endl;
                                    break;
                                }
                                letter++;
                                n++;
                            }
                            direction++;
                        }
                        else if(direction == 5) { //kiri bawah
                            letter=1;
                            n=i;
                            o=j;
                            while(letter<answerList[k].length() && n<row && o>=0 && found != true) {
                                if(answerList[k][letter] != matrix[n+1][o-1]) {
                                    break;
                                }
                                else if(letter == answerList[k].length()-1) {
                                    found = true;
                                    cout << "(" << i << "," << j << ")" << "to" << "(" << n+1 << "," << o-1 << ")" << endl;
                                    cout << "Kiri Bawah" << endl;
                                    cout << displayAnswerMatrix(row, col, i, j, n+1, o-1, answerList[k]) << endl;
                                    break;
                                }
                                letter++;
                                n++;
                                o--;
                            }
                            direction++;
                        }
                        else if(direction == 6) { //kiri
                            letter=1;
                            o=j;
                            while(letter<answerList[k].length() && o>=0 && found != true) {
                                if(answerList[k][letter] != matrix[i][o-1]) {
                                    break;
                                }
                                else if(letter == answerList[k].length()-1) {
                                    found = true;
                                    cout << "(" << i << "," << j << ")" << "to" << "(" << i << "," << o-1 << ")" << endl;
                                    cout << "Kiri" << endl;
                                    cout << displayAnswerMatrix(row, col, i, j, i, o-1, answerList[k]) << endl;
                                    break;
                                }
                                letter++;
                                o--;
                            }
                            direction++;
                        }
                        else if(direction == 7) { //kiri atas
                            letter=1;
                            n=i;
                            o=j;
                            while(letter<answerList[k].length() && n>=0 && o>=0 && found != true) {
                                if(answerList[k][letter] != matrix[n-1][o-1]) {
                                    break;
                                }
                                else if(letter == answerList[k].length()-1) {
                                    found = true;
                                    cout << "(" << i << "," << j << ")" << "to" << "(" << n-1 << "," << o-1 << ")" << endl;
                                    cout << "Kiri Atas" << endl;
                                    cout << displayAnswerMatrix(row, col, i, j, n-1, o-1, answerList[k]) << endl;
                                    break;
                                }
                                letter++;
                                n--;
                                o--;
                            }
                            direction++;
                        }
                    }
                }
                else if(i==row-1 && j==col-1){
                    cout<<"kata tidak ditemukan"<<endl;
                }
                j++;
            }
            i++;
        }
    }
    
    readFile.close();
}
