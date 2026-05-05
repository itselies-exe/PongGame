#include <raylib.h>

//struct = type personnalisé qui regroupe les variables liées à la balle
//permet d'accéder via ball.x, ball.speedX etc.
struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;
};

int main() 
{
	InitWindow(800, 600, "PongGameLearn"); // permet de crée une fenetre Application avec la taille et le nom
	SetWindowState(FLAG_VSYNC_HINT); // regle le taux de rafraichissement de l'ecrant

	Ball ball;
	//au lieu d'appeler les float j'ai fait une struct en haut se qui permet de mettre directement la valeur 
	//permet de changer la position de la balle 
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 300; // on ajoute de la vitesse 
	ball.speedY = 300;


	while (!WindowShouldClose()) // une boucle qui permet de garder la fenetre ouverte 
	{
		ball.x += ball.speedX * GetFrameTime(); //ajoute une vitesse a notre balle et on multiplie par le temp entre frames pour que la vitesse soit identique peut importe le FPS
		ball.y += ball.speedY * GetFrameTime();

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
		
		// Fonction Largeur écrant
		if (ball.x < 0) // si la balle depasse le coté gauche de l'écrant alors
		{
			ball.x = 0;
			ball.speedX *= -1; // inverse la direction gauche
		}
		if (ball.x > GetScreenWidth()) // si la balle depasse le coté droit alors
		{
			ball.x = GetScreenWidth();
			ball.speedX *= -1; // inverse la direction droit
		}

		BeginDrawing(); //dessine la page avec ce qui suit en dessou couleur ect
		ClearBackground(BLACK); // permet de colorer le fond de la page 

		//drawCircle attend des int on ne peut pas lui donner un (float 2.0f) directement ça va raler on fait un (cast) on dit au compliateur de convertir ce float en int il devient du coup 2
		DrawCircle((int) ball.x, (int) ball.y, ball.radius, WHITE); //on prend la largeur et hauteur de l'écrant puis on la divise par 2 le rayon est mis a 5 et mis une couleur blanche
		DrawRectangle(50, GetScreenHeight() / 2 - 50, 10, 100, WHITE); //rectangle Gauche est legerement decaler par rapport a la gauche on soutrai la moitier de deux a 50pour centrer le rectangle

		/*
		le rectangle Droit nous devons obtenir la largeur total de l'écrant et soustraire a 50
		le rectangle est dessiner a partir de la gauche on soustrait egalement la largeur de la raquette
		*/
		DrawRectangle(GetScreenWidth() - 50 - 10, GetScreenHeight() / 2 - 50, 10, 100, WHITE); 

		EndDrawing(); //permet de terminer le processus dessin et gere aussi des evenements exemple quiter plein ecrant reduire page ect

		DrawFPS(10, 10); // affiche FPS
	}

	CloseWindow();

	return 0;
}