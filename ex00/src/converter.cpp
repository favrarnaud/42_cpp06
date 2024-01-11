#include "../include/converter.hpp"

converter::converter( void ) {
	this->_c = '\0';
	this->_n = 0;
	this->_f = 0.0f;
	this->_d = 0.0;
}

converter::converter( const converter& src ) {
	*this = src;
}

converter::~converter( void ) {}

converter& converter::operator=( const converter& rhs ) {
	if ( this != &rhs ) {
		this->_n = rhs.getI();
		this->_f = rhs.getF();
		this->_c = rhs.getC();
	}
	return *this;
}

char    converter::getC( void ) const {
	return this->_c;
}

void    converter::setC( char c ) {
	this->_c = c;
}

bool    converter::isLiterals( void ) const {
	if ( ( _impossible ) || ( _str.compare( "nan" ) == 0 ) || ( _str.compare( "nanf" ) == 0 )
		 || ( _str.compare( "+inf" ) == 0 ) || ( _str.compare( "+inff" ) == 0 )
		 || ( _str.compare( "-inf" ) == 0 ) || ( _str.compare( "-inff" ) == 0 )
		 || ( _str.compare( "-inff" ) == 0 ) || ( _str.compare( "-inff" ) == 0 )
		 || ( _str.compare( "+inff" ) == 0 ) || ( _str.compare( "+inff" ) == 0 ) ) {
		return true;
	}
	return false;
}

void    converter::printChar( void ) const {
	if ( this->isLiterals() || ( !std::isprint( _n ) && ( _n >= 127 ) ) ) {
		std::cout << "Impossible";
	} else if ( !std::isprint( this->_n ) ) {
		std::cout << "None displayable";
	} else {
		std::cout << "'" << getC() << "'";
	}
	std::cout << std::endl;
}

int    converter::getI( void ) const {
	return this->_n;
}

void    converter::setI( int n ) {
	this->_n = n;
}

void    converter::printInt( void ) const {
	if ( this->isLiterals() || ( !std::isprint( _n ) && ( _n >= 127 ) ) ) {
		std::cout << "Impossible";
	} else {
		std::cout << getI();
	}
	std::cout << std::endl;
}

float   converter::getF( void ) const {
	return this->_f;
}

void    converter::setF( float f ) {
	this->_f = f;
}

double  converter::getD( void ) const {

	return this->_d;
}

void    converter::setD( double d ) {
	this->_d = d;
}

std::string converter::getStr( void ) const {
	return this->_str;
}

void converter::setStr( std::string str ) {
	this->_str = str;
	this->setType();
	if ( getType() == NONE ) {
		throw converter::ConverterException();
	}
}

e_type  converter::getType( void ) const {
	return this->_type;
}

bool    converter::isChar( void ) const {
	return _str.length() == 1 && std::isalpha( _str[0] ) && std::isprint( _str[0] );
}

bool    converter::isInt( void ) const {
	int    j = 0;
	if ( _str[j] == '-' || _str[j] == '+' )
		j++;
	for ( int i( j ); i < ( int ) _str.length(); i++ ) {
		if ( !std::isdigit( _str[i] ) )
			return false;
	}
	return true;
}

bool converter::isDouble( void ) const {

	if ( _str.find( '.' ) == std::string::npos || _str.find( '.' ) == 0
		 || _str.find( '.' ) == _str.length() - 1 )
		return false;
	int j = 0;
	int found = 0;
	if ( _str[j] == '-' || _str[j] == '+' )
		j++;
	for ( int i( j ); i < ( int ) _str.length(); i++ ) {
		if ( _str[i] == '.' )
			found++;
		if ( ( !std::isdigit( _str[i] ) && _str[i] != '.' ) || found > 1 )
			return false;
	}

	return true;
}

bool    converter::isFloat ( void ) const {

	if ( _str.find( '.' ) == std::string::npos || _str.back() != 'f'
		 || _str.find( '.' ) == 0 || _str.find( '.' ) == _str.length() - 2 )
		return false;
	int found = 0;
	int j = 0;
	if ( _str[j] == '-' || _str[j] == '+' )
		j++;
	for ( int i( j ); i < ( int ) _str.length() - 1; i++ ) {
		if ( _str[i] == '.' )
			found++;
		if ( ( !std::isdigit( _str[i] ) && _str[i] != '.' ) || found > 1 )
			return false;
	}

	return true;
}

void    converter::printFloat( void ) const {
	if ( _str.compare( "nan" ) == 0 || _str.compare( "nanf" ) == 0 ) {
		std::cout << "nanf";
	} else if ( _str.compare( "+inff" ) == 0 || _str.compare( "+inf" ) == 0 ) {
		std::cout << "+inff";
	} else if ( _str.compare( "-inff" ) == 0 || _str.compare( "-inf" ) == 0 ) {
		std::cout << "-inff";
	} else if ( _impossible ) {
		std::cout << "Impossible";
	} else {
		if ( _f - static_cast< int > ( _f ) == 0 ) {
			std::cout << _f << ".0f";
		} else {
			std::cout << getF() << "f";
		}
	}
	std::cout << std::endl;
}

void    converter::printDouble( void ) const {
	if ( _str.compare( "nan" ) == 0 || _str.compare( "nanf" ) == 0 ) {
		std::cout << "nan";
	} else if ( _str.compare( "+inff" ) == 0 || _str.compare( "+inf" ) == 0 ) {
		std::cout << "+inf";
	} else if ( _str.compare( "-inff" ) == 0 || _str.compare( "-inf" ) == 0 ) {
		std::cout << "-inf";
	} else if ( _impossible ) {
		std::cout << "Impossible";
	} else {
		if ( _d - static_cast< int > ( _d ) == 0 ) {
			std::cout << _d << ".0";
		} else {
			std::cout << getD() << "f";
		}
	}
	std::cout << std::endl;

}

void    converter::setType( void ) {
	if ( isChar() ) {
		_type = CHAR;
	} else if ( isInt() ) {
		_type = INT;
	} else if ( isFloat() ) {
		_type = FLOAT;
	} else if ( isDouble() ) {
		_type = DOUBLE;
	} else if ( isLiterals() ) {
		_type = LITERALS;
	} else {
		_type = NONE;
	}
}

bool    converter::isImpossible( void ) {
	try
	{
		if ( _type == INT ) {
			_n = std::stoi( _str );
		} else if ( _type == FLOAT ) {
			_f = std::stof( _str );
		} else if ( _type == DOUBLE ) {
			_d = std::stod( _str );
		}
	}
	catch ( std::exception& e )
	{
		_impossible = true;
		return true;
	}
	return false;
}

void    converter::convert( void ) {
	if ( isImpossible() )
		return;
	switch ( _type ) {
		case CHAR:
			_c = _str[0];
			_n = static_cast< int >( _c );
			_f = static_cast< float >( _c );
			_d = static_cast< double >( _c );
			break;
		case INT:
			_n = std::stoi( _str );
			_f = static_cast< float >( _n );
			_d = static_cast< double >( _n );
			_c = static_cast< char >( _n );
			break;
		case FLOAT:
			_f = std::stof( _str );
			_n = static_cast< int >( _f );
			_d = static_cast< double >( _f );
			_c = static_cast< char >( _f );
			break;
		case DOUBLE:
			_d = std::stod( _str );
			_n = static_cast< int >( _d );
			_f = static_cast< float >( _d );
			_c = static_cast< char >( _d );
			break;
		default:
			break;
	}
}

std::ostream&    operator<<( std::ostream& out, const converter& rhs ) {
	out << "char: "; rhs.printChar();
	out << "int: "; rhs.printInt();
	out << "float: "; rhs.printFloat();
	out << "double: "; rhs.printDouble();
	return out;
}