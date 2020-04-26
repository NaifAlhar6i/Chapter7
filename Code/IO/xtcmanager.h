#ifndef XTCMANAGER_H
#define XTCMANAGER_H

#include "gromanager.h"
#include "xdrfile_xtc.h"
#include <QObject>
#include <QFile>

class XTCManager : public QObject, public virtual MemoryManager
{
    Q_OBJECT
public:
    XTCManager(GROManager *gromanager);
    void FetchFrames(const unsigned int start, const unsigned int end, short stride = 0);

protected:

signals:
    void FrameFetched(uint, void *frame, QVector3D, QVector3D, QVector3D );

private:
    XDRFILE *m_XTC_Read;
    GROManager *m_GROManager;
    float PREC_XTC = 1000.0;

    inline XDRFILE *getXDRFile() { return m_XTC_Read; }
    inline GROManager *getGROManager() { return m_GROManager; }

    int moveToFirstFrame(unsigned int start , unsigned int atomsnumber);
    void closeXTC();
    void openXTC();
    void readFrames(const unsigned int &start, const unsigned int &end, short stride = 0);
    int readFrame(unsigned int atomsnumber , unsigned int &frameindex);
    int readUnSequenceFrames(unsigned int atomsnumber, int &currentframenumber, int end, int stride);
    int readSequencedFrames(unsigned int atomsnumber, int &currentframenumber, int end);
    int skipFrame(unsigned int atomsnumber );
    void computeFrameMinMaxBoundaries(QVector3D &minDimentions, QVector3D &maxDimentions, rvec *frame );
    void min(float &value1, float value2);
    void max(float &value1, float value2);
    float fAbs(float value );

};

#endif // XTCMANAGER_H
