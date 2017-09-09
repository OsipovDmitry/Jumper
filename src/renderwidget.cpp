#include <QTimer>
#include <QDateTime>
#include <QMouseEvent>

#include "core.h"
#include "renderer.h"
#include "renderwidget.h"

RenderWidget::RenderWidget(QWidget* pParentWidget) :
	QGLWidget(pParentWidget),
	m_pTimer(new QTimer()),
	m_pRenderer(nullptr),
	m_startTime(QDateTime::currentMSecsSinceEpoch()),
	m_lastUpdateTime(0),
	m_keys()
{
	const int height = 20;
	resize(height * Renderer::s_viewportAspect, height);

	connect(m_pTimer, SIGNAL(timeout()), SLOT(update()));
	m_pTimer->start(16);
}

RenderWidget::~RenderWidget()
{
	delete m_pRenderer;
	delete m_pTimer;
}

bool RenderWidget::testKey(RenderWidget::KeyCode keyCode) const
{
	return m_keys[keyCode];
}

Renderer *RenderWidget::renderer() const
{
	return m_pRenderer;
}

void RenderWidget::initializeGL()
{
	m_pRenderer = new Renderer;
	Core::getController()->sendMessage(new CoreInitMessage(), AbstractController::MessagePriority_High);
}

void RenderWidget::resizeGL(int w, int h)
{
	m_pRenderer->resize(w, h);
}

void RenderWidget::paintGL()
{
	uint64_t time = QDateTime::currentMSecsSinceEpoch() - m_startTime;
	uint32_t dt = time - m_lastUpdateTime;
	m_lastUpdateTime = time;

	Core::getController()->sendMessage(new CoreUpdateMessage(time, dt));
	Core::getController()->readMessages();

	m_pRenderer->render();
}

void RenderWidget::mousePressEvent(QMouseEvent* pEvent)
{
	Core::getController()->sendMessage(new CoreMouseClickMessage(pEvent->x(), pEvent->y()));
}

void RenderWidget::keyPressEvent(QKeyEvent* pEvent)
{
	KeyCode code;
	switch (pEvent->key()) {
		case Qt::Key_Left:
			code = KeyCode_Left;
			break;
		case Qt::Key_Right:
			code = KeyCode_Right;
			break;
		case Qt::Key_Up:
			code = KeyCode_Up;
			break;
		case Qt::Key_Down:
			code = KeyCode_Down;
			break;
		default:
			return;
	}

	m_keys[code] = true;
}

void RenderWidget::keyReleaseEvent(QKeyEvent* pEvent)
{
	KeyCode code;
	switch (pEvent->key()) {
		case Qt::Key_Left:
			code = KeyCode_Left;
			break;
		case Qt::Key_Right:
			code = KeyCode_Right;
			break;
		case Qt::Key_Up:
			code = KeyCode_Up;
			break;
		case Qt::Key_Down:
			code = KeyCode_Down;
			break;
		default:
			return;
	}

	m_keys[code] = false;
}
