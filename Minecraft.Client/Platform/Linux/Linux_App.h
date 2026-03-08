#pragma once

class CConsoleMinecraftApp : public CMinecraftApp
{
public:
	CConsoleMinecraftApp();

	virtual void SetRichPresenceContext(int iPad, int contextId);

	virtual void StoreLaunchData();
	virtual void ExitGame();
	virtual void FatalLoadError();

	virtual void CaptureSaveThumbnail();
	virtual void GetSaveThumbnail(uint8_t**,uint32_t*);
	virtual void ReleaseSaveThumbnail();
	virtual void GetScreenshot(int iPad,uint8_t* *pbData,uint32_t *pdwSize);

	virtual int LoadLocalTMSFile(wchar_t *wchTMSFile);
	virtual int LoadLocalTMSFile(wchar_t *wchTMSFile, eFileExtensionType eExt);

	virtual void FreeLocalTMSFiles(eTMSFileType eType);
	virtual int GetLocalTMSFileIndex(wchar_t *wchTMSFile,bool bFilenameIncludesExtension,eFileExtensionType eEXT=eFileExtensionType_PNG);

	// BANNED LEVEL LIST
	virtual void ReadBannedList(int iPad, eTMSAction action=(eTMSAction)0, bool bCallback=false) {}

	C4JStringTable *GetStringTable()																									{ return NULL;}

	// original code
	virtual void TemporaryCreateGameStart();
};

extern CConsoleMinecraftApp app;
