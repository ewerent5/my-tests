#include "Snack.h"

Snack::Snack(const std::string& name) : name_(name) {
}
std::string Snack::getName() const {
	return name_;
}


SnackSlot::SnackSlot(const unsigned short size) : size_(size){
	array_ = new Snack * [size] {nullptr}; // all value = {nullptr}
}
void SnackSlot::addSnack(Snack* snack) {
	array_[counter++] = snack;
}
void SnackSlot::show_() const {
	for (unsigned short i = 0; i < counter; i++) {
		std::cout << "count: " << i + 1 << ' ' << array_[i]->getName() << std::endl;
	}
}


Slot::Slot(const unsigned short size) : size_(size) {
	array_ = new SnackSlot * [size] {nullptr};  
}
void Slot::addSlot(SnackSlot* slot) {
	array_[counter++] = slot;
}
void Slot::show() const {
	for (unsigned short i = 0; i < counter; i++) {
		std::cout << "slot: " << i + 1 << std::endl;
		array_[i]->show_();
	}
}
int Slot::getFreeSlotsCount() const {
	return size_ - counter;
}

