#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
using namespace std;

//Todo: Randomizer, Save Hasil

int convertStrToInt(string* num){
    if (*num == "A"){
        return 1;
    } else if (*num == "J") {
        return 11;
    } else if (*num == "Q") {
        return 12;
    } else if (*num == "K") {
        return 13;
    } else {
        return stoi(*num);
    }
}

float calculate(float num1, float num2, char op){
    switch(op){
        case '+':
            return (num1 + num2);
        case '-':
            return (num1 - num2);
        case '/':
            return num1/num2;
        default:
            return (num1 * num2);
    }
}

int main() {
    string n1, n2, n3, n4;
    int i, j, k, l;
    int a, b, c, d;
    char op1, op2, op3;
    char operators[4] = {'+', '-', '*', '/'};
    char permOp[64][3];
    int intCards[4];
    int permCards[24][4];
    
    cout << "Silahkan input 4 kartu: " << endl;
    cin >> n1;
    cin >> n2;
    cin >> n3;
    cin >> n4;

    // proses konversi string ke array of int
    intCards[0] = convertStrToInt(&n1);
    intCards[1] = convertStrToInt(&n2);
    intCards[2] = convertStrToInt(&n3);
    intCards[3] = convertStrToInt(&n4);

    // Membuat permutasi operator
    int countOp = 0;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            for(k = 0; k < 4; k++){
                    permOp[countOp][0] = operators[i]; 
                    permOp[countOp][1] = operators[j];
                    permOp[countOp][2] = operators[k];
                    countOp++;
            }
        }
    }

    // Membuat permutasi angka
    int countNum = 0;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(i == j){
                continue;
            }
            for(k = 0; k < 4; k++){
                if (k == j || k == i){
                    continue;
                }
                for(l = 0; l < 4; l++){
                    if (l == i || l == j || l == k){
                        continue;
                    }
                    permCards[countNum][0] = intCards[i];
                    permCards[countNum][1] = intCards[j];
                    permCards[countNum][2] = intCards[k];
                    permCards[countNum][3] = intCards[l];
                    countNum++;
                }
            }
        }
    }

    // for(int i=0; i < countNum; i++){
    //     cout << permCards[i][0] << permCards[i][1]  << permCards[i][2]  << permCards[i][3]  << endl;
    // }

    float total;
    int totalVariation = 0;
    for(i = 0; i < countNum ; i++){
        for (j = 0; j < countOp ; j++){
            a = (float) permCards[i][0];
            b = (float) permCards[i][1];
            c = (float) permCards[i][2];
            d = (float) permCards[i][3];
            op1 = permOp[j][0];
            op2 = permOp[j][1];
            op3 = permOp[j][2];

            // Posisi Kurung 1 (a op b) op (c op d)
            total = calculate(calculate(a, b, op1), calculate(c, d, op3), op2);
            if (abs(total-24) < 0.00001){
                cout << "(" << a << op1 << b << ")" << op2 << "(" << c << op3 << d << ")" << endl;
                totalVariation++;
            }

            // Posisi Kurung 2 ((a op b) op c) op d
            total = calculate(calculate(calculate(a, b, op1), c, op2), d, op3);
            if (abs(total-24) < 0.00001){
                cout << "((" << a << op1 << b << ")" << op2 << c << ")" << op3 << d << endl;
                totalVariation++;
            }

            //Posisi Kurung 3 (a op (b op c)) op d
            total = calculate(calculate(a, calculate(b, c, op2), op1), d, op3);
            if (abs(total-24) < 0.00001){
                cout << "(" << a << op1 << "(" << b << op2 << c << "))" << op3 << d << endl;
                totalVariation++;
            }

            // Posisi Kurung 4 a op ((b op c) op d)
            total = calculate(a, calculate(calculate(b, c, op2), d, op3), op1);
            if (abs(total-24) < 0.00001){
                cout << a << op1 << "((" << b << op2 << c << ")" << op3  << d << ")" << endl;
                totalVariation++;
            }

            // Posisi Kurung 5 a op (b op (c op d))
            total = calculate(a, calculate(b, calculate(c, d, op3), op2), op1); 
            if (abs(total-24) < 0.00001){
                cout << a << op1 << "(" << b << op2 << "(" << c << op3 << d << "))" << endl;
                totalVariation++;
            }
        }
    }

    cout << "Ada sebanyak " << totalVariation << " solusi.";

    return 0;
}
