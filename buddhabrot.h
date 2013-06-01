#ifndef BUDDHABROT_H
#define BUDDHABROT_H

#include <QThread>

class Buddhabrot : public QThread
{
    Q_OBJECT
public:
    explicit Buddhabrot(QObject* receiver, float crMin, float crMax, float ciMin, float ciMax,
                        int w, int h, int maxIterations);

    void run();

signals:
    void dataAvailable(unsigned short*);

public slots:

private:

    float m_crMin, m_crMax, m_ciMin, m_ciMax;
    int m_w, m_h, m_maxIterations;
    unsigned short* m_accumulationBuffer;
    int* m_orbit;
    QObject* m_receiver;
};

#endif // BUDDHABROT_H
