#include <QImage>
#include <QDebug>
#include <math.h>

#include "viewer.h"
#include "buddhabrot.h"


Viewer::Viewer()
{

}

void Viewer::start()
{
    QThread::currentThread()->setPriority(QThread::HighestPriority);

    int size = width() * height();
    m_target = new QImage(width(), height(), QImage::Format_RGB888);
    m_accumulationBuffer = new int[size];
    memset(m_accumulationBuffer, 0, size * sizeof(int));

#ifdef Q_OS_LINUX
    int threadCount = sysconf(_SC_NPROCESSORS_ONLN);
#else
    inf threadCount = 4;    // I just can't be bothered...
#endif

    qDebug() << "Starting" << threadCount << "threads.";
    for (int i=0; i < threadCount; i++) {
        qreal ratio = (qreal) width() / height();
        Buddhabrot* b = new Buddhabrot(this, -2.0, 1.0, -1.5 * ratio, 1.5 * ratio, width(), height(), 2000);
        b->start();
        b->setPriority(QThread::IdlePriority);
    }
}

void Viewer::onDataAvailable(void *b) {
    unsigned short* buffer = (quint16*) b;
    int pixelCount = width() * height();
    int maxValue = 0;
    for (int i=0; i < pixelCount; i++) {
        m_accumulationBuffer[i] += buffer[i];
        if (m_accumulationBuffer[i] > maxValue)
            maxValue = m_accumulationBuffer[i];
    }
    delete buffer;


    unsigned char* bits = (unsigned char*) m_target->constBits();
    for (int i=0; i < pixelCount; i++) {
        float norm = (float) m_accumulationBuffer[i] / maxValue;
        int v = log10(norm * 5.0 + 1.0) * 255;
        *bits++ = v; *bits++ = v; *bits++ = v;
    }

    setPixmap(QPixmap::fromImage(*m_target));
}
