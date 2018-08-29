#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#endif
#include <array>
#include <vector>
#ifndef PLAYERLEFT_H
#define PLAYERLEFT_H
#include "PlayerLeft.h"
#endif
#ifndef PLAYERRIGHT_H
#define PLAYERRIGHT_H
#include "PlayerRight.h"
#endif


class Observable {
protected:
	std::vector<Observer*> obs_list;
public:
	Observable();
	~Observable();
	bool attach(Observer* obs);
	bool detach(Observer* obs);
	void notify();
}; 
