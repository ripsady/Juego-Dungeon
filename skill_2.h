#pragma once
#include "skills.h"

class Skill_2 : public Skills
{
private:
public:
	Skill_2(); // constructor.

	// override sobreescribe los metodos heredados Skills (padre).
	void activate() override; // activamos la habilidad .
	void levelUp() override; // subida de nivel de la habilidad.
};