//
//  OLogger.cpp
//  logger_
//
//  Created by Francesco Ferrara on 21.11.11.
//  Copyright 2011 ETH Zürich. All rights reserved.
//

#include "OLogger.hpp"


// Standard constructor
OLogger::OLogger(){}

// Copy constructor
OLogger::OLogger( const OLogger & ologger )
{
	// Output stream
	oname = ologger.oname;
    
    // List
	olist = ologger.olist;
    
    // Number of columns
	ocols = ologger.ocols;
}

// Constructor with file name ( for either input or output )
OLogger::OLogger( const char * file_name )
{
	oname = string( file_name );
    
    cout << "\noutput_filename: " << oname << endl;
}

// Standard destructor
OLogger::~OLogger(){}

// Get data line
vector< double > OLogger::get_line( int line )
{
	// List iterator
    list< vector< double > >::iterator line_it = olist.begin();
    
    // Advance the iterator
    for ( int i = 0; i < line; i++ )
    {
        line_it++;
    }
    return *line_it;
}

// Operator =
OLogger & OLogger::operator=( const OLogger & ologger )
{
    // Output file
    oname = ologger.oname;
    olist = ologger.olist;
    ocols = ologger.ocols;
    
    return *this;
}

// Operator ()
double OLogger::operator()( int i, \
                            int j )
{
	// Check if the indices are negative
	if ( ( i < 0 ) || ( j < 0 ) )
	{
		cout << "\nNeither i nor j are allowed to be negative!\n";
		abort();
	}
    
	// Line vector
	vector< double > line;
    
	if ( i < ( int )olist.size() )
    {
        if ( j < ocols )
        {
            // Get the line
            line = get_line( i );
        }
        else
        {
            cout << "\nj > num_data_cols - 1!\n";
            abort();
        }
    }
    else
    {
        cout << "\ni > num_data_rows - 1!\n";
        abort();
    }
    return line[ j ];
}

// Get the size of a list
size_l OLogger::get_osize()
{
    // Temporary variable
    size_l size;
    
    // Get the rows
    size.rows = ( int )olist.size();
    
    // Get the columns
    list< vector< double > >::iterator i = olist.begin();
    size.cols = ( int )i->size();
            
    return size;
}

// Open a file
bool OLogger::open_file( ios_base::openmode open_mode )
{
	// Close the file
    close_file();
    
    // Open the file
    ofile.open( oname.c_str(), open_mode );
    
    // Return the value of the check if it is open
    return ofile.is_open();
}

// Close a file
void OLogger::close_file()
{
	// If the file is already open
    if ( ofile.is_open() )
    {
        // Clear the error flags
        ofile.clear( ios_base::goodbit );
        
        // Close the file
        ofile.close();
    }
}

// Write header
bool OLogger::write_header( const char * header )
{
	// Check if the file is open
	bool check = open_file( ios_base::out | ios_base::trunc );
    
	// Check if the file is open and there is a header to be written
	if ( ( check == true ) && ( strcmp( header, "no header" ) != 0 ) )
	{
		// Output the header
		ofile << header << endl;
        
		cout << "\nheader written successfully!\n";
	}
	else if ( ( check == true ) && ( strcmp( header, "no header" ) == 0 ) )
	{
		cout << "\nNo header to be written!\n";
	}
	else if ( check == false )
	{
		cout << "\nheader not written!\n";
	}
    
	// Close the file
	close_file();
    
	return check;
}

// Output the stream
void OLogger::output_stream( int precision )
{
	// Temporary variable
	vector< double > line;
    
	// Set the precision
	ofile.precision( precision );
    
	// Iterate through the list
	for ( list< vector< double > >::iterator i = olist.begin(); i != olist.end(); i++ )
	{
		// Get the line
		line = *i;
        
		// Iterate through the vector
		for ( int j = 0; j < ( int )( i->size() ); j++ )
		{
			ofile << line[ j ] << " ";
		}
		ofile << endl;
	}
}

// Write a log file
bool OLogger::write_log( const char * header, \
                       int precision )
{
	// Write the header
	write_header( header );
    
	// Check if the file is open
	bool check = open_file( ios_base::out | ios_base::app );
    
	// Abort if the output list is empty
	if ( olist.empty() )
	{
		cout << "\noutput_list is empty!\n";
		abort();
	}
    
	// Check if the file is open
	if ( check == true )
	{
		// Output the stream
		output_stream( precision );
	}
	else
	{
		cout << "\noutput_file is not open!\n";
		abort();
	}
	// Close the file
	close_file();
    
	return check;
}

// Set the number of data columns
int OLogger::set_cols( list< vector< double > > olist )
{
    // Get the iterator on the first line of the list
    list< vector< double > >::iterator i = olist.begin();
    
    return ( int )i->size();
}

// Set the output list
void OLogger::set_olist( const list< vector< double > > & olist )
{
    // Set the number of output columns
    set_cols( olist );
    
	this->olist = olist;
}