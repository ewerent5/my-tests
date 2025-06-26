// Автомат батончиков

#include "Snack.h"

int main() {
	Snack* bounty = new Snack("Bounty"); // создаём батончики
	Snack* snickers = new Snack("Snickers");

	SnackSlot* ddr = new SnackSlot(3);// пишем размер хранилища
	ddr->addSnack(bounty);
	ddr->addSnack(snickers);
	ddr->show_();

	Slot* slot_1 = new Slot(4); // создание слотов
	slot_1->addSlot(ddr);// в 1 слот 2 батончика
	slot_1->show();

	std::cout << slot_1->getFreeSlotsCount() << std::endl;

	delete slot_1;
	delete bounty;
	delete snickers;
	delete ddr;

	
}