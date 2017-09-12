#include "types.h"
#include "core.h"
#include "renderwidget.h"
#include "renderer.h"
#include "renderwidget.h"
#include "graphicsscene.h"
#include "graphicscamera.h"
#include "physicsscene.h"
#include "physicsbody.h"
#include "gameobjectbrick.h"
#include "gameobjectplayer.h"
#include "gameobjectguibutton.h"
#include "gameobjectgun.h"
#include "gamescenelevel.h"
#include "gameobjectmodifierrotate.h"
#include "gameobjectmodifieroffset.h"
#include "gameobjectmodifiertrain.h"

void GameSceneLevel::update(uint64_t time, uint32_t dt)
{
	if (Core::getController()->renderWidget()->testKey(RenderWidget::KeyCode_Left))
		m_pPlayer->transform()->pos.x -= 0.05f;
	if (Core::getController()->renderWidget()->testKey(RenderWidget::KeyCode_Right))
		m_pPlayer->transform()->pos.x += 0.05f;

	graphicsScene()->camera()->transform()->pos.x = m_pPlayer->transform()->pos.x;
}

void GameSceneLevel::mouseClick(int32_t x, int32_t y)
{
	ObjectsList list = selectObjects(x, y);

	if (std::find(list.cbegin(), list.cend(), m_pButtonStart) != list.cend()) {
		m_pPlayer->transform()->pos = glm::vec2(0.0f, 0.7f);
		m_pPlayer->physicsBodies().front()->setVelocity(glm::vec2(0.0f, 0.0f));
	}

	if (std::find(list.cbegin(), list.cend(), m_pButtonExit) != list.cend()) {
		Core::getController()->sendMessage(new CoreExitMessage());
	}
}

GameSceneLevel::GameSceneLevel() :
	GameAbstractScene()
{
	physicsScene()->setGravity(glm::vec2(0.0f, -5.0f));

	const int N = 20;
	for (int i = 0; i < N; ++i) {
		auto *pBrick = createGameObject<GameObjectBrick>();
		pBrick->transform()->pos = glm::vec2(1.375f * i, ((float)rand()/(float)RAND_MAX*2 - 1) * 0.4f - 0.5f);
		if (i == 0) {
			pBrick->transform()->pos.y = -0.7f;
			auto pMod = pBrick->addModifier<GameObjectModifierTrain>();
			pMod->keyFramesList().emplace_back(Transform(glm::vec2(-0.5f, -0.7f), 0.0f), 0.0f);
			pMod->keyFramesList().emplace_back(Transform(glm::vec2(0.5f, -0.7f), 0.0f), 2.0f);
			pMod->keyFramesList().emplace_back(Transform(glm::vec2(0.5f, 0.3f), 0.0f), 2.0f);
			pMod->keyFramesList().emplace_back(Transform(glm::vec2(-0.5f, 0.3f), 0.0f), 2.0f);
			pMod->keyFramesList().emplace_back(Transform(glm::vec2(-0.5f, -0.7f), 0.0f), 2.0f);
		}

		if ((i % 4 == 1) && (i != 1))
			pBrick->addModifier<GameObjectModifierRotate>(3.14f / 4.0f);
		if (i % 4 == 2)
			pBrick->addModifier<GameObjectModifierOffset>(glm::vec2(0.0f, 1.0f), 0.5f);
		if (i % 4 == 3)
			pBrick->addModifier<GameObjectModifierOffset>(glm::vec2(1.0f, 0.0f), 0.5f);
	}

	m_pPlayer = createGameObject<GameObjectPlayer>();
	m_pPlayer->transform()->pos = glm::vec2(-0.5f, 0.7f);

	GameObjectGun *pGun = createGameObject<GameObjectGun>();
	pGun->transform()->pos = glm::vec2(5.5f, 0.05f);

	m_pButtonStart = createGameObject<GameObjectGuiButton>(GuiButtonId_Start);
	m_pButtonStart->transform()->pos = glm::vec2(-1.2f, 0.8f);

	m_pButtonExit = createGameObject<GameObjectGuiButton>(GuiButtonId_Exit);
	m_pButtonExit->transform()->pos = glm::vec2(+1.2f, 0.8f);
}

GameSceneLevel::~GameSceneLevel()
{
}
