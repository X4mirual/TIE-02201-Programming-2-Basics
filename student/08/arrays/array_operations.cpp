#include "array_operations.hh"
#include <iostream>

int greatest_v1(int* itemptr, int size) {
    int greatest = 0;
    int* taulukko_osoitin = itemptr;
    while(taulukko_osoitin < itemptr + size) {
        if(*taulukko_osoitin > greatest) {
            greatest = *taulukko_osoitin;
        }
        ++taulukko_osoitin;
    }
    return greatest;
}

int greatest_v2(int* itemptr, int* endptr) {
    int greatest = 0;
    int* taulukko_osoitin = itemptr;
    while(taulukko_osoitin < endptr) {
        if(*taulukko_osoitin > greatest) {
            greatest = *taulukko_osoitin;
        }
        ++taulukko_osoitin;
    }
    return greatest;
}

void copy(int* itemptr, int* endptr, int* targetptr) {
    int i = 0;
    --endptr;
    while(i < 30) {
        targetptr[i] = itemptr[i];
        ++i;
    }
}

/* Reverses the elements of the array
 * int* leftptr: pointer to the first element of the reversable part
 * int* rightptr: pointer to the next memory address after the reversable part
 */
void reverse(int* leftptr, int* rightptr) {
    --rightptr;
    while(leftptr < rightptr) {
        int temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;
        ++leftptr;
        --rightptr;
    }
}














