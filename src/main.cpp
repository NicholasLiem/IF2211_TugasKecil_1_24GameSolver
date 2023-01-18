#include <iostream>
#include <string>
#include <string.h>
using namespace std;

//Todo: Randomizer, Save Hasil, Gabungin Op Kurung dan Num

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

int calculate(int num1, int num2, char op){
    switch(op){
        case '+':
            return (num1 + num2);
        case '-':
            return (num1 - num2);
        case '/':
            if (num2 == 0){
                return -1;
            } else {
                return num1/num2;
            }
        default:
            return (num1 * num2);
    }
}

int main() {
    string n1, n2, n3, n4;
    char operators[4] = {'+', '-', '*', '/'};
    char permOp[256][3];
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
    for(int i=0; i < 4; i++){
        for(int j=0; j < 4; j++){
            for(int k=0; k < 4; k++){
                    permOp[i+j+k][0] = operators[i]; 
                    permOp[i+j+k][1] = operators[j];
                    permOp[i+j+k][2] = operators[k];
                    countOp++;
            }
        }
    }

    // Membuat permutasi angka
    int countNum = 0;
    for(int i=0; i < 4; i++){
        for(int j=0; j < 4; j++){
            if(i == j){
                continue;
            }
            for(int k=0; k < 4; k++){
                if (k == j || k == i){
                    continue;
                }
                for(int l=0; l < 4; l++){
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
    
    cout << countOp << countNum  << endl;

    // posisi kurung yang ada
    // (a op b) op (c op d), ((a op b) op c) op d, (a op (b op c)) op d, a op ((b op c) op d), a op (b op (c op d))i
    // untuk setiap permutasi angka dan permutasi operator ada 5 permutasi kurung
    // total operasi yang dilakukan adalah  * 256 * 5 = 30.720 operasi

    return 0;
}
