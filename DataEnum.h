#pragma once
#include <cstdint>

enum Gamemode : uint8_t
{
	Survival = 0,
	Creative = 1,
	Adventure = 2,
	Spectator = 3,
	Hardcore = 8
};

enum Dimension : int
{
	Nether = -1,
	Overworld = 0,
	End = 1
};

enum Difficulty : uint8_t
{
	Peaceful = 0,
	Easy = 1,
	Normal = 2,
	Hard = 3
};