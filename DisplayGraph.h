#ifndef ATC_DISPLAYGRAPH_H
#define ATC_DISPLAYGRAPH_H

#include "Display.h"

#ifdef ATC_DISPLAY_GRAPH

#define ATC_MODE_GRAPH1 0
#define ATC_MODE_GRAPH2 1

#include <U8glib.h>

class DisplayGraph : public Display {
protected:
    U8GLIB *mGraph;
    char mBuf[12];

    virtual void nextMode();
    virtual void setMode(uint8_t aMode);

    void drawMode1();
    void drawMode2();

public:
    DisplayGraph(uint8_t aPinKey1, uint8_t aPinKey2, uint8_t aPinTerm, uint8_t aSizeTerm=10);
    virtual ~DisplayGraph() {}

    virtual void init();
    virtual void draw();
};

#endif

#endif //ATC_DISPLAYGRAPH_H
