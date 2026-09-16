
#ifndef rotation_control_h
#define rotation_control_h

// --- Public configuration ----------------------------------------------------
// Put user‑tunable parameters here so callers can see/adjust them at compile time.
// (Match your .c values; you can keep them here to avoid duplication)

// #ifndef ROT_STEPS_PER_DEGREE
// // Example: 400 steps per full revolution / 360 degrees
// #define ROT_STEPS_PER_DEGREE  (400.0f / 360.0f)
// #endif

// #ifndef ROT_MAX_SPEED_DELAY
// // Base delay (microseconds) used in your stepping loop; lower is faster.
// #define ROT_MAX_SPEED_DELAY   800
// #endif

// #ifndef ROT_ACCEL_STEPS
// // Number of steps to ramp up/down the delay for simple accel/decel.
// #define ROT_ACCEL_STEPS       50
// #endif

// --- Public API --------------------------------------------------------------
// Initialize rotation driver GPIO (DIR and STEP pins low, configured as outputs).
void rotation_init(void);

// Move to an absolute angle in degrees (blocking).
// Positive angles rotate in the DIR=HIGH direction per your hardware wiring; negative the opposite.
void rotate_to_angle(float angle);

// --- Notes -------------------------------------------------------------------
// • This module expects the following macros to be defined (usually via grbl.h or a board config):
//     ROT_STEP_DDR, ROT_STEP_PORT, ROT_STEP_BIT
//     ROT_DIR_DDR,  ROT_DIR_PORT,  ROT_DIR_BIT
//   They should map to the AVR (or Arduino) registers/bits for your STEP and DIR pins.
// • It also expects a microsecond delay function: delay_us(unsigned int us).
//   If your environment only has Arduino's delayMicroseconds(), you can provide a wrapper:
//
//   static inline void delay_us(unsigned int us) { delayMicroseconds(us); }
//
// • Do NOT include this header inside the .c file more than once; the guard prevents that.
//   And never #include a .c file from any header.

// -----------------------------------------------------------------------------

#endif // rotation_control_h