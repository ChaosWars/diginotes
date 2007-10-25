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
	fileDialog.setFileMode( QFileDialog::ExistingFile );

	if( fileDialog.exec() ){
		DHWReader reader( fileDialog.selectedFiles().first() );
		drawDHWFileContents( &reader );
	}
}

void MainWindow::drawDHWFileContents( DHWReader *reader )
{
	QGraphicsScene *scene = new QGraphicsScene( 0.0, 0.0,
												static_cast<double>( reader->data()->paperWidth() ),
												static_cast<double>( -reader->data()->paperHeight() ),
												viewer );
	QPainterPath *path = reader->data()->drawDHWData();
	scene->addPath( *path );
	viewer->getView()->setScene( scene );
}

#include "mainwindow.moc"