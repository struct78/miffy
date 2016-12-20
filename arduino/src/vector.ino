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
