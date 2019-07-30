#pragma once

#include <SFML/Graphics.hpp>

class GameObject;
class RigidBody;

/**
	Implementation of a 2d box collider
**/
class Collider {
	int m_id;

	sf::Vector2f m_position;
	sf::Vector2f m_offset;
	sf::Vector2f m_size;

	bool m_isTrigger = true;
	bool m_isStatic = false;

	GameObject * m_gameObject = nullptr;
	RigidBody * m_rigidBody = nullptr;

	// Visuals
	const sf::Color COLLIDER_COLOR = sf::Color{ 0, 255, 0 };
	sf::RectangleShape m_shape;
	const float m_lineThickness = 2.f;
public:
	Collider(GameObject * _gameObject, sf::Vector2f _position = sf::Vector2f{ 0.f, 0.f }, sf::Vector2f _size = sf::Vector2f{ 0.f, 0.f }, int _id = 0);
	~Collider();
	
	const sf::Drawable &getDrawable();

#pragma region Getters and setters
	inline void setID(const int &_id) { m_id = _id; };
	inline int getID() const { return m_id; };

	inline void setOffset(const sf::Vector2f &_offset) { m_offset = _offset; };

	inline void setPosition(const sf::Vector2f &_pos) { m_position = _pos + m_offset; updateShape(); };
	inline const sf::Vector2f &getPosition() const { return m_position; }; 

	inline void setSize(const sf::Vector2f &_size) { m_size = _size; m_shape.setSize(_size); };
	inline const sf::Vector2f &getSize() const { return m_size; };

	inline bool isTrigger() const { return m_isTrigger; };
	void setTrigger(bool _trigger, RigidBody * _rb = nullptr);

	inline bool isStatic() const { return m_isStatic; };
	inline void setStatic(bool _s) { m_isStatic = _s; };

	inline void setRigidBody(RigidBody * _rb) { m_rigidBody = _rb; };
	inline RigidBody * getRigidBody() const { return m_rigidBody; };

	inline GameObject * getGameObject() const { return m_gameObject; };
#pragma endregion
private:
	void updateShape();
};

