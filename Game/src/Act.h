#pragma once

#include "../assets/nlohmann/json/json.hpp"
#include "Alexio/Engine.h"

nlohmann::json Parse(const std::string& jsonFile);

struct Collider
{
	int x;
	int y;
	int width;
	int height;
};

enum class TileSolidity
{
	NONE = -1,
	GROUD_ONLY = 0,
	SIDE_AND_CEILING = 1,
	FULLY_SOLID = 2
};

struct Tile
{
public:
	Tile();
	Tile(unsigned int id);

	inline bool IsSolid() { return colliders.size() != 0; }
	inline bool IsFullBlock() { return colliders.size() == 1; }
public:
	unsigned int ID;
	float angle;
	TileSolidity solidity;
	std::vector<Collider> colliders;
};

struct TileSet
{
public:
	TileSet();
	TileSet(const std::string& jsonFile);

	std::vector<Tile>::iterator begin() { return mTiles.begin(); }
	std::vector<Tile>::iterator end() { return mTiles.end(); }

	std::vector<Tile>::const_iterator begin() const { return mTiles.begin(); }
	std::vector<Tile>::const_iterator end() const { return mTiles.end(); }

private:
	nlohmann::json mJson;
	std::vector<Tile> mTiles;
};

class Act
{
public:
	Act();

	void Load(const std::string& name, const std::string& tileSet);

	Tile* GetTile(unsigned int mapIndex);
	Tile* GetTile(const Alexio::Vector2i& pos);

	unsigned int GetTileID(unsigned int mapIndex);
	unsigned int GetTileID(const Alexio::Vector2i& pos);

	void Draw();
public:
	Alexio::Vector2i screenSize;

	bool tileHorizontalFlip;
	bool tileVerticalFlip;
private:
	int mWidth;
	int mHeight;
	std::vector<unsigned int> mTileIDs;

	Alexio::Ref<Alexio::Texture> mGFX;

	TileSet mTileSet;
	nlohmann::json mJson;
};