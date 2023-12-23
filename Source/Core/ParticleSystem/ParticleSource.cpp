#include "ParticleSource.h"
#include "../Scene.h"
#include "ParticleObject.h"
#include "../../CoreStructs/Vector.h"

void ParticleSource::Init() //TODO: make this component
{
	isRenderable = false;
	hasCollider = false;
	
}

void ParticleSource::Update(float deltaTime)
{
	
}

void ParticleSource::EmitParticle(int count, int particleType)
{
	for (int i = 0; i < count; i++)
	{
		double randomAngle = static_cast<double>(rand()) / RAND_MAX * 2 * 3.14f;

		
		double speed = 25.0; 
		double randomVelocityX = speed * std::cos(randomAngle);
		double randomVelocityY = speed * std::sin(randomAngle);

	
		Vector2 randomVelocity(randomVelocityX, randomVelocityY);
		GetCurrentScene().AddGameObject(new ParticleObject(GetCurrentScene(), randomVelocity, particleType), transform.Position);
	}
}
