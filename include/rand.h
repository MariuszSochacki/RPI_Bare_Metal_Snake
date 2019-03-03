#ifndef RAND_H
#define RAND_H

/** Initializes the random number generator of RPI
 */
void rand_init();

/** Returns a random number in a given range
 * @param min Start of the range
 * @param min End of the range
 * @return Random number in a given range
 */
unsigned int rand(unsigned int min, unsigned int max);

#endif  // RAND_H