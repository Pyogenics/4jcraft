#pragma once

#include "../Util/ArrayWithLength.h"

class BlockGenMethods
{
public:
	static void generateBox(Level *level, byteArray blocks, int sx, int sy, int sz, int ex, int ey, int ez, uint8_t edge, uint8_t filling);
	static void generateFrame(Level *level, byteArray blocks, int sx, int sy, int ex, int ey, int flatZ, int direction, uint8_t edge, uint8_t filling);
	static void generateDirectionLine(Level *level, byteArray blocks, int sx, int sy, int sz, int ex, int ey, int ez, int startDirection, int endDirection, uint8_t block);
	static void generateLine(Level *level, byteArray blocks, int sx, int sy, int sz, int ex, int ey, int ez, uint8_t block);
};