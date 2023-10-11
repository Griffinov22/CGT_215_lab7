// CGT_215_lab7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(100, 120));
	ball.applyImpulse(Vector2f(0.4, 0));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		thudCount++;
		cout << "thud " << thudCount << endl;
	};

	// Create left wall OFFSET SO WALLS DONT COLLIDE WITH FLOOR
	PhysicsRectangle leftWall;
	leftWall.setSize(Vector2f(20, 580));
	leftWall.setCenter(Vector2f(10, 290));
	leftWall.setStatic(true);
	world.AddPhysicsBody(leftWall);

	// Create right wall OFFSET SO WALLS DONT COLLIDE WITH FLOOR
	PhysicsRectangle rightWall;
	rightWall.setSize(Vector2f(20, 580));
	rightWall.setCenter(Vector2f(790, 290));
	rightWall.setStatic(true);
	world.AddPhysicsBody(rightWall);

	// Create ceiling wall
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800,20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	// Create center block
	PhysicsRectangle centerBlock;
	centerBlock.setSize(Vector2f(100, 60));
	centerBlock.setCenter(Vector2f(400, 300));
	centerBlock.setStatic(true);
	world.AddPhysicsBody(centerBlock);

	int bangCount(0);
	centerBlock.onCollision = [&bangCount, &centerBlock, &window](PhysicsBodyCollisionResult result) {
		bangCount++;
		cout << "Bang " << bangCount << endl;

		//This just pauses the screen and makes the center rectangle red for 2s before closing
		if (bangCount == 3) {
			Clock simpleClock;
			Time start(simpleClock.getElapsedTime());
			Time simpleDelta(start - start); //start at 0

			while (simpleDelta.asMilliseconds() < 2000) {
				Time currTime = simpleClock.getElapsedTime();
				simpleDelta = currTime - start;

				centerBlock.setFillColor(Color(255, 20, 0));
				window.draw(centerBlock);
				window.display();
			}

			exit(0);
		}
	};
	

	Clock clock;
	Time lastTime(clock.getElapsedTime());

	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());

		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear();
		window.draw(ball);
		window.draw(floor);
		window.draw(leftWall);
		window.draw(rightWall);
		window.draw(ceiling);
		window.draw(centerBlock);
		window.display();
	}
}

