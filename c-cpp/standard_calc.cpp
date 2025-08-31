#include "stdbool.h"
#include "standard_calc.h"
#include "math.h"

/**
 * @brief Bounds the provided angle between [-180, 180) degrees.
 *
 * e.g.)
 *      bound_to_180(135) = 135.0
 *      bound_to_180(200) = -160.0
 *
 * @param angle: The input angle in degrees.
 *
 * @return float: The bounded angle in degrees.
 */
float bound_to_180(float angle) {
    angle = fmod(angle, 360.0);
    if (angle >= 180.0) {
        return angle - 360.0;
    } else if (angle < -180.0) {
        return angle + 360.0;
    }
    return angle;
}


/**
 * @brief Normalizes an angle to the range [0, 360) degrees.
 *
 * @param angle: The input angle in degrees.
 *
 * @return float: The normalized angle in degrees.
 */
float normalize_angle(float angle) {
    angle = fmod(angle, 360.0);
    if (angle < 0.0) {
        angle += 360.0;
    }
    return angle;
}

/**
 * @brief Determines whether an angle is between two other angles
 *
 *  e.g.)
 *      is_angle_between(0, 45, 90) = true
 *      is_angle_between(45, 90, 270) = false
 * 
 * @param first_angle:  The first bounding angle in degrees.
 * @param middle_angle: The angle in question in degrees.
 * @param second_angle: The second bounding angle in degrees.
 * @return bool: TRUE when `middle_angle` is not in the reflex angle of `first_angle` and `second_angle`, FALSE otherwise
 */
bool is_angle_between(float first_angle, float middle_angle, float second_angle) {
    float norm_first = normalize_angle(first_angle);
    float norm_middle = normalize_angle(middle_angle);
    float norm_second = normalize_angle(second_angle);

    // distance between first and second angle
    float dist_first_second = fmod(norm_second - norm_first + 360.0, 360.0);

    if (dist_first_second <= 180.0) {
        // Minor arc is CCW from first to second
        float dist_first_middle = fmod(norm_middle - norm_first + 360.0, 360.0);
        return (dist_first_middle <= dist_first_second);
    } else {
        // Minor arc is CCW from second to first
        float minor_arc = 360 - dist_first_second;
        float dist_second_middle = fmod(norm_middle - norm_second + 360.0, 360.0);
        return (dist_second_middle <= minor_arc);
    }
}
