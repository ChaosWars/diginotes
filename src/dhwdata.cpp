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

#include <QPainterPath>
#include "dhwdata.h"

DHWData::DHWData( int file_version, int paper_width, int paper_height, int paper_type )
				: _file_version(file_version), _paper_width(paper_width), _paper_height(paper_height), _paper_type(paper_type)
{
}

DHWData::~DHWData()
{
}

void DHWData::printDHWInfo()
{
	qDebug( "Version : %d", _file_version );
	qDebug( "Paper width : %d", _paper_width );
	qDebug( "Paper height : %d", _paper_height );
	qDebug( "Paper type : %d", _paper_type );
}

void DHWData::printDHWData()
{
	for( int i = 0; i < _strokes.size(); i++ ){
		_strokes.at( i )->printStroke();
	}
}

void DHWData::addStroke( Stroke *stroke )
{
	_strokes.append( stroke );
}

const int DHWData::version()
{
	return _file_version;
}

const int DHWData::paperWidth()
{
	return _paper_width;
}

const int DHWData::paperHeight()
{
	return _paper_height;
}

const int DHWData::paperType()
{
	return _paper_type;
}

const QList<Stroke*> DHWData::strokes()
{
	return _strokes;
}

QPainterPath* DHWData::drawDHWData()
{
	QPainterPath *newPath = new QPainterPath();

	for( int s = 0; s < _strokes.size(); s++ ){

		newPath->moveTo( *_strokes.at( s )->points().first() );

		for( int p = 0; p < _strokes.at( s )->points().size(); p++ ){
			newPath->lineTo( *_strokes.at( s )->points().at( p ) );
		}
	}
	
	return newPath;
}
