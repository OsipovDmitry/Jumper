#include <QTimer>
#include <QDateTime>
#include <QMouseEvent>
#include <QDebug>
#ifdef Q_OS_ANDROID
#include <QTiltSensor>
#endif

#include "core.h"
#include "renderer.h"
#include "renderwidget.h"

RenderWidget::RenderWidget(QWidget* pParentWidget) :
	QGLWidget(pParentWidget),
	m_pRenderer(nullptr),
	m_startTime(QDateTime::currentMSecsSinceEpoch()),
	m_lastUpdateTime(0)
{
	const int height = 20;
	resize(height * Renderer::s_viewportAspect, height);

#if defined(Q_OS_ANDROID)
	m_pTiltSensor = new QTiltSensor(this);
	if (!m_pTiltSensor->connectToBackend())
		qDebug() << "Error: pTiltSensor->connectToBackend() return false!";
	bool b = connect(m_pTiltSensor, SIGNAL(readingChanged()), SLOT(sTiltSensorReading()));
	m_pTiltSensor->start();
	m_pTiltSensor->calibrate();
#elif defined(Q_OS_LINUX) || defined(Q_OS_WIN)
	;
#else
#endif

	m_pTimer = new QTimer(this);
	connect(m_pTimer, SIGNAL(timeout()), SLOT(update()));
	m_pTimer->start(16);
}

RenderWidget::~RenderWidget()
{
	m_pTimer->stop();
	delete m_pTimer;

#if defined(Q_OS_ANDROID)
	delete m_pTiltSensor;
#elif defined(Q_OS_LINUX) || defined(Q_OS_WIN)
	;
#endif

	delete m_pRenderer;
}

Renderer *RenderWidget::renderer() const
{
	return m_pRenderer;
}

#if defined(Q_OS_ANDROID)
void RenderWidget::calibrateTiltSensor()
{
	m_pTiltSensor->calibrate();
}
#elif defined(Q_OS_LINUX) || defined(Q_OS_WIN)
#else
#endif

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

#if defined(Q_OS_ANDROID)
void RenderWidget::sTiltSensorReading()
{
	auto pReading = m_pTiltSensor->reading();
	if (!pReading)
		return;
	static const float s_angleValue = 7.0f;
	if (pReading->yRotation() > s_angleValue) {
		m_keys[KeyCode_Right] = true;
		m_keys[KeyCode_Left] = false;
	}
	else if (pReading->yRotation() < -s_angleValue) {
		m_keys[KeyCode_Right] = false;
		m_keys[KeyCode_Left] = true;
	}
	else {
		m_keys[KeyCode_Right] = false;
		m_keys[KeyCode_Left] = false;
	}

	for (auto& f: m_tiltSensorCallbacks)
		f.second(f.first, pReading->xRotation(), pReading->yRotation());
}
#elif defined(Q_OS_LINUX) || defined(Q_OS_WIN)
void RenderWidget::keyPressEvent(QKeyEvent* pEvent)
{
	auto code = qtKeyToKeyCode(pEvent->key());

	for (auto& f: m_keyPressCallbacks)
		f.second(f.first, code);
}

void RenderWidget::keyReleaseEvent(QKeyEvent* pEvent)
{
	auto code = qtKeyToKeyCode(pEvent->key());

	for (auto& f: m_keyReleaseCallbacks)
		f.second(f.first, code);
}

RenderWidget::KeyCode RenderWidget::qtKeyToKeyCode(int qtKey)
{
	KeyCode code = KeyCode_None;
	switch (qtKey) {
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
			break;
	}
	return code;
}
#else
#endif
