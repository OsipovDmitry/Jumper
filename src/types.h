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

	TextureId_GuiButtonStart,
	TextureId_GuiButtonExit,
	TextureId_GuiButtonEmpty,

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
};

#endif // TYPES_H
