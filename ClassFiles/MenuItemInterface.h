#ifndef MENUITEMINTERFACE_H
#define MENUITEMINTERFACE_H
#endif
#include "string"

class MenuItemInterface {
	public:
		virtual bool loadMedia() = 0;
		virtual void render() = 0;
		virtual void tick() = 0;
		virtual void setX(int x) = 0;
		virtual void setY(int y) = 0;
		virtual int getX() = 0;
		virtual int getY() = 0;
		virtual int getW() = 0;
		virtual int getH() = 0;
		virtual void free() = 0;
		virtual std::string getType() = 0;
};
