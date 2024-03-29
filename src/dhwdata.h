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
#ifndef _DHWDATA_H_
#define _DHWDATA_H_

#include <QList>
#include "stroke.h"

class QPainterPath;

class DHWData{
	public:
		DHWData( int file_version, int paper_width, int paper_height, int paper_type );
		~DHWData();
		void printDHWInfo();
		void printDHWData();
		void addStroke( Stroke *stroke );
		const int version();
		const int paperWidth();
		const int paperHeight();
		const int paperType();
		const QList<Stroke*> strokes();
		QPainterPath* drawDHWData();

	private:
		const int _file_version;
		const int _paper_width;
		const int _paper_height;
		const int _paper_type;
		QList<Stroke*> _strokes;
};

#endif	//_DHWDATA_H_
