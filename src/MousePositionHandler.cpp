#include "MousePositionHandler.h"

MousePositionHandler::MousePositionHandler(int x, int y)
	: currentX(x), currentY(y), lastX(x), lastY(y), relPosX(0), relPosY(0)
{
	this->setCursorPos(currentX, currentY);
}

void MousePositionHandler::update(int x, int y)
{
	lastX = currentX;
	lastY = currentY;
	currentX = x;
	currentY = y;
	relPosX = currentX - lastX;
	relPosY = currentY - lastY;
	cout << this->mouseIsNearTheEdgeOfWindow() << endl;
	if(this->mouseIsNearTheEdgeOfWindow())
	{
		this->centerCursorPosition();
	}
}

bool MousePositionHandler::mouseIsNearTheEdgeOfWindow()
{
	if(currentX < WINDOW_EDGE_CURSOR_LIMIT)
		return true;
	else if (currentY < WINDOW_EDGE_CURSOR_LIMIT)
		return true;
	else if(currentX > ofGetWindowWidth() - WINDOW_EDGE_CURSOR_LIMIT)
		return true;
	else if(currentY > ofGetWindowHeight() - WINDOW_EDGE_CURSOR_LIMIT)
		return true;
	return false;
}

void MousePositionHandler::centerCursorPosition()
{
	setCursorPos(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
	lastX = currentX + relPosX;
	lastY = currentY + relPosY;
}

void MousePositionHandler::setCursorPos(int x, int y)
{
	SetCursorPos(x, y);
}

int MousePositionHandler::getMouseX()
{
	return currentX;
}

int MousePositionHandler::getMouseY()
{
	return currentY;
}

int MousePositionHandler::getRelPosX()
{
	return relPosX;
}

int MousePositionHandler::getRelPosY()
{
	return relPosY;
}