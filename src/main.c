#define GLFW_INCLUDE_NONE

#include "../inc/menu.h"
#include "../inc/jeu.h"
#include "../inc/affichage_graphique.h"



int main(int argc, char **argv)
{	
	if(launchMenu() == 1){ // The user choosed to play a game
		switch(launchGame()){
			case 1 : {	// The user won
				launchWinWindow();
				break;
			}

			case 2 : {	// The user ost
				launchLooseWindow();
				break;
			}

			default : { // The user exited the game
				break;
			}
		}
	}
	return 0;
}