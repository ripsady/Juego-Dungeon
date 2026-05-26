#pragma once
#include <string>

class Skills
{
protected:
	std::string _name;
	int _level;
	int _damage;
	float _range;
	float _cdDuration;
	float _cdCurrent;
	bool _cdReady;
	
public:
	// constructor. Guardo parametros que las clases hijas van a utilizar.
	Skills(std::string name, int damage, float range, float cdDuration); 
	virtual ~Skills(){} // destructor.

	// al ponerle virtual al metodo esto hace que unicamente la clase hija (habilidad)
	// sea la que la activa dependiendo el cd.
	virtual void activate() = 0; 
	virtual void levelUp(); // metodo que subira el nivel de la habilidad.

	// segun lei es necesario para poder manejar los tiempos del cd
	// esta relacionada al framerate y de esta manera supuestamente se controla muchas cosas
	// en los juegos relacionados al tiempo de, por ej en este caso, una habilidad.
	void cdUpdate(float deltaTime); 
};