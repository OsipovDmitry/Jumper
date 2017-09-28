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

	TextureId_SymSpace, // ' '
	TextureId_SymExclamation, // '!'
	TextureId_SymDoubleQuot, // '"'
	TextureId_SymGrid, // '#'
	TextureId_SymDollar, // '$'
	TextureId_SymPercent, // '%'
	TextureId_SymAmpersand, // '&'
	TextureId_SymQuot, // '''
	TextureId_SymLeftCBracket, // '('
	TextureId_SymRightCBracket, // ')'
	TextureId_SymStar, // '*'
	TextureId_SymPlus, // '+'
	TextureId_SymComma, // ','
	TextureId_SymMinus, // '-'
	TextureId_SymPoint, // '.'
	TextureId_SymSlash, // '/'
	TextureId_Sym0, // '0'
	TextureId_Sym1, // '1'
	TextureId_Sym2, // '2'
	TextureId_Sym3, // '3'
	TextureId_Sym4, // '4'
	TextureId_Sym5, // '5'
	TextureId_Sym6, // '6'
	TextureId_Sym7, // '7'
	TextureId_Sym8, // '8'
	TextureId_Sym9, // '9'
	TextureId_SymColon, // ':'
	TextureId_SymSemicolon, // ';'
	TextureId_SymLess, // '<'
	TextureId_SymEqual, // '='
	TextureId_SymGreat, // '>'
	TextureId_SymQuestion, // '?'
	TextureId_SymAt, // '@'
	TextureId_SymA, // 'A'
	TextureId_SymB, // 'B'
	TextureId_SymC, // 'C'
	TextureId_SymD, // 'D'
	TextureId_SymE, // 'E'
	TextureId_SymF, // 'F'
	TextureId_SymG, // 'G'
	TextureId_SymH, // 'H'
	TextureId_SymI, // 'I'
	TextureId_SymJ, // 'J'
	TextureId_SymK, // 'K'
	TextureId_SymL, // 'L'
	TextureId_SymM, // 'M'
	TextureId_SymN, // 'N'
	TextureId_SymO, // 'O'
	TextureId_SymP, // 'P'
	TextureId_SymQ, // 'Q'
	TextureId_SymR, // 'R'
	TextureId_SymS, // 'S'
	TextureId_SymT, // 'T'
	TextureId_SymU, // 'U'
	TextureId_SymV, // 'V'
	TextureId_SymW, // 'W'
	TextureId_SymX, // 'X'
	TextureId_SymY, // 'Y'
	TextureId_SymZ, // 'Z'
	TextureId_SymLeftQBracket, // '['
	TextureId_SymBackSlash, // '\'
	TextureId_SymRightQBracket, // ']'
	TextureId_SymPower, // '^'
	TextureId_SymLine, // '_'
	TextureId_SymBackQuote, // '`'
	TextureId_Sym_a, // 'a'
	TextureId_Sym_b, // 'b'
	TextureId_Sym_c, // 'c'
	TextureId_Sym_d, // 'd'
	TextureId_Sym_e, // 'e'
	TextureId_Sym_f, // 'f'
	TextureId_Sym_g, // 'g'
	TextureId_Sym_h, // 'h'
	TextureId_Sym_i, // 'i'
	TextureId_Sym_j, // 'j'
	TextureId_Sym_k, // 'k'
	TextureId_Sym_l, // 'l'
	TextureId_Sym_m, // 'm'
	TextureId_Sym_n, // 'n'
	TextureId_Sym_o, // 'o'
	TextureId_Sym_p, // 'p'
	TextureId_Sym_q, // 'w'
	TextureId_Sym_r, // 'r'
	TextureId_Sym_s, // 's'
	TextureId_Sym_t, // 't'
	TextureId_Sym_u, // 'u'
	TextureId_Sym_v, // 'v'
	TextureId_Sym_w, // 'w'
	TextureId_Sym_x, // 'x'
	TextureId_Sym_y, // 'y'
	TextureId_Sym_z, // 'z'
	TextureId_SymLeftFBracket, // '{'
	TextureId_SymBackPipe, // '|'
	TextureId_SymRightFBracket, // '}'
	TextureId_SymTilde, // '~'
	TextureId_SymRect, // '[]'


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
