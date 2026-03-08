
#pragma once
#ifndef XMLMOJANGCALLBACK_H
#define XMLMOJANGCALLBACK_H
// xml reading

using namespace ATG;

class xmlMojangCallback : public ATG::ISAXCallback
{
public:
	virtual HRESULT  StartDocument() { return S_OK; };
	virtual HRESULT  EndDocument() { return S_OK; };

	virtual HRESULT  ElementBegin( CONST wchar_t* strName, uint32_t NameLen, CONST XMLAttribute *pAttributes, uint32_t NumAttributes )
	{
		wchar_t wTemp[35] = L"";
		wchar_t wAttName[32] = L"";
		wchar_t wNameXUID[32] = L"";
		wchar_t wNameSkin[32] = L"";
		wchar_t wNameCloak[32] = L"";
		PlayerUID xuid=0LL;


		if (NameLen >31)
			return S_FALSE;
		else
			wcsncpy( wAttName, strName, NameLen);

		if  ( _wcsicmp(wAttName,L"root") == 0)
		{
			return S_OK;
		}
		else if ( _wcsicmp(wAttName,L"data") == 0)
		{
			for(uint32_t i = 0; i < NumAttributes; i++)
			{
				wcsncpy_s( wAttName, pAttributes[i].strName, pAttributes[i].NameLen);
				if (_wcsicmp(wAttName,L"name")==0)
				{
					if (pAttributes[i].ValueLen <= 32)
						wcsncpy_s( wNameXUID, pAttributes[i].strValue, pAttributes[i].ValueLen);
				}
				else if (_wcsicmp(wAttName,L"xuid")==0)
				{
					if (pAttributes[i].ValueLen <= 32)
					{
						ZeroMemory(wTemp,sizeof(wchar_t)*35);
						wcsncpy_s( wTemp, pAttributes[i].strValue, pAttributes[i].ValueLen);
						xuid=_wcstoui64(wTemp,NULL,10);					
					}
				}
				else if (_wcsicmp(wAttName,L"cape")==0)
				{
					if (pAttributes[i].ValueLen <= 32)
					{
						wcsncpy_s( wNameCloak, pAttributes[i].strValue, pAttributes[i].ValueLen);
					}
				}
				else if (_wcsicmp(wAttName,L"skin")==0)
				{
					if (pAttributes[i].ValueLen <= 32)
					{
						wcsncpy_s( wNameSkin, pAttributes[i].strValue, pAttributes[i].ValueLen);
					}
				}

			}

			// if the xuid hasn't been defined, then we can't use the data
			if(xuid!=0LL)
			{
				return CConsoleMinecraftApp::RegisterMojangData(wNameXUID , xuid, wNameSkin, wNameCloak );
			}
			else return S_FALSE;
		}
		else
		{
			return S_FALSE;
		}
	};

	virtual HRESULT  ElementContent( CONST wchar_t *strData, uint32_t DataLen, BOOL More ) {    return S_OK;   };

	virtual HRESULT  ElementEnd( CONST wchar_t *strName, uint32_t NameLen ){       return S_OK;    };

	virtual HRESULT  CDATABegin( )  { return S_OK; };

	virtual HRESULT  CDATAData( CONST wchar_t *strCDATA, uint32_t CDATALen, BOOL bMore ){ return S_OK; };

	virtual HRESULT  CDATAEnd( ){ return S_OK; };

	virtual VOID     Error( HRESULT hError, CONST char *strMessage )    {     app.DebugPrintf("Error when Parsing xuids.XML\n");    };

};

class xmlDLCInfoCallback : public ATG::ISAXCallback
{
public:
	virtual HRESULT  StartDocument() { return S_OK; };
	virtual HRESULT  EndDocument() { return S_OK; };

	virtual HRESULT  ElementBegin( CONST wchar_t* strName, uint32_t NameLen, CONST XMLAttribute *pAttributes, uint32_t NumAttributes )
	{
		wchar_t wTemp[35] = L"";
		wchar_t wAttName[32] = L"";
		wchar_t wNameBanner[32] = L"";
		wchar_t wType[32] = L"";
		wchar_t wFirstSkin[32] = L"";
		wchar_t wDataFile[32] = L"";
		ULONGLONG ullFull=0ll;
		ULONGLONG ullTrial=0ll;
		int iGender=0;
		int iConfig=0;

		if (NameLen >31)
			return S_FALSE;
		else
			wcsncpy_s( wAttName, strName, NameLen);

		if  ( _wcsicmp(wAttName,L"root") == 0)
		{
			return S_OK;
		}
		else if ( _wcsicmp(wAttName,L"data") == 0)
		{
			for(uint32_t i = 0; i < NumAttributes; i++)
			{
				wcsncpy_s( wAttName, pAttributes[i].strName, pAttributes[i].NameLen);
				if (_wcsicmp(wAttName,L"Banner")==0)
				{
					if (pAttributes[i].ValueLen <= 32)
					{
						wcsncpy_s( wNameBanner, pAttributes[i].strValue, pAttributes[i].ValueLen);
					}
				}
				else if (_wcsicmp(wAttName,L"Full")==0)
				{
					if (pAttributes[i].ValueLen <= 32)
					{		
						ZeroMemory(wTemp,sizeof(wchar_t)*35);
						wcsncpy_s( wTemp, pAttributes[i].strValue, pAttributes[i].ValueLen);
						ullFull=_wcstoui64(wTemp,NULL,16);
					}
				}
				else if (_wcsicmp(wAttName,L"Trial")==0)
				{
					if (pAttributes[i].ValueLen <= 32)
					{
						ZeroMemory(wTemp,sizeof(wchar_t)*35);
						wcsncpy_s( wTemp, pAttributes[i].strValue, pAttributes[i].ValueLen);
						ullTrial=_wcstoui64(wTemp,NULL,16);					
					}
				}				
				else if (_wcsicmp(wAttName,L"FirstSkin")==0)
				{
					if (pAttributes[i].ValueLen <= 32)
					{
						wcsncpy_s( wFirstSkin, pAttributes[i].strValue, pAttributes[i].ValueLen);			
					}
				}	
				else if (_wcsicmp(wAttName,L"DataFile")==0)
				{
					if (pAttributes[i].ValueLen <= 32)
					{
						wcsncpy_s( wDataFile, pAttributes[i].strValue, pAttributes[i].ValueLen);			
					}
				}	
				else if (_wcsicmp(wAttName,L"Type")==0)
				{
					if (pAttributes[i].ValueLen <= 32)
					{
						wcsncpy_s( wType, pAttributes[i].strValue, pAttributes[i].ValueLen);			
					}
				}
				else if (_wcsicmp(wAttName,L"Gender")==0)
				{
					if (_wcsicmp(wAttName,L"Male")==0)
					{
						iGender=1;
					}
					else if (_wcsicmp(wAttName,L"Female")==0)
					{
						iGender=2;
					}
					else
					{
						iGender=0;
					}					
				}
				else if(_wcsicmp(wAttName,L"Config")==0)
				{
					if (pAttributes[i].ValueLen <= 32)
					{
						iConfig=_wtoi(wTemp);
					}
				}
			}

			// if the xuid hasn't been defined, then we can't use the data
			if(ullFull!=0LL)
			{
#ifdef _DEBUG
				wprintf(L"Type - %ls, Name - %ls, ",wType, wNameBanner);
#endif
				app.DebugPrintf("Full = %lld, Trial %lld\n",ullFull,ullTrial);

				return CConsoleMinecraftApp::RegisterDLCData(wType, wNameBanner , iGender, ullFull, ullTrial, wFirstSkin, iConfig, wDataFile );
			}
			else return S_FALSE;
		}
		else
		{
			return S_FALSE;
		}
	};

	virtual HRESULT  ElementContent( CONST wchar_t *strData, uint32_t DataLen, BOOL More ) {    return S_OK;   };

	virtual HRESULT  ElementEnd( CONST wchar_t *strName, uint32_t NameLen ){       return S_OK;    };

	virtual HRESULT  CDATABegin( )  { return S_OK; };

	virtual HRESULT  CDATAData( CONST wchar_t *strCDATA, uint32_t CDATALen, BOOL bMore ){ return S_OK; };

	virtual HRESULT  CDATAEnd( ){ return S_OK; };

	virtual VOID     Error( HRESULT hError, CONST char *strMessage )    {     app.DebugPrintf("Error when Parsing DLC.XML\n");    };

};

#endif