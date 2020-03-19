#include "cards.hh"

using namespace std;

Cards::Cards(): top_(nullptr) {
}

Cards::~Cards() {
    while(top_ != nullptr) {
        Card_data* to_be_deleted = top_;
        top_ = top_->next;
        delete to_be_deleted;
    }
}

void Cards::add(int id) {
    Card_data* new_item = new Card_data{id, nullptr};

    if(top_ == nullptr) {
        top_ = new_item;
    }
    else {
        //edelliseksi viimeisenä olleen nextiksi laitetaan uusi viimeisenä oleva
       //(edellisen viimeisenä olleen nexti oli ennen nullptr)
        Card_data* previous_item = top_;
        top_ = new_item;
        top_->next = previous_item;
    }
}

// Removes the topmost card and passes it in the reference parameter id.
// Returns false, if the data structure is empty, otherwise returns true.
// HOX: otetaan kortti pois siitä kohtaan
bool Cards::remove(int& id){
    if(top_ == nullptr) {
        return false;
    }
    else {
        Card_data* to_be_removed = top_;
        id = to_be_removed->data;
        top_ = top_->next;
        delete to_be_removed;
    }
}


void Cards::print_from_top_to_bottom(std::ostream& s) {
    Card_data* to_be_printed = top_;
    int running_number = 1;

    while(to_be_printed != nullptr) {
        cout << running_number << ": " << to_be_printed->data << endl;
        ++running_number;
        to_be_printed = to_be_printed->next;
    }
}





