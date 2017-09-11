#ifndef GAMEOBJECTGUIBUTTON_H
#define GAMEOBJECTGUIBUTTON_H

#include "gameobject.h"
#include "types.h"

class GraphicsObject;

class GameObjectGuiButton : public GameObject
{
public:
	void setButtonId(GuiButtonId id);

protected:
private:
	GameObjectGuiButton(GameAbstractScene *pScene, GuiButtonId id);
	~GameObjectGuiButton();

	GraphicsObject *m_pGraphicsObject;

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTGUIBUTTON_H
