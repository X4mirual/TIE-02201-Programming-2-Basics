#include "player.hh"
#include <iostream>
#include <string>
using namespace std;


Player::Player(string nimi):
    nimi_(nimi)  {
}

string Player::get_name() const {
    return nimi_;
}

int Player::get_points() {
    return pisteet_;
}

bool Player::has_won() {
    if (pisteet_ == 50) {
        return true;
    } else {
        return false;
    }
}

void Player::add_points(int lisattavat_pisteet) {
    pisteet_ += lisattavat_pisteet;
    if (pisteet_ > 50) {
        cout << nimi_ << " gets penalty points!" << endl;
        pisteet_ = 25;
    }
}



//    string get_name() const;
//    int get_points();
//    void has_won();
//    void add_points();
