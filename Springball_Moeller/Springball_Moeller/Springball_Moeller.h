
#include  <utility>
using namespace std;

class Ball {

public:

	Ball(int xPos, int yPos, int xVel, int yVel) : xPos(xPos), yPos(yPos), xVel(xVel), yVel(yVel), isFrozen(false), freezeStartTime(0), frozenTime(5000) {}

	int xPos;
	int yPos;
	int xVel;
	int yVel;
	bool isFrozen;
	long freezeStartTime = 0L;
	long frozenTime = 5000L;  //five seconds

};


	//All Methods that are used
	void setupGameElements();
	void generateDuckBarriers(int a, int b, int c);
	void generateBarriers(int a, int b, int c);
	void generateBalls(int a, int b, int c);
	void updateBalls();
	void updateDuckBarriers();
	void updateBarriers();
	void clearScreen();
	void hideCursor();
	int getRandomVelocity();
	void checkInput();
	pair<int, int> detectionBarriers(Ball ball);

	//Global ArrayList instance for the generated balls
	extern vector<Ball> generateBall;
	//Global ArrayList instance for the generated barriers
	extern std::vector<std::pair<int, int>> arrayListDuckBarriers;
	extern std::vector<std::pair<int, int>> arrayListBarriers;

	//stored the default window width and height.
	extern int windowWidth;
	extern int windowHeight;

