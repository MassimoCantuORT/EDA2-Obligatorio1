#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

bool symbolsMatch(char textChar, char patternChar){
    if (patternChar == '.') return true;
    return textChar == patternChar;
}

int patternMatch(string text, string pattern, int textIndex, int patternIndex, int** matchCache){
    if (patternIndex == -1) return (textIndex == -1)?1:0;
    if (textIndex == -1) {
        if (patternIndex >= 0 && pattern[patternIndex] == '*'){
            return patternMatch(text, pattern, textIndex, patternIndex-2, matchCache);
        }
        return 0;
    }

    if (matchCache[textIndex][patternIndex] != -1){ //ya sabemos la respuesta
        return matchCache[textIndex][patternIndex];
    }

    //caso normal
    if (symbolsMatch(text[textIndex], pattern[patternIndex])){
        int result = patternMatch(text, pattern, textIndex-1, patternIndex-1, matchCache);
        matchCache[textIndex][patternIndex] = result;
        return result;
    }
    //caso asterisco
    if (pattern[patternIndex] == '*'){
         int zeroResult = patternMatch(text, pattern, textIndex, patternIndex-2, matchCache);
         int oneResult = symbolsMatch(text[textIndex], pattern[patternIndex-1]) 
                    && patternMatch(text, pattern, textIndex-1, patternIndex, matchCache);
         int result = ((zeroResult==1) || (oneResult==1))?1:0;
         matchCache[textIndex][patternIndex] = result;
         return result;
    }

    return 0;
}

string readCache(int value){
    if (value == -1) return "-";
    if (value == 0) return "F";
    if (value == 1) return "T";
    return to_string(value);
}

int main()
{
    string text, pattern;
    cin >> text >> pattern;

    int textLength = text.length();
    int patternLength = pattern.length();
    int** matchCache = new int*[textLength];
    for (int i=0; i<textLength; i++){
        matchCache[i] = new int[patternLength];
            for (int j=0; j<patternLength; j++){
                matchCache[i][j] = -1; //-1 significa "sin explorar"
            }
    }

    bool matched = patternMatch(text, pattern, textLength-1, patternLength-1, matchCache);

    cout << (matched?"true":"false") << endl;

    // cout << "  | ";
    // for (int i=0; i<patternLength; i++){
    //     cout << (pattern[i]) << " | ";
    // }
    // cout << endl;
    // for (int i=0; i<textLength; i++){
    //     cout << (text[i]) << " | ";
    //     for (int j=0; j<patternLength; j++){
    //         cout << readCache(matchCache[i][j]) << " | ";
    //     }
    //     cout << endl;
    // }
    
    return 0;
}

//Se rompió grep, y como buenos ingenieros, no se les ocurrió mejor idea que reescribirlo desde cero.

//Dado un texto t formado por letras minúsculas, y un patrón p formado por letras minúsculas y dos carateres 
//especiales . y *, de forma que:

// . representa a un caracter cualquiera
// * representa a 0 o más del caracter anterior
//Se pide indicar si el texto cumple con el patrón.