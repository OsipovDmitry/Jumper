#ifndef GAMEOBJECTTEXT_H
#define GAMEOBJECTTEXT_H

#include "gameobject.h"
#include "types.h"

class GameObjectText : public GameObject
{
GAME_OBJECT_META(Type_Text)
public:	
	void setTransform(const Transform& value);

    const std::string& text() const;
    void setText(const std::string& str);

    float size() const;
    void setSize(const float sz);

	Color4ub color() const;
	void setColor(const Color4ub& value);

	// 0 <= x,y <= 1; (0,0 - left up corner, 1,1 - right down corner)
	void setCentering(float x, float y);
	float centeringX() const;
	float centeringY() const;

protected:
private:
	GameObjectText(GameAbstractScene *pScene, const std::string& str);
	~GameObjectText();

    void destroy();
    void rebuild();

	std::list<Transform*> m_symbolTransforms;
    std::string m_text;
    float m_size;
	float m_centeringX, m_centeringY;
	Color4ub m_color;

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTTEXT_H
