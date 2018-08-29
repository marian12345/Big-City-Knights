#include "Observable.h"

Observable::Observable() {
	obs_list.clear();
};

bool Observable::attach(Observer* obs) {
	bool success = true;

	//Check if obs already exists
	for (int i = 0; i < obs_list.size(); i++) {
		if (obs_list.at(i) == obs) {
			success = false;
			break;
		}
	}

	//If element is not already existing, attach it to the list
	if (success == true) {
		obs_list.push_back(obs);
	}

	return success;
};

bool Observable::detach(Observer* obs) {
	bool success = false;

	//Look for element
	for (int i = 0; i < obs_list.size(); i++) {
		//If found delete from list
		if (obs_list.at(i) == obs) {
			obs_list.erase(obs_list.begin() + i);
			success = true;
			break;
		}
	}

	return success;
};

void Observable::notify() {
};

Observable::~Observable() {
	obs_list.clear();
};