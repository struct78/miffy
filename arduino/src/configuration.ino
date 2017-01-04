enum Pattern {
	WIPE,
	RADIAL,
	PULSE,
	PATTERNMAX
};

/* Neomatrix Specific constants */
const int cols      = 8;
const int rows      = 5;
const int pin       = 6;

/* User-configurable variables */
float theta         = 0.5;
bool power          = true;
int contrast        = 2;
int brightness      = 64;
Pattern pattern     = RADIAL;

float delta         = 0;
