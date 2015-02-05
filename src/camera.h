#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "ofMain.h"

class Camera
{
    public:
		//Constructeurs
		Camera();
		//Camera(ofVec3f _position, ofVec3f _pointCible, ofVec3f _axeVertical);
		Camera(ofVec3f _position, ofVec3f _pointCible, ofVec3f _axeVertical, float _sensibilite, float _vitesse);
		//Destructeur
		~Camera();


		//Fonctions
		void orienter(int xRel, int yRel);

		void deplacer(int touche);

		void setPosition(ofVec3f _position);

		void lookAt(ofMatrix4x4 &modelview);

		//Getters
		float getSensibilite() const;
		float getVitesse() const;

		//Setters
		void setSensibilite(float _sensibilite);
		void setVitesse(float _vitesse);

    private:
		//orientation
		float m_phi;
		float m_theta;
		ofVec3f m_orientation;

		//déplacement
		ofVec3f m_axeVertical;
		ofVec3f m_deplacementLateral;

		ofVec3f m_position;
		ofVec3f m_pointCible;

		float m_sensibilite;
		float m_vitesse;
};

#endif