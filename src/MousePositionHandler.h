#pragma once

#include "ofMain.h"

const static int WINDOW_EDGE_CURSOR_LIMIT = 300;

class MousePositionHandler
{
public:
	MousePositionHandler();
	~MousePositionHandler(void) {}

	void update(int x, int y);
	void setCursorPos(int x, int y);
	void resetCusor();
	int getRelPosX();
	int getRelPosY();

private:
	void centerCursorPosition();
	bool mouseIsNearTheEdgeOfWindow();

	int currentX;
	int currentY;
	int relPosX;
	int relPosY;
};

