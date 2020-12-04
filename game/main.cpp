
#include <bangtal>
#include<iostream>
#include <time.h>
using namespace bangtal;
using namespace std;

/*
���� ���� :
5�ʸ��� ������ ����´�.

�� �ʱ�ȭ : 2560 x 1680 �̹Ƿ� 80 x 80 ũ�� ������  �׸�� ������ map[21][32]

���� ���� : 0
������ �� �ִ� ���� : 1
�밨�� ���� ��ġ : 2
������ : 3
���� : 4
���� ��ġ : 5
�հ� ��ġ : 6


ȭ�� �ʱ�ȭ
�������� ȭ���� ũ�Ⱑ 1280 x 720 �̹Ƿ� scene[8][16]


*/

typedef struct _pos {
	int x = 0;
	int y = 0;
}Pos;

int map[21][32] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,5,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
	{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,3},
	{0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,6,1,0,0,0,0,0,0},
};

//�㿡���� ĳ���� ��ġ
Pos now;

//  ���� ������ ��� ��ġ���� �������� ����ش�.
Pos criteria;



void init(ScenePtr scene, ObjectPtr* rockets, ObjectPtr* hearts)
{
	// map �������� ��ǥ
	now.x = 0;
	now.y = 6;

	//scene ���� map�� ������ 
	criteria.x = 6;
	criteria.y = -12;

	for (int i = 0; i < 20; i++)
	{
		rockets[i] = Object::create("images/rocket.png", scene, 1280, 0);
	}

	for (int i = 0; i < 3; i++)
	{
		hearts[i] = Object::create("images/filledheart.png", scene, 700 + 80 * i, 600);
	}
	return;
}

void sceneChange(ScenePtr scene, ObjectPtr garden, ObjectPtr con, ObjectPtr crown, int xMove, int yMove, int& find)
{
	// ����� �ݴ�� ������
	criteria.x = criteria.x - xMove;
	criteria.y = criteria.y + yMove;

	// map  �󿡼��� ĳ���� ��ġ ���� -> scene�������� ��ǥ�� ����
	now.x = now.x + xMove;
	now.y = now.y + yMove;

	
	// �հ� ��ġ
	if (map[now.y][now.x] == 5)
	{
		find++;
		crown->pick();
		map[now.y][now.x] = 1;
	}

	// ����ġ
	if (map[now.y][now.x] == 6)
	{
		find++;
		con->pick();
		map[now.y][now.x] = 1;
	}

	//���� ����
	if (map[now.y][now.x] == 3)
	{
		if (find == 2) endGame();
	}

	//scene ���� 
	garden->locate(scene, (criteria.x * 80), (criteria.y * 80));
	crown->locate(scene, (criteria.x * 80) + (18 * 80), (criteria.y * 80) + (18 * 80));
	con->locate(scene, (criteria.x * 80) + (24 * 80), (criteria.y * 80));

}

bool moveAvailable(int xMove, int yMove)
{
	return  map[now.y + yMove][now.x + xMove] != 0;

}

void rocketInitPos(Pos* rocketPos)
{

	for (int i = 0; i < 20; i++)
	{
		rocketPos[i].x = 16 + rand() % 4; // ȭ�� ���� ��ǥ�� ����
		rocketPos[i].y = rand() % 21;
	}
	return;
}

bool checkTouched(int x, int y)
{
	return (480 == x && 160 == y);

}

bool moveRocket(ScenePtr scene, ObjectPtr* rockets, Pos* rocketPos, int xspeed, ObjectPtr explode, TimerPtr rocketstop)
{
	int x, y;
	int finishCount = 0;

	for (int i = 0; i < 20; i++)
	{
		x = rocketPos[i].x * 80 - xspeed * 4; //��ǥ ��� ����
		y = rocketPos[i].y * 80 + (criteria.y * 80);

		rockets[i]->locate(scene, x, y);

		// �����̴� ���ϸ��� ĳ���Ϳ� ����� üũ 
		if (checkTouched(x, y))
		{
			cout << "X :" << x << "Y: " << y << endl;
			explode->show();
			rocketstop->start();
		}

		// ������ ȭ�� ���� ��� ��� üũ 
		if (x <= 0) finishCount++;

	}

	//��� ������ ȭ���� ����� 
	return finishCount == 20;
}

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	srand(time(NULL));

	//1280 * 720 ȭ��
	auto scene = Scene::create("sea", "images/sea.png");

	// garden ũ�� : 2560 x 1680  

	// ���� �� ����, �� �Ʒ� ����� �ʱ� scene���� (480,-960) ��ǥ�� ��ġ�Ѵ�.
	auto garden = Object::create("images/garden2.png", scene, 480, -960);
	auto character = Object::create("images/yonggam7.png", scene, 480, 165);

	// ��, �հ�
	auto crown = Object::create("images/crown.png", scene, 480 + 18 * 80, -960 + 18 * 80); //���� �𼭸��� �������� (18 * 80 ,18*80 ) ������ ���� ��ġ  480 + (18*80) , -960 + 18 * 80 
	auto con = Object::create("images/key.png", scene, 480 + 24 * 80, -960); // ���� �𼭸��� �������� (24 * 80 , 0) ������ ���� ��ġ 480 + (24*80), -960 
	int find = 0;
	/*
	crown->setOnPickCallback([](ObjectPtr object)->bool {

		object->setImage("Images/����.png");

		});
	con-> setOnPickCallback([](ObjectPtr object)->bool {

		object->setImage("Images/����.png");
		});
		*/
		// �ȳ� ����
	auto map = Object::create("images/map.png", scene, 1000, 500);

	// ������� ���ϵ� 
	ObjectPtr rockets[20];
	Pos rocketPos[20];
	int xspeed = 0;


	// ����
	ObjectPtr hearts[3];
	int heartCount = 3;


	// �ʱ�ȭ 
	init(scene, rockets, hearts);
	rocketInitPos(rocketPos);

	// ����
	auto explode = Object::create("images/explode.png", scene, 480, 160);
	explode->hide();



	// �������� ���� ���� ����
	auto rocketStopTimer = Timer::create(0.1f);

	rocketStopTimer->setOnTimerCallback([&](TimerPtr timer)->bool {
		explode->hide();
		hearts[--heartCount]->setImage("images/emptyheart.png");

		if (heartCount == 0) endGame();

		rocketStopTimer->set(0.1f);

		return true;
		});


	// �̵����� - Ű���� �Է�

	// 82 83 84 85
	int pressedkey = 0;
	int moveX, moveY = 0;
	auto keyMoveTimer = Timer::create(0.1f);

	keyMoveTimer->setOnTimerCallback([&](TimerPtr timer)->bool
		{
			switch (pressedkey)
			{
			case 82:
				if (moveAvailable(-1, 0))
				{
					moveX = -1; moveY = 0;
					sceneChange(scene, garden, con, crown, moveX, moveY,find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}
				break;

			case 83:
				if (moveAvailable(1, 0))
				{
					moveX = 1; moveY = 0;
					sceneChange(scene, garden, con, crown, moveX, moveY, find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}
				break;
			case 84:
				if (moveAvailable(0, -1))
				{
					moveX = 0; moveY = -1;
					sceneChange(scene, garden, con, crown, moveX, moveY, find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}
				break;
			case 85:
				if (moveAvailable(0, 1))
				{
					moveX = 0; moveY = 1;
					sceneChange(scene, garden, con, crown, moveX, moveY, find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}

				break;
			}
			return false;
		});

	scene->setOnKeyboardCallback([&](ScenePtr scene, int key, bool pressed)->bool
		{
			if (pressed)
			{
				pressedkey = key;
				keyMoveTimer->start();
			}
			if (!pressed) keyMoveTimer->stop();

			return true;
		});



	// ������ �������� ���� 
	auto rocketMoveTimer = Timer::create(0.5f);
	rocketMoveTimer->start();

	rocketMoveTimer->setOnTimerCallback([&](TimerPtr timer)->bool
		{
			// ��� ������ ���������� Ȯ�� 
			if (moveRocket(scene, rockets, rocketPos, xspeed, explode, rocketStopTimer))
			{
				rocketInitPos(rocketPos);
				xspeed = 0;

			}
			rocketMoveTimer->start();
			xspeed++;
			return true;
		});



	startGame(scene);

	return 0;
}
