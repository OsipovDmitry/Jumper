#ifndef TYPES_H
#define TYPES_H

#include "glm/vec2.hpp"

enum ControllerType {
	ControllerType_Core = 0,
	ControllerType_Graphics,
	ControllerType_Physics,
	ControllerType_Game,
	ControllerType_Count
};

struct Transform {
	glm::vec2 pos;
	float angle;

	Transform(const glm::vec2& p = glm::vec2(), float a = 0.0f) : pos(p), angle(a) {}
};

enum LayerId {
	LayerId_Background = 0,
	LayerId_Objects,
	LayerId_Gui,
	LayerId_Count
};

enum TextureId {
	TextureId_None = 0,
	TextureId_Brick,
	TextureId_Circle,
	TextureId_Rect,
	TextureId_BrokenBrick,
	TextureId_BrockenBrickPart,

	TextureId_GuiButtonStart,
	TextureId_GuiButtonExit,
	TextureId_GuiButtonEmpty,
	TextureId_GuiButtonAuthors,
	TextureId_GuiButtonBack,
	TextureId_GuiButtonLevel1,
	TextureId_GuiButtonLevel2,
	TextureId_GuiButtonLevel3,

	TextureId_Gun,

	TextureId_Background0,

	TextureId_Count
};

enum BackgroundId {
	BackgroundId_0 = TextureId_Background0,

	BackgroundId_Count
};

enum GuiButtonId {
	GuiButtonId_Start = TextureId_GuiButtonStart,
	GuiButtonId_Exit = TextureId_GuiButtonExit,
	GuiButtonId_Empty = TextureId_GuiButtonEmpty,
	GuiButtonId_Authors = TextureId_GuiButtonAuthors,
	GuiButtonId_Back = TextureId_GuiButtonBack,
	GuiButtonId_Level1 = TextureId_GuiButtonLevel1,
	GuiButtonId_Level2 = TextureId_GuiButtonLevel2,
	GuiButtonId_Level3 = TextureId_GuiButtonLevel3,
};

enum GameSceneId {
	GameSceneId_None = -1,
	GameSceneId_MainMenu = 0,
	GameSceneId_Authors,
	GameSceneId_SelectLevel,
	GameSceneId_Level,
	GameSceneId_Count
};

const float GLOBAL_DOWN = -500.0f;

#endif // TYPES_H
