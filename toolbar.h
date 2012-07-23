#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QtGui/QToolBar>
#include <QAction>

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    QAction *backstepAction;
    QAction *backstepsAction;
    QAction *qbackstepsAction;
    QAction *forwardstepAction;
    QAction *forwardstepsAction;
    QAction *qforwardstepsAction;
    QAction *pauseAction;
    QAction *stopAction;
    QAction *finishAction;

public:
    explicit ToolBar(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // TOOLBAR_H
