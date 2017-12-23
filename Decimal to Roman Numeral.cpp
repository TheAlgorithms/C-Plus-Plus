//This Function Returns a string after Converting an integer in the range [1,4000) to a Roman numeral



//This functions fills a string with character c, n times and returns it
string fill( char c, int n )
{
    string s;
    while( n-- ) s += c;
    return s;
}

//to convert to lowercase Roman Numeral

string toRoman( int n )
{
    if( n < 4 ) return fill( 'i', n );
    if( n < 6 ) return fill( 'i', 5 - n ) + "v";
    if( n < 9 ) return string( "v" ) + fill( 'i', n - 5 );
    if( n < 11 ) return fill( 'i', 10 - n ) + "x";
    if( n < 40 ) return fill( 'x', n / 10 ) + toRoman( n % 10 );
    if( n < 60 ) return fill( 'x', 5 - n / 10 ) + 'l' + toRoman( n % 10 );
    if( n < 90 ) return string( "l" ) + fill( 'x', n / 10 - 5 ) + toRoman( n % 10 );
    if( n < 110 ) return fill( 'x', 10 - n / 10 ) + "c" + toRoman( n % 10 );
    if( n < 400 ) return fill( 'c', n / 100 ) + toRoman( n % 100 );
    if( n < 600 ) return fill( 'c', 5 - n / 100 ) + 'd' + toRoman( n % 100 );
    if( n < 900 ) return string( "d" ) + fill( 'c', n / 100 - 5 ) + toRoman( n % 100 );
    if( n < 1100 ) return fill( 'c', 10 - n / 100 ) + "m" + toRoman( n % 100 );
    if( n < 4000 ) return fill( 'm', n / 1000 ) + toRoman( n % 1000 );

}

//to convert to uppercase Roman Numeral

string toRoman( int n )
{
    if( n < 4 ) return fill( 'I', n );
    if( n < 6 ) return fill( 'I', 5 - n ) + "V";
    if( n < 9 ) return string( "V" ) + fill( 'I', n - 5 );
    if( n < 11 ) return fill( 'I', 10 - n ) + "X";
    if( n < 40 ) return fill( 'X', n / 10 ) + toRoman( n % 10 );
    if( n < 60 ) return fill( 'X', 5 - n / 10 ) + 'L' + toRoman( n % 10 );
    if( n < 90 ) return string( "L" ) + fill( 'X', n / 10 - 5 ) + toRoman( n % 10 );
    if( n < 110 ) return fill( 'X', 10 - n / 10 ) + "C" + toRoman( n % 10 );
    if( n < 400 ) return fill( 'C', n / 100 ) + toRoman( n % 100 );
    if( n < 600 ) return fill( 'C', 5 - n / 100 ) + 'D' + toRoman( n % 100 );
    if( n < 900 ) return string( "D" ) + fill( 'C', n / 100 - 5 ) + toRoman( n % 100 );
    if( n < 1100 ) return fill( 'C', 10 - n / 100 ) + "M" + toRoman( n % 100 );
    if( n < 4000 ) return fill( 'M', n / 1000 ) + toRoman( n % 1000 );
}
