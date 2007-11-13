/***************************************************************************
 *   Copyright (C) 2007 by Lawrence Lee   *
 *   valheru@facticius.net   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <QMouseEvent>
#include <QGLWidget>
#include "viewer.h"

Viewer::Viewer( QWidget *parent ) : QWidget( parent )
{
	setupUi( this );
	graphicsView->setDragMode( QGraphicsView::RubberBandDrag );
    QGLWidget *glView = new QGLWidget();

    if( glView->isValid() ){
        graphicsView->setViewport( glView );
    }else{
        delete glView;
    }

    setSceneWidth( width() );
    setSceneHeight( height() );
}

Viewer::~Viewer()
{
}

QGraphicsView* Viewer::getView()
{
	return graphicsView;
}

void Viewer::fitScene()
{
    if( graphicsView->scene() ){
        graphicsView->fitInView( 0, 0, sceneWidth(), sceneHeight(), Qt::KeepAspectRatio );
    }
}

int Viewer::sceneWidth()
{
    return w;
}

int Viewer::sceneHeight()
{
    return h;
}

void Viewer::setSceneWidth( int width )
{
    w = width;
}

void Viewer::setSceneHeight( int height )
{
    h = height;
}
