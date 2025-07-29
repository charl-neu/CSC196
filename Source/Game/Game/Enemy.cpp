#include "Enemy.h"
#include "Engine.h"
#include "Game/scene.h"
#include "Renderer/Renderer.h"
#include "GamePlayer.h"
#include "Game/Game.h"

void Enemy::Update(float deltaTime)
{
	Player* player = scene->GetActorByName<Player>("Player");
	if (player) {
		viper::vec2 direction{ 0, 0 };
		direction = player->transform.position - transform.position;
		direction = direction.Normalized();
		transform.rotation = viper::RadToDeg(direction.Angle());
	}

	viper::vec2 force = viper::vec2{1,0}.Rotate(viper::DegToRad(transform.rotation)) * accel;
	velocity += force * deltaTime;

	transform.position.x = viper::Wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	transform.position.y = viper::Wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	Actor::Update(deltaTime);
}

void Enemy::onCollision(Actor* other)
{
	if (other->tag != this->tag)
	{
		destroyed = true;
		scene->GetGame()->AddPoints(100);
	}
}
