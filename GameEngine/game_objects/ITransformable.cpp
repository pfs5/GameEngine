#include "ITransformable.h"
#include <algorithm>

void ITransformable::setLocalPosition(const sf::Vector2f & _pos)
{
	_globalPosition += _pos - _localPosition;
	_localPosition = _pos;
	for (auto &child : _children)
	{
		child->setParentGlobalPosition(_globalPosition);
	}
}

 void ITransformable::attachChild(ITransformable* child)
{
	 child->_parent = this;
	 _children.push_back(child);
}

 void ITransformable::setParent(ITransformable * parent)
 {
	 parent->attachChild(this);
 }

void ITransformable::clearParent()
{
	if (_parent == nullptr) return;

	_parent->_children.erase(std::remove(_parent->_children.begin(), _parent->_children.end(), this), _parent->_children.end());
	_parent = nullptr;
}

void ITransformable::setParentGlobalPosition(sf::Vector2f pos)
{
	_globalPosition = pos + _localPosition;
	setLocalPosition(_localPosition);
}
