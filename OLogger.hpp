//
//  OLogger.hpp
//  logger
//
//  Created by Francesco Ferrara on 21.11.11.
//  Copyright 2011 ETH Zürich. All rights reserved.
//

#ifndef logger_OLogger_hpp
#define logger_OLogger_hpp


#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <vector>
#include <string>

// TODO: Remove
#include "ILogger.hpp"


using namespace std;


// Define a data type for the size of a list
/*typedef struct
{
    int rows, cols;
}size_l;*/

class OLogger
{
	// Output stream
	ofstream ofile;
    
    // File name
    string oname;
    
    // List
	list< vector< double > > olist;
    
    // Number of columns
	int ocols;
    
    // Size of the list
    size_l osize;
    
	// Get data line
	vector< double > get_line( int line );
    
	// Open a file
	bool open_file( ios_base::openmode open_mode );
    
	// Close a file
	void close_file();
    
	// Write header
	bool write_header( const char * header );
    
	// Output the stream
	void output_stream( int precision );
    
    // Set the number of data columns
    int set_cols( list< vector< double > > output_list );
    
public:
	// Standard constructor
	OLogger();
    
	// Copy constructor
	OLogger( const OLogger & ologger );
    
	// Constructor with file name ( for either input or output )
	OLogger( const char * file_name );
    
	// Standard destructor
	~OLogger();
    
	// Operator =
	OLogger & operator=( const OLogger & ologger );
    
	// Operator ()
	double operator()( int i, \
                       int j );
    
    // Get the size of a list
    size_l get_osize();
    
	// Write a log file
	bool write_log( const char * header, \
                    int precision );
    
	// Set the output list
	void set_olist( const list< vector< double > > & olist );
};


#endif
