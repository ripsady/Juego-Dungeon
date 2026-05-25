#include "skills.h"
#include <string>

// se dan valores por defecto con el constructor.
Skills::Skills(std::string name, int damage, float range, float cdDuration)
	:_name(name), _level(1), _damage(damage), _range(range),
	_cdDuration(cdDuration), _cdCurrent(0.0f), _cdReady(true)
{

}

// metodo de aumento de nivel
void Skills::levelUp()
{ 
	_level++;
}

// logica de ejecucion del cdUpdate utilizando deltaTime.
void Skills::cdUpdate(float deltaTime)
{
    if (!_cdReady) {
        _cdCurrent -= deltaTime;
        if (_cdCurrent <= 0.0f) {
            _cdReady = true;
            _cdCurrent = 0.0f;
        }
    }
}   