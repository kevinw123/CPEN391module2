#include <stdio.h>
#include "minunit.h"
#include "graphics.h"
#include "Colours.h"
#include "Gps.h"

int tests_run = 0;

/*
 * Test that deg2rad() converts a degree to a radian correctly
 */
static char * test_deg2rad() {
	double degree = 50.0;
	double radians = degree * pi / 180;
	mu_assert("Incorrect conversion from degree to radians", deg2rad(degree) == radians);
    return 0;
}

/*
 * Test that rad2grad() converts a radian to a degree correctly
 */
static char * test_rad2deg() {
	double radians = 5.0;
	double degrees = radians * 180 / pi;
	mu_assert("Incorrect conversion from radians to degrees", rad2deg(radians) == degrees);
    return 0;
}

/*
 * Tests that getAverageSpeed() returns the correct average speed of the session
 */
static char * test_getAverageSpeed() {
	distance_int = 100;
	time_elapsed_seconds = 50;
	getAverageSpeed();

	mu_assert("Incorrect average speed string", strcmp("2 M/S", speed));
    return 0;
}

/*
 * Tests that getDistanceAndSpeed() returns 0 M and 0 M/S before a session starts
 */
static char * test_getDistanceAndSpeedBeforeSessionStarts() {
	previous_latitude_float = 49.262477;
	previous_longitude_float = -123.250759;
	latitude_float = 49.261933;
	longitude_float = -123.250289;

	extracted_first_log = 0;
	session_started = 0;
	getDistanceAndSpeed();
	mu_assert("Distance should be 0 M before starting session", strcmp("0 M", distance) == 0);
	mu_assert("Speed should be 0 M/S before starting session", strcmp("0 M/S", speed) == 0);

    return 0;
}

/*
 * Tests that getDistanceAndSpeed() adds the distance of the last two logged points to the previously accumulated distance
 */
static char * test_getDistanceAndSpeedAfterSessionStarts() {
	previous_latitude_float = 49.262477;
	previous_longitude_float = -123.250759;
	latitude_float = 49.261933;
	longitude_float = -123.250289;
	distance_int = 10;

	extracted_first_log = 1;
	session_started = 1;

	getDistanceAndSpeed();
	mu_assert("Distance should be greater than 10 M after starting session", strcmp("10 M", distance) < 0);
	mu_assert("Speed should be 0 M/S after starting session", strcmp("0 M/S", speed) < 0);

    return 0;
}

/*
 * Tests that validPointOnScreen() returns 1 given a point within screen bounds
 */
static char * test_validPoint() {
    mu_assert("(2, 477) should be a valid point", validPointOnScreen(2, 477) == 1);
    return 0;
}

/*
 * Tests that validPointOnScreen() returns 0 given a point outside screen bounds
 */
static char * test_invalidPoint(){
	mu_assert("(-1, 477) should be an invalid point", validPointOnScreen(-1, 477) == 0);
	mu_assert("(0, 480) should be an invalid point", validPointOnScreen(0, 480) == 0);
	return 0;
}

/*
 * Run all minunit tests
 */
static char * all_tests() {
	mu_run_test(test_validPoint);
	mu_run_test(test_invalidPoint);
	mu_run_test(test_deg2rad);
	mu_run_test(test_rad2deg);
	mu_run_test(test_getAverageSpeed);
	mu_run_test(test_getDistanceAndSpeedBeforeSessionStarts);
	mu_run_test(test_getDistanceAndSpeedAfterSessionStarts);
    return 0;
}

/*
 * Manual tests to draw on the screen for lines, circle, and rectangle
 */
void TestDrawings() {
    // Tests drawing line from one edge of screen to another
    WriteHLine(0, 800, 10, RED);

    // Tests drawing line from middle of screen top to bottom
    WriteVLine(400, 0, 400, RED);

    // Tests drawing line from one corner to another
    WriteLine(0, 800, 0, 400, RED);

    // Draw circle at the middle of the screen with radius 10
    Circle(400, 240, 10, RED);

    // Draw rectangle on the top left of the screen
    Rectangle(0, 400, 0, 240, RED);
}


// Test main. Uncomment when running tests and comment out main in hello_world.c
/*
int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
*/
