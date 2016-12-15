enum Pattern {
	WIPE,
	RADIAL,
	PULSE,
	PATTERNMAX
};

bool power          = true;
float theta         = 0.01;
int contrast        = 5;
int brightness      = 40;
int cols            = 8;
int rows            = 5;
int pin             = 6;
float delta         = 0;
Pattern pattern     = RADIAL;
