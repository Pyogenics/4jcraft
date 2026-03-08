#pragma once



class WstringLookup
{
private:
	uint32_t numIDs;
	std::unordered_map<std::wstring, uint32_t> str2int;
	std::vector<std::wstring> int2str;

public:
	WstringLookup();

	std::wstring lookup(uint32_t id);
	
	uint32_t lookup(std::wstring);

	VOID getTable(std::wstring **lookup, uint32_t *len);
};