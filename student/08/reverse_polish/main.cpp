#include <iostream>

using namespace std;

int main()
{
    cout << "Input an expression in reverse Polish notation (end with #):" << endl;
    cout << "EXPR> ";
    char c;
    int N = 80;
    int u;
    char merkit[N];
    for(int i = 0; i < N; ++i) {
        cin >> c;
        if(c == ' ') {
            continue;
        }
        merkit[i] = c;

        if(c == '#') {
            u = i;
            break;
        }
    }

    for(int i = 0; i < u; ++i) {
        cout << merkit[i];
    }












    return 0;
}
