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
    return true;
}

// Moves the last element of the data structure as the first one.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::bottom_to_top() {
    if(top_ == nullptr) {
        return false;
    }
    Card_data* chosen_card = top_;
    Card_data* prev_chosen = nullptr;

    //prev_chosen will be the second last card
    // chosen_card will be the last card
    while(chosen_card->next != nullptr) {
        prev_chosen = chosen_card;
        chosen_card = chosen_card->next;
    }
    chosen_card->next = top_;
    top_ = chosen_card;
    prev_chosen->next = nullptr;
    return true;
}

// Moves the first element of the data structure as the last one.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::top_to_bottom() {
    if(top_ == nullptr) {
        return false;
    }
    Card_data* prev_top = top_;
    top_ = top_->next;
    Card_data* last_card = top_;

    while(last_card->next != nullptr) {
        last_card = last_card->next;
    }
    prev_top->next = nullptr;
    last_card->next = prev_top;
    return true;

}

void Cards::print_from_bottom_to_top(ostream &s)
{
    s << "";

}


void Cards::print_from_top_to_bottom(std::ostream& s) {
    Card_data* to_be_printed = top_;
    int running_number = 1;

    while(to_be_printed != nullptr) {
        s << running_number << ": " << to_be_printed->data << endl;
        ++running_number;
        to_be_printed = to_be_printed->next;
    }
}





