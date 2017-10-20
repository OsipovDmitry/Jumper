#ifndef TYPES_H
#define TYPES_H

#include <inttypes.h>

#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

struct Transform {
	glm::vec2 pos;
	float angle;

	Transform(const glm::vec2& p = glm::vec2(), float a = 0.0f) : pos(p), angle(a) {}
};

using Color4ub = glm::tvec4<uint8_t>;

enum ControllerType {
	ControllerType_Core = 0,
	ControllerType_Graphics,
	ControllerType_Physics,
	ControllerType_Audio,
	ControllerType_Game,
	ControllerType_Count
};

enum LayerId {
	LayerId_Background = 0,
	LayerId_Objects,
	LayerId_TransparentObjects,
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
	TextureId_GuiButtonRestart,
	TextureId_GuiButtonToMenu,
	TextureId_GuiButtonNextLevel,

	TextureId_Gun,
	TextureID_LevelPassed,

	TextureId_SymPercent, // '%' 40
    TextureId_SymExclamation, // '!' 8
    TextureId_SymDoubleQuot, // '"' 16
    TextureId_SymGrid, // '#' 32
    TextureId_SymDollar, // '$' 32
    TextureId_SymAmpersand, // '&' 32
    TextureId_SymQuot, // ''' 8
    TextureId_SymComma, // ',' 8
    TextureId_SymLeftCBracket, // '(' 16
    TextureId_SymRightCBracket, // ')' 16
    TextureId_SymStar, // '*' 16
    TextureId_SymPlus, // '+' 32
    TextureId_SymMinus, // '-' 16
    TextureId_SymPoint, // '.' 8
    TextureId_SymPipe, // '|' 8
    TextureId_SymSlash, // '/' 16
    TextureId_SymBackQuote, // '`' 16
    TextureId_SymColon, // ':' 8
    TextureId_SymSemicolon, // ';' 8
    TextureId_SymLess, // '<' 24
    TextureId_SymEqual, // '=' 24
    TextureId_SymGreat, // '>' 24
    TextureId_SymQuestion, // '?' 24
    TextureId_SymLeftQBracket, // '[' 16
    TextureId_SymBackSlash, // '\' 16
    TextureId_SymRightQBracket, // ']' 16
    TextureId_SymLine, // '_' 32

    TextureId_Sym0, // '0' 32
    TextureId_Sym1, // '1' 32
    TextureId_Sym2, // '2' 32
    TextureId_Sym3, // '3' 32
    TextureId_Sym4, // '4' 32
    TextureId_Sym5, // '5' 32
    TextureId_Sym6, // '6' 32
    TextureId_Sym7, // '7' 32
    TextureId_Sym8, // '8' 32
    TextureId_Sym9, // '9' 32
    TextureId_SymL, // 'L' 32
    TextureId_SymM, // 'M' 48
    TextureId_SymN, // 'N' 48
    TextureId_SymO, // 'O' 48

    TextureId_SymAt, // '@' 48
    TextureId_SymA, // 'A' 48
    TextureId_SymB, // 'B' 48
    TextureId_SymC, // 'C' 48
    TextureId_SymD, // 'D' 48
    TextureId_SymE, // 'E' 48
    TextureId_SymF, // 'F' 48
    TextureId_SymG, // 'G' 48
    TextureId_SymH, // 'H' 48
    TextureId_SymI, // 'I' 16
    TextureId_SymJ, // 'J' 32
    TextureId_SymK, // 'K' 32

    TextureId_SymP, // 'P' 48
    TextureId_SymQ, // 'Q' 48
    TextureId_SymR, // 'R' 48
    TextureId_SymS, // 'S' 48
    TextureId_SymT, // 'T' 48
    TextureId_SymU, // 'U' 48
    TextureId_SymV, // 'V' 48
    TextureId_SymW, // 'W' 48
    TextureId_SymX, // 'X' 48
    TextureId_SymY, // 'Y' 48
    TextureId_SymZ, // 'Z' 32

    TextureId_Sym_a, // 'a' 32
    TextureId_Sym_b, // 'b' 32
    TextureId_Sym_c, // 'c' 32
    TextureId_Sym_d, // 'd' 32
    TextureId_Sym_e, // 'e' 32
    TextureId_Sym_f, // 'f' 32
    TextureId_Sym_g, // 'g' 32
    TextureId_Sym_h, // 'h' 32
    TextureId_Sym_i, // 'i' 16
    TextureId_Sym_j, // 'j' 16
    TextureId_Sym_k, // 'k' 32
    TextureId_Sym_l, // 'l' 16
    TextureId_Sym_m, // 'm' 48
    TextureId_Sym_n, // 'n' 32
    TextureId_Sym_o, // 'o' 32
    TextureId_Sym_p, // 'p' 32
    TextureId_Sym_q, // 'q' 32

    TextureId_Sym_r, // 'r' 32
    TextureId_Sym_s, // 's' 32
    TextureId_Sym_t, // 't' 32
    TextureId_Sym_u, // 'u' 32
    TextureId_Sym_v, // 'v' 32
    TextureId_Sym_w, // 'w' 40
    TextureId_Sym_x, // 'x' 24
    TextureId_Sym_y, // 'y' 32
    TextureId_Sym_z, // 'z' 32
    TextureId_SymLeftFBracket, // '{' 16
    TextureId_SymRightFBracket, // '}' 16
    TextureId_SymTilde, // '~' 24
    TextureId_SymPower, // '^' 24

    TextureId_Background0,
    TextureId_Background1,
	TextureId_Background2,
	TextureId_Background3,

	TextureId_Count
};

enum BackgroundId {
	BackgroundId_0 = TextureId_Background0,
    BackgroundId_1 = TextureId_Background1,
	BackgroundId_2 = TextureId_Background2,
	BackgroundId_3 = TextureId_Background3,

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
	GuiButtonId_Restart = TextureId_GuiButtonRestart,
	GuiButtonId_ToMenu = TextureId_GuiButtonToMenu,
	GuiButtonId_NextLevel = TextureId_GuiButtonNextLevel,
};

enum SoundId {
	SoundId_Jump,
	SoundId_BrokenJump,
	SoundId_LevelPassed,
	SoundId_Shot,
	SoundId_Count
};

enum GameSceneId {
	GameSceneId_None = -1,
	GameSceneId_MainMenu = 0,
	GameSceneId_Authors,
	GameSceneId_SelectLevel,
	GameSceneId_Level,
	GameSceneId_GameOver,
	GameSceneId_LevelPassed,
	GameSceneId_Count
};

enum GameLevelId {
	GameLevelId_None = -1,
	GameLevelId_1 = 0,
	GameLevelId_2,
	GameLevelId_3,
	GameLevelId_Count
};

const float GLOBAL_DOWN = -5.0f;

#endif // TYPES_H
