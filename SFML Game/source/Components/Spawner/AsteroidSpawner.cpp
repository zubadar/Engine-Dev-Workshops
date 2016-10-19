#include "AsteroidSpawner.h"

#include "../Physics/AsteroidsPhysics.h"
#include "../Graphics/AsteroidGraphics.h"
#include "../Controller/AsteroidController.h"

#include "../../Structs.h"
#include "../../Helpers.h"

AsteroidSpawner::AsteroidSpawner(GameState* state, ResourceManager* resourceManager) {
	_state = state;
	_resourceManager = resourceManager;
	_bounds = state->GetBounds();
	_remainingSpawns = NUM_SPAWNS;
}

void AsteroidSpawner::Update(GameObject* gameobject, sf::Int32 deltaTime) {
	if (_clock.getElapsedTime().asSeconds() >= SPAWN_INTERVAL) {
		if (_remainingSpawns > 0) {
			_clock.restart();

			// Create asteroid object
			GameObject* newAsteroid = new GameObject({
				new AsteroidController(),
				new AsteroidsPhysics(_bounds),
				new AsteroidGraphics(_resourceManager)
			});

			// Generate random initial position outside bounds
			Vec3<float> position;
			position.SetDirection(RandInt(1, 360));
			position.SetMagnitude(hypot(_bounds.x, _bounds.y));

			// Generate random initial velocity
			Vec3<float> velocity;
			velocity.SetMagnitude(RandFloat(MIN_SPEED, MAX_SPEED));
			velocity.SetDirection(RandInt(1, 360));

			// Set asteroid to use calculated position and velocity
			newAsteroid->_sprite.setPosition(_bounds.x / 2.0f + position.GetX(), _bounds.y / 2.0f + position.GetY());
			newAsteroid->_velocity = { velocity.GetX(), velocity.GetY() };

			// Add object to game state
			_state->AddObject(newAsteroid);

			// Decrease remaining spawns for spawner
			_remainingSpawns--;
		}
	}
}
