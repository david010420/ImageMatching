#include <bangtal.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

time_t startTime;
TimerID timer1;
SceneID scene1;
ObjectID startButton, restartButton;
ObjectID puzzleArray[16];

int flippedCount = 0;

const char* imageArray[] = { "images/0.png","images/0.png","images/1.png","images/1.png","images/2.png","images/2.png","images/3.png",
	"images/3.png","images/4.png","images/4.png","images/5.png","images/5.png","images/6.png","images/6.png","images/7.png",
	"images/7.png"};

bool isFlipped = false;
int prevPos = -1;
int lastPos = -1;

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}
	return object;
}



bool isCompleted() {
	if (flippedCount == 8) {
		return true;
	}
	return false;
	
}

void processEndGame() {
	showMessage("Game Completed");
}

void swapImage(int pos1, int pos2) {
	char* tempName = (char*)imageArray[pos1];
	imageArray[pos1] = imageArray[pos2];
	imageArray[pos2] = tempName;
	setObjectImage(puzzleArray[pos1], imageArray[pos1]);
	setObjectImage(puzzleArray[pos2], imageArray[pos2]);	
}


void shuffle() {
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		int pos1 = rand() % 16;
		int pos2 = rand() % 16;
		if (pos1!=pos2) {
			swapImage(pos1, pos2);
		}
	}
}

void flip(int i) {
	if (prevPos == i) return;
	setObjectImage(puzzleArray[i], imageArray[i]);
	if (isFlipped == false) {
		isFlipped = !isFlipped;
		prevPos = i;
	}
	else {
		if (imageArray[prevPos] == imageArray[i]) {
			isFlipped = !isFlipped;
			hideObject(puzzleArray[i]);
			hideObject(puzzleArray[prevPos]);
			prevPos = -1;
			flippedCount++;
		}
		else {
			lastPos = i;
			setTimer(timer1, 1.0f);
			startTimer(timer1);
		}
	}
	if (isCompleted()) {
		processEndGame();
	}
}

void timerCallback(TimerID timer) {

	if (timer == timer1) {
		setObjectImage(puzzleArray[lastPos], "images/back.png");
		setObjectImage(puzzleArray[prevPos], "images/back.png");
		isFlipped = !isFlipped;
		prevPos = -1;
		stopTimer(timer1);
	}
}
void mousetCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == startButton) {
		hideObject(startButton);
		showObject(restartButton);
	
		for (int i = 0; i < 16; i++) {
			showObject(puzzleArray[i]);
		}
		shuffle();
		startTime = time(NULL);
		for (int i = 0; i < 16; i++) {
			setObjectImage(puzzleArray[i], "images/back.png");
		}
	}
	else if (object == restartButton) {
		flippedCount = 0;
		isFlipped = false;
		prevPos = -1;
		lastPos = -1;
		for (int i = 0; i < 16; i++) {
			showObject(puzzleArray[i]);
		}

		shuffle();
		startTime = time(NULL);
		for (int i = 0; i < 16; i++) {
			setObjectImage(puzzleArray[i], "images/back.png");
		}
	}
	else if (object == puzzleArray[0]) {
		flip(0);
	}
	else if (object == puzzleArray[1]) {
		flip(1);
	}
	else if (object == puzzleArray[2]) {
		flip(2);
	}
	else if (object == puzzleArray[3]) {
		flip(3);
	}
	else if (object == puzzleArray[4]) {
		flip(4);
	}
	else if (object == puzzleArray[5]) {
		flip(5);
	}
	else if (object == puzzleArray[6]) {
		flip(6);
	}
	else if (object == puzzleArray[7]) {
		flip(7);
	}
	else if (object == puzzleArray[8]) {
		flip(8);
	}
	else if (object == puzzleArray[9]) {
		flip(9);
	}
	else if (object == puzzleArray[10]) {
		flip(10);
	}
	else if (object == puzzleArray[11]) {
		flip(11);
	}
	else if (object == puzzleArray[12]) {
		flip(12);
	}
	else if (object == puzzleArray[13]) {
		flip(13);
	}
	else if (object == puzzleArray[14]) {
		flip(14);
	}
	else if (object == puzzleArray[15]) {
		flip(15);
	}
}

int main()
{
	setMouseCallback(mousetCallback);
	setTimerCallback(timerCallback);
	scene1 = createScene("IU", "images/IuFull.png");
	puzzleArray[0] = createObject(imageArray[0], scene1, 0, 540, false);
	puzzleArray[1] = createObject(imageArray[1], scene1, 320, 540, false);
	puzzleArray[2] = createObject(imageArray[2], scene1, 640, 540, false);
	puzzleArray[3] = createObject(imageArray[3], scene1, 960, 540, false);
	puzzleArray[4] = createObject(imageArray[4], scene1, 0, 360, false);
	puzzleArray[5] = createObject(imageArray[5], scene1, 320, 360, false);
	puzzleArray[6] = createObject(imageArray[6], scene1, 640, 360, false);
	puzzleArray[7] = createObject(imageArray[7], scene1, 960, 360, false);
	puzzleArray[8] = createObject(imageArray[8], scene1, 0, 180, false);
	puzzleArray[9] = createObject(imageArray[9], scene1, 320, 180, false);
	puzzleArray[10] = createObject(imageArray[10], scene1, 640, 180, false);
	puzzleArray[11] = createObject(imageArray[11], scene1, 960, 180, false);
	puzzleArray[12] = createObject(imageArray[12], scene1, 0, 0, false);
	puzzleArray[13] = createObject(imageArray[13], scene1, 320, 0, false);
	puzzleArray[14] = createObject(imageArray[14], scene1, 640, 0, false);
	puzzleArray[15] = createObject(imageArray[15], scene1, 960, 0, false);
	startButton = createObject("images/start.png", scene1, 590, 70, true);
	restartButton = createObject("images/restart.png", scene1, 590, 20, false);
	isFlipped = false;
	prevPos = -1 ;
	timer1 = createTimer(1.0f);
	startGame(scene1);
}

