#include <iostream>

using namespace std;

bool is_too_few_operands(int index) {
    if (index == 1) {
        return true;
    }
    else{
        return false;
    }
}

int main()
{
    cout << "Input an expression in reverse Polish notation (end with #):" << endl;
    cout << "EXPR> ";
    char c;
    int N = 80;
    int index = 0;
    int merkit[N];
    bool failure = false;
    while(true) {
        cin >> c;
        if(c == ' ') {
            continue;
        }

        if(c =='+' || c =='-' || c =='*' || c =='/') {
            if(is_too_few_operands(index) == true) {
                cout << "Error: Too few operands" << endl;
                failure = true;
                break;
            }
            else if(index == 0) {
                cout << "Error: Expression must start with a number"
                     << endl;
                failure = true;
                break;
            }

            else if(c == '+') {
                merkit[index - 2] = merkit[index - 2] + merkit[index - 1];
                merkit[index - 1] = -1;
                index -= 2;
            }
            else if(c == '-') {
                merkit[index - 2] = merkit[index - 2] - merkit[index - 1];
                merkit[index - 1] = -1;
                index -= 2;
            }
            else if(c == '*') {
                merkit[index - 2] = merkit[index - 2] * merkit[index - 1];
                merkit[index - 1] = -1;
                index -= 2;
            }
            else if(c == '/') {
                if(merkit[index - 1] == 0) {
                    cout << "Error: Division by zero" << endl;
                    failure = true;
                    break;
                }
                merkit[index - 2] = merkit[index - 2] / merkit[index - 1];
                merkit[index - 1] = -1;
                index -= 2;
            }
        }
        else if(c == '#') {
            break;
        }
        else if(c < 48 || c > 59) {
            cout << "Error: Unknown character" << endl;
            failure = true;
            break;
        }
        else {
            merkit[index] = c - 48;
        }
        ++index;
    }
    if(failure == true) {
        return 1;
    }
    if(merkit[1] != -1) {
        cout << "Error: Too few operators" << endl;
        failure = true;
    }
    if(failure == true) {
        return 1;
    }
    else{
        cout << "Correct: " << merkit[0]
             << " is the result" << endl;
        return 0;
    }
}
