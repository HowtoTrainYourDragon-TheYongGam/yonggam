#include <iostream>
#include <bangtal>
#include <ctime>
#include <string>
#include <string.h>

using namespace bangtal;
using namespace std;


// Ű���� 
enum{
		UP = 84,
		LEFT = 82,
		RIGHT = 83,
		DOWN = 85,
		SPACEBAR = 75
};



// GAME 2 �޼���
void makingImage(string filename[5], string number[10], ObjectPtr comboNum[10], int& num_index, int& index, ScenePtr& game2scene) {
	for (num_index = 0; num_index < 10; num_index++) {
		number[num_index] = "images2/" + to_string(num_index + 1) + ".png";
		comboNum[num_index] = Object::create(number[num_index], game2scene, 515, 500, false);
		comboNum[num_index]->setScale(3.0f);
	}
	for (index = 0; index < 5; index++) {
		filename[index] = "images2/ingredient" + to_string(index + 1) + ".png";
	}
}

void ingredientCase(int& num, int& i, int& level, int question[], ObjectPtr q_ingredient[], string filename[], ScenePtr& game2scene, int questX, int questY[], ObjectPtr& q_bread1) {
	for (i = 0; i < level; i++) {
		num = rand() % 5;
		switch (num) {
		case 0:
			question[i] = UP;
			q_ingredient[i] = Object::create(filename[0], game2scene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		case 1:
			question[i] = RIGHT;
			q_ingredient[i] = Object::create(filename[1], game2scene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		case 2:
			question[i] = LEFT;
			q_ingredient[i] = Object::create(filename[2], game2scene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		case 3:
			question[i] = DOWN;
			q_ingredient[i] = Object::create(filename[3], game2scene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		case 4:
			question[i] = SPACEBAR;
			q_ingredient[i] = Object::create(filename[4], game2scene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		}
	}
	q_bread1->locate(game2scene, questX, questY[i]);
	q_bread1->show();
}

void ingredient2case(int& q_index, int& key_flag, int question[], ObjectPtr ingredient[], string filename[], ScenePtr& game2scene, int& answerX, int answerY[]) {
	switch (question[q_index]) {
	case UP:
		ingredient[q_index] = Object::create(filename[0], game2scene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
		break;
	case RIGHT:
		ingredient[q_index] = Object::create(filename[1], game2scene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
		break;
	case LEFT:
		ingredient[q_index] = Object::create(filename[2], game2scene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
		break;
	case DOWN:
		ingredient[q_index] = Object::create(filename[3], game2scene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
		break;
	case SPACEBAR:
		ingredient[q_index] = Object::create(filename[4], game2scene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
	}
	cout << "correct" << endl;
	key_flag = 1;
	q_index++;
}
void clearArray(int key_press[], ObjectPtr ingredient[], ObjectPtr q_ingredient[], int& q_index, int& key_index, int& key_flag) {
	for (int i = 0; i < 100; i++) {
		key_press[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		ingredient[i]->hide();
		ingredient[i] = nullptr;
	}
	for (int i = 0; i < 5; i++) {
		q_ingredient[i]->hide();
		q_ingredient[i] = nullptr;
	}
	q_index = 0;
	key_index = 0;
	key_flag = 0;
}
void makeTimer(ObjectPtr& bread1, ObjectPtr& clear, ObjectPtr& combo, ObjectPtr comboNum[], int& cnt, int& q_index, int& answerX, int answerY[], TimerPtr& breadTimer, TimerPtr& clearTimer, TimerPtr& comboTimer, ScenePtr& game2scene) {
	bread1->locate(game2scene, answerX, answerY[q_index]);
	bread1->show();
	clear->show();
	combo->show();
	comboNum[cnt - 1]->show();
	cnt++;
	breadTimer->set(0.2f);
	breadTimer->start();
	clearTimer->set(0.4f);
	clearTimer->start();
	comboTimer->set(0.4f);
	comboTimer->start();
}



//GAME3 �޼���
// game3 ��ǥ ��ġ
typedef struct _pos {
	int x = 0;
	int y = 0;
}Pos;

// Game3 map
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

//game 3 �㿡���� ĳ���� ��ġ
Pos now;

// game3 ���� ������ ��� ��ġ���� �������� ����ش�.
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
		rockets[i] = Object::create("images3/rocket.png", scene, 1280, 0);
	}

	for (int i = 0; i < 3; i++)
	{
		hearts[i] = Object::create("images3/filledheart.png", scene, 700 + 80 * i, 600);
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
		rocketPos[i].x = 16 + rand() % 8; // ȭ�� ���� ��ǥ�� ����
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
		x = rocketPos[i].x * 80 - xspeed * 8; //��ǥ ��� ����
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

//����
int main()
{
	unsigned int srand(time(NULL));
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);


// ��Ʈ��

	//��Ʈ�� 
	auto intro = Scene::create(" INTRO ", "images/intro2.png");
	auto introMusic = Sound::create("images/introMusic.mp3");
	introMusic->play();
	auto nextToStage1 = Object::create("images/next.png", intro, 1060, 230);
	
	//stage1
	auto stage1 = Scene::create("stage1", "images/stage1.png");
	auto stage1story = Scene::create("stage1", "images/stage1story.png");
	auto nextToStage2 = Object::create("images/next.png", stage1story, 1060, 350);

	//stage2
	auto stage2 = Scene::create("stage2", "images/stage2.png");
	auto stage2story = Scene::create("stage2", "images/stage2story.png");
	auto nextToGame2 = Object::create("images/next.png", stage2story, 1060, 350);
	auto Game2End = Scene::create("stage2", "images/stage2story.png");


	// stage3 
	auto stage3 = Scene::create("stage3", "images/stage3story.png");
	auto stage3story = Scene::create("stage3", "images/stage3story.png");
	auto nextToGame3 = Object::create("images/next.png", stage3story, 1060, 350);
	auto Game3End = Scene::create("stage2", "images/stage2story.png");




// GAME 1 


// GAME 2 ����

	//-----start scene ----------
	auto game2intro = Scene::create("game2intro", "images2/startscene.png");
	auto badbgm = Sound::create("images2/badbgm.mp3");
	auto method = Object::create("images2/game2method.png", game2intro, 720, 200);
	auto game2startbtn = Object::create("images2/startbtn.png", game2intro, 590, 0);
	game2startbtn->setScale(0.15f);

	// game scene
	auto game2scene = Scene::create("Hamburger Game", "images2/backgroundscene.png");
	auto bigmac = Sound::create("images2/bigmac.mp3");



	int level = 5;
	int num = 0;
	int questX = 200;
	int answerX = 830;
	int answerY[10] = { 317,354,391,428,465,502,539,576,613,650 };
	int questY[10] = { 317,354,391,428,465,502,539,576,613,650 };
	int i = 0;
	int question[10] = { 0 };

	auto clear = Object::create("images2/clear.png", game2scene, 500, 320, false);
	clear->setScale(1.5f);
	auto combo = Object::create("images2/combo.png", game2scene, 570, 500, false);
	combo->setScale(1.5f);
	auto bread2 = Object::create("images2/bread2.png", game2scene, 830, 290);
	auto q_bread2 = Object::create("images2/bread2.png", game2scene, 200, 290);
	auto q_bread1 = Object::create("images2/bread1.png", game2scene, questX, questY[0], false);
	auto bread1 = Object::create("images2/bread1.png", game2scene, answerX, answerY[0], false);
	auto timer = Timer::create(0.1f);
	auto basetimer = Timer::create(4.0f);
	auto combosound = Sound::create("images2/gamesound.mp3");
	bread1->setScale(3.0f);
	q_bread1->setScale(3.0f);

	ObjectPtr q_ingredient[5] = { 0 };
	ObjectPtr ingredient[5] = { 0 };
	ObjectPtr comboNum[10] = { 0 };
	string filename[5];
	string number[10];
	int index = 0;
	int num_index = 0;
	int key_index = 0;
	int q_index = 0;
	int key_press[100] = { 0 };
	int key_flag = 0;
	int cnt = 1;
	q_bread2->setScale(3.0f);
	bread2->setScale(3.0f);
	basetimer->set(40.f);


//GAME 3 ����

	//1280 * 720 ȭ��
	auto game3intro = Scene::create("escape game", "images/game3intro.png");
	auto game3startbtn = Object::create("images2/startbtn.png", game3intro, 800, 80);
	game3startbtn->setScale(0.1f);



	auto game3scene = Scene::create("escape game", "images3/sea.png");

	// garden ũ�� : 2560 x 1680  
	// ���� �� ����, �� �Ʒ� ����� �ʱ� scene���� (480,-960) ��ǥ�� ��ġ�Ѵ�.
	auto garden = Object::create("images3/garden2.png", game3scene, 480, -960);
	auto character = Object::create("images3/yonggam7.png", game3scene, 480, 165);

	// ��, �հ�
	auto crown = Object::create("images3/crown.png", game3scene, 480 + 18 * 80, -960 + 18 * 80); //���� �𼭸��� �������� (18 * 80 ,18*80 ) ������ ���� ��ġ  480 + (18*80) , -960 + 18 * 80 
	auto con = Object::create("images3/key.png", game3scene, 480 + 24 * 80, -960); // ���� �𼭸��� �������� (24 * 80 , 0) ������ ���� ��ġ 480 + (24*80), -960 
	int find = 0;

	// �ȳ� ����
	auto map = Object::create("images3/map.png", game3scene, 1000, 500);

	// ������� ���ϵ� 
	ObjectPtr rockets[20];
	Pos rocketPos[20];
	int xspeed = 0;


	// ����
	ObjectPtr hearts[3];
	int heartCount = 3;


	// �ʱ�ȭ 
	init(game3scene, rockets, hearts);
	rocketInitPos(rocketPos);

	// ����
	auto explode = Object::create("images3/explode.png", game3scene, 480, 160);
	explode->hide();



	// �������� ���� ���� ����
	auto rocketStopTimer = Timer::create(0.1f);

	// �̵����� - Ű���� �Է�
	int pressedkey = 0;
	int moveX, moveY = 0;
	auto keyMoveTimer = Timer::create(0.1f);


	// ������ �������� ���� 
	auto rocketMoveTimer = Timer::create(0.5f);


//��Ʈ�� �����Լ�

	nextToStage1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		stage1story->enter();
		return true;
		});

	nextToStage2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		stage2story->enter();
		return true;
	});

	nextToGame2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		game2intro->enter();
		showTimer(basetimer);
		badbgm->play(true);
		return true;
	});

	nextToGame3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		game3intro->enter();

		return true;
	});


//GAME2 �����Լ� 
	makingImage(filename, number, comboNum, num_index, index, game2scene);

	game2startbtn->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		game2scene->enter();
		bigmac->play(true);
		badbgm->stop();
		return true;
		});


	timer->setOnTimerCallback([&](TimerPtr t)->bool {
		ingredientCase(num, i, level, question, q_ingredient, filename, game2scene, questX, questY, q_bread1);
		return true;
		});
	timer->start();
	

	auto clearTimer = Timer::create(0.3f);
	clearTimer->setOnTimerCallback([&](TimerPtr clearT)->bool {
		clear->hide();
		return true;
		});
	auto comboTimer = Timer::create(0.3f);
	comboTimer->setOnTimerCallback([&](TimerPtr comboT)->bool {
		combo->hide();
		for (auto& e : comboNum) {
			e->hide();
		}
		combosound->stop();
		return true;
		});
	int flag = 0;
	auto breadTimer = Timer::create(0.3f);
	breadTimer->setOnTimerCallback([&](TimerPtr breadT)->bool {
		bread1->hide();
		if (1) {
			breadT->set(0.3f);
		}
		flag = 1;
		return true;
		});

	basetimer->setOnTimerCallback([&](TimerPtr baseT)->bool {
		showMessage("YOU LOSE");
		//endGame();
		return true;
		});

	game2scene->setOnKeyboardCallback([&](ScenePtr game2scene, int key, bool pressed)->bool {
		basetimer->start();
		key_press[key_index] = key;
		timer->stop();
		if (key_index % 2 == 0) {
			if (question[q_index] == key_press[key_index]) {
				ingredient2case(q_index, key_flag, question, ingredient, filename, game2scene, answerX, answerY);
			}
			else if (question[q_index] != key_press[key_index] && question[q_index] != 0) {
				showMessage("YOU LOSE");
				//endGame();
			}
			else if (question[q_index] == 0 && key_flag == 1) {
				basetimer->set(40.0f);
				combosound->play(true);
				basetimer->stop();
				makeTimer(bread1, clear, combo, comboNum, cnt, q_index, answerX, answerY, breadTimer, clearTimer, comboTimer, game2scene);
				clearArray(key_press, ingredient, q_ingredient, q_index, key_index, key_flag);
				if (cnt > 0) {
					basetimer->stop();
					bigmac->stop();
					hideTimer();
					stage3story->enter();
				}
				timer->start();
			}
		}
		key_index++;
		return true;
	});


	// GAME 3 �����Լ�
	game3startbtn->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		game3scene->enter();
		rocketMoveTimer->start();
		return true;
	});

	rocketStopTimer->setOnTimerCallback([&](TimerPtr timer)->bool {
		explode->hide();
		hearts[--heartCount]->setImage("images3/emptyheart.png");

		if (heartCount == 0) endGame();

		rocketStopTimer->set(0.1f);

		return true;
		});




	keyMoveTimer->setOnTimerCallback([&](TimerPtr timer)->bool
		{
			switch (pressedkey)
			{
			case LEFT:
				if (moveAvailable(-1, 0))
				{
					moveX = -1; moveY = 0;
					sceneChange(game3scene, garden, con, crown, moveX, moveY,find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}
				break;

			case RIGHT:
				if (moveAvailable(1, 0))
				{
					moveX = 1; moveY = 0;
					sceneChange(game3scene, garden, con, crown, moveX, moveY, find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}
				break;
			case UP:
				if (moveAvailable(0, -1))
				{
					moveX = 0; moveY = -1;
					sceneChange(game3scene, garden, con, crown, moveX, moveY, find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}
				break;
			case DOWN:
				if (moveAvailable(0, 1))
				{
					moveX = 0; moveY = 1;
					sceneChange(game3scene, garden, con, crown, moveX, moveY, find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}

				break;
			}
			return false;
	});

	game3scene->setOnKeyboardCallback([&](ScenePtr scene, int key, bool pressed)->bool
		{
			if (pressed)
			{
				pressedkey = key;
				keyMoveTimer->start();
			}
			if (!pressed) keyMoveTimer->stop();

			return true;
		});


	rocketMoveTimer->setOnTimerCallback([&](TimerPtr timer)->bool
		{
			// ��� ������ ���������� Ȯ�� 
			if (moveRocket(game3scene, rockets, rocketPos, xspeed, explode, rocketStopTimer))
			{
				rocketInitPos(rocketPos);
				xspeed = 0;

			}
			rocketMoveTimer->start();
			xspeed++;
			return true;
		});



	startGame(intro);

	return 0;
}
