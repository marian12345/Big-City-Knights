#include "ObservableCollisionDetection.h"

ObservableCollisionDetection* ObservableCollisionDetection::cd = NULL;

ObservableCollisionDetection::ObservableCollisionDetection() {};

void ObservableCollisionDetection::checkCollisions() {
	if (obs_list.empty() != true) {
		//Checking Collisions Algorithm
		//First loop - Grab list x
		for (int i1 = 0; i1 < obs_list.size()-1; i1++) { 
			std::vector<SDL_Rect> list_x = obs_list.at(i1)->getColliders();
			//Second Loop - to go through all the rectangles in list x
			for (int i2 = 0; i2 < list_x.size(); i2++) {
				//Only the Player class has 2 colliders, therefore i2 won't count higher than 2
				//Third loop - Grab next list y 
				for (int i3 = i1+1; i3 < obs_list.size(); i3++) {
					std::vector<SDL_Rect> list_y = obs_list.at(i3)->getColliders();
					//Fourth Loop - to go through all the rectangles in list y
					for (int i4 = 0; i4 < list_y.size(); i4++) {
						//Only the Player class has 2 colliders, therefore i4 won't count higher than 2
						//compare first_list[i2] with second_list[i4]
						if (collisionBetween(&list_x.at(i2), &list_y.at(i4)) == true) {
							// If i4 == 1 it means that list_y.at(i4) is a sword collider
							// If i2 == 1 it means that list_x.at(i2) is a sword collider
							//enum collider_types { BODY, SWORD, BOTTLE, BOTTLEHARMLESS }; 
							//update(collided_with, own_collider, rectangle with which the collision appeared);
							obs_list.at(i1)->update(obs_list.at(i3)->getColliderType(i4), obs_list.at(i1)->getColliderType(i2), list_y.at(i4));
							obs_list.at(i3)->update(obs_list.at(i1)->getColliderType(i2), obs_list.at(i3)->getColliderType(i4), list_x.at(i2));
						}
					}
				}
			}
		}
	}
};

bool ObservableCollisionDetection::intersect(int start1, int end1, int start2, int end2) {
	bool intersection = true;
	if (end1 < start2) {
		intersection = false;
	}
	else if (end2 < start1) {
		intersection = false;
	}
	return intersection;
};

bool ObservableCollisionDetection::collisionBetween(SDL_Rect* a, SDL_Rect* b) {
	bool success = false;

	if ((a != NULL) && (b != NULL)) {
		//Check if collided on x or y axis
		bool x_axis = false;
		bool y_axis = false;
		
		//Check x_axis
		if (intersect(a->x, a->x + a->w, b->x, b->x + b->w) == true) {
			x_axis = true;
			//Check y_axis
			if (intersect(a->y, a->y + a->h, b->y, b->y + b->h) == true) {
				y_axis = true;
			}
		}

		//Check for actual collision
		if ((x_axis == true) && (y_axis == true)) {
			success = true;
		}
	}

	return success;
};

ObservableCollisionDetection* ObservableCollisionDetection::getInstance() {
	if (cd == NULL) {
		cd = new ObservableCollisionDetection();
	}

	return cd;
};

ObservableCollisionDetection::~ObservableCollisionDetection() {
	cd = NULL;
};
