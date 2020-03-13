#include "array_operations.hh"

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


    int* a_osoitin = itemptr;
    int* b_osoitin = targetptr;
    while(a_osoitin != endptr) {
        *b_osoitin = *a_osoitin;
        ++b_osoitin;
        ++a_osoitin;
    }
}

void reverse(int* leftptr, int* rightptr) {
    int* v_leftptr = leftptr;
    int* v_rightptr = rightptr - 1;

    while(v_leftptr < v_rightptr) {
        int temp = *v_leftptr;
        *v_leftptr = *v_rightptr;
        *v_rightptr = temp;
        ++v_leftptr;
        --v_rightptr;
    }
}
