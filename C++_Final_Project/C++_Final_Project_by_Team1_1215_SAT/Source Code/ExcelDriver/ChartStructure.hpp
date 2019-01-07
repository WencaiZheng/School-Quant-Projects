// ChartStructure.hpp
// 
// Simple class to store essential information about a 
// two d chart for Excel:
//
//		Actual data: Vector
//		Chart title
//		Horizontal and vertical texts
//		Legend text (describes the meaning of the chart line)
//
// NB: All code is inline and we use struct (all public members).
// It is more like a record than a class.
//
// (C) Datasim Education BV 2005
//

#ifndef ChartStructure_HPP
#define ChartStructure_HPP

#include <string>
#include <list>
#include <iostream>
#include "VectorsAndMatrices\Vector.cpp"
using namespace std;

struct ChartStructure
{
		// Optimise later to work with pointers (get it right)
		Vector<double, long> xdata;
		Vector<double, long> ydata;

		string title;
		string horizontal;
		string vertical;
		string legend;

		// Default constructor, default text only
		ChartStructure()
		{
			
			title = string("Title");
			horizontal = string("X axis");
			vertical = string("Y axis");
			legend = string("Legend");
		}

		void print() const
		{
			cout << title << ", " << horizontal << ", " << vertical 
				 << ", " << legend << endl;
		}

};

typedef list<ChartStructure> ChartStructureList;

#endif
