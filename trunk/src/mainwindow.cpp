/***************************************************************************
 *   Copyright (C) 2007 by Lawrence Lee   *
 *   valheru@facticius.net   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
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
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainterPath>
#include "mainwindow.h"
#include "viewer.h"

MainWindow::MainWindow()
{
	viewer = new Viewer();
	setCentralWidget( viewer );
	file = new QMenu( tr( "&File" ), this );
	open = new QAction( tr( "&Open" ), file );
	exit = new QAction( tr( "&Exit" ), file );
	file->addAction( open );
	file->addSeparator();
	file->addAction( exit );
	menuBar()->addMenu( file );

	connect( exit, SIGNAL( triggered() ), this, SLOT( close() ) );
	connect( open, SIGNAL( triggered() ), this, SLOT( openDHWFile() ) );
}

MainWindow::~MainWindow()
{
	delete open;
	delete file;
}

void MainWindow::openDHWFile()
{
	QFileDialog fileDialog( this, tr( "Open DHW File" ), QDir::homePath(), tr( "DHW Files (*.DHW *.dhw)" ) );

	if( fileDialog.exec() ){
		DHWReader reader( fileDialog.selectedFiles().first() );
		drawDHWFileContents( &reader );
	}
}

void MainWindow::drawDHWFileContents( DHWReader *reader )
{
	QGraphicsScene *scene = new QGraphicsScene( 0.0, 0.0,
												static_cast<double>( reader->data()->paperWidth() ),
												static_cast<double>( reader->data()->paperWidth() ),
												viewer );
	QPainterPath *path = reader->data()->drawDHWData();
	scene->addPath( *path );
	viewer->getView()->setScene( scene );
	viewer->getView()->setGeometry( 0, 0, reader->data()->paperWidth(), reader->data()->paperHeight() );
	//viewer->getView()->scale( 0.1, 0.1 );
	qDebug( "View x size : %f", viewer->getView()->sceneRect().x() );
	qDebug( "View y size : %f", viewer->getView()->sceneRect().y() );
	qDebug( "Scene x size : %f", scene->sceneRect().x() );
	qDebug( "Scene y size : %f", scene->sceneRect().y() );
	qDebug( "Paper width : %d", reader->data()->paperWidth() );
	qDebug( "Paper height : %d", reader->data()->paperHeight() );
}

#include "mainwindow.moc"
