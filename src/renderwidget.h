#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <list>

#include <QGLWidget>

#include "types.h"

class QTimer;
class QTiltSensor;

class Renderer;

class RenderWidget : public QGLWidget
{
	Q_OBJECT
public:
	explicit RenderWidget(QWidget *pParentWidget = nullptr);
	~RenderWidget();

	Renderer *renderer() const;

#if defined(Q_OS_ANDROID)
	void calibrateTiltSensor();
#elif defined(Q_OS_LINUX) || defined(Q_OS_WIN)
#else
#endif

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	void mousePressEvent(QMouseEvent *pEvent);
	void showEvent(QShowEvent*);
	void hideEvent(QHideEvent*);

#if defined(Q_OS_ANDROID)
private slots:
	void sTiltSensorReading();
	void sAppStateChanged(Qt::ApplicationState state);
#elif defined(Q_OS_LINUX) || defined(Q_OS_WIN)
protected:
	void keyPressEvent(QKeyEvent *pEvent);
	void keyReleaseEvent(QKeyEvent *pEvent);
#else
#endif

private:
	QTimer *m_pTimer;
	Renderer *m_pRenderer;
	qint64 m_startTime, m_lastUpdateTime;

#if defined(Q_OS_ANDROID)
	QTiltSensor *m_pTiltSensor;
#elif defined(Q_OS_LINUX) || defined(Q_OS_WIN)
	static KeyCode qtKeyToKeyCode(int qtKey);
#else
#endif
};

#endif // RENDERWIDGET_H
