/********************************************************************************
** Form generated from reading ui file 'viewer.ui'
**
** Created: Thu Oct 25 07:25:09 2007
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_VIEWER_H
#define UI_VIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QWidget>
#include "digipad.h"

class Ui_Viewer
{
public:
    QGridLayout *gridLayout;
    Digipad *graphicsView;

    void setupUi(QWidget *Viewer)
    {
    if (Viewer->objectName().isEmpty())
        Viewer->setObjectName(QString::fromUtf8("Viewer"));
    Viewer->resize(658, 498);
    gridLayout = new QGridLayout(Viewer);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    graphicsView = new Digipad(Viewer);
    graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
    graphicsView->setMinimumSize(QSize(640, 480));
    graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    gridLayout->addWidget(graphicsView, 0, 0, 1, 1);


    retranslateUi(Viewer);

    QMetaObject::connectSlotsByName(Viewer);
    } // setupUi

    void retranslateUi(QWidget *Viewer)
    {
    Viewer->setWindowTitle(QApplication::translate("Viewer", "Viewer", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Viewer);
    } // retranslateUi

};

namespace Ui {
    class Viewer: public Ui_Viewer {};
} // namespace Ui

#endif // UI_VIEWER_H
