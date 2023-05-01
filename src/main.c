/*
======================================================
=  													 =
=    Created by Nicolas Atrax and Dylan DE JESUS	 =
=													 =
=													 =
=  The Main module is the one which launches the     =
=  work, it is the root of the project               =
=													 =
======================================================
*/

#include "../inc/menu.h"
#include "../inc/jeu.h"
#include "../inc/affichage_graphique.h"

/* Start of the game handling */
int main(int argc, char **argv)
{
	if (launchMenu() == 1)
	{ // The user choosed to play a game
		switch (launchGame())
		{
		case 1:
		{ // The user won
			launchWinWindow();
			break;
		}

		case 2:
		{ // The user ost
			launchLooseWindow();
			break;
		}

		default:
		{ // The user exited the game
			break;
		}
		}
	}
	return 0;
}