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
#include "stroke.h"

Stroke::Stroke()
{
}

Stroke::~Stroke()
{
}

void Stroke::addPoint( int x, int y )
{
	QPointF *p = new QPointF( x, y );
	_points.append( p );
}

void Stroke::addPoint( QPointF *point )
{
	_points.append( point );
}

void Stroke::printStroke()
{
	for( int i = 0; i < _points.size(); i++ ){
		qDebug("%f,%f", _points.at( i )->x(), _points.at( i )->y() );
	}
}

QList<QPointF*> Stroke::points()
{
	return _points;
}
