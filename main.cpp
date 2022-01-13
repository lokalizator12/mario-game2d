#include <SFML/Graphics.hpp>
//#include "map.h"

using namespace sf;
int ground = 360;					// где находится земля

class play {						// класс с гравитацией
public:
	float Vx, Vy;					// скорость
	FloatRect rectplay; 
	bool Ground;					// на земле ли
	Sprite spriteplay;				//создаем новый спрайт для гравитации
	float currentFrame;				// текущий кадр для анимации

	play(Texture & image) {
		
		spriteplay.setTexture(image);
		
		rectplay = FloatRect(100, 360, 0, 0);// где появляется чел
		Vx, Vy, currentFrame = 0;
		
	}
	void update(float time) {
		rectplay.left = rectplay.left + Vx * time; // координата Х

		if (!Ground) {				// если не на земле то,
			Vy = Vy + 0.0005 * time; //доавбляем ускорение падения ко времени = скорость
			rectplay.top = rectplay.top + Vy * time; // выситчываем на каком расстоянии находимся по Y
			Ground = false;			// сообщить что мы не на земле
		}
		if (rectplay.top > ground){ // если наше расстояние выше земли то
			rectplay.top = ground;	//то нужно его "спустить на землю" задав значение земли
			Vy = 0;					// и задать ускорение падения нулевым т.к. мы уже стоим
			Ground = true;			// сообщить что мы на земле
		}
		currentFrame += 0.005 * time;// добавляем по чуть кадров исходя из увеличения времени и расстояния в 0.005
		if (currentFrame > 3) { currentFrame -= 3; }// если дошел до заданного (3) кадра то отнимает и начинает сначала
		
		if (Vx < 0) {
			spriteplay.setTextureRect(IntRect(90 * int(currentFrame) + 90, 0, -80, 111));//спрайт меняет свою позицию с каждым нажатием кл. (меняется время)=меняется Х(умножается на кадр)
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
	Settings.antialiasingLevel = 10;// сглаживание
	RenderWindow window(VideoMode(800, 500), "Mario", Style::Default, Settings); // настройки окна и создание
	
	
	//Image mapImage; // переменная с картинками
	//mapImage.loadFromFile("images\\blocks.png");
	Image heroImage;
	heroImage.loadFromFile("images\\marioold.png");//путь к картинке(в папке с проектом)

	
	//Texture textureMap; //текстура в которой находится картинка
	//textureMap.loadFromImage(mapImage);
	Texture textureHero;
	textureHero.loadFromImage(heroImage);

	//Sprite spriteMap;
	//spriteMap.setTexture(textureMap);
	

	play one(textureHero);//отправляем текстуру 
	/*/Sprite spritetextr; // спрайт из текстуры с картинкой
	spritetextr.setTexture(textr);
	spritetextr.setTextureRect(IntRect(444, 0, 56, 111));//первоначальный перс
	spritetextr.setPosition(200, 200);// где находится с начала
	textr.setSmooth(true);// сглаживание
	*/
	float currentFrame = 0;// первоначальное количетсво кадров

	Clock clock;// функция времени
	while (window.isOpen()) {//цикл пока окно открыто

		float time = clock.getElapsedTime().asMicroseconds();//создаем время в микросекундах
		clock.restart();// перезапускаем его
		time = time / 800;// настройка времени - собсна и скорости

		
		Event event;// события
		while (window.pollEvent(event)) { //когда событие станет типо - закрыто (крестик)
			if (event.type == Event::Closed) {//событие закрытия
				window.close();// то оно закроется
			}

		}
		if (Keyboard::isKeyPressed(Keyboard::A)) { // если нажалась кнопка на клавиатуре :: А, то
			one.Vx = (-0.1);// создаем движение влево по Х, исходя из времени и расстояния = скорость.
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			one.Vx = (0.1);//задаем ускорение для право по Х
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) {//кнопка вверх
			if (one.Ground) {// если мы на земле то 
				one.Vy = -0.4;// задаем ускорение вверх по Y
				one.Ground = false;//сообщаем что уже не на земле
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