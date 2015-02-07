#pragma once

#include "ofMain.h"

const static int WINDOW_EDGE_CURSOR_LIMIT = 50;

class MousePositionHandler
{
public:
	MousePositionHandler(): currentX(0), currentY(0), lastX(0), lastY(0) {}
	MousePositionHandler(int x, int y);
	~MousePositionHandler(void) {}

	void update(int x, int y);
	void setCursorPos(int x, int y);
	int getMouseX();
	int getMouseY();
	int getRelPosX();
	int getRelPosY();

private:
	void centerCursorPosition();
	bool mouseIsNearTheEdgeOfWindow();

	int currentX;
	int currentY;
	int lastX;
	int lastY;
	int relPosX;
	int relPosY;
};

