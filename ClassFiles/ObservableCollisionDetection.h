#ifndef OBSERVABLECOLLISIONDETECTION_H
#define OBSERVABLECOLLISIONDETECTION_H
#endif
#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#include "Observable.h"
#endif
#include <array>
#include <string>

class ObservableCollisionDetection : public Observable {
	private:
		ObservableCollisionDetection();
		static ObservableCollisionDetection* cd;
		bool collisionBetween(SDL_Rect* a, SDL_Rect* b);
		bool intersect(int start1, int end1, int start2, int end2);
	public:
		static ObservableCollisionDetection* getInstance();
		~ObservableCollisionDetection();
		void checkCollisions();
};