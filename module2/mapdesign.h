/*
 * mapdesign.h
 *
 *  Created on: 2017-03-12
 *      Author: ahboo
 */

/*
 * Each character represents a 50px by 50px square in the screen.
 */

// Map Dimensions
#define MAX_AREAS 3
#define MAX_HORI_SQUARES 16
#define MAX_VERT_SQUARES 8
#define SQUARE_WIDTH 50
#define SQUARE_HEIGHT 50

// Character definitions
#define WALL 35					// 35 = #
#define SPACE 79				// 79 = O
#define FINISH 36				// 36 = $
#define ENEMY 88				// 88 = X
#define PLAYER 80				// 80 = P

// Player's current position in terms of the character map below. For example, these two values would initialize to
// 1 and 7 respectively (according to the position of 'P' in map[0].
int player_current_x_pos;
int player_current_y_pos;

static int startPos [MAX_AREAS][2] =
{
		{ 1, 7 },
		{ 1, 7 },
		{ 1, 7 }
};

#ifdef  MAIN_FILE
char map [MAX_AREAS][MAX_VERT_SQUARES][MAX_HORI_SQUARES] =
{
		{
				{'#','#','#','#','#','#','#','#','#','#','#','O','O','O','O','$'},
				{'#','#','#','#','#','#','#','O','O','X','#','O','O','O','O','O'},
				{'#','O','#','#','O','O','#','O','#','O','#','O','#','#','#','#'},
				{'#','O','#','#','O','O','O','O','#','O','#','O','O','O','#','#'},
				{'#','O','#','#','O','#','#','#','#','O','O','O','O','O','#','X'},
				{'#','X','#','#','O','#','#','#','#','O','#','#','#','O','#','O'},
				{'#','O','O','O','O','#','#','#','#','O','#','#','#','X','#','O'},
				{'#','O','#','#','#','#','O','O','O','O','#','#','#','O','O','O'}
		},
		{
				{'#','#','#','#','#','#','#','#','#','#','#','O','O','O','O','$'},
				{'#','#','#','#','#','#','#','O','O','X','#','O','O','O','O','O'},
				{'#','O','#','#','O','O','#','O','#','O','#','O','#','#','#','#'},
				{'#','O','#','#','O','O','O','O','#','O','#','O','O','O','#','#'},
				{'#','O','#','#','O','#','#','#','#','O','O','O','O','O','#','X'},
				{'#','O','#','#','O','#','#','#','#','O','#','#','#','O','#','$'},
				{'#','O','O','O','O','#','#','#','#','O','#','#','#','X','#','$'},
				{'#','O','#','#','#','#','O','O','O','O','#','#','#','O','O','$'}
		},
		{
				{'#','#','#','#','#','#','#','#','#','#','#','O','O','O','O','$'},
				{'#','#','#','#','#','#','#','O','O','X','#','O','O','O','O','O'},
				{'#','O','#','#','O','O','#','O','#','O','#','O','#','#','#','#'},
				{'#','O','#','#','O','O','O','O','#','O','#','O','O','O','#','#'},
				{'#','O','#','#','O','#','#','#','#','O','O','O','O','O','#','X'},
				{'#','O','#','#','O','#','#','#','#','O','#','#','#','O','#','$'},
				{'#','O','O','O','O','#','#','#','#','O','#','#','#','X','#','$'},
				{'#','O','#','#','#','#','O','O','O','O','#','#','#','O','O','$'}
		}
};
#else
extern char map [MAX_AREAS][MAX_VERT_SQUARES][MAX_HORI_SQUARES];
#endif
