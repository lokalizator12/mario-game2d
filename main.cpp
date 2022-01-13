#include <SFML/Graphics.hpp>
//#include "map.h"

using namespace sf;
int ground = 360;					// ��� ��������� �����

class play {						// ����� � �����������
public:
	float Vx, Vy;					// ��������
	FloatRect rectplay; 
	bool Ground;					// �� ����� ��
	Sprite spriteplay;				//������� ����� ������ ��� ����������
	float currentFrame;				// ������� ���� ��� ��������

	play(Texture & image) {
		
		spriteplay.setTexture(image);
		
		rectplay = FloatRect(100, 360, 0, 0);// ��� ���������� ���
		Vx, Vy, currentFrame = 0;
		
	}
	void update(float time) {
		rectplay.left = rectplay.left + Vx * time; // ���������� �

		if (!Ground) {				// ���� �� �� ����� ��,
			Vy = Vy + 0.0005 * time; //��������� ��������� ������� �� ������� = ��������
			rectplay.top = rectplay.top + Vy * time; // ����������� �� ����� ���������� ��������� �� Y
			Ground = false;			// �������� ��� �� �� �� �����
		}
		if (rectplay.top > ground){ // ���� ���� ���������� ���� ����� ��
			rectplay.top = ground;	//�� ����� ��� "�������� �� �����" ����� �������� �����
			Vy = 0;					// � ������ ��������� ������� ������� �.�. �� ��� �����
			Ground = true;			// �������� ��� �� �� �����
		}
		currentFrame += 0.005 * time;// ��������� �� ���� ������ ������ �� ���������� ������� � ���������� � 0.005
		if (currentFrame > 3) { currentFrame -= 3; }// ���� ����� �� ��������� (3) ����� �� �������� � �������� �������
		
		if (Vx < 0) {
			spriteplay.setTextureRect(IntRect(90 * int(currentFrame) + 90, 0, -80, 111));//������ ������ ���� ������� � ������ �������� ��. (�������� �����)=�������� �(���������� �� ����)
		}
		if (Vx > 0) { 
			spriteplay.setTextureRect(IntRect(90 * int(currentFrame), 0, 80, 111)); 
		}
		
		
		spriteplay.setPosition(rectplay.left, rectplay.top);
		Vx = 0;
	}

};


int main() {
	ContextSettings Settings;
	Settings.antialiasingLevel = 10;// �����������
	RenderWindow window(VideoMode(800, 500), "Mario", Style::Default, Settings); // ��������� ���� � ��������
	
	
	//Image mapImage; // ���������� � ����������
	//mapImage.loadFromFile("images\\blocks.png");
	Image heroImage;
	heroImage.loadFromFile("images\\marioold.png");//���� � ��������(� ����� � ��������)

	
	//Texture textureMap; //�������� � ������� ��������� ��������
	//textureMap.loadFromImage(mapImage);
	Texture textureHero;
	textureHero.loadFromImage(heroImage);

	//Sprite spriteMap;
	//spriteMap.setTexture(textureMap);
	

	play one(textureHero);//���������� �������� 
	/*/Sprite spritetextr; // ������ �� �������� � ���������
	spritetextr.setTexture(textr);
	spritetextr.setTextureRect(IntRect(444, 0, 56, 111));//�������������� ����
	spritetextr.setPosition(200, 200);// ��� ��������� � ������
	textr.setSmooth(true);// �����������
	*/
	float currentFrame = 0;// �������������� ���������� ������

	Clock clock;// ������� �������
	while (window.isOpen()) {//���� ���� ���� �������

		float time = clock.getElapsedTime().asMicroseconds();//������� ����� � �������������
		clock.restart();// ������������� ���
		time = time / 800;// ��������� ������� - ������ � ��������

		
		Event event;// �������
		while (window.pollEvent(event)) { //����� ������� ������ ���� - ������� (�������)
			if (event.type == Event::Closed) {//������� ��������
				window.close();// �� ��� ���������
			}

		}
		if (Keyboard::isKeyPressed(Keyboard::A)) { // ���� �������� ������ �� ���������� :: �, ��
			one.Vx = (-0.1);// ������� �������� ����� �� �, ������ �� ������� � ���������� = ��������.
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			one.Vx = (0.1);//������ ��������� ��� ����� �� �
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) {//������ �����
			if (one.Ground) {// ���� �� �� ����� �� 
				one.Vy = -0.4;// ������ ��������� ����� �� Y
				one.Ground = false;//�������� ��� ��� �� �� �����
			}
		
		}
			
			window.clear(Color::Blue);

			/*for (int i = 0; i < heigthMap; ++i) {
				for (int x = 0; x < wigthMap; ++i) {
					if (MAP[i][x] == '2') { spriteMap.setTextureRect(IntRect(320, 0, 160, 160)); }
					if (MAP[i][x] == '1') { spriteMap.setTextureRect(IntRect(480, 0, 160, 160)); }
					if (MAP[i][x] == '#') { spriteMap.setTextureRect(IntRect(160, 0, 160, 160)); }
					if (MAP[i][x] == '0') { spriteMap.setTextureRect(IntRect(640, 0, 160, 160)); }
					spriteMap.setPosition(i * 160, x * 160);
					window.draw(spriteMap);
				}
			}
			*/
			one.update(time);
			window.draw(one.spriteplay);
			window.display();
			
		}

		return 0;
	}