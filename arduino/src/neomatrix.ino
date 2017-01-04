Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(cols, rows, pin, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE, NEO_GRB + NEO_KHZ800);

/**
 * @name neomatrix_setup
 * @description Called from main setup()
 * @return {void}
**/
void neomatrix_setup() {
	matrix.begin();
	matrix.setBrightness( get_neomatrix_brightness() );
	matrix.fillScreen( matrix.Color( 255, 50, 255 ) );
	matrix.show();
}

/**
 * @name set_neomatrix_power
 * @description Sets the power on or off. True = on. False = off.
 * @param {bool} power
 * @return {void}
**/
void set_neomatrix_power( bool p ) {
	power = p;
}

/**
 * @name get_neomatrix_power
 * @description Returns the current power state.
 * @return {bool}
**/
bool get_neomatrix_power() {
	return power;
}

/**
 * @name set_neomatrix_speed
 * @description Sets the speed of the colour cycle.
 * @param {float} theta - A number between 1 and 100
 * @return {void}
**/
void set_neomatrix_speed( float t ) {
	theta = (float) constrain(t, 1, 100) / 100;
}

/**
 * @name get_neomatrix_speed
 * @description Gets the speed of the colour cycle as a number between 1 and 100
 * @return {int}
**/
int get_neomatrix_speed() {
	return (int) theta * 100;
}

/**
 * @name set_neomatrix_brightness
 * @description Sets the brightness of the LEDs.
 * @param {int} t - A number between 1 and 255.
 * @return {void}
**/
void set_neomatrix_brightness( int t ) {
	brightness = constrain(t, 1, 255);
}

/**
 * @name get_neomatrix_brightness
 * @description Gets the brightness of the LEDs as a number between 1 and 255.
 * @return {int}
**/
int get_neomatrix_brightness() {
	return (int) brightness;
}

/**
 * @name set_neomatrix_brightness
 * @description Sets the contrast of the LEDs.
 * @param {int} t - A number between 1 and 10.
 * @return {void}
**/
void set_neomatrix_contrast( int t ) {
	contrast = constrain(t, 1, 10);
}

/**
 * @name get_neomatrix_contrast
 * @description Gets the contrast of the LEDs as a number between 1 and 10.
 * @return {int}
**/
int get_neomatrix_contrast() {
	return (int) contrast;
}

/**
 * @name set_neomatrix_pattern
 * @description Sets the algorithm for the colour cycle.
 * @param {int} t - A number between 1 and PATTERNMAX.
 * @return {void}
**/
void set_neomatrix_pattern( int p ) {
	pattern = (Pattern)constrain( p, 1, PATTERNMAX-1 );
}

/**
 * @name get_neomatrix_pattern
 * @description Gets the algorithm of the colour cycle.
 * @return {int}
**/
int get_neomatrix_pattern() {
	return (int) pattern;
}

/**
 * @name hue_to_rgb
 * @description Helper function for hue_to_rgb. Converts hue degrees to RGB.
 * @param {float} p - Combination of lightness/brightness (0.0 - 1.0)
 * @param {float} q - Combination of lightness/brightness (0.0 - 1.0)
 * @param {float} t - Hue (0.0 - 1.0)
 * @return {float}
**/
float hue_to_rgb( float p, float q, float t ) {
	if ( t < 0 ) t += 1.0;
	if ( t > 1 ) t -= 1.0;
	if ( t < 1/6.0 ) return p + ( q - p ) * 6 * t;
	if ( t < 1/2.0 ) return q;
	if ( t < 2/3.0 ) return p + ( q - p ) * ( 2/3.0 - t ) * 6;
	return p;
}

/**
 * @name hue_to_rgb
 * @description Converts HSL to RGB.
 * @param {float} h - Hue (0.0 - 1.0)
 * @param {float} s - Saturation (0.0 - 1.0)
 * @param {float} l - Lightness (0.0 - 1.0)
 * @return {Color}
**/
uint16_t hsl_to_rgb( float h, float s, float l ) {
		float r, g, b;

		if ( s == 0.0 ) {
			// No saturation, so it's grey
			r = g = b = l;
		} else {
				// If the lightness is less than 0.5, then multiply by 1+saturation, otherwise add the saturation and subtract lightness multipled by saturation.
				float q = l < 0.5 ? l * (1.0 + s) : l + s - l * s;
				float p = 2.0 * l - q;
				r = hue_to_rgb(p, q, h + 1/3.0);
				g = hue_to_rgb(p, q, h);
				b = hue_to_rgb(p, q, h - 1/3.0);
		}

		// Return a neomatrix colour
		return matrix.Color( round(r * 255), round(g * 255), round(b * 255) );
}

/**
 * @name neomatrix_loop
 * @description This function is called from main loop() and sets the LED values if the lamp is on.
 * @return {void}
**/
void neomatrix_loop() {
	uint8_t x, y, z;
	float hue = 0.0;

	if ( get_neomatrix_power() ) {
		matrix.setBrightness( get_neomatrix_brightness() );

		delta += theta;
		for ( x = 0 ; x < cols ; x++ ) {
			for ( y = 0 ; y < rows ; y++ ) {
				float distance = dist( (float)cols/2, (float)rows/2, (float)x, (float)y );
				//z = ((rows*cols)>>1) + ( q%2 == 0 ? q/2 : -(q/2+1));

				// matrix.drawPixel( z / rows , z % rows, neomatrix_wheel((( q * 256 / 294) + iteration) & 255)); // This one is fine - but goes outside in
			 //  // This one goes left to right in a wave

				//matrix.drawPixel( z / rows, z % rows, neomatrix_wheel ( ( q + iteration) & 255) );
				//matrix.drawPixel( z / rows, z % rows, HSLtoRGB( (float)((iteration - x) % 360) / 360, 1.0, 0.5 )); //This one animates lengthwise

				//matrix.drawPixel( z / rows, z % rows, HSLtoRGB( (float)((iteration - y) % 360) / 360, 1.0, 0.5 ));

				// matrix.drawPixel( x, y, HSLtoRGB( hue, abs(sin(delta)), 0.5 ) ); - Sine wave does flashy flashy
				switch ( pattern ) {
					case RADIAL:
						hue = (float)(int((delta - distance) * contrast) % 360) / 360;
						matrix.drawPixel( x, y, hsl_to_rgb( hue, 1.0, 0.5 ) );
						break;
					case WIPE:
						hue = (float)(int((z / rows) + delta) % 360) / 360;
						matrix.drawPixel( x, y, hsl_to_rgb( hue, 1.0, 0.5 ));
						break;
					case PULSE:
						hue = (float)(int((delta - distance) * contrast) % 360) / 360;
						matrix.drawPixel( x, y, hsl_to_rgb( hue, abs(sin(delta)), 0.5 ) );
					default:
						break;
				}
			}
		}
	}
	else {
		matrix.fillScreen(0);
	}

	matrix.show();
}
