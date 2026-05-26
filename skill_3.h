#pragma once
#include "skills.h"

class Skill_3 : public Skills
{
private:
public:
	Skill_3(); // constructor.

	// override sobreescribe los metodos heredados Skills (padre).
	void activate() override; // activamos la habilidad .
	void levelUp() override; // subida de nivel de la habilidad.
};