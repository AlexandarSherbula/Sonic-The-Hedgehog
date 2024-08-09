#include "Object.h"
#include "Game.h"

AnchorPoint::AnchorPoint(const Alexio::Vector2i& direction, TileSolidity tileChecker)
{
	this->direction = direction;
	this->tileChecker = tileChecker;
	position = { 0.0f, 0.0f };
	distance = 0.0f;
}

Object::Object()
{
	mHitbox.widthRad = 0;
	mHitbox.heightRad = 0;
}

Object::Object(const Alexio::Vector2& position, int widthRadius, int heightRadius, Direction direction, const std::string& gfxFilePath)
{
	this->position = position;
	mHitbox.widthRad = widthRadius;
	mHitbox.heightRad = heightRadius;

	mDirection = direction;

	mGFX = Alexio::Texture::Create(gfxFilePath);
}

void Object::Draw()
{
	Alexio::Renderer::DrawQuad({ position.x - mHitbox.widthRad, position.y - mHitbox.heightRad }, { 2 * mHitbox.widthRad + 1, 2 * mHitbox.heightRad + 1 },
		{1.0f, 0.0f, 1.0f, 0.5f});
	Alexio::Renderer::DrawQuad(Alexio::Vector2((position.x - 1), position.y), Alexio::Vector2(1, 1));
	Alexio::Renderer::DrawQuad(Alexio::Vector2((position.x + 1), position.y), Alexio::Vector2(1, 1));
	Alexio::Renderer::DrawQuad(Alexio::Vector2(position.x, position.y - 1), Alexio::Vector2(1, 1));
	Alexio::Renderer::DrawQuad(Alexio::Vector2(position.x, position.y + 1), Alexio::Vector2(1, 1));
}

MovingObject::MovingObject()
{
	mSpeed = { 0.0f, 0.0f };
	mGroundSpeed = 0.0f;
	mAirSpeed = 0.0f;
}

MovingObject::MovingObject(const Alexio::Vector2& position, int widthRad, int heightRad, Direction direction, const std::string& gfxFilePath)
	: Object(position, widthRad, heightRad, direction, gfxFilePath)
{
	mSpeed = { 0.0f, 0.0f };
	mGroundSpeed = 0.0f;
	mAirSpeed = 0.0f;
}

void MovingObject::FindSurface(AnchorPoint& point)
{
	if (point.direction.x != 0 || point.direction.y != 0)
	{
		bool search = true;

		Alexio::Vector2 searchPoint = point.position;
		point.distance = 0.0f;

		while (search)
		{
			game.currentAct->tileHorizontalFlip = false;
			game.currentAct->tileVerticalFlip = false;
			Tile* tile = game.currentAct->GetTile(searchPoint);
			if (tile != nullptr && tile->IsSolid() && (point.tileChecker == tile->solidity || tile->solidity == TileSolidity::FULLY_SOLID))
			{
				Alexio::Vector2i tilePosition;
				tilePosition.x = ((int)searchPoint.x / 16) * 16;
				tilePosition.y = ((int)searchPoint.y / 16) * 16;

				if (!tile->IsFullBlock())
				{
					int colliderIndex;
					float startPoint;
					int tilePosOffset;

					const Collider& firstCollider = tile->colliders[0];
					const Collider& lastCollider = tile->colliders[tile->colliders.size() - 1];

					if (point.direction.y != 0)
					{
						int colliderHeight;
						bool isEmptyOnLeft = firstCollider.x != 0;
						bool isEmptyOnRight = lastCollider.x + lastCollider.width < 16.0f;

						if (game.currentAct->tileHorizontalFlip)
							tilePosOffset = (tilePosition.x + 15.0f) - searchPoint.x;
						else
							tilePosOffset = searchPoint.x - tilePosition.x;

						if (isEmptyOnLeft || isEmptyOnRight)
						{
							if (tilePosOffset < firstCollider.x || tilePosOffset >= lastCollider.x + lastCollider.width)
							{
								colliderHeight = 0;
							}
							else
							{
								if (isEmptyOnLeft)
									colliderIndex = tilePosOffset - firstCollider.x;
								else
									colliderIndex = (tilePosOffset * tile->colliders.size()) / (lastCollider.x + lastCollider.width);

								colliderHeight = tile->colliders[colliderIndex].height * point.direction.y;
							}
						}
						else
						{
							colliderIndex = (tilePosOffset * tile->colliders.size()) / 16;
							colliderHeight = tile->colliders[colliderIndex].height * point.direction.y;
						}

						startPoint = (point.direction.y == 1) ? 15.0f : 0.0f;

						searchPoint.y = tilePosition.y + startPoint - colliderHeight;
						point.distance = searchPoint.y - point.position.y;
					}
					else if (point.direction.x != 0)
					{
						int colliderWidth;
						bool isEmptyOnTop = firstCollider.y != 0;
						bool isEmptyOnBottom = lastCollider.y + lastCollider.height < 16.0f;

						if (game.currentAct->tileVerticalFlip)
							tilePosOffset = (tilePosition.y + 15.0f) - searchPoint.y;
						else
							tilePosOffset = searchPoint.y - tilePosition.y;

						if (isEmptyOnTop || isEmptyOnBottom)
						{
							if (tilePosOffset < firstCollider.y || tilePosOffset >= lastCollider.y + lastCollider.height)
							{
								colliderWidth = 0;
							}
							else
							{
								if (isEmptyOnTop)
									colliderIndex = tilePosOffset - firstCollider.y;
								else
									colliderIndex = (tilePosOffset * tile->colliders.size()) / (lastCollider.y + lastCollider.height);

								colliderWidth = tile->colliders[colliderIndex].width * point.direction.x;
							}
						}
						else
						{
							colliderIndex = (tilePosOffset * tile->colliders.size()) / 16;
							colliderWidth = tile->colliders[colliderIndex].width * point.direction.x;
						}

						startPoint = (point.direction.x == 1) ? 15.0f : 0.0f;

						searchPoint.x = tilePosition.x + startPoint - colliderWidth;
						point.distance = searchPoint.x - point.position.x;
					}

					search = false;
				}
				else
				{
					if (point.direction.y != 0)
					{
						if (point.direction.y == 1)
							searchPoint.y = tilePosition.y - 1.0f;
						else
							searchPoint.y = tilePosition.y + 16.0f;

						if (point.distance != 0.0f)
							search = false;
						point.distance = searchPoint.y - point.position.y;
					}
					else if (point.direction.x != 0)
					{
						if (point.direction.x == 1)
							searchPoint.x = tilePosition.x - 1.0f;
						else
							searchPoint.x = tilePosition.x + 16.0f;

						if (point.distance != 0.0f)
							search = false;
						point.distance = searchPoint.x - point.position.x;
					}
				}
			}
			else
			{
				if (point.distance == 0.0f)
				{
					point.distance += 16.0f * point.direction.x;
					point.distance += 16.0f * point.direction.y;
					searchPoint += (Alexio::Vector2)point.direction * 16.0f;
				}
				else
				{
					search = false;
				}
			}
		}
	}
}