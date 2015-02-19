#include "MousePositionHandler.h"

MousePositionHandler::MousePositionHandler()
	: relPosX(0), relPosY(0)
{
	this->centerCursorPosition();
}

void MousePositionHandler::update(int x, int y)
{
	int lastX = currentX;
	int lastY = currentY;
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
	currentX = ofGetWindowWidth() * 0.5;
	currentY = ofGetWindowHeight() * 0.5;
	setCursorPos(currentX + ofGetWindowPositionX(), currentY + ofGetWindowPositionY());
}

void MousePositionHandler::setCursorPos(int x, int y)
{
	SetCursorPos(x, y);
}

void MousePositionHandler::resetCusor(){
	SetCursorPos(currentX + ofGetWindowPositionX(), currentY + ofGetWindowPositionY());
}

int MousePositionHandler::getRelPosX(){
	return relPosX;
}

int MousePositionHandler::getRelPosY(){
	return relPosY;
}