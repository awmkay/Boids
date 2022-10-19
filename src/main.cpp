#include "boid.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>

const int windowWidth = 1200;
const int windowHeight = 900;
const int numBoids = 100;
	
std::vector<Boid> boids;

std::vector<Boid> GetNClosestBoids(const Boid &boid);
glm::vec2 GetAveragePos();
glm::vec2 GetAverageVel();

int main() {
	sf::RenderWindow window({windowWidth, windowHeight}, "Boids");
	window.setFramerateLimit(30);

	sf::CircleShape triangle(10, 3);
	triangle.setFillColor(sf::Color::Cyan);
	triangle.setPosition((float)windowWidth / 2, (float)windowHeight / 2);

	for (int i = 0; i < numBoids; i++) {
		boids.push_back(Boid(windowWidth, windowHeight));
		boids[i].sprite.setFillColor(sf::Color(std::rand() % 255, std::rand() & 255, std::rand() & 255));
	}

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape) { window.close(); }
					break;
				default:
					break;
			}
		}

		glm::vec2 averagePos = GetAveragePos();
		glm::vec2 averageVel = GetAverageVel();
		for (Boid &boid : boids) {
			boid.Update(averagePos, averageVel, boids);
		}

		window.clear(sf::Color(128, 128, 128));
		for (Boid &boid : boids) {
			boid.Draw(window);
		}
		window.display();
	}
}

std::vector<Boid> GetNClosestBoids(const Boid &boid, int n) {
	std::vector<Boid> sortedBoids = boids;
	std::sort(std::begin(sortedBoids), std::end(sortedBoids),
			[&boid](const Boid &boidA, const Boid &boidB) { return glm::distance(boid.pos, boidA.pos) < glm::distance(boid.pos, boidB.pos); });
	return std::vector<Boid>(sortedBoids.begin() + (sortedBoids.size() - n), sortedBoids.end());
}

glm::vec2 GetAveragePos() {
	glm::vec2 averagePos(0);

	for (auto boid : boids) {
		averagePos += boid.pos;
	}

	averagePos /= numBoids;
	return averagePos;
}

glm::vec2 GetAverageVel() {
	glm::vec2 averageVel(0);

	for (auto boid : boids) {
		averageVel += boid.vel;
	}

	return glm::vec2(averageVel.x / numBoids, averageVel.y / numBoids);
}

void Draw(sf::RenderWindow &window, const Boid& boid) {
}
