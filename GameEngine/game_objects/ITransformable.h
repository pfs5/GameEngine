#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

class ITransformable
{
public:
	ITransformable() : _parent {nullptr} {}
	virtual ~ITransformable() = default;

	virtual void setLocalPosition(const sf::Vector2f &_pos);
	inline const sf::Vector2f &getLocalPosition() const { return _localPosition; }
	inline const sf::Vector2f &getGlobalPosition() const { return _globalPosition; }
	inline void move(sf::Vector2f delta) { setLocalPosition(getLocalPosition() + delta); }

	void attachChild(ITransformable * child);
	void setParent(ITransformable * parent);
	void clearParent();

protected:
	sf::Vector2f _localPosition;						
	sf::Vector2f _globalPosition;						
	sf::Vector2f _parentGlobalPosition;

	ITransformable * _parent;
	std::vector<ITransformable *> _children;

private:
	void setParentGlobalPosition(sf::Vector2f pos);
};
