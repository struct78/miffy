int cols = 8;
int rows = 5;
int pin = 6;
float delta = 0;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(cols, rows, pin, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE, NEO_GRB + NEO_KHZ800);


void neomatrix_setup() {
  matrix.begin();
  matrix.setBrightness( 10 );
  matrix.fillScreen( matrix.Color( 255, 255, 255 ) );
  matrix.show();
}

void neomatrix_toggle() {
  on = !on;
}

void neomatrix_off() {
  on = false;
}

void neomatrix_on() {
  on = true;
}

bool neomatrix_status() {
  return on;
}

void neomatrix_loop() {
  uint16_t x, y, z;
  float hue = 0.0;
  
  if (on) {
    delta += theta;

    for ( x = 0 ; x < cols ; x++ ) {
      for ( y = 0 ; y < rows ; y++ ) {
        float distance = dist( (float)cols/2, (float)rows/2, (float)x, (float)y );
        //z = ((rows*cols)>>1) + ( q%2 == 0 ? q/2 : -(q/2+1));

        // matrix.drawPixel( z / rows , z % rows, neomatrix_wheel((( q * 256 / 294) + iteration) & 255)); // This one is fine - but goes outside in
       // matrix.drawPixel( z / rows , z % rows, neomatrix_wheel ( ((z / rows) + iteration) & 255)); // This one goes left to right in a wave
       
        //matrix.drawPixel( z / rows, z % rows, neomatrix_wheel ( ( q + iteration) & 255) );
        //matrix.drawPixel( z / rows, z % rows, HSLtoRGB( (float)((iteration - x) % 360) / 360, 1.0, 0.5 )); //This one animates lengthwise

        //matrix.drawPixel( z / rows, z % rows, HSLtoRGB( (float)((iteration - y) % 360) / 360, 1.0, 0.5 ));

        // matrix.drawPixel( x, y, HSLtoRGB( hue, abs(sin(delta)), 0.5 ) ); - Sine wave does flashy flashy
        switch ( pattern ) {
          case RADIAL:
            hue = (float)(int((delta - distance) * 5) % 360) / 360;
            matrix.drawPixel( x, y, HSLtoRGB( hue, 1.0, 0.5 ) );
            break;
          default:
            break;
        }
      }
    }
    
    matrix.show(); 
  }
  else {
    matrix.fillScreen(0);
    matrix.show();
  }
}




float HueToRGB( float p, float q, float t ) {
  if ( t < 0 ) t += 1.0;
  if ( t > 1 ) t -= 1.0;
  if ( t < 1/6.0 ) return p + ( q - p ) * 6 * t;
  if ( t < 1/2.0 ) return q;
  if ( t < 2/3.0 ) return p + ( q - p ) * ( 2/3.0 - t ) * 6;
  return p;
}



uint16_t HSLtoRGB( float h, float s, float l ) {
    float r, g, b;
    
    if ( s == 0.0 ) {
        r = g = b = l; // achromatic
    } else {
        float q = l < 0.5 ? l * (1.0 + s) : l + s - l * s;
        float p = 2.0 * l - q;
        r = HueToRGB(p, q, h + 1/3.0);
        g = HueToRGB(p, q, h);
        b = HueToRGB(p, q, h - 1/3.0);
    }
    
    return matrix.Color( round(r * 255), round(g * 255), round(b * 255) );
}



