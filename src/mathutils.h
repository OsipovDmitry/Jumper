#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "glm/gtc/matrix_transform.hpp"
#include "types.h"

template <typename T>
inline T rand(const T& a = static_cast<T>(0.0), const T& b = static_cast<T>(1.0)) {
	return a + (b-a)*static_cast<T>((float)rand()/(float)(RAND_MAX-1));
}

inline glm::vec2 toWorldSpace(Transform *pLocalTransform, const glm::vec2& localPoint, const bool isDirection = false) {
	return glm::vec2(
				glm::translate(glm::mat4x4(), glm::vec3(pLocalTransform->pos, 0.0f)) *
				glm::rotate(glm::mat4x4(), pLocalTransform->angle, glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::vec4(localPoint, 0.0f, isDirection ? 0.0f : 1.0f)
				);
}

inline glm::vec2 toLocalSpace(Transform *pLocalTrasform, const glm::vec2& worldPoint) {
	return glm::vec2(
				glm::vec4(worldPoint, 0.0f, 1.0f)
				);
}


#endif // MATHUTILS_H
