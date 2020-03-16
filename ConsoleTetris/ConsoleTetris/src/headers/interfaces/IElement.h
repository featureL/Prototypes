#pragma once

#include <Pair.h>

class IElement
{
public:
	virtual types::Shape GetShape() const = 0;
	virtual void SetShape(types::Shape) = 0;
	virtual Pair<int, int> GetCoord() const = 0;
	virtual void SetCoord(const Pair<int, int> &) = 0;
	virtual void Move(const Pair<int, int> &) = 0;
	virtual Pair<int, int> GetShapeSzie() const = 0;
	virtual void SetShapeSize(const Pair<int, int> &) = 0;
	virtual void Update() = 0;
	virtual int GetId() const = 0;
	virtual void SetId(int) = 0;
	virtual void SetBoundingRect(const types::Rectangle &boundingRect) = 0;
	virtual types::Rectangle GetBoundingRect() const = 0;
};