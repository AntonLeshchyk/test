#include<iostream>
#include<time.h>
#include<conio.h>
using namespace std;

enum En { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };
class Ball {
private: 
	En Direction;
	int x, y, originalX, originalY;
public:
	Ball(int xValue,int yValue) {
		originalX = xValue;
		originalY = yValue;
		x = xValue;
		y = yValue;
		Direction = STOP;
	}
	void Reset() {
		x = originalX;
		y = originalY;
		Direction = STOP;
	}
	void ChangeDirection(En dir) {
		Direction = dir;
	}
	void RadnomDirection() {
		Direction =(En)((rand() % 6)+1);
	}
	int getX() { return x;};
	int getY() { return y;};
	En getDirection() { return Direction;};

	void Move() {
		switch (Direction)
		{
		case STOP: break;
		case LEFT:x--; break;
		case DOWNLEFT:x--; y++; break;
		case DOWNRIGHT:x++; y++; break;
		case UPLEFT:x--; y--; break;
		case UPRIGHT:x++; y++; break;
		case RIGHT:x++; break;
		default: break;
		}
	}
};


class Paddle {
private:
	int padX, padY, padOriginalX, padOroginalY;
public:
	Paddle() { padX = padY = 0;};
	Paddle(int posX, int posY) : Paddle() {
		padOriginalX = posX;
		padOroginalY = posY;
		padX = posX;
		padY = posY;
	}
	void Reset() { padX = padOriginalX; padY = padOroginalY;}
	int getX() { return padX;}
	int getY() { return padY;}
	void moveUp() { padY--;}
	void moveDown() { padY++;}

};

class GameManager {
private:
	int height, width, score1, score2;
	char up1, up2, down1, down2;
	bool gameOver;
	Ball *ball;
	Paddle *player1;
	Paddle *player2;
public:
	
	GameManager(int width, int height) {
		srand(time(NULL));
		this->height = height;
		this->width = width;
		score1 = score2 = 0;
		gameOver = false;
		up1 = 'w'; down1 = 's'; up2 = 'i'; down2 = 'k';
		ball = new Ball(width / 2, height / 2);
		player1 = new Paddle(1,height/ 2 - 3);
		player2 = new Paddle(width - 2, height / 2 - 3);
	}
	~GameManager() { delete ball, player1, player2;};
	
	void ScoreUp(Paddle *player) {
		if (player == player1)
			score1++;
		else if (player == player2)
			score2++;
		ball->Reset();
		player1->Reset();
		player2->Reset();
	}

	void Draw() {
		system("cls");

		for (int i = 0; i < width+2; i++)
		    cout << "#";
		cout << endl;
//---------------------------------------------------
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int ballX = ball->getX();
				int ballY = ball->getY();
				int player1X = player1->getX();
				int player1Y = player1->getY();
				int player2X = player2->getX();
				int player2Y = player2->getY();

            	if (j == 0)
					cout << '#';


				if (ballX == j && ballY == i)   //ball drowing 
					cout << 'O';

                else if (player1X == j && player1Y == i)   // first player drowwing  
					cout << '#';
				else if (player1X == j && player1Y+1 == i)   // first player drowwing  
					cout << '#';
				else if (player1X == j && player1Y+2 == i)   // first player drowwing  
					cout << '#';
				else if (player1X == j && player1Y+3 == i)   // first player drowwing  
					cout << '#';

				else if (player2X == j && player2Y == i)   // second player drowwing  
					cout << '#';
				else if (player2X == j && player2Y + 1 == i)   // second player drowwing  
					cout << '#';
				else if (player2X == j && player2Y + 2 == i)   // second player drowwing  
					cout << '#';
				else if (player2X == j && player2Y + 3 == i)   // second player drowwing  
					cout << '#';

				
				else
					cout << " ";

				if (j == width-1)
					cout << '#';
				
				
			}
			cout << endl;
		}



//---------------------------------------------------
		for (int i = 0; i < width + 2; i++)
			cout << "#";
		cout << endl;
		cout << "Score player 1 - " << score1 << endl;
		cout << "Score player 2 - " << score2 << endl;
	}

	void Input() {
		ball->Move();

		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1X = player1->getX();
		int player1Y = player1->getY();
		int player2X = player2->getX();
		int player2Y = player2->getY();

		if (_kbhit()) {
			
			char temp = _getch();
			
			if (temp == up1)
				if (player1Y > 0)
					player1->moveUp();
			if (temp == up2)
				if (player2Y > 0)
					player2->moveUp();
            if (temp == down1)
				if (player1Y + 4 < height)
					player1->moveDown();
			if (temp == down2)
				if (player2Y + 4 < height)
					player2->moveDown();

			if (ball->getDirection() == STOP)
				ball->RadnomDirection();

			if (temp == 'q')
				gameOver = true;

       }

	}

	void Logic() {
	
		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1X = player1->getX();
		int player1Y = player1->getY();
		int player2X = player2->getX();
		int player2Y = player2->getY();

		for (int i = 0; i < 4; i++)                                 // Left paddle contact
			if (ballX == player1X + 1)
				if (ballY == player1Y + i)
					ball->ChangeDirection((En)((rand() % 3) + 4));

		for (int i = 0; i < 4; i++)                                 // Right paddle contact
			if (ballX == player2X - 1)
				if (ballY == player2Y + i)
					ball->ChangeDirection((En)((rand() % 3) + 1));

	
		if (ballY == height -1)                                                             // the lower border contact
			ball->ChangeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
	
		if (ballY == 0)
			ball->ChangeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);   // the apper border contact

		if (ballX == width - 1)
			ScoreUp(player1);
		if (ballX == 0)
			ScoreUp(player2);
	}

	void Run() {
		while (!gameOver)
		{
			Draw();
			Input();
			Logic();
		}
	}
};

int main() {
	
	GameManager g(40, 20);
	g.Run();
   
	return 0;
}