#ifndef VIEWER_H
#define VIEWER_H

#include <QLabel>
#include <QList>

class Viewer : public QLabel
{
    Q_OBJECT
public:
    explicit Viewer();

    void start();

signals:

public slots:
    void onDataAvailable(void*);

private:
    QImage* m_target;
    int* m_accumulationBuffer;
};

#endif // VIEWER_H
