/**
 * @name dist
 * @description Gets the distance between two vectors. This is used for the radial pattern.
 * @param {float} x1 - The x coordinate of the first vector.
 * @param {float} y2 - The y coordinate of the first vector.
 * @param {float} x2 - The x coordinate of the second vector.
 * @param {float} y2 - The y coordinate of the second vector.
 * @return {float}
**/
float dist( float x1, float y1, float x2, float y2 ) {
	float dx = x1 - x2;
	float dy = y1 - y2;
	return (float) sqrt(dx*dx + dy*dy);
}

/**
 * @name mapf
 * @description Maps a floating point number to a range of floating point numbers
 * @param {float} val - The value
 * @param {float} in_min - The minimum expected value
 * @param {float} in_max - The maximum expected value
 * @param {float} out_min - The minimum range value
 * @param {float} out_max - The maximum range value
 * @return {float}
**/
double mapf(float val, float in_min, float in_max, float out_min, float out_max) {
	return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
