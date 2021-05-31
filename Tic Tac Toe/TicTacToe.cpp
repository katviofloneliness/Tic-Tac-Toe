#include <iostream>
#include <Windows.h>

using namespace std;
// To do: Make player unable to press any other button if there is one already pressed
// Smart bot plays, ex. copycat, smart prevention to prevent player from using only output like only Rock strat

int screenWidth = 120, screenHeight = 50;
int main() {
	// Screen / WinApi magic
	wchar_t* screen = new wchar_t[screenWidth * screenHeight];
	for (int i = 0; i < screenWidth * screenHeight; i++) { screen[i] = L' '; }
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dw_bytes_written = 0;

	// Main game loop Menu
	while (1) {
		// Set starting parameters
		srand(rand());
		bool isKeyPressed = false;
		//bool isMenu = false; // not used currently
		bool isPlaying = true;
		bool isPlayerReady = false;
		bool isPlayerWinner = false;
		int playerChoice = 1, npcChoice = 1;
		int score = 0, scoreBot = 0;

		// Draw Main Menu
		for (int i = 0; i < screenWidth; i++) {
			screen[i] = '=';
			screen[2 * screenWidth + i] = L'=';
		}
		wsprintf(&screen[screenWidth + 5], L"Tic Tac Shotgun Main Menu ");
		wsprintf(&screen[15 * screenWidth + 40], L"   Press space to play");
		WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, { 0,0 }, &dw_bytes_written);

		// Wait for space in hex
		while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);

		// Clear Screen
		for (int i = 0; i < screenWidth * screenHeight; i++) { screen[i] = L' '; }

		while (isPlaying) {
			isPlayerReady = false;
			isKeyPressed = false;

			// Draw Stats & Border
			for (int i = 0; i < screenWidth; i++) {
				screen[i] = '=';
				screen[2 * screenWidth + i] = L'=';
			}
			wsprintf(&screen[screenWidth + 5], L"Tic Tac Shotgun SCORE: %d %d", score, scoreBot);
			wsprintf(&screen[3 * screenWidth + 5], L"Press F to choose Rock > Scissors");
			wsprintf(&screen[4 * screenWidth + 5], L"Press H to choose Paper > Rock");
			wsprintf(&screen[5 * screenWidth + 5], L"Press K to choose Scissors > Paper");
			wsprintf(&screen[6 * screenWidth + 5], L"Press ESC to exit to Main Menu");

			// Display Frame
			WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, { 0,0 }, &dw_bytes_written);

			// Clear Screen
			for (int i = 0; i < screenWidth * screenHeight; i++) { screen[i] = L' '; }

			// Get Key in hexadecimal 
			// To do: Make player unable to press any other button if there is one already pressed
			while (isPlayerReady != true && isKeyPressed == false) {
				if (!HIWORD(GetKeyState(VK_ESCAPE)) && GetAsyncKeyState(VK_ESCAPE) && isKeyPressed == 0) { // ESC
					isPlaying = false, isPlayerReady = false, isKeyPressed = true; break;
				}
				if (HIWORD(GetKeyState(0x46)) == 0 && GetAsyncKeyState(0x46) && isKeyPressed == 0) { // F
					playerChoice = 1, isPlayerReady = true, isKeyPressed = true;
				}
				if (HIWORD(GetKeyState(0x48)) == 0 && GetAsyncKeyState(0x48) && isKeyPressed == 0) { // H
					playerChoice = 2, isPlayerReady = true, isKeyPressed = true;
				}
				if (HIWORD(GetKeyState(0x4B)) == 0 && GetAsyncKeyState(0x4B) && isKeyPressed == 0) { // K
					playerChoice = 3, isPlayerReady = true, isKeyPressed = true;
				}
			}

			// Randomise NPC Choice
			npcChoice = rand() % 3 + 1;

			// Showdown RNG vs Player
			if (npcChoice == playerChoice) {
				wsprintf(&screen[15 * screenWidth + 40], L"Draw");
			}
			else if (playerChoice == 3 && npcChoice == 2 || playerChoice == 2 && npcChoice == 1 || playerChoice == 1
				&& npcChoice == 3)
			{
				wsprintf(&screen[15 * screenWidth + 40], L"Player wins");
				score++;
			}
			else {
				scoreBot++;
				wsprintf(&screen[15 * screenWidth + 40], L"Bot wins");
			}

		}	//  player pressed ESC 
		if (isPlaying == false) {
			wsprintf(&screen[15 * screenWidth + 40], L"   Press space to play");
		}
	}
	return 0;
}