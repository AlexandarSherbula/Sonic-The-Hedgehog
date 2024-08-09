#include "Act.h"

#include <fstream>
#include <iostream>

nlohmann::json Parse(const std::string& jsonFile)
{
    std::ifstream fstream(jsonFile);
    std::string jsonData((std::istreambuf_iterator<char>(fstream)), std::istreambuf_iterator<char>());

    nlohmann::json json = nlohmann::json::parse(jsonData);

    return json;
}

Tile::Tile()
{
    ID = 0;
    angle = 0.0f;
    solidity = TileSolidity::NONE;
}

Tile::Tile(unsigned int id)
{
    ID = id;
    angle = 0.0f;
    solidity = TileSolidity::NONE;
}

TileSet::TileSet()
{

}

TileSet::TileSet(const std::string& jsonFile)
{
    mJson = Parse(jsonFile);

    mTiles.reserve(mJson["tiles"].size());
    for (int i = 0; i < mJson["tiles"].size(); i++)
    {
        int id = mJson["tiles"][i]["id"];
        mTiles.emplace_back(id);

        if (mJson["tiles"][i].contains("properties"))
        {
            int propertiesObjSize = mJson["tiles"][i]["properties"].size();

            for (int j = 0; j < propertiesObjSize; j++)
            {
                if (mJson["tiles"][i]["properties"][j]["name"] == "TileSolidity")
                {
                    mTiles[i].solidity = mJson["tiles"][i]["properties"][j]["value"];
                }
            }
        }

        int objectSize = mJson["tiles"][i]["objectgroup"]["objects"].size();
        for (int j = 0; j < objectSize; j++)
        {
            float colX = mJson["tiles"][i]["objectgroup"]["objects"][j]["x"];
            float colY = mJson["tiles"][i]["objectgroup"]["objects"][j]["y"];
            int mWidth = mJson["tiles"][i]["objectgroup"]["objects"][j]["width"];
            int mHeight = mJson["tiles"][i]["objectgroup"]["objects"][j]["height"];

            float colXFract = colX - (int)colX;
            float colYFract = colY - (int)colY;

            if (colXFract > 0.7f) colX = (int)colX + 1;
            if (colYFract > 0.7) colY = (int)colY + 1;

            mTiles[i].colliders.push_back({
                (int)colX,
                (int)colY,
                mWidth,
                mHeight
                });

        }
    }
}

Act::Act()
{
    mWidth = 0;
    mHeight = 0;
    mTileSet = TileSet();
}

void Act::Load(const std::string& name, const std::string& tileSet)
{
    mGFX = Alexio::Texture::Create("assets/images/" + name + ".png");
    mTileSet = TileSet("assets/json/" + tileSet + ".json");

    mJson = Parse("assets/json/" + name + ".json");

    AIO_ASSERT(!mJson["infinite"], "You forgot to turn off infinite mode in Tiled");

    mWidth = mJson["width"];
    mHeight = mJson["height"];

    screenSize = { mWidth * 16, mHeight * 16 };

    mTileIDs.reserve(mWidth * mHeight);

    for (int i = 0; i < mWidth * mHeight; i++)
        mTileIDs.push_back(mJson["layers"][0]["data"][i]);
}

Tile* Act::GetTile(unsigned int mapIndex)
{
    int tileID = (mapIndex >= 0 && mapIndex < mTileIDs.size()) ? mTileIDs[mapIndex] : -1;

    if (tileID == -1)
    {
        std::cerr << "Index is out of range" << std::endl;
        __debugbreak();
    }
    else if (tileID > 0)
    {
        for (Tile& tile : mTileSet)
        {
            if (tileID == tile.ID)
                return &tile;
        }
    }

    return nullptr;
}

Tile* Act::GetTile(const Alexio::Vector2i& pos)
{
    int64_t tileID = (pos.x / 16 >= 0 && pos.x / 16 < mWidth && pos.y / 16 >= 0 && pos.y / 16 < mHeight) ? mTileIDs[(pos.y / 16) * mWidth + (pos.x / 16)] : -1;

    const uint32_t horizontalFlag = 0x80000000;
    const uint32_t verticalFlag = 0x40000000;
    const uint32_t diagonalFlag = 0x20000000;
    const uint32_t rotatedHexagonal120Flag = 0x10000000;

    tileHorizontalFlip = tileID & horizontalFlag;
    tileVerticalFlip = tileID & verticalFlag;

    tileID &= ~(horizontalFlag | verticalFlag | diagonalFlag | rotatedHexagonal120Flag);

    if (tileID == -1)
    {
        std::cerr << "Position is out of range" << std::endl;
        __debugbreak();
    }

    if (tileID > 0)
    {
        for (Tile& tile : mTileSet)
        {
            if (tileID - 1 == tile.ID)
                return &tile;
        }
    }

    return nullptr;
}

unsigned int Act::GetTileID(unsigned int mapIndex)
{
    if (mapIndex >= 0 && mapIndex < mTileIDs.size())
        return mTileIDs[mapIndex];

    AIO_ASSERT(false, "Index was out of range");
}

unsigned int Act::GetTileID(const Alexio::Vector2i& pos)
{
    if (pos.x >= 0 && pos.x < mWidth &&
        pos.y >= 0 && pos.y < mHeight)
        return mTileIDs[pos.y * mWidth + pos.x];

    AIO_ASSERT(false, "Position was out of range");
}

void Act::Draw()
{
    Alexio::Renderer::DrawSprite(mGFX, { 0.0f, 0.0f });
}