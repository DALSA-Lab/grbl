#include "grbl.h"


// // --- Motor + drive parameters ---
// #define MOTOR_STEPS_PER_REV    400  
// #define GEAR_RATIO            180.0      // worm gear 180:1 (stage : motor = 1:180)

// // Steps (microsteps) per STAGE degree:
// #define ROT_STEPS_PER_DEGREE  ((MOTOR_STEPS_PER_REV * GEAR_RATIO) / 360.0)

// Optional: derived resolution for sanity-check/logging
#define STAGE_RESOLUTION_DEG  (360.0 / (MOTOR_STEPS_PER_REV * MICROSTEPS_PER_STEP * GEAR_RATIO))



// Rotation parameters
#define ROT_STEPS_PER_DEGREE  ((400.0 * 180.0) / 360.0)
#define ROT_MAX_SPEED_DELAY   100
#define ROT_ACCEL_STEPS       50

void rotation_init()
{
    // Configure pins as outputs
    ROT_STEP_DDR |= (1 << ROT_STEP_BIT);
    ROT_DIR_DDR  |= (1 << ROT_DIR_BIT);

    // Set both low
    ROT_STEP_PORT &= ~(1 << ROT_STEP_BIT);
    ROT_DIR_PORT  &= ~(1 << ROT_DIR_BIT);
}


void rotate_to_angle(float angle)
{
    static float current_angle = 0.0;

    float delta = angle - current_angle;
    int direction = (delta >= 0) ? 1 : -1;
    long steps = labs((long)(delta * ROT_STEPS_PER_DEGREE));

    // Set direction
    if (direction > 0)
        ROT_DIR_PORT |=  (1 << ROT_DIR_BIT);
    else
        ROT_DIR_PORT &= ~(1 << ROT_DIR_BIT);

    int d = ROT_MAX_SPEED_DELAY * 2;

    for (long i = 0; i < steps; i++) {

        // Acceleration
        if (i < ROT_ACCEL_STEPS && d > ROT_MAX_SPEED_DELAY)
            d--;

        // Deceleration
        if (i > (steps - ROT_ACCEL_STEPS) && d < ROT_MAX_SPEED_DELAY * 2)
            d++;

        // Step HIGH
        ROT_STEP_PORT |= (1 << ROT_STEP_BIT);
        delay_us(d);

        // Step LOW
        ROT_STEP_PORT &= ~(1 << ROT_STEP_BIT);
        delay_us(d);
    }

    current_angle = angle;
}
