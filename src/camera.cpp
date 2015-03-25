#include "camera.h"

Camera::Camera() 
: m_phi(0.0), m_theta(0.0), m_orientation(), m_axeVertical(0, 0, 1), m_deplacementLateral(), m_position(), m_pointCible(), m_sensibilite(0.0), m_vitesse(0.0)
{

}

Camera::Camera(ofVec3f _position, ofVec3f _pointCible, ofVec3f _axeVertical, float _sensibilite, float _vitesse, MousePositionHandler *mouse)
	: m_phi(0.0), m_theta(0.0), m_orientation(), m_axeVertical(_axeVertical), m_deplacementLateral(), m_position(_position), m_pointCible(_pointCible),
	m_sensibilite(_sensibilite), m_vitesse(_vitesse), mouseHandler(mouse)
 {
	 movingBackward = false;
	 movingForward = false;
	 movingLeft = false;
	 movingRight = false;

    m_orientation = m_pointCible - m_position;
	m_orientation.normalize();

    if(m_axeVertical.x == 1.0)
    {
        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.y / cos(m_phi));

        if(m_orientation.y < 0)
            m_theta *= -1;
    }
    else if(m_axeVertical.y == 1.0)
    {
        m_phi = asin(m_orientation.y);
        m_theta = acos(m_orientation.z / cos(m_phi));

        if(m_orientation.z < 0)
            m_theta *= -1;
    }
    else
    {
        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.z / cos(m_phi));

        if(m_orientation.z < 0)
            m_theta *= -1;
    }

    m_phi = m_phi * 180 / PI;
    m_theta = m_theta * 180 / PI;
}

void Camera::update()
{
	this->deplacer();
	this->orienter();
}

void Camera::lookAt(ofMatrix4x4 &modelview)
{
	modelview.makeLookAtViewMatrix(m_position, m_pointCible, m_axeVertical);
}

ofVec3f Camera::getOrientation() const
{
	return m_orientation;
}

void Camera::orienter()
{
    // Récupération des angles
	m_phi += -mouseHandler->getRelPosY() * m_sensibilite;
	m_theta += -mouseHandler->getRelPosX() * m_sensibilite;

    // Limitation de l'angle phi
    if(m_phi > 89.0)
        m_phi = 89.0;

    else if(m_phi < -89.0)
        m_phi = -89.0;

	// Conversion des angles en radian
	float phiRadian = m_phi * PI / 180;
	float thetaRadian = m_theta * PI / 180;
	
	// Calcul des coordonnées sphériques
	if(m_axeVertical.x == 1.0)// Si l'axe vertical est l'axe X
	{
		m_orientation.x = sin(phiRadian);
		m_orientation.y = cos(phiRadian) * cos(thetaRadian);
		m_orientation.z = cos(phiRadian) * sin(thetaRadian);
	}else if(m_axeVertical.y == 1.0)// Si c'est l'axe Y
	{
		m_orientation.x = cos(phiRadian) * sin(thetaRadian);
		m_orientation.y = sin(phiRadian);
		m_orientation.z = cos(phiRadian) * cos(thetaRadian);
	}else// Sinon c'est l'axe Z
	{
		m_orientation.x = cos(phiRadian) * cos(thetaRadian);
		m_orientation.y = cos(phiRadian) * sin(thetaRadian);
		m_orientation.z = sin(phiRadian);
	}

	//Calcul de la normale, retour le vecteur orthogonal et le normalise (le rend de longeur 1)
	m_deplacementLateral = m_axeVertical.getCrossed(m_orientation);
	m_deplacementLateral.normalize();

	//Calcul du point ciblé
	m_pointCible = m_position + m_orientation; 
	
}

void Camera::deplacer()
{
	if(movingForward)
    {
        m_position = m_position + m_orientation * m_vitesse;
        m_pointCible = m_position + m_orientation;
    }
	if(movingBackward)
    {
        m_position = m_position - m_orientation * m_vitesse;
        m_pointCible = m_position + m_orientation;
    }
	if(movingLeft)
    {
        m_position = m_position + m_deplacementLateral * m_vitesse;
        m_pointCible = m_position + m_orientation;
    }
	if(movingRight)
    {
        m_position = m_position - m_deplacementLateral * m_vitesse;
        m_pointCible = m_position + m_orientation;
    }
}

void Camera::setMoveForward(bool isMoving)
{
	movingForward = isMoving;
}

void Camera::setMoveBackward(bool isMoving)
{
	movingBackward = isMoving;
}

void Camera::setMoveLeft(bool isMoving)
{
	movingLeft = isMoving;
}

void Camera::setMoveRight(bool isMoving)
{
	movingRight = isMoving;
}

void Camera::setPosition(ofVec3f _position)
{
    m_position = _position;
    m_pointCible = m_position + m_orientation;
}

float Camera::getSensibilite() const
{
    return m_vitesse;
}


float Camera::getVitesse() const
{
    return m_vitesse;
}

ofVec3f Camera::getPosition() const
{
	return m_position;
}

void Camera::setSensibilite(float _sensibilite)
{
    m_sensibilite = _sensibilite;
}

void Camera::setVitesse(float _vitesse)
{
    m_vitesse = _vitesse;
}

bool Camera::isMovingForward() const
{
	return movingForward;
}

bool Camera::isMovingBackward() const
{
	return movingBackward;
}

bool Camera::isMovingRight() const
{
	return movingRight;
}

bool Camera::isMovingLeft() const
{
	return movingLeft;
}