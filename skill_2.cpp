#include "skill_2.h"

Skill_2::Skill_2() : Skills("Skill_2", 5, 1.5f, 0.5f) // valores inventados de momento, cambiarian a medida que avanza el juego.
{
}

// activacion de la habilida tomando en cuenta si el cd esta disponible.
// cd seria cooldown, el tiempo de espera de la habilidad.
void Skill_2::activate()
{
	if (_cdReady)
	{
		// aca iria la logica del SFML + sprite + colision con objetivo

		_cdReady = false;
		_cdCurrent = _cdDuration;
	}

}

// subida de nivel de la habilidad, aumenta las estadisticas mas relevantes dependiendo el nivel.
void Skill_2::levelUp() 
{
	Skills::levelUp();

	switch (_level)
	{
	case 2:
		_damage += 5;
		break;
	case 3:
		_damage += 5;
		_range += 0.5f;
		break;
	case 4:
		_damage += 5;
		_cdDuration -= 0.1f;
		break;
	case 5:
		_damage += 10;
		_range += 1.0f;
		_cdDuration -= 0.3f;
		break;
	default:
		break;
	}
}