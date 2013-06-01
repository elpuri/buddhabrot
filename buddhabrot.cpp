#include "buddhabrot.h"
#include <stdlib.h>
#include <QDebug>

#define ORBITS_PER_UPDATE 1000000

#define random() ((float) rand() / RAND_MAX)

Buddhabrot::Buddhabrot(QObject* receiver, float crMin, float crMax, float ciMin, float ciMax,
                       int w, int h, int maxIterations)
{
    m_receiver = receiver;
    m_ciMin = ciMin;
    m_ciMax = ciMax;
    m_crMin = crMin;
    m_crMax = crMax;
    m_w = w;
    m_h = h;
    m_maxIterations = maxIterations;
    m_accumulationBuffer = new unsigned short[w * h];
    m_orbit = new int[maxIterations];
}

void Buddhabrot::run()
{
    float rScale, iScale;
    rScale = m_crMax - m_crMin;
    iScale = m_ciMax - m_ciMin;
    int bufferSize = m_w * m_h;

    while (1) {
        memset(m_accumulationBuffer, 0, bufferSize * sizeof(unsigned short));
        for (int i=0; i < ORBITS_PER_UPDATE; i++) {
            // Randomize a new point on the source plane
            float cr = m_crMin + random() * rScale;
            float ci = m_ciMin + random() * iScale;
            bool escaped = false;
            float zr = 0;
            float zi = 0;
            int iteration = 0;
            // Iterate mandelbrot
            while (!escaped && iteration < m_maxIterations) {
                float zrSq = zr * zr;
                float ziSq = zi * zi;
                float temp = zrSq - ziSq + cr;
                zi = 2.0 * zr * zi + ci;
                zr = temp;

                // Calculate where this point is in our buffer
                int y = (zr - m_crMin) / rScale * m_h;
                int x = (zi - m_ciMin) / iScale * m_w;

                if (x < 0 || x >= m_w || y < 0 || y >= m_h)
                    m_orbit[iteration] = -1;
                else
                    m_orbit[iteration] = y * m_w + x;

                if (zrSq + ziSq > 4.0)
                    escaped = true;
                iteration++;
            }

            // If the orbit escaped add it to the accumulation buffer
            if (escaped) {
                for (int i=0; i < iteration; i++) {
                    int index = m_orbit[i];
                    if (i != -1)
                        m_accumulationBuffer[m_orbit[i]]++;
                }
            }
        }

        unsigned short* buf = new unsigned short[bufferSize];
        memcpy(buf, m_accumulationBuffer,  bufferSize * sizeof(unsigned short));
        QMetaObject::invokeMethod(m_receiver, "onDataAvailable", Qt::QueuedConnection, Q_ARG(void*, buf));
    }
}
