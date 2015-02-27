#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "ofMain.h"
#include "MousePositionHandler.h"


class Camera
{
    public:
		Camera();
		Camera(ofVec3f _position, ofVec3f _pointCible, ofVec3f _axeVertical, float _sensibilite, float _vitesse, MousePositionHandler *mouse);
		~Camera() {}

		void update();
		void setPosition(ofVec3f _position);
		void lookAt(ofMatrix4x4 &modelview);

		float getSensibilite() const;
		float getVitesse() const;
		ofVec3f getPosition() const;
		bool isMovingForward() const;
		bool isMovingBackward() const;
		bool isMovingRight() const;
		bool isMovingLeft() const;

		void setMoveForward(bool isMoving);
		void setMoveBackward(bool isMoving);
		void setMoveLeft(bool isMoving);
		void setMoveRight(bool isMoving);
		void setSensibilite(float _sensibilite);
		void setVitesse(float _vitesse);

    private:
		void orienter();
		void deplacer();

		float m_phi;
		float m_theta;
		ofVec3f m_orientation;

		ofVec3f m_axeVertical;
		ofVec3f m_deplacementLateral;
		bool movingForward;
		bool movingBackward;
		bool movingLeft;
		bool movingRight;

		ofVec3f m_position;
		ofVec3f m_pointCible;

		float m_sensibilite;
		float m_vitesse;

		MousePositionHandler* mouseHandler;
};

#endif