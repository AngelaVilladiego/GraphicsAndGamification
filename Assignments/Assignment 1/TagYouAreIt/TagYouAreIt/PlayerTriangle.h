#ifndef PLAYER_TRIANGLE_H
#define PLAYER_TRIANGLE_H

#include "GameEntity.h"

class PlayerTriangle : public GameEntity
{
public:
	// Constructors / Destructors
	PlayerTriangle();
	virtual ~PlayerTriangle();

	//methods
	virtual void Create(Shader* _shader, Camera _camera) override;

private:
};

#endif // TRIANGLE_H

