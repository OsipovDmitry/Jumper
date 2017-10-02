#ifndef GAMEOBJECTTEXT_H
#define GAMEOBJECTTEXT_H

#include "gameobject.h"

class GameObjectText : public GameObject
{
public:	
	void setTransform(const Transform& value);

    const std::string& text() const;
    void setText(const std::string& str);

    float size() const;
    void setSize(const float sz);

	// 0 <= x,y <= 1; (0,0 - left up corner, 1,1 - right down corner)
	void setCentering(float x, float y);
	float centeringX() const;
	float centeringY() const;

protected:
private:
    GameObjectText(GameAbstractScene *pScene, const std::string& str, const float textSize = 0.2f);
	~GameObjectText();

    void destroy();
    void rebuild();

	std::list<Transform*> m_symbolTransforms;
    std::string m_text;
    float m_size;
	float m_centeringX, m_centeringY;

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTTEXT_H
