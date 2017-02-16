/*
 * ColourPalletteData.c
 *
 *  Created on0xApr 12, 2015
 *      Author0xPaul
 */

// see --http://www.rapidtables.com/web/color/RGB_Color.htm for example colours
//
// Constants for each pallette number using the name for the colour can be found in the header file "Colours.h"
//
// this data represents the 24 bit RGB values of 256 colours. DE2 can display all 256 simultaneously, but DE1 can only display 64 at any one time.
// It should be setup in hardware in a ROM file in Quartus
// but the software ('C' code) version of the data is also given below and can be used as a reference to the original data in graphics chip ROM
//
// You should program the colour pallette (DE2 = 256, DE1 = 64) at the start, i.e in main() by calling ProgramPallette(BLACK, ColourPalletteData[0])
// for each colour and programming the colour(s) you want, 1 RGB value per pallette. BLACK is enumerated as 0 in Colours.h header file
//
// You should include this as part of the project so it gets compiled, but if you want to reference it in multiple source file
// you should put an "extern" declaration in those source files e.g. extern const unsigned int ColourPalletteData[256]
const unsigned int ColourPalletteData[256] = {
	0x00000000, // 0 - BLACK
	0x00000055,
	0x000000aa,
	0x000000ff,
	0x00002400,
	0x00002455,
	0x000024aa,
	0x000024ff,
	0x00004800,
	0x00004855,
	0x000048aa, // 10
	0x000048ff,
	0x00006c00,
	0x00006c55, // DARK SEA GREEN
	0x00006caa,
	0x00006cff,
	0x00009000,
	0x00009055,
	0x000090aa,
	0x000090ff,
	0x0000b400, // 20
	0x0000b455,
	0x0000b4aa,
	0x0000b4ff,
	0x0000d800,
	0x0000d855,
	0x0000d8aa,
	0x0000d8ff,
	0x0000fc00,
	0x0000fc55,
	0x0000fcaa, // 30
	0x0000fcff,
	0x00240000,
	0x00240055,
	0x002400aa,
	0x002400ff,
	0x00242400,
	0x00242455,
	0x002424aa, // MIDNIGHT BLUE
	0x002424ff,
	0x00244800, // 40
	0x00244855,
	0x002448aa,
	0x002448ff,
	0x00246c00,
	0x00246c55,
	0x00246caa,
	0x00246cff,
	0x00249000,
	0x00249055,
	0x002490aa, // 50
	0x002490ff,
	0x0024b400,
	0x0024b455,
	0x0024b4aa,
	0x0024b4ff,
	0x0024d800,
	0x0024d855,
	0x0024d8aa,
	0x0024d8ff,
	0x0024fc00, // 60
	0x0024fc55,
	0x0024fcaa,
	0x0024fcff,
	0x00480000, // TEAL
	0x00480055,
	0x004800aa,
	0x004800ff,
	0x00482400,
	0x00482455,
	0x004824aa, // 70
	0x004824ff,
	0x00484800,
	0x00484855,
	0x004848aa,
	0x004848ff,
	0x00486c00,
	0x00486c55,
	0x00486caa,
	0x00486cff,
	0x00489000, // 80
	0x00489055,
	0x004890aa,
	0x004890ff,
	0x0048b400, // FOREST GREEN
	0x0048b455,
	0x0048b4aa,
	0x0048b4ff,
	0x0048d800,
	0x0048d855,
	0x0048d8aa, // 90
	0x0048d8ff,
	0x0048fc00,
	0x0048fc55,
	0x0048fcaa,
	0x0048fcff,
	0x006c0000,
	0x006c0055,
	0x006c00aa,
	0x006c00ff,
	0x006c2400, // 100 - BROWN
	0x006c2455,
	0x006c24aa,
	0x006c24ff,
	0x006c4800,
	0x006c4855,
	0x006c48aa,
	0x006c48ff,
	0x006c6c00,
	0x006c6c55,
	0x006c6caa, // 110
	0x006c6cff,
	0x006c9000,
	0x006c9055,
	0x006c90aa,
	0x006c90ff,
	0x006cb400,
	0x006cb455,
	0x006cb4aa,
	0x006cb4ff,
	0x006cd800, // 120
	0x006cd855,
	0x006cd8aa,
	0x006cd8ff,
	0x006cfc00,
	0x006cfc55,
	0x006cfcaa,
	0x006cfcff,
	0x00900000,
	0x00900055,
	0x009000aa, // 130
	0x009000ff,
	0x00902400, // MAROON
	0x00902455,
	0x009024aa,
	0x009024ff,
	0x00904800,
	0x00904855,
	0x009048aa,
	0x009048ff,
	0x00906c00, // 140
	0x00906c55,
	0x00906caa,
	0x00906cff,
	0x00909000,
	0x00909055,
	0x009090aa,
	0x009090ff,
	0x0090b400,
	0x0090b455,
	0x0090b4aa, // 150
	0x0090b4ff,
	0x0090d800,
	0x0090d855,
	0x0090d8aa,
	0x0090d8ff,
	0x0090fc00,
	0x0090fc55,
	0x0090fcaa,
	0x0090fcff,
	0x00b40000, // 160
	0x00b40055,
	0x00b400aa,
	0x00b400ff,
	0x00b42400,
	0x00b42455,
	0x00b424aa,
	0x00b424ff,
	0x00b44800,
	0x00b44855,
	0x00b448aa, // 170
	0x00b448ff,
	0x00b46c00,
	0x00b46c55,
	0x00b46caa,
	0x00b46cff,
	0x00b49000,
	0x00b49055,
	0x00b490aa,
	0x00b490ff,
	0x00b4b400, // 180
	0x00b4b455,
	0x00b4b4aa,
	0x00b4b4ff,
	0x00b4d800,
	0x00b4d855,
	0x00b4d8aa,
	0x00b4d8ff,
	0x00b4fc00,
	0x00b4fc55,
	0x00b4fcaa, // 190
	0x00b4fcff,
	0x00d80000,
	0x00d80055,
	0x00d800aa,
	0x00d800ff,
	0x00d82400, // MEDIUM VIOLET RED
	0x00d82455,
	0x00d824aa,
	0x00d824ff,
	0x00d84800, // 200
	0x00d84855,
	0x00d848aa,
	0x00d848ff,
	0x00d86c00,
	0x00d86c55,
	0x00d86caa,
	0x00d86cff,
	0x00d89000,
	0x00d89055,
	0x00d890aa, // 210
	0x00d890ff,
	0x00d8b400,
	0x00d8b455,
	0x00d8b4aa,
	0x00d8b4ff,
	0x00d8d800,
	0x00d8d855,
	0x00d8d8aa,
	0x00d8d8ff,
	0x00d8fc00, // 220
	0x00d8fc55,
	0x00d8fcaa,
	0x00d8fcff,
	0x00fc0000,
	0x00fc0055,
	0x00fc00aa,
	0x00fc00ff,
	0x00fc2400, // RED
	0x00fc2455,
	0x00fc24aa, // 230
	0x00fc24ff,
	0x00fc4800,
	0x00fc4855,
	0x00fc48aa,
	0x00fc48ff,
	0x00fc6c00,
	0x00fc6c55,
	0x00fc6caa,
	0x00fc6cff,
	0x00fc9000, // 240
	0x00fc9055, // PINK
	0x00fc90aa,
	0x00fc90ff,
	0x00fcb400,
	0x00fcb455,
	0x00fcb4aa,
	0x00fcb4ff,
	0x00fcd800,
	0x00fcd855,
	0x00fcd8aa, // 250
	0x00fcd8ff,
	0x00fcfc00,
	0x00fcfc55,
	0x00fcfcaa,
	0x00fcfcff, // WHITE
};

/*
const unsigned int ColourPalletteData[256] = {
0x00000000, // Black
0x00FFFFFF, // White
0x00FF0000, // Red
0x0000FF00, // Green/Lime
0x000000FF, // Blue
0x00FFFF00, // Yellow
0x0000FFFF, // Cyan
0x00FF00FF, // Magenta
0x00C0C0C0, // Silver
0x00808080, // Gray
0x00800000, // Maroon
0x00808000, // Olive
0x00008000, // DarkGreen
0x00800080, // Purple
0x00008080, // Teal
0x00000080, // Navy
0x008B0000, // Dark Red
0x00A52A2A, // Brown
0x00B22222, // FireBrick
0x00DC143C, // Crimson
0x00FF6347, // Tomato
0x00FF7F50, // Coral
0x00Cd5C5C, // Indian Red
0x00F08080, // Light Coral
0x00E9967A, // Dark Salmon
0x00FA8072, // Salmon
0x00FFA07A, // Light Salmon
0x00FF4500, // Orange Red
0x00FF8C00, // Dark Orange
0x00FFA500, // Orange
0x00FFD700, // Gold
0x00B8860B, // Dark Golden Rod
0x00DAA520, // Golden Rod
0x00EEE8AA, // Pale Golden Rod
0x00BDB76B, // Dark Kharki
0x00F0E68C, // Khaki
0x00808000, // Olive
0x00FFFF00, // Yellow
0x009ACD32, // Yellow Green
0x00556B2F, // Dark Olive Green
0x006B8E23, // Olive Drab
0x007CFC00, // Lawn Green
0x007FFF00, // Chart Reuse
0x00ADFF2F, // Green Yellow
0x00006400, // Dark Green
0x00008000, // Green
0x00228B22, // Forest Green
0x0000FF00, // Green/Lime
0x0032CD32, // Lime Green
0x0090EE90, // Light Green
0x0098FB98, // Pale Green
0x008FBC8F, // Dark See Green
0x0000FA9A, // Medium Spring Green
0x0000FF7F, // Spring Green
0x002E8B57, // Sea Green
0x0066CDAA, // Medium Aqua Marine
0x003CB371, // Medium Sea Green
0x0020B2AA, // Light Sea Green
0x002F4F4F, // Dark Slate Gray
0x00008080, // Teal
0x00008B8B, // Dark Cyan
0x0000FFFF, // Aqua/Cyan
0x00E0FFFF, // Light Cyan
0x0000CED1, // Dark Turquise
0x0040E0D0, // Turquoise
0x0048D1CC, // Medium Turquoise
0x00AFEEEE, // Pale Turquoise
0x007FFFD4, // Aqua Marine
0x00B0E0E6, // Powder Blue
0x005F9EA0, // Cadet Blue
0x004682B4, // Steel Blue
0x006495ED, // Corn Flower Blue
0x0000BFFF, // Deep Sky Blue
0x001E90FF, // Dodger Blue
0x00ADD8E6, // Light Blue
0x0087CEEB, // Sky Blue
0x0087CEFA, // Light Sky Blue
0x00191970, // Midnight Blue
0x00000080, // Navy
0x0000008B, // Bark Blue
0x000000CD, // Medium Blue
0x000000FF, // Blue
0x004169E1, // Royal Blue
0x008A2BE2, // Blue Violet
0x004B0082, // Indigo
0x00483D8B, // Dark Slate Blue
0x006A5ACD, // Slate Blue
0x007B68EE, // Medium Slate Blue
0x009370DB, // Medium Purple
0x008B008B, // Dark Magenta
0x009400D3, // Dark Violet
0x009932CC, // Dark Orchid"
0x00BA55D3, // Medium Orchid
0x00800080, // Purple
0x00D8BFD8, // Thistle
0x00DDA0DD, // Plum
0x00EE82EE, // Violet
0x00FF00FF, // Magenta/Fuchia
0x00DA70D6, // Orchid
0x00C71585, // Medium Violet Red
0x00DB7093, // Pale Violet Red
0x00FF1493, // Deep Pink
0x00FF69B4, // Hot Pink
0x00ffB6C1, // Light Pink
0x00FFC0CB, // Pink
0x00FAEBD7, // Antique White
0x00F5F5DC, // Beige
0x00FFE4C4, // Bisque
0x00FFEBCD, // Blanched Almond
0x00F5DEB3, // Wheat
0x00FFF8DC, // Corn Silk
0x00FFFACD, // Lemon Chiffon
0x00FAFAD2, // Light Golden Rod Yellow
0x00FFFFE0, // Light Yellow
0x008B4513, // Saddle Brown
0x00A0522D, // Sienna
0x00D2691E, // Chocolate
0x00CD853F, // Peru
0x00F4A460, // Sandy Brown
0x00DEB887, // Burley Wood
0x00D2B48C, // Tan
0x00BC8F8F, // Rosy Tan
0x00FFE4B5, // Moccasin
0x00FFDEAD, // Navajo White
0x00FFDAB9, // Peach Puff
0x00FFE4E1, // Misty Rose
0x00FFF0F5, // Lavendar Blush
0x00FAF0E6, // Linen
0x00FDF5E6, // Old Lace
0x00FFEFD5, // Papaya Whip
0x00FFF5EE, // Sea Shell
0x00F5FFFA, // Mint Cream
0x00708090, // Slate Gray
0x00778899, // Light Slate Gray
0x00B0C4DE, // Light Steel Blue
0x00E6E6FA, // Lavender
0x00FFFAF0, // Floral White
0x00F0F8FF, // Alice Blue
0x00F8F8FF, // Ghost White
0x00F0FFF0, // Honey Dew
0x00FFFFF0, // Ivory
0x00F0FFFF, // Azure
0x00FFFAFA, // Snow
0x00000000, // Black
0x00696969, // Dim Gray
0x00808080, // Gray
0x00A9A9A9, // Dark Gray
0x00D3D3D3, // Light Gray
0x00DCDCDC, // GainsBoro
0x00F5F5F5, // White Smoke
0x00FFFFFF, // White

// Repeating colour - change these if you like
0x00000000, // Black
0x00FFFFFF, // White
0x00FF0000, // Red
0x0000FF00, // Green/Lime
0x000000FF, // Blue
0x00FFFF00, // Yellow
0x0000FFFF, // Cyan
0x00FF00FF, // Magenta
0x00C0C0C0, // Silver
0x00808080, // Gray
0x00800000, // Maroon
0x00808000, // Olive
0x00008000, // DarkGreen
0x00800080, // Purple
0x00008080, // Teal
0x00000080, // Navy
0x008B0000, // Dark Red
0x00A52A2A, // Brown
0x00B22222, // FireBrick
0x00DC143C, // Crimson
0x00FF6347, // Tomato
0x00FF7F50, // Coral
0x00Cd5C5C, // Indian Red
0x00F08080, // Light Coral
0x00E9967A, // Dark Salmon
0x00FA8072, // Salmon
0x00FFA07A, // Light Salmon
0x00FF4500, // Orange Red
0x00FF8C00, // Dark Orange
0x00FFA500, // Orange
0x00FFD700, // Gold
0x00B8860B, // Dark Golden Rod
0x00DAA520, // Golden Rod
0x00EEE8AA, // Pale Golden Rod
0x00BDB76B, // Dark Kharki
0x00F0E68C, // Khaki
0x00808000, // Olive
0x00FFFF00, // Yellow
0x009ACD32, // Yellow Green
0x00556B2F, // Dark Olive Green
0x006B8E23, // Olive Drab
0x007CFC00, // Lawn Green
0x007FFF00, // Chart Reuse
0x00ADFF2F, // Green Yellow
0x00006400, // Dark Green
0x00008000, // Green
0x00228B22, // Forest Green
0x0000FF00, // Green/Lime
0x0032CD32, // Lime Green
0x0090EE90, // Light Green
0x0098FB98, // Pale Green
0x008FBC8F, // Dark See Green
0x0000FA9A, // Medium Spring Green
0x0000FF7F, // Spring Green
0x002E8B57, // Sea Green
0x0066CDAA, // Medium Aqua Marine
0x003CB371, // Medium Sea Green
0x0020B2AA, // Light Sea Green
0x002F4F4F, // Dark Slate Gray
0x00008080, // Teal
0x00008B8B, // Dark Cyan
0x0000FFFF, // Aqua/Cyan
0x00E0FFFF, // Light Cyan
0x0000CED1, // Dark Turquise
0x0040E0D0, // Turquoise
0x0048D1CC, // Medium Turquoise
0x00AFEEEE, // Pale Turquoise
0x007FFFD4, // Aqua Marine
0x00B0E0E6, // Powder Blue
0x005F9EA0, // Cadet Blue
0x004682B4, // Steel Blue
0x006495ED, // Corn Flower Blue
0x0000BFFF, // Deep Sky Blue
0x001E90FF, // Dodger Blue
0x00ADD8E6, // Light Blue
0x0087CEEB, // Sky Blue
0x0087CEFA, // Light Sky Blue
0x00191970, // Midnight Blue
0x00000080, // Navy
0x0000008B, // Bark Blue
0x000000CD, // Medium Blue
0x000000FF, // Blue
0x004169E1, // Royal Blue
0x008A2BE2, // Blue Violet
0x004B0082, // Indigo
0x00483D8B, // Dark Slate Blue
0x006A5ACD, // Slate Blue
0x007B68EE, // Medium Slate Blue
0x009370DB, // Medium Purple
0x008B008B, // Dark Magenta
0x009400D3, // Dark Violet
0x009932CC, // Dark Orchid
0x00BA55D3, // Medium Orchid
0x00800080, // Purple
0x00D8BFD8, // Thistle
0x00DDA0DD, // Plum
0x00EE82EE, // Violet
0x00FF00FF, // Magenta/Fuchia
0x00DA70D6, // Orchid
0x00C71585, // Medium Violet Red
0x00DB7093, // Pale Violet Red
0x00FF1493, // Deep Pink
0x00FF69B4, // Hot Pink
0x00ffB6C1, // Light Pink
0x00FFC0CB // Pink
};

*/
