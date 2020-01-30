#ifndef PLAYER_HH
#define PLAYER_HH
#include <iostream>
#include <string>

using namespace std;

class Player{
public:
    Player(string nimi);
    string get_name() const;
    int get_points();
    bool has_won();
    void add_points(int lisattavat_pisteet);
private:
    string nimi_;
    int pisteet_ = 0;
};

#endif // PLAYER_HH
