#include <iostream>
#include <sstream> 
#include <string>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <chrono>
using namespace std;

bool correctInput(string *num){
    if (*num == "A" || *num == "J" || *num == "Q" || *num == "K" || *num == "2" || *num == "3" || *num == "4"
    || *num == "5" || *num == "6" || *num == "7" || *num == "8" || *num == "9" || *num == "10" || *num == "1"
    || *num == "11" || *num == "12" || *num == "13"){
        return 1;
    } else {
        return 0;
    }
}

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

void randomizeCard(int* card){
    int i;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    for(i = 0; i < 4; i++){
        card[i] = 1 + (rand() % 13);
    }
}

int menuMode(){
    int choice;
    cout << "Selamat datang di 24 Game Solver!" << endl;
    while(true){
        cout << "Pilih menu yang anda inginkan: " << endl;
        cout << "1. Random Card | Kartu yang dihasilkan akan digenerate secara random" << endl;
        cout << "2. Isi Sendiri | Masukkan nilai kartu sendiri" << endl;
        cout << "3. Keluar Program | Exit" << endl;
        cin >> choice;
        if (choice == 1 || choice == 2 || choice == 3){
            break;
        }
        cout << "Masukan tidak valid!" << endl;
    }
    return choice;
}

void clearDuplicate(int cards[24][4]){
    int count = 0;
    for(int i = 0; i < 24; i++){
        for(int j = i + 1; j < 24 ; j++){
            
            if (cards[j][0] == -1){
                continue;
            } else {
                count = 0;
                for(int k = 0; k < 4; k++){
                    if (cards[i][k] == cards[j][k]){
                        count++;
                    } else {
                        break;
                    }
                }
                if (count == 4){
                    for(int k = 0; k < 4; k++){
                        cards[j][k] = -1;
                    }
                }
            }
        }
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
    
    int choice = menuMode();

    if (choice == 1){
        randomizeCard(intCards);
        cout << "Kartu yang dihasilkan adalah: " << intCards[0] << " " << intCards[1] << " " << intCards[2] << " " << intCards[3] << endl;
    } else if (choice == 2) {
        while(true){
            cout << "Silahkan input 4 kartu anda: " << endl;
            cin >> n1 >> n2 >> n3 >> n4;
            if (correctInput(&n1) && correctInput(&n2) && correctInput(&n3) && correctInput(&n4)){
                intCards[0] = convertStrToInt(&n1);
                intCards[1] = convertStrToInt(&n2);
                intCards[2] = convertStrToInt(&n3);
                intCards[3] = convertStrToInt(&n4);
                break;
            } else {
                cout << "Masukan tidak valid!" << endl;
            }
        }
    } else {
        cout << "Program dihentikan" << endl;
        exit(0);
    }

    char saveChoice;
    cout << "Apakah anda mau untuk menghitung tanpa solusi double? (jika ada angka sama) (y/n)" << endl;
    cin >> saveChoice;
    
    /* Begin time measurement */
    auto begin = std::chrono::high_resolution_clock::now();

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

    if (saveChoice == 'y' || saveChoice == 'Y'){
        clearDuplicate(permCards);
    }

    float total;
    int totalVariation = 0;
    std::stringstream buffer;
    for(i = 0; i < countNum; i++){
        for (j = 0; j < countOp; j++){
            
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
                buffer << "(" << a << op1 << b << ")" << op2 << "(" << c << op3 << d << ")" << endl;
                totalVariation++;
            }

            // Posisi Kurung 2 ((a op b) op c) op d
            total = calculate(calculate(calculate(a, b, op1), c, op2), d, op3);
            if (abs(total-24) < 0.00001){
                buffer << "((" << a << op1 << b << ")" << op2 << c << ")" << op3 << d << endl;
                totalVariation++;
            }

            //Posisi Kurung 3 (a op (b op c)) op d
            total = calculate(calculate(a, calculate(b, c, op2), op1), d, op3);
            if (abs(total-24) < 0.00001){
                buffer << "(" << a << op1 << "(" << b << op2 << c << "))" << op3 << d << endl;
                totalVariation++;
            }

            // Posisi Kurung 4 a op ((b op c) op d)
            total = calculate(a, calculate(calculate(b, c, op2), d, op3), op1);
            if (abs(total-24) < 0.00001){
                buffer << a << op1 << "((" << b << op2 << c << ")" << op3  << d << ")" << endl;
                totalVariation++;
            }

            // Posisi Kurung 5 a op (b op (c op d))
            total = calculate(a, calculate(b, calculate(c, d, op3), op2), op1); 
            if (abs(total-24) < 0.00001){
                buffer << a << op1 << "(" << b << op2 << "(" << c << op3 << d << "))" << endl;
                totalVariation++;
            }
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    if (totalVariation > 0){
        cout << "Ada sebanyak " << totalVariation << " solusi" << endl;
    } else {
        cout << "Tidak ada solusi" << endl;
        exit(0);
    }

    cout << buffer.str() << endl;
    cout << "Waktu terukur: " << elapsed.count() * 1e-9 << " seconds" << endl;

    // Mekanisme saving file
    while(true && totalVariation > 0){
        cout << "Apakah anda ingin menyimpan solusi ini? y/n" << endl;
        cin >> saveChoice;
        if(saveChoice == 'y' || saveChoice == 'Y'){
            string namaFile;
            cout << "Apa nama file yang anda akan simpan?" << endl;
            cin >> namaFile;
            ofstream output;
            output.open("test/" + namaFile + ".txt");
            output << buffer.str();
            output.close();
            cout << "File " << namaFile << ".txt berhasil dibuat, silahkan cek di folder test" << endl;
            break;
        } else if (saveChoice == 'n' || saveChoice == 'N'){
            cout << "Program dihentikan" << endl;
            break;
        }
    }

    return 0;
}