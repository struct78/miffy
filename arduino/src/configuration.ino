enum Pattern {
	WIPE,
	DIAGONAL_WIPE,
	RADIAL,
	RAINBOW_STRIPE,
	FIREPLACE
};

/* Neomatrix Specific constants */
const int cols           = 8;
const int rows           = 5;
const int pin            = 6;
const int min_contrast   = 1;
const int max_contrast   = 20;
const int min_brightness = 1;
const int max_brightness = 255;
const int min_speed      = 1;
const int max_speed      = 20;


/* User-configurable variables */
float theta              = 0.025;
bool power               = true;
int brightness           = 64;
int contrast             = 5;
Pattern pattern          = DIAGONAL_WIPE;
float delta              = 0;
