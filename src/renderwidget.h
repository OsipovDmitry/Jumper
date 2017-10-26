#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <bitset>

#include <QGLWidget>

class QTimer;
class QTiltSensor;

class Renderer;

class RenderWidget : public QGLWidget
{
	Q_OBJECT
public:
	enum KeyCode {
		KeyCode_Left = 0,
		KeyCode_Right,
		KeyCode_Up,
		KeyCode_Down,
		KeyCode_Count
	};

	explicit RenderWidget(QWidget *pParentWidget = nullptr);
	~RenderWidget();

	bool testKey(KeyCode keyCode) const;

	Renderer *renderer() const;

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	void mousePressEvent(QMouseEvent *pEvent);
	void keyPressEvent(QKeyEvent *pEvent);
	void keyReleaseEvent(QKeyEvent *pEvent);

private slots:
#ifdef Q_OS_ANDROID
	void sTiltSensorReading();
#endif

private:
	QTimer *m_pTimer;
#ifdef Q_OS_ANDROID
	QTiltSensor *m_pTiltSensor;
#endif
	Renderer *m_pRenderer;
	qint64 m_startTime, m_lastUpdateTime;
	std::bitset<KeyCode_Count> m_keys;
};

#endif // RENDERWIDGET_H
