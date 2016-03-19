#pragma once
#include "TablePair.hpp"

class EntryTable
{
public:
	EntryTable();
	~EntryTable();
private:
	std::vector<TablePair> tablePairs;

};

