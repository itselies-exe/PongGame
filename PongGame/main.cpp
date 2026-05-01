#include <raylib.h>

int main() 
{
	InitWindow(800, 600, "PongGameLearn"); // permet de crée une fenetre Application avec la taille et le nom
	SetWindowState(FLAG_VSYNC_HINT); // regle le taux de rafraichissement de l'ecrant

	while (!WindowShouldClose()) // une boucle qui permet de garder la fenetre ouverte 
	{
		BeginDrawing(); //dessine la page avec ce qui suit en dessou couleur ect
		ClearBackground(BLACK); // permet de colorer le fond de la page 

		DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 5, WHITE); //on prend la largeur et hauteur de l'écrant puis on la divise par 2 le rayon est mis a 5 et mis une couleur blanche
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