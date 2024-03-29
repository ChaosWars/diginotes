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
#ifndef _VIEWER_H_
#define _VIEWER_H_

#include "ui_viewer.h"

class QMouseEvent;

class Viewer : public QWidget, Ui::Viewer
{
	public:
		Viewer( QWidget *parent = 0 );
		~Viewer();
		QGraphicsView* getView();
        void fitScene();
        int sceneWidth();
        int sceneHeight();
        void setSceneWidth( int width );
        void setSceneHeight( int height );

    private:
        int w, h;
};

#endif // _VIEWER_H_
