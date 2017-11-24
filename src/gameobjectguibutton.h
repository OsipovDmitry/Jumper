#ifndef GAMEOBJECTGUIBUTTON_H
#define GAMEOBJECTGUIBUTTON_H

#include "gameobject.h"
#include "types.h"

class GraphicsObject;

class GameObjectGuiButton : public GameObject
{
GAME_OBJECT_META(Type_GuiButton)
public:
	bool setParam(const std::string& key, const std::string& value) override;

	void setButtonId(GuiButtonId id);

protected:
private:
	GameObjectGuiButton(GameAbstractScene *pScene, GuiButtonId id);
	~GameObjectGuiButton();

	static GuiButtonId paramToButtonId(const std::string& param);

	GraphicsObject *m_pGraphicsObject;

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTGUIBUTTON_H
