#include <iostream>
#include <vector> 
#include "ConsoleHelper.h"
#include "Springball_Moeller.h"
#include  <utility>
#include <chrono>
#include <random>

using namespace std;


//Global ArrayList instance
ConsoleHelper consoleHelper;

std::vector<Ball> generateBall;
std::vector<std::pair<int, int>> arrayListDuckBarriers;
std::vector<std::pair<int, int>> arrayListBarriers;

//stored the default window width and height.
int windowWidth;
int windowHeight;
		

int main()
{
	srand(time(NULL));
	setupGameElements();
	
	while (true) { 

		clearScreen(); 
		hideCursor();
		updateDuckBarriers();
		updateBarriers();
		_Thrd_sleep_for(1000);
		updateBalls();
		
	}

	return 0;
   
}



// The user decides how many game elements to place on the map
void setupGameElements() {
	while (true) {
		//stored the numbers of balls and barriers
		int sumOfBalls;
		int sumOfBarriers;
		int sumOfDuckBarriers;


		//Get User-Input
		cout << "Wie viele Bälle sollen erstellt werden?";

		cin >> sumOfBalls;

		cout << "Wie viele Hindernisse wollen sie erstellen?";

		cin >> sumOfBarriers;

		cout << "Wie viel Enten wollen sie?";

		cin >> sumOfDuckBarriers;

		cout << "Wie viel Breite soll das Spielfeld haben?";

		cin >> windowWidth;

		cout << "Wie hoch soll das Spielfeld sein?";

		cin >> windowHeight;


		if (sumOfBalls >= 0 && sumOfBarriers >= 0 && sumOfDuckBarriers >= 0) {
			generateBalls(sumOfBalls, windowWidth, windowHeight);
			generateBarriers(sumOfBarriers, windowWidth, windowHeight);
			generateDuckBarriers(sumOfDuckBarriers, windowWidth, windowHeight);
			break;
		}

		continue;
	}
}



// Generate balls and set them on the map
void generateBalls(int sumOfBalls, int windowWidth, int windowsHeight) {

	for (int i = 0; i < sumOfBalls; i++) {

		int xPos = rand() % windowWidth;
		int yPos = rand() % windowsHeight;
		int xVel = getRandomVelocity();
		int yVel = getRandomVelocity();

		Ball ball = Ball(xPos, yPos, xVel, yVel);

		generateBall.push_back(ball);
		consoleHelper.gotoXY(xPos, yPos);
		cout << "*"+i;

	}
}

// Generate barriers and set their coordinates in a global ArrayList
void generateBarriers(int sumOfBarriers, int windowWidth, int windowHeight) {

	for (int i = 0; i < sumOfBarriers; i++) {

		int xPos = rand() % windowWidth;
		int yPos = rand() % windowHeight;

		pair<int, int> pair = make_pair(xPos, yPos);

		arrayListBarriers.push_back(pair);
		consoleHelper.gotoXY(xPos, yPos);
		cout << "#";

	}
}

// Set the duck barriers on the map+void 
void generateDuckBarriers(int sumOfBarriers, int windowWidth, int windowHeight) {

	for (int i = 0; i < sumOfBarriers; i++) {

		int xPos = rand() % windowWidth;
		int yPos = rand() % windowHeight;

		pair<int, int> pair = make_pair(xPos, yPos);

		arrayListDuckBarriers.push_back(pair);
		cout << "\U0001F986"; //Duck Emoji
		consoleHelper.gotoXY(xPos, yPos);

	}
}


//set the balls on the Map after it has been cleared
void updateBalls() {
	for (auto& ball : generateBall) {
		if (!ball.isFrozen) {
			ball.xPos += ball.xVel;  // Korrigiert
			ball.yPos += ball.yVel;  // Hier war auch ein Fehler, du hast ball.yPos += ball.yPos verwendet

			// Detect collisions with window
			if (ball.xPos <= 0 || ball.xPos >= windowWidth) {
				ball.xVel *= -1;
			}
			else if (ball.yPos <= 0 || ball.yPos >= windowHeight) {
				ball.yVel *= -1;
			}

			// Check for collisions with barriers
			pair<int, int> newVel = detectionBarriers(ball);
			ball.xVel = newVel.first;
			ball.yVel = newVel.second;
		}
		else {
			//get current Time in milisec
			long currentTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
			if (currentTime - ball.freezeStartTime >= ball.frozenTime)
			{
				ball.isFrozen = false;
				ball.yVel = getRandomVelocity();
				ball.xVel = getRandomVelocity();

				if (ball.yVel == 0) {
					ball.yVel = getRandomVelocity();
				}
				else if (ball.xVel == 0) {
					ball.xVel = getRandomVelocity();
				}
			}
		}


	}

}

//Update the Duck-barriers on the map
void updateDuckBarriers() {

	for (auto& pair : arrayListDuckBarriers) {

		int barrierX = pair.first;
		int barrierY = pair.second;

		consoleHelper.gotoXY(barrierX, barrierY);
		cout << "D";

	}
}

// Set the barriers on the map after it has been cleared
	void updateBarriers(){

		for (auto& pair : arrayListBarriers) {

			int barrierX = pair.first;
			int barrierY = pair.second;

			consoleHelper.gotoXY(barrierX, barrierY);
			cout << "#";

		}
	}
	

pair<int, int> detectionBarriers(Ball ball) {
	int newXVel = ball.yVel;
	int newYVel = ball.xVel;

	for (auto& pair : arrayListDuckBarriers) {

		int barrierX = pair.first;
		int barrierY = pair.second;

		if (ball.xVel == barrierX && ball.yPos == barrierY && !ball.isFrozen) {
			newXVel = 0;
			newYVel = 0;
			ball.isFrozen = true;
			long currentTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
			ball.freezeStartTime = currentTime;

		}
	}
	return make_pair(newXVel, newYVel);
}



int getRandomVelocity() {
	int vel;
	std::random_device random;
	std::mt19937 gen(random());

	// Define range from -3 to 3 (inclusive)
	std::uniform_int_distribution<> dis(-3, 3);

	do {
		vel = dis(gen);  // Generate random value between -3 and 3
		cout << vel;
	} while (vel == 0);  // if vel is 0

	return vel;
}


//Clear the terminal
void clearScreen() {

	consoleHelper.clearScreen();
}

void hideCursor() {

	consoleHelper.hideCursor();
}

