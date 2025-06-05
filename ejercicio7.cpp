#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

string constructHalf(int* digits){
    string newNumber;
    int currentDigit = 9;
    while (currentDigit >= 0){
        if (digits[currentDigit] >= 2){
            newNumber += char('0' + currentDigit);
            digits[currentDigit] -= 2;
        } else {
            currentDigit--;
            //Si llegamos al 0 y no añadimos nada entonces no hay palindromo válido
            if (currentDigit == 0 && newNumber.length() == 0){
                return "";
            }
        }
    }
    return newNumber;
}

char* findLargestDigit(int* digits){
    int currentDigit = 9;
    while (currentDigit >= 0){
        if (digits[currentDigit] >= 1){
            return new char('0' + currentDigit);
        } else {
            currentDigit--;
        }
    }
    return nullptr;
}

int main()
{
    string number;
    cin >> number;
    int originalLen = number.length();
    int* digits = new int[10]();

    for(int i=0; i<number.length(); i++){
        int digit = number[i] - '0';
        digits[digit]++;
    }

    //cout << "[" << digits[0] << "," << digits[1] << "," << digits[2] << "," << digits[3] << "," << digits[4] << "," << digits[5] << "," << digits[6] << "," << digits[7] << "," << digits[8] << "," << digits[9] << "]" <<endl;

    //first find pairs
    string firstHalf = constructHalf(digits);
    if (firstHalf == ""){
        cout << "No" << endl;
        return 0;
    }
    //cout << firstHalf << endl;
    
    //then find largest number for the center
    char* centerDigit = findLargestDigit(digits);

    string result;
    for(int i=0; i<firstHalf.size(); i++){
        result += firstHalf[i];
    }
    if (centerDigit != nullptr){
        result += *centerDigit;
    }
    for(int i=firstHalf.size()-1; i>=0; i--){
        result += firstHalf[i];
    }

    //Usamos todos los números
    if (result.length() != originalLen){
        cout << "No" << endl;
        return 0;
    }

    cout << result << endl;

    return 0;
}

//Dado un número, imprimir el palíndromo más grande posible usando todas las cifras. En caso de no ser posible, imprimir "No".

//O(N) Siendo N la cantidad de dígitos del número.