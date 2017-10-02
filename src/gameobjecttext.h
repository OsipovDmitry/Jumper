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

protected:
private:
    GameObjectText(GameAbstractScene *pScene, const std::string& str, const float textSize = 0.2f);
	~GameObjectText();

    void destroy();
    void rebuild();

	std::list<Transform*> m_symbolTransforms;
    std::string m_text;
    float m_size;

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTTEXT_H
