#include "queue.hh"
#include <iostream>

using namespace std;

Queue::Queue(unsigned int cycle){
    cycle_ = cycle;
}

Queue::~Queue(){
    while(first_ != nullptr) {
        Vehicle* to_be_deleted = first_;
        first_ = first_->next;

        delete to_be_deleted;
    }
}

void Queue::enqueue(string reg_num) {
    Vehicle* vehicle_reg = new Vehicle{reg_num, nullptr};
    if(first_ != nullptr) {
        last_->next = vehicle_reg;
        last_ = vehicle_reg; //lastillä ei ole nextiä
    }
    else { // first_ == nullptr
        if(is_green_) {
            cout << "GREEN: The vehicle " << vehicle_reg->reg_num
                 << " need not stop to wait" << endl;
            delete vehicle_reg;
        }
        else {
            first_ = vehicle_reg;
            last_ = vehicle_reg;
        }
    }
}

void Queue::dequeue() {
    if(first_ != nullptr) {
        Vehicle* leaves_queue = first_;
        first_ = first_->next;
        cout << " " << leaves_queue->reg_num;
        delete leaves_queue;
    }
}

void Queue::switch_light() {
    if(is_green_ == false) { //valo on punainen
        is_green_ = true; //valo vaihdetaan vihreäksi
        if(first_ != nullptr) { //autoja ei ole jonossa
            print();
            unsigned int i = 0;
            while(i < cycle_) {
                dequeue();
                ++i;
            }
            cout << " can go on" << endl;

            is_green_ = false;
        }
        else {
            print();
        }
    }
    else {
        is_green_ = false;
        print();
    }

}

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

void Queue::print() {
    if(not is_green_) {
        cout << "RED: ";
    }
    else {
        cout << "GREEN: ";
    }

    if(first_ == nullptr) {
        cout << "No vehicles waiting in traffic lights" << endl;
    }
    else if(not is_green_){
        cout << "Vehicle(s)";
        Vehicle* to_be_printed = first_;
        while(to_be_printed != nullptr) {
            cout << " " << to_be_printed->reg_num;
            to_be_printed = to_be_printed->next;
        }
        cout << " waiting in traffic lights" << endl;
    }
    else if(is_green_) {
        cout << "Vehicle(s)";

    }
}









