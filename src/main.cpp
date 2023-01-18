#include <iostream>
using namespace std;

int convertCharToInt(char cards){
    switch(cards){
        case 'A':
            return 1;
        case 'J':
            return 10;
        case 'Q':
            return 11;
        case 'K':
            return 12;
        default:
            return int(cards)-48;
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
    char charCards[4];
    char operators[4] = {'+', '-', '*', '/'};
    int intCards[4];
    
    cout << "Silahkan input 4 kartu: " << endl;
    cin >> charCards;

    // Proses konversi array of char ke array of int
    for(int i=0; i < 4; i++){
        intCards[i] = convertCharToInt(charCards[i]);
    }

    // bikin array permutasi dari num, array permutasi dari op
    // posisi kurung yang ada
    // (a op b) op (c op d), ((a op b) op c) op d, (a op (b op c)) op d, a op ((b op c) op d), a op (b op (c op d))
    // jumlah permutasi dari angka adalah -> 4! = 24 permutasi
    // jumlah permutasi dari operator adalah -> 4 * 4 * 4 * 4 -> 4^4 = 256 permutasi
    // untuk setiap permutasi angka dan permutasi operator ada 5 permutasi kurung
    // total operasi yang dilakukan adalah 24 * 256 * 5 = 30.720 operasi

    return 0;
}
