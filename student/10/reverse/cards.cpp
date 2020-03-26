#include <iostream>
#include <memory>
#include "cards.hh"

using namespace std;


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

// Removes the topmost card and passes it in the reference parameter id.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::remove(int &id) {
    if(top_ == nullptr) {
        return false;
    }
    else {
        shared_ptr<Card_data> removable_ptr = top_;
        id = removable_ptr->data;
        top_ = top_->next;
        return true;
    }
}

// Reverses the content of the data structure as opposite.
void Cards::reverse() {
    shared_ptr<Card_data> bottom = top_;
    int i = 0;
    while ( bottom->next != nullptr ) {
       bottom = bottom->next;
       ++i;
    }



    shared_ptr<Card_data> chosen_card = top_;
    shared_ptr<Card_data> prev_chosen;
   /* while(chosen_card->next != nullptr) {
        prev_chosen = chosen_card;
        chosen_card = chosen_card->next;
        top_ = chosen_card;
}*/
    //card values: 1,2,3,4,5
    //chosen: 5
    chosen_card = chosen_card->next; //chosen: 4
    int n = 1;
    while(chosen_card->next != nullptr) {
        prev_chosen = chosen_card; //prev_chosen = 4
        chosen_card = chosen_card->next; //chosen_card = 3
        //top_ = 5
        prev_chosen->next = top_;
        if(n == 1) {
            top_->next = nullptr;
            n = 0;
        }
        top_ = prev_chosen;
    }
    chosen_card->next = top_;
    top_ = chosen_card;
}

// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file reverse.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in reverse.cpp

















