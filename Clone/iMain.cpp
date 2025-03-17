#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

// Include necessary header files
#include "iGraphics.h"
void drawTextBox();      // Function to draw the text box (for game over screen)
#include "Explosion.h"      // For explosion effects
#include "Rocket.h"         // For rocket firing logic
void drawHealthBar();    // Function to draw the health bar

// Game screen dimensions
#define screenWidth 1000
#define screenHeight 600

#include "Score.h"           // For score handling
#include "Menu.h"            // For menu-related functionality
#include "Background.h"      // For background handling

// Function to reset the game variables when health reaches 0 or on restart
void resetGame();

// Function to initialize the birds (enemies) in the game
void initializeBirds();

// Game-related variables
int health[10];          // Array to hold health bar images
int words = 200;         // Number of words in the word list for enemy ships


void newHighscore();     // Function to store new high scores
int Eship[10];           // Array for enemy spaceship images
int birdNumber = 6;      // Number of enemy spaceships
int activeBirdIndex = -1; // Index for the active bird
string currentInput = ""; // The current word typed by the player

// Flags for game states
bool music = true;       // Background music flag
bool gmusic = false;     // In-game music flag
bool gameOver = false;   // Flag for game over state

// List of words for the game that enemies (birds) will have
char List[][200] = {
	"ANT", "BAT", "CAT", "DOG", "ELK", "FOX", "GUM", "HAT", "JAM", "KIT", "LAB",
	"MAN", "NAP", "OWL", "PIG", "HAT", "RAT", "TOY", "VAN", "WAX", "YAK", "ZAP",
	"MILK", "FUND", "RING", "LEAP", "VENT", "YARD", "HIKE", "TILT", "OVEN", "FLUX",
	"BEAD", "PAVE", "GASP", "QUIZ", "JOLT", "QUIP", "TIDE", "ZONE", "FUME", "CURB",
	"WISP", "LEND", "HELM", "DART", "KITE", "RAKE", "MULE", "FLAP", "YARN", "VASE",
	"IRON", "DOME", "HUSH", "JEST", "LURE", "PINT", "SIFT", "TACK", "WART", "AQUA",
	"VAST", "GAZE", "JUMP", "KNOT", "NOVA", "QUAD", "RIPE", "SLOE", "TORN", "VIBE",
	"APPLE", "BRICK", "CLOUD", "DANCE", "EAGLE", "FAIRY", "GRAPE", "HOTEL", "IVORY",
	"JUICE", "KNIFE", "LEMON", "MUSIC", "NUDGE", "OLIVE", "PEACH", "QUILT", "ROAST",
	"SHEEP", "TIGER", "UMBRA", "VIPER", "WATCH", "XEROX", "YACHT", "ZEBRA"
};

// Function to generate random words for the enemy ships
string GenerateWord() {
	int index;
	string word;
	string prevWord = "";  // Store previous word to avoid repetition

	for (int i = 0; i < 25; i++) {
		index = rand() % words; // Generate a random index for the word list
		word = List[index];     // Select the word from the list

		if (word != prevWord) { // Ensure no duplicate words
			if (dy == 1 && word.length() == 3) { // Level 1: 3-letter words
				return word;
			}
			else if (dy == 2 && word.length() == 4) { // Level 2: 4-letter words
				return word;
			}
			else if (dy == 3 && word.length() >= 5) { // Level 3: 5+ letter words
				return word;
			}
		}
	}
	return "HELLO"; // Default word if no match found
}

// Struct to represent each enemy (spaceship)
struct BirdFall {
	int birdX, birdY;   // Position of the bird
	int bIndex;         // Index for the spaceship image
	string word;        // Word assigned to the bird
	bool birdShow;      // Whether the bird is currently visible on the screen
	bool cross;         // Whether the bird has crossed the screen's bottom boundary
};

// Array to hold the spaceship objects
BirdFall angryBirds[4];  // Store 4 bird objects

// Function to display the (spaceships) and their associated words
void birdFigure() {
	for (int i = 0; i < birdNumber; i++) {
		if (angryBirds[i].birdShow == true) {  // If the bird is visible
			iSetColor(255, 255, 255);         // Set the color to white
			iShowImage(angryBirds[i].birdX, angryBirds[i].birdY, 50, 50, Eship[angryBirds[i].bIndex]);  // Show the spaceship image
			iText(angryBirds[i].birdX - 10, angryBirds[i].birdY + 50, &angryBirds[i].word[0], GLUT_BITMAP_TIMES_ROMAN_24);  // Display the word associated with the bird
		}
	}
}

// Function to draw the health bar based on player's health
void drawHealthBar() {
	int healthImageIndex = 0;

	// Determine which health bar image to show based on current health
	if (hp == 10) {
		healthImageIndex = 0;
	}
	else if (hp == 9) {
		healthImageIndex = 1;
	}
	else if (hp == 8) {
		healthImageIndex = 2;
	}
	else if (hp == 7) {
		healthImageIndex = 3;
	}
	else if (hp == 6) {
		healthImageIndex = 4;
	}
	else if (hp == 5) {
		healthImageIndex = 5;
	}
	else if (hp == 4) {
		healthImageIndex = 6;
	}
	else if (hp == 3) {
		healthImageIndex = 7;
	}
	else if (hp == 2) {
		healthImageIndex = 8;
	}
	else if (hp == 1) {
		healthImageIndex = 9;
	}
	else if (hp == 0) {
		gameOver = true;  // Game over when health reaches 0
	}

	// Display the corresponding health bar image
	iShowImage(20, screenHeight - 100, 120, 50, health[healthImageIndex]);
}

// Function to reset the game when health reaches 0 or player chooses to restart
void resetGame() {
	activeBirdIndex = -1;  // Reset active bird index
	currentInput = "";     // Clear the current word input
	score = 0;             // Reset score
	hp = 10;               // Reset health points
	gameOver = false;      // Reset game over flag
	initializeBirds();     // Reinitialize the birds
}

// Function to handle keyboard input (to type the correct word and destroy the enemy spaceship)
void iKeyboard(unsigned char key) {
	if (gameOver == false && key >= 'A' && key <= 'Z') {
		PlaySound("music\\shot.wav", NULL, SND_ASYNC);  // Play sound when key is pressed
	}

	if (currentInput.length() == 0) {
		for (int i = 0; i < birdNumber; i++) {
			if (key == angryBirds[i].word[0]) {  // Check if the first letter of the word matches
				activeBirdIndex = i;
				currentInput += key;  // Add the typed key to the current input
				break;
			}
		}
	}
	else {
		if (key == angryBirds[activeBirdIndex].word[currentInput.length()]) {  // If the typed key matches the next letter
			currentInput += key;  // Add the key to the current input
			if (currentInput == angryBirds[activeBirdIndex].word) {  // If the entire word is typed correctly
				showExplosion(angryBirds[activeBirdIndex].birdX, angryBirds[activeBirdIndex].birdY);  // Show explosion
				score += angryBirds[activeBirdIndex].word.length() * 2;  // Update score
				activeBirdIndex = -1;  // Reset active bird
				currentInput = "";  // Clear current input
			}
		}
		else {
			currentInput = "";  // Reset input if incorrect letter is typed
		}
	}
}

// Function to handle explosion animation when a word is typed correctly
void showExplosion(int x, int y) {
	// Display explosion images at the given position (x, y)
	for (int i = 0; i < 7; i++) {
		iShowImage(x - 25, y - 25, 50, 50, ex[i]);  // Show explosion image
		iDelay(50);  // Delay to create animation effect
	}
}

// Main function to initialize and run the game
int main() {
	srand(time(NULL));  // Initialize random seed

	iInitialize(screenWidth, screenHeight, "Diving in Typing");  // Initialize graphics window

	// Load images and sounds for the game
	ship = iLoadImage("bullet/mainShip.png");
	b = iLoadImage("bullet/b1.png");
	bg1 = iLoadImage("bg/bg11.jpg");
	bg2 = iLoadImage("bg/bg12.jpg");
	bg3 = iLoadImage("bg/bg13.jpg");
	bg4 = iLoadImage("bg/bg14.jpg");
	bg5 = iLoadImage("bg/GO.jpg");

	initializeBirds();  // Initialize enemy birds

	// Play background music if enabled
	if (music) {
		PlaySound("music\\menu.wav", NULL, SND_LOOP | SND_ASYNC);
	}
	if (gmusic) {
		PlaySound("music\\bgame.wav", NULL, SND_LOOP | SND_ASYNC);
	}

	iStart();  // Start the game loop

	return 0;
}
