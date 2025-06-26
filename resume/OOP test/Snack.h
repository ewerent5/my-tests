#pragma once
#include <string>
#include <iostream>

class Snack { // класс батончиков 
public:
	Snack(const std::string& name);// копи. имя
	std::string getName() const;// return name_ = ( const std::string& name)
		
private:
	std::string name_;
};

class SnackSlot {
public:
	SnackSlot(const unsigned short size);// размер хранилища
	void addSnack(Snack* snack);// add
	void show_() const; 
private:
	unsigned short size_{ 0 };
	Snack** array_{ nullptr };
	unsigned short counter{ 0 };
};


class Slot {
public:
	Slot(const unsigned short size); // создание сслотов
	void addSlot(SnackSlot* slot);// добавление в слот
	void show() const;
	int getFreeSlotsCount() const;
private:
	unsigned short size_{ 0 };
	SnackSlot** array_ = {nullptr};
	unsigned short counter{ 0 };
};