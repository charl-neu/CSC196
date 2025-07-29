#include "Rocket.h"
#include "Engine.h"
#include "Game/scene.h"
#include "Renderer/Renderer.h"
#include "GamePlayer.h"

void Rocket::Update(float deltaTime)
{
	viper::vec2 force = viper::vec2{ 1,0 }.Rotate(viper::DegToRad(transform.rotation)) * accel;
	velocity = force;

	transform.position.x = viper::Wrap(transform.position.x, 0.0f, (float) viper::GetEngine().GetRenderer().GetWidth());
	transform.position.y = viper::Wrap(transform.position.y, 0.0f, (float) viper::GetEngine().GetRenderer().GetHeight());

	Actor::Update(deltaTime);
}

void Rocket::onCollision(Actor* other)
{
	if (other->tag == "enemy") {
		destroyed = true;
	}
}
