#include "MousePositionHandler.h"

MousePositionHandler::MousePositionHandler(int x, int y)
	: currentX(x), currentY(y), lastX(x), lastY(y), relPosX(0), relPosY(0)
{
	this->centerCursorPosition();
}

void MousePositionHandler::update(int x, int y)
{
	lastX = currentX;
	lastY = currentY;
	currentX = x;
	currentY = y;
	relPosX = currentX - lastX;
	relPosY = currentY - lastY;
	if(this->mouseIsNearTheEdgeOfWindow())
		this->centerCursorPosition();
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
	currentX = ofGetWindowWidth() / 2;
	currentY = ofGetWindowHeight() / 2;
	setCursorPos(ofGetWindowWidth()/2 + ofGetWindowPositionX(), ofGetWindowHeight()/2 + ofGetWindowPositionY());
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