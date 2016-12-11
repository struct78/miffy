float dist( float x1, float y1, float x2, float y2 ) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    return (float) sqrt(dx*dx + dy*dy);
}

float scale( float x, float y ) {
  return (float) x * y;
}

