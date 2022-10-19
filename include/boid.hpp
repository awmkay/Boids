#ifndef BOID_BOID_H
#define BOID_BOID_H

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <random>
#include <iostream>

class Boid {
	public:
		Boid(int width, int height) : width(width), height(height), sprite(5, 3) {
			pos = glm::vec2(std::rand() % width, std::rand() % height);
			vel = glm::vec2(std::rand() % speedLimit, std::rand() % speedLimit);
		}

		Boid& operator=(Boid otherBoid) {
			pos = otherBoid.pos;
			vel = otherBoid.vel;
			sprite = otherBoid.sprite;

			return *this;
		}

		void KeepWithinBounds() {
			if (pos.x < margin) {
				vel.x += turnFactor;
			}

			if (pos.x > width - margin) {
				vel.x -= turnFactor;
			}

			if (pos.y < margin) {
				vel.y += turnFactor;
			}

			if (pos.y > height - margin) {
				vel.y -= turnFactor; 
			}
		}

		void FlyTowardsCenter(glm::vec2 averagePos) {
			vel += (averagePos - pos) * centeringFactor;
		}

		void AvoidOthers(const std::vector<Boid> boids) {
			glm::vec2 move(0);

			for (auto otherBoid : boids) {
				if (otherBoid.pos != pos) {
					if (distance(otherBoid.pos, pos) < maxDistance) {
						move += pos - otherBoid.pos;
					}
				}
			}

			vel += move * avoidFactor;
		}

		void MatchVelocity(glm::vec2 averageVel) {
			vel += (averageVel - vel) * matchingFactor;
		}

		void LimitSpeed() {
			const float speed = glm::length(vel);

			if (speed > speedLimit) {
				vel = glm::normalize(vel) * (float)speedLimit;
			}
		}

		void Update(const glm::vec2 &averagePos, const glm::vec2 &averageVel, const std::vector<Boid> &boids) {
			FlyTowardsCenter(averagePos);
			AvoidOthers(boids);
			MatchVelocity(averageVel);
			LimitSpeed();
			KeepWithinBounds();

			pos += vel;
		}

		void Draw(sf::RenderWindow &window) {
			sprite.setPosition(pos.x, pos.y);
			sprite.setRotation(std::atan(vel.y / vel.x) * 180 / M_PI);
			window.draw(sprite);
		}

		glm::vec2 pos;
		glm::vec2 vel;
		
		sf::CircleShape sprite;

		const int width;
		const int height;
		const float margin = 150;
		const float turnFactor = 2;
		const float centeringFactor = 0.005;
		const float maxDistance = 30;
		const float avoidFactor = 0.05;
		const float matchingFactor = 0.005;
		const int speedLimit = 15;
};

#endif
