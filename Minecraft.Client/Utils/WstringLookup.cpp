
#include "../Build/stdafx.h"

#include "WstringLookup.h"

WstringLookup::WstringLookup()
{
	numIDs = 0;
}

std::wstring WstringLookup::lookup(uint32_t id)
{
	// TODO
	//if (id > currentMaxID)
	//	throw error

	return int2str.at(id);
}
	
uint32_t WstringLookup::lookup(std::wstring str)
{
	if (str2int.find(str) == str2int.end())
	{
		std::pair<std::wstring,uint32_t> p = 
			std::pair<std::wstring,uint32_t>(str, numIDs);

		str2int.insert( p );
		int2str.push_back( str );

		return numIDs++;
	}
	else
	{
		return str2int.at(str);
	}
}

void WstringLookup::getTable(std::wstring **lookup, uint32_t *len)
{
	// Outputs
	std::wstring *out_lookup; uint32_t out_len;

	// Fill lookup.
	out_lookup = new std::wstring[int2str.size()];
	for (uint32_t i = 0; i < numIDs; i++)
		out_lookup[i] = int2str.at(i);

	out_len = numIDs;

	// Return.
	*lookup = out_lookup;
	*len = out_len;
	return;
}