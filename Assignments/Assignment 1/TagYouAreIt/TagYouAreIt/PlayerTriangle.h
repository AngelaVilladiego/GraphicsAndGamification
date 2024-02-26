#ifndef PLAYER_TRIANGLE_H
#define PLAYER_TRIANGLE_H

#include "Triangle.h"
#include "GameEntity.h"

class PlayerTriangle : public GameEntity
{
public:
	// Constructors / Destructors
	PlayerTriangle();
	virtual ~PlayerTriangle();

	virtual void Create(Shader* _shader, Camera _camera) override;

private:
};

#endif // TRIANGLE_H

