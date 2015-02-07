#pragma once

#include "ofMain.h"
#include "Shader.h"
#include "camera.h"
#include "Cube.h"
#include "Axes.h"
#include "MousePositionHandler.h"

const static float ROTATION_SPEED = 2.0;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		~ofApp();

	private:
		Shader m_shader;
		Camera m_camera;

		ofMatrix4x4 m_projection;
		ofMatrix4x4 m_modelview;

		int m_largeurFenetre;
		int m_hauteurFenetre;

		float m_angle;

		Axes m_axes;

		bool m_pause;

		int dernierePositionX;
		int dernierePositionY;

		MousePositionHandler* mouseHandler;
};
