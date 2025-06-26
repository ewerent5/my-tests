#pragma once
#include <string>
#include <iostream>

class Snack { // ����� ���������� 
public:
	Snack(const std::string& name);// ����. ���
	std::string getName() const;// return name_ = ( const std::string& name)
		
private:
	std::string name_;
};

class SnackSlot {
public:
	SnackSlot(const unsigned short size);// ������ ���������
	void addSnack(Snack* snack);// add
	void show_() const; 
private:
	unsigned short size_{ 0 };
	Snack** array_{ nullptr };
	unsigned short counter{ 0 };
};


class Slot {
public:
	Slot(const unsigned short size); // �������� �������
	void addSlot(SnackSlot* slot);// ���������� � ����
	void show() const;
	int getFreeSlotsCount() const;
private:
	unsigned short size_{ 0 };
	SnackSlot** array_ = {nullptr};
	unsigned short counter{ 0 };
};