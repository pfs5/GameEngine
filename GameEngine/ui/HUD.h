#pragma once
#include "../game_objects/GameObject.h"
#include <vector>

// ----------------------------------------------------------------------------
class HUDButton;

// ----------------------------------------------------------------------------
class HUD : public GameObject
{
	GAME_OBJECT_BODY()

public:
	HUD();
	~HUD();

// GameObject
public:
	virtual void update(float _dt) override;

	virtual void draw() override;

	virtual GameObject * clone() override;

protected:
	void addNewButton(HUDButton* btn);

private:
	std::vector<HUDButton*> _buttons;

private:
	void handleMouseEvents() const;
};
// ----------------------------------------------------------------------------