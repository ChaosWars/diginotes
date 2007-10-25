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

#include <QFile>
#include <QDataStream>
#include "dhwreader.h"
#include "dhwdata.h"

const QString SIGNATURE( "ACECAD_DIGIMEMO_HANDWRITING_____" );
const uchar PENDOWNMASK = 0x01;
const uchar TIMESTAMPMASK = 0x88;
const uchar ENDOFLAYERMASK = 0x90;
const uchar COORDINATEMASK = 0x80;

DHWReader::DHWReader( QString dhwFile )
{
	_data = NULL;
	file = new QFile( dhwFile );

	if( !file->open( QIODevice::ReadOnly ) ){
		qDebug( "Failed to open file." );
		//throw( DHWReaderError( DHW_READER_ERROR::OPEN_FILE_FAIL, file->error() ) );
	}

	_stream = new QDataStream( file );

	if( verifyDHWFileSignature( _stream ) ){
		readHeader( _stream );
		readBody( _stream );
	}else{
		qDebug( "Invalid file." );
		//throw( DHWReaderError( DHW_READER_ERROR::INVALID_HEADER ) );
	}
	
	file->close();
}

DHWReader::~DHWReader()
{
	delete _stream;

	if( file->isOpen() )
		file->close();
	
	delete file;
	delete _data;
	
}

DHWData* DHWReader::data()
{
	return _data;
}

bool DHWReader::verifyDHWFileSignature( QDataStream *stream )
{
	bool check = true;
	int len = 32;
	qint8 c;
	QByteArray signature;
	
	for( int i = 0; i < len; i++ ){
		*stream >> c;
		signature.append( static_cast<char>( c ) );
	}

	if( qstrcmp( SIGNATURE.toLatin1(), signature ) != 0 ){
		qDebug( "DHW signature not found. Signature read from file : %s", signature.data() );
		return false;
	}

	return check;

}

void DHWReader::readHeader( QDataStream *stream )
{
	qint8 file_version;
	qint8 paper_width_a;
	qint8 paper_width_b;
	qint8 paper_height_a;
	qint8 paper_height_b;
	qint8 paper_type;
	qint16 skip;
	*stream >> file_version;
	*stream >> paper_width_a;
	*stream >> paper_width_b;
	*stream >> paper_height_a;
	*stream >> paper_height_b;
	*stream >> paper_type;
	//Skip two bytes
	*stream >> skip;
	_data = new DHWData( static_cast<int>( file_version ),
						 static_cast<int>( paper_width_a + ( paper_width_b << 8 ) ),
						 static_cast<int>( paper_height_a + ( paper_height_b << 8 ) ),
					     static_cast<int>( paper_type ) );
}

void DHWReader::readBody( QDataStream *stream )
{
	quint8 currentByte;
	Stroke *currentStroke = new Stroke();
	*stream >> currentByte;
	//qDebug("Beginning read");
	
	while( !stream->atEnd() ){
		*stream >> currentByte;

		if( ( currentByte & ~7 ) == COORDINATEMASK ){

			if( ( currentByte & PENDOWNMASK ) == 1 ){
				currentStroke = new Stroke();
				//qDebug("New stroke");
			}else{
				_data->addStroke( currentStroke );
				//qDebug("Adding stroke");
			}

		}else if( currentByte == TIMESTAMPMASK ){
			*stream >> currentByte;
			//qDebug("Time stamp");
		}else if( currentByte ==  ENDOFLAYERMASK ){
			*stream >> currentByte;
			//qDebug("End of layer");
		}else if( !(currentByte & ~0x7f) == 1 ){
			qint8 x1, x2, y1, y2;
			x1 = currentByte;
			*stream >> x2;
			*stream >> y1;
			*stream >> y2;
			int x = interpretCoordinate( x1, x2 );
			int y = -interpretCoordinate( y1, y2 );
			//qDebug("Coordinate %d,%d read", x, y );
			currentStroke->addPoint( x, y );
		}else{
			qDebug("Unknown byte read.");
		}

	}

	//qDebug("Read finished.");

	//_data->printDHWInfo();
	//_data->printDHWData();
}

int DHWReader::interpretCoordinate( qint8 first, qint8 second )
{
	return static_cast<int>( first + ( second << 7 ) );
}

