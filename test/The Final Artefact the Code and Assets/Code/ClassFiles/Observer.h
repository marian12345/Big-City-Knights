#ifndef OBSERVER_H
#define OBSERVER_H
#endif
#include <SDL.h>
#include <vector>

class Observer {
public:
	virtual void update(int collided_with, int own_collider, SDL_Rect rec) = 0;
	virtual std::vector<SDL_Rect> getColliders() = 0;
	virtual int getColliderType(int index_in_vector) = 0;
};