#include <raylib.h>

//struct = type personnalisé qui regroupe les variables liées à la balle
//permet d'accéder via ball.x, ball.speedX etc.
struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;
	float spin;

	void Draw() 
	{
		//drawCircle attend des int on ne peut pas lui donner un (float 2.0f) directement ça va raler on fait un (cast) on dit au compliateur de convertir ce float en int il devient du coup 2
		DrawCircle((int) x, (int) y, radius, WHITE); //on prend la largeur et hauteur de l'écrant puis on la divise par 2 le rayon est a 5 et une couleur blanche
	}
};

struct Paddle
{
	float x, y;
	float speed;
	float width, height;

	Rectangle GetRect()
	{
		return Rectangle{ x - width / 2, y - height / 2, 10, 100 };
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), WHITE); 
	}
};

int main() 
{
	InitWindow(800, 600, "PongGameLearn"); // permet de crée une fenetre Application avec la taille et le nom
	SetWindowState(FLAG_VSYNC_HINT); // regle le taux de rafraichissement de l'ecrant

	Ball ball;
	//au lieu d'appeler les float j'ai fait une struct en haut se qui permet de mettre directement la valeur ball.x ball.y etc.
	//permet de changer la position de la balle 
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 300; // on ajoute de la vitesse 
	ball.speedY = 300;
	ball.spin = 0;

	//raquette gauche
	Paddle leftPaddle;
	leftPaddle.x = 50;//je prend la valeur 50 de DrawRectangle(50, GetScreenHeight() / 2 - 50, 10, 100, WHITE); plus bas
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 500;
	//raquette droite
	//au lieu de DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 5, WHITE); nous le transformons en une seule fonction rightPaddle pareil pour celui de gauche
	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 500;

	const char* winnerText = nullptr;

	while (!WindowShouldClose()) // une boucle qui permet de garder la fenetre ouverte 
	{
		ball.x += ball.speedX * GetFrameTime(); //ajoute une vitesse a notre balle et on multiplie par le temp entre frames pour que la vitesse soit identique peut importe le FPS
		ball.y += ball.speedY * GetFrameTime();
		ball.speedY += ball.spin * GetFrameTime();

		//Fonction haut/bas écran
		if (ball.y < 0) //si la balle dépasse le Haut de l'écran alors
		{
			ball.y = 0; // remet la balle exactement au bord
			ball.speedY *= -1; // inverse la direction haut
		}
		if (ball.y > GetScreenHeight()) // si la balle dépasse le bas de l'écran alors
		{
			ball.y = GetScreenHeight(); //permet d'eviter que la balle reste bloquée en bas de l'écran pendent un moment 
			ball.speedY *= -1; // inverse la direction bas 
		}
		
		
		//Raquette gauche
		if (IsKeyDown(KEY_S)) //deplace vers le haut 
		{
			leftPaddle.y -= leftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_X)) //deplace vers le bas
		{
			leftPaddle.y += leftPaddle.speed * GetFrameTime();
		}
		//Raquette droite
		if (IsKeyDown(KEY_UP))
		{
			rightPaddle.y -= rightPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			rightPaddle.y += rightPaddle.speed * GetFrameTime();
		}

		//verifie la collision raquette droite et gauche
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRect()))
		{
			// La balle va vers la gauche ? (speedX négatif)
			if (ball.speedX < 0)
			{
				ball.speedX *= -1.1f;// inverse + accélère
				ball.spin = (ball.y - leftPaddle.y) * 1.0f;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;// angle de rebond selon la zone touchée sur la raquette : haut/bas/centre
			}	
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1.1f;// inverse + accélère
				ball.spin = (ball.y - leftPaddle.y) * 1.0f;
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * - ball.speedX;
			}
		}

		if (ball.x < 0)
		{
			winnerText = "Right Player Wins!";
		}
		if (ball.x > GetScreenWidth())
		{
			winnerText = "Left Player Wins!";
		}
		if (winnerText && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 300;
			ball.speedY = 300;
			winnerText = nullptr;
		}

			
		BeginDrawing(); //dessine la page avec ce qui suit en dessou couleur ect
		ClearBackground(BLACK); // permet de colorer le fond de la page 

		//On appel la fonction DrawCircle((int) x, (int) y, radius, WHITE); plus haut
		ball.Draw();
		//on appel leftPaddle rightPaddle qui sont plus haut 
		leftPaddle.Draw();
		rightPaddle.Draw();

		if (winnerText)
		{
			int textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
		}

		EndDrawing(); //permet de terminer le processus dessin et gere aussi des evenements exemple quiter plein ecrant reduire page ect

		DrawFPS(10, 10); // affiche FPS
	}

	CloseWindow();

	return 0;
}