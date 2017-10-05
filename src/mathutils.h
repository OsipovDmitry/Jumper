#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <unordered_map>

#include "glm/gtc/matrix_transform.hpp"
#include "types.h"

template <typename T>
inline T rand(const T& a = static_cast<T>(0.0), const T& b = static_cast<T>(1.0)) {
	return a + (b-a)*static_cast<T>((float)rand()/(float)(RAND_MAX-1));
}

inline glm::vec2 toWorldSpace(Transform *pLocalToWorldTransform, const glm::vec2& localPoint, const bool isDirection = false) {
	return glm::vec2(
				glm::translate(glm::mat4x4(), glm::vec3(pLocalToWorldTransform->pos, 0.0f)) *
				glm::rotate(glm::mat4x4(), pLocalToWorldTransform->angle, glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::vec4(localPoint, 0.0f, isDirection ? 0.0f : 1.0f)
				);
}

inline glm::vec2 toLocalSpace(Transform *pLocalToWorldTransform, const glm::vec2& worldPoint) {
	return glm::vec2(
				glm::rotate(glm::mat4x4(), -pLocalToWorldTransform->angle, glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::translate(glm::mat4x4(), -glm::vec3(pLocalToWorldTransform->pos, 0.0f)) *
				glm::vec4(worldPoint, 0.0f, 1.0f)
				);
}

inline TextureId symbolToTextureId(char c) {
    static const std::unordered_map<char, TextureId> table {
		{'!', TextureId_SymExclamation}, // '!'
		{'\"', TextureId_SymDoubleQuot}, // '"'
		{'#', TextureId_SymGrid}, // '#'
		{'$', TextureId_SymDollar}, // '$'
		{'%', TextureId_SymPercent}, // '%'
		{'&', TextureId_SymAmpersand}, // '&'
		{'\'', TextureId_SymQuot}, // '''
		{'(', TextureId_SymLeftCBracket}, // '('
		{')', TextureId_SymRightCBracket}, // ')'
		{'*', TextureId_SymStar}, // '*'
		{'+', TextureId_SymPlus}, // '+'
		{',', TextureId_SymComma}, // ','
		{'-', TextureId_SymMinus}, // '-'
		{'.', TextureId_SymPoint}, // '.'
		{'/', TextureId_SymSlash}, // '/'
		{'0', TextureId_Sym0}, // '0'
		{'1', TextureId_Sym1}, // '1'
		{'2', TextureId_Sym2}, // '2'
		{'3', TextureId_Sym3}, // '3'
		{'4', TextureId_Sym4}, // '4'
		{'5', TextureId_Sym5}, // '5'
		{'6', TextureId_Sym6}, // '6'
		{'7', TextureId_Sym7}, // '7'
		{'8', TextureId_Sym8}, // '8'
		{'9', TextureId_Sym9}, // '9'
		{':', TextureId_SymColon}, // ':'
		{';', TextureId_SymSemicolon}, // ';'
		{'<', TextureId_SymLess}, // '<'
		{'=', TextureId_SymEqual}, // '='
		{'>', TextureId_SymGreat}, // '>'
		{'?', TextureId_SymQuestion}, // '?'
		{'@', TextureId_SymAt}, // '@'
		{'A', TextureId_SymA}, // 'A'
		{'B', TextureId_SymB}, // 'B'
		{'C', TextureId_SymC}, // 'C'
		{'D', TextureId_SymD}, // 'D'
		{'E', TextureId_SymE}, // 'E'
		{'F', TextureId_SymF}, // 'F'
		{'G', TextureId_SymG}, // 'G'
		{'H', TextureId_SymH}, // 'H'
		{'I', TextureId_SymI}, // 'I'
		{'J', TextureId_SymJ}, // 'J'
		{'K', TextureId_SymK}, // 'K'
		{'L', TextureId_SymL}, // 'L'
		{'M', TextureId_SymM}, // 'M'
		{'N', TextureId_SymN}, // 'N'
		{'O', TextureId_SymO}, // 'O'
		{'P', TextureId_SymP}, // 'P'
		{'Q', TextureId_SymQ}, // 'Q'
		{'R', TextureId_SymR}, // 'R'
		{'S', TextureId_SymS}, // 'S'
		{'T', TextureId_SymT}, // 'T'
		{'U', TextureId_SymU}, // 'U'
		{'V', TextureId_SymV}, // 'V'
		{'W', TextureId_SymW}, // 'W'
		{'X', TextureId_SymX}, // 'X'
		{'Y', TextureId_SymY}, // 'Y'
		{'Z', TextureId_SymZ}, // 'Z'
		{'[', TextureId_SymLeftQBracket}, // '['
		{'\\', TextureId_SymBackSlash}, // '\'
		{']', TextureId_SymRightQBracket}, // ']'
		{'^', TextureId_SymPower}, // '^'
		{'_', TextureId_SymLine}, // '_'
		{'`', TextureId_SymBackQuote}, // '`'
		{'a', TextureId_Sym_a}, // 'a'
		{'b', TextureId_Sym_b}, // 'b'
		{'c', TextureId_Sym_c}, // 'c'
		{'d', TextureId_Sym_d}, // 'd'
		{'e', TextureId_Sym_e}, // 'e'
		{'f', TextureId_Sym_f}, // 'f'
		{'g', TextureId_Sym_g}, // 'g'
		{'h', TextureId_Sym_h}, // 'h'
		{'i', TextureId_Sym_i}, // 'i'
		{'j', TextureId_Sym_j}, // 'j'
		{'k', TextureId_Sym_k}, // 'k'
		{'l', TextureId_Sym_l}, // 'l'
		{'m', TextureId_Sym_m}, // 'm'
		{'n', TextureId_Sym_n}, // 'n'
		{'o', TextureId_Sym_o}, // 'o'
		{'p', TextureId_Sym_p}, // 'p'
		{'q', TextureId_Sym_q}, // 'q'
		{'r', TextureId_Sym_r}, // 'r'
		{'s', TextureId_Sym_s}, // 's'
		{'t', TextureId_Sym_t}, // 't'
		{'u', TextureId_Sym_u}, // 'u'
		{'v', TextureId_Sym_v}, // 'v'
		{'w', TextureId_Sym_w}, // 'w'
		{'x', TextureId_Sym_x}, // 'x'
		{'y', TextureId_Sym_y}, // 'y'
		{'z', TextureId_Sym_z}, // 'z'
		{'{', TextureId_SymLeftFBracket}, // '{'
        {'|', TextureId_SymPipe}, // '|'
		{'}', TextureId_SymRightFBracket}, // '}'
        {'~', TextureId_SymTilde}, // '~'
	};
	auto it = table.find(c);
	return (it == table.end()) ? TextureId_SymQuestion : it->second;
}

inline float stof(const char* s){
    float rez = 0, fact = 1;
    if (*s == '-'){
      s++;
      fact = -1;
    };
    for (int point_seen = 0; *s; s++){
      if (*s == '.'){
        point_seen = 1;
        continue;
      };
      int d = *s - '0';
      if (d >= 0 && d <= 9){
        if (point_seen) fact /= 10.0f;
        rez = rez * 10.0f + (float)d;
      };
    };
    return rez * fact;
  }


#endif // MATHUTILS_H
