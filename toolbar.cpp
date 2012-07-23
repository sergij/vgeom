#include "toolbar.h"

ToolBar::ToolBar( QWidget *parent) :
    QToolBar(parent)
{

    backstepAction = new QAction(tr("<"), this);
    backstepsAction = new QAction(tr("<<"), this);
    qbackstepsAction = new QAction(tr("<<<"), this);
    forwardstepAction = new QAction(tr(">"), this);
    forwardstepsAction = new QAction(tr(">>"), this);
    qforwardstepsAction = new QAction(tr(">>>"), this);
    pauseAction = new QAction(tr("||"), this);
    stopAction = new QAction(tr("X"), this);
    finishAction = new QAction(tr("|>"), this);

    addAction(finishAction);
    addAction(stopAction);

    addSeparator();

    addAction(qbackstepsAction);
    addAction(backstepsAction);
    addAction(backstepAction);
    addAction(pauseAction);
    addAction(forwardstepAction);
    addAction(forwardstepsAction);
    addAction(qforwardstepsAction);


}
