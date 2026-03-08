#include "stdafx.h"
#ifndef __PS3__
//#include <compressapi.h>
#endif // __PS3__

#ifdef __PS3__
#include "../Platform/PS3/Sentient/SentientManager.h"
#include "../GameState/StatsCounter.h"
#include "../Platform/PS3/Social/SocialManager.h"
#include <libsn.h>
#include <libsntuner.h>
#elif defined _DURANGO
#include "../Platform/Durango/Sentient/SentientManager.h"
#include "../GameState/StatsCounter.h"
#include "../Platform/Durango/Social/SocialManager.h"
#include "../Platform/Durango/Sentient/DynamicConfigurations.h"
#include "../Platform/Durango/DurangoExtras/xcompress.h"
#elif defined _WINDOWS64
#include "../Platform/Windows64/Sentient/SentientManager.h"
#include "../GameState/StatsCounter.h"
#include "../Platform/Windows64/Social/SocialManager.h"
#include "../Platform/Windows64/Sentient/DynamicConfigurations.h"
#elif defined __PSVITA__
#include "../Platform/PSVita/Sentient/SentientManager.h"
#include "../GameState/StatsCounter.h"
#include "../Platform/PSVita/Social/SocialManager.h"
#include "../Platform/PSVita/Sentient/DynamicConfigurations.h"
#include <libperf.h>
#elif defined __linux__
// On Linux, stdafx.h already provides Orbis-compatible Sentient/Dynamic headers
// via #pragma once. Pull in SentientManager for CSentientManager class declaration
// and StatsCounter; CSocialManager is provided as inline stubs via Platform/Linux/Social/SocialManager.h.
#include "../Platform/Orbis/Sentient/SentientManager.h"
#include "../GameState/StatsCounter.h"
#else
#include "../Platform/Orbis/Sentient/SentientManager.h"
#include "../GameState/StatsCounter.h"
#include "../Platform/Orbis/Social/SocialManager.h"
#include "../Platform/Orbis/Sentient/DynamicConfigurations.h"
#endif

#if !defined(__PS3__) && !defined(__ORBIS__) && !defined(__PSVITA__)
#ifdef _WINDOWS64
//C4JStorage StorageManager;
C_4JProfile ProfileManager;
#endif
#endif // __PS3__
CSentientManager SentientManager;
#ifndef __linux__
// On Linux this global shadows the project's StringTable class name in unity builds
CXuiStringTable StringTable;
#endif

#if !defined(_XBOX_ONE) && !defined(__linux__)
ATG::XMLParser::XMLParser() {}
ATG::XMLParser::~XMLParser() {}
HRESULT    ATG::XMLParser::ParseXMLBuffer( CONST char* strBuffer, uint32_t uBufferSize ) { return S_OK; }   
void ATG::XMLParser::RegisterSAXCallbackInterface( ISAXCallback *pISAXCallback ) {}
#endif

#ifndef __linux__
bool	CSocialManager::IsTitleAllowedToPostAnything() { return false; }
bool	CSocialManager::AreAllUsersAllowedToPostImages() { return false; }
bool	CSocialManager::IsTitleAllowedToPostImages() { return false; }

bool	CSocialManager::PostLinkToSocialNetwork( ESocialNetwork eSocialNetwork, uint32_t dwUserIndex, bool bUsingKinect ) { return false; }
bool	CSocialManager::PostImageToSocialNetwork( ESocialNetwork eSocialNetwork, uint32_t dwUserIndex, bool bUsingKinect ) { return false; }
CSocialManager *CSocialManager::Instance() { return NULL; }
void CSocialManager::SetSocialPostText(const wchar_t* Title, const wchar_t* Caption, const wchar_t* Desc) {};
#endif // !__linux__

uint32_t XShowPartyUI(uint32_t dwUserIndex) { return 0; }
uint32_t XShowFriendsUI(uint32_t dwUserIndex) { return 0; }
HRESULT XPartyGetUserList(XPARTY_USER_LIST *pUserList) { return S_OK; }
uint32_t XContentGetThumbnail(uint32_t dwUserIndex, const XCONTENT_DATA *pContentData,  uint8_t* pbThumbnail,  uint32_t* pcbThumbnail,  PXOVERLAPPED *pOverlapped) { return 0; }
void XShowAchievementsUI(int i) {}
uint32_t XBackgroundDownloadSetMode(XBACKGROUND_DOWNLOAD_MODE Mode) { return 0; }

#ifndef _DURANGO
void PIXAddNamedCounter(int a, const char *b, ...) {}
//#define PS3_USE_PIX_EVENTS 
//#define PS4_USE_PIX_EVENTS 
void PIXBeginNamedEvent(int a, const char *b, ...)
{
#ifdef PS4_USE_PIX_EVENTS
	char buf[512];
    va_list args;
    va_start(args,b);
    vsprintf(buf,b,args);
	sceRazorCpuPushMarker(buf, 0xffffffff, SCE_RAZOR_MARKER_ENABLE_HUD);

#endif
#ifdef PS3_USE_PIX_EVENTS
	char buf[256];
	wchar_t wbuf[256];
    va_list args;
    va_start(args,b);
    vsprintf(buf,b,args);
	snPushMarker(buf);

// 	mbstowcs(wbuf,buf,256);
// 	RenderManager.BeginEvent(wbuf);
    va_end(args);
#endif
}
#if 0//__PSVITA__
	if( PixDepth < 64 )
	{
		char buf[512];
		va_list args;
		va_start(args,b);
		vsprintf(buf,b,args);
		sceRazorCpuPushMarkerWithHud(buf, 0xffffffff, SCE_RAZOR_MARKER_ENABLE_HUD);
	}
	PixDepth += 1;
#endif


void PIXEndNamedEvent()
{
#ifdef PS4_USE_PIX_EVENTS
	sceRazorCpuPopMarker();
#endif
#ifdef PS3_USE_PIX_EVENTS
	snPopMarker();
// 	RenderManager.EndEvent();
#endif
#if 0//__PSVITA__
	if( PixDepth <= 64 )
	{
		sceRazorCpuPopMarker();
	}
	PixDepth -= 1;
#endif
}
void PIXSetMarkerDeprecated(int a, char *b, ...) {}
#else
// 4J Stu - Removed this implementation in favour of a macro that will convert our string format
// conversion at compile time rather than at runtime
//void PIXBeginNamedEvent(int a, char *b, ...)
//{
//	char buf[256];
//	wchar_t wbuf[256];
//	va_list args;
//	va_start(args,b);
//	vsprintf(buf,b,args);
//
//	mbstowcs(wbuf,buf,256);
//	PIXBeginEvent(a,wbuf);
//}
//
//void PIXEndNamedEvent()
//{
//	PIXEndEvent();
//}
//
//void PIXSetMarkerDeprecated(int a, char *b, ...)
//{
//	char buf[256];
//	wchar_t wbuf[256];
//	va_list args;
//	va_start(args,b);
//	vsprintf(buf,b,args);
//
//	mbstowcs(wbuf,buf,256);
//	PIXSetMarker(a, wbuf);
//}
#endif

// void *D3DXBUFFER::GetBufferPointer() { return NULL; }
// int D3DXBUFFER::GetBufferSize() { return 0; }
// void D3DXBUFFER::Release() {}

// #ifdef _DURANGO
// void GetLocalTime(SYSTEMTIME *time) {}
// #endif


bool IsEqualXUID(PlayerUID a, PlayerUID b)
{
#if defined(__PS3__) || defined(__ORBIS__) || defined (__PSVITA__) || defined(_DURANGO)
	return (a == b);
#else
	return false;
#endif
}

void XMemCpy(void *a, const void *b, size_t s) { memcpy(a, b, s); }
void XMemSet(void *a, int t, size_t s) { memset(a, t, s); }
void XMemSet128(void *a, int t, size_t s) { memset(a, t, s); }
void *XPhysicalAlloc(size_t a, uintptr_t  b, uintptr_t c, uint32_t d) { return malloc(a); }
void XPhysicalFree(void *a) { free(a); }

D3DXVECTOR3::D3DXVECTOR3() {}
D3DXVECTOR3::D3DXVECTOR3(float x,float y,float z) : x(x), y(y), z(z) {}
D3DXVECTOR3& D3DXVECTOR3::operator += ( CONST D3DXVECTOR3& add ) { x += add.x; y += add.y; z += add.z; return *this; }

uint8_t IQNetPlayer::GetSmallId() { return 0; }
void IQNetPlayer::SendData(IQNetPlayer *player, const void *pvData, uint32_t dwDataSize, uint32_t dwFlags)
{
#ifndef __linux__
	app.DebugPrintf("Sending from 0x%x to 0x%x %d bytes\n",this,player,dwDataSize);
#endif
}
bool IQNetPlayer::IsSameSystem(IQNetPlayer *player) { return true; }
uint32_t IQNetPlayer::GetSendQueueSize( IQNetPlayer *player, uint32_t dwFlags ) { return 0; }
uint32_t IQNetPlayer::GetCurrentRtt() { return 0; }
bool IQNetPlayer::IsHost() { return this == &IQNet::m_player[0]; }
bool IQNetPlayer::IsGuest() { return false; }
bool IQNetPlayer::IsLocal() { return true; }
PlayerUID IQNetPlayer::GetXuid() { return INVALID_XUID; }
const wchar_t* IQNetPlayer::GetGamertag() { static const wchar_t *test = L"stub"; return test; }
int IQNetPlayer::GetSessionIndex() { return 0; }
bool IQNetPlayer::IsTalking() { return false; }
bool IQNetPlayer::IsMutedByLocalUser(uint32_t dwUserIndex) { return false; }
bool IQNetPlayer::HasVoice() { return false; }
bool IQNetPlayer::HasCamera() { return false; }
int IQNetPlayer::GetUserIndex() { return this - &IQNet::m_player[0]; }
void IQNetPlayer::SetCustomDataValue(uintptr_t ulpCustomDataValue) {
	m_customData = ulpCustomDataValue;
}
uintptr_t IQNetPlayer::GetCustomDataValue() {
	return m_customData;
}

IQNetPlayer IQNet::m_player[4];

bool _bQNetStubGameRunning = false;

HRESULT IQNet::AddLocalPlayerByUserIndex(uint32_t dwUserIndex){ return S_OK; }
IQNetPlayer *IQNet::GetHostPlayer() { return &m_player[0]; }
IQNetPlayer *IQNet::GetLocalPlayerByUserIndex(uint32_t dwUserIndex) { return &m_player[dwUserIndex]; } 
IQNetPlayer *IQNet::GetPlayerByIndex(uint32_t dwPlayerIndex) { return &m_player[0]; }
IQNetPlayer *IQNet::GetPlayerBySmallId(uint8_t SmallId){ return &m_player[0]; }
IQNetPlayer *IQNet::GetPlayerByXuid(PlayerUID xuid){ return &m_player[0]; }
uint32_t IQNet::GetPlayerCount() { return 1; }
QNET_STATE IQNet::GetState() { return _bQNetStubGameRunning ? QNET_STATE_GAME_PLAY : QNET_STATE_IDLE; }
bool IQNet::IsHost() { return true; }
HRESULT IQNet::JoinGameFromInviteInfo(uint32_t dwUserIndex, uint32_t dwUserMask, const INVITE_INFO *pInviteInfo) { return S_OK; }
void IQNet::HostGame() { _bQNetStubGameRunning = true; }
void IQNet::EndGame() { _bQNetStubGameRunning = false; }

uint32_t MinecraftDynamicConfigurations::GetTrialTime() { return DYNAMIC_CONFIG_DEFAULT_TRIAL_TIME; }

void XSetThreadProcessor(HANDLE a, int b) {}
// #if !(defined __PS3__) && !(defined __ORBIS__)
// BOOL XCloseHandle(HANDLE a) { return CloseHandle(a); }
// #endif // __PS3__

uint32_t XUserGetSigninInfo(
         uint32_t dwUserIndex,
         uint32_t dwFlags,
         PXUSER_SIGNIN_INFO pSigninInfo
)
{
	return 0;
}

const wchar_t* CXuiStringTable::Lookup(const wchar_t* szId) { return szId; }
const wchar_t* CXuiStringTable::Lookup(uint32_t nIndex) { return L"String"; }
void CXuiStringTable::Clear() {}
HRESULT CXuiStringTable::Load(const wchar_t* szId) { return S_OK; }

uint32_t XUserAreUsersFriends( uint32_t dwUserIndex, PPlayerUID pXuids, uint32_t dwXuidCount, PBOOL pfResult, void *pOverlapped) { return 0; }

#if defined __ORBIS__ || defined __PS3__ || defined _XBOX_ONE
#else
HRESULT XMemDecompress(
         XMEMDECOMPRESSION_CONTEXT Context,
         void *pDestination,
         size_t *pDestSize,
         void *pSource,
         size_t SrcSize
)
{
	memcpy(pDestination, pSource, SrcSize);
	*pDestSize = SrcSize;
	return S_OK;

	/*
	DECOMPRESSOR_HANDLE Decompressor    = (DECOMPRESSOR_HANDLE)Context;
	if( Decompress(
        Decompressor,           //  Decompressor handle
        (void *)pSource,		//  Compressed data
        SrcSize,				//  Compressed data size
        pDestination,			//  Decompressed buffer
        *pDestSize,				//  Decompressed buffer size
        pDestSize) )				//  Decompressed data size
	{
		return S_OK;
	}
	else
	*/
	{
		return E_FAIL;
	}
}

HRESULT XMemCompress(
         XMEMCOMPRESSION_CONTEXT Context,
         void *pDestination,
         size_t *pDestSize,
         void *pSource,
         size_t SrcSize
)
{
	memcpy(pDestination, pSource, SrcSize);
	*pDestSize = SrcSize;
	return S_OK;

	/*
	COMPRESSOR_HANDLE Compressor    = (COMPRESSOR_HANDLE)Context;
	if( Compress(
			Compressor,                  //  Compressor Handle
			(void *)pSource,             //  Input buffer, Uncompressed data
			SrcSize,					 //  Uncompressed data size
			pDestination,                //  Compressed Buffer
			*pDestSize,                  //  Compressed Buffer size
			pDestSize)	)				//  Compressed Data size
	{
		return S_OK;
	}
	else
	*/
	{
		return E_FAIL;
	}
}

HRESULT XMemCreateCompressionContext(
         XMEMCODEC_TYPE CodecType,
         CONST void *pCodecParams,
         uint32_t Flags,
         XMEMCOMPRESSION_CONTEXT *pContext
)
{
	/*
	COMPRESSOR_HANDLE Compressor    = NULL;

	HRESULT hr = CreateCompressor(
		COMPRESS_ALGORITHM_XPRESS_HUFF, //  Compression Algorithm
		NULL,                           //  Optional allocation routine
		&Compressor);                   //  Handle

	pContext = (XMEMDECOMPRESSION_CONTEXT *)Compressor;
	return hr;
	*/
	return 0;
}

HRESULT XMemCreateDecompressionContext(
         XMEMCODEC_TYPE CodecType,
         CONST void *pCodecParams,
         uint32_t Flags,
         XMEMDECOMPRESSION_CONTEXT *pContext
)
{
	/*
	DECOMPRESSOR_HANDLE  Decompressor    = NULL;

	HRESULT hr = CreateDecompressor(
		COMPRESS_ALGORITHM_XPRESS_HUFF, //  Compression Algorithm
		NULL,                           //  Optional allocation routine
		&Decompressor);                   //  Handle

	pContext = (XMEMDECOMPRESSION_CONTEXT *)Decompressor;
	return hr;
	*/
	return 0;
}

void XMemDestroyCompressionContext(XMEMCOMPRESSION_CONTEXT Context)
{
//	COMPRESSOR_HANDLE Compressor    = (COMPRESSOR_HANDLE)Context;
//	CloseCompressor(Compressor);
}

void XMemDestroyDecompressionContext(XMEMDECOMPRESSION_CONTEXT Context)
{
//	DECOMPRESSOR_HANDLE Decompressor    = (DECOMPRESSOR_HANDLE)Context;
//	CloseDecompressor(Decompressor);
}
#endif

//#ifndef __PS3__
#if !(defined _DURANGO || defined __PS3__ || defined __ORBIS__ || defined __PSVITA__)
uint32_t XGetLanguage() { return 1; }
uint32_t XGetLocale() { return 0; }
uint32_t XEnableGuestSignin(BOOL fEnable) { return 0; }
#endif



/////////////////////////////////////////////// Profile library
#ifdef _WINDOWS64
static void *profileData[4];
static bool s_bProfileIsFullVersion;
void				C_4JProfile::Initialise( uint32_t dwTitleID,
								uint32_t dwOfferID,
								unsigned short usProfileVersion,
								uint32_t uiProfileValuesC,
								uint32_t uiProfileSettingsC,
								uint32_t *pdwProfileSettingsA, 
								int iGameDefinedDataSizeX4,
								unsigned int *puiGameDefinedDataChangedBitmask)
{
	for( int i = 0; i < 4; i++ )
	{
		profileData[i] = new uint8_t[iGameDefinedDataSizeX4/4];
		ZeroMemory(profileData[i],sizeof(uint8_t)*iGameDefinedDataSizeX4/4);

		// Set some sane initial values!
		GAME_SETTINGS *pGameSettings = (GAME_SETTINGS *)profileData[i];
		pGameSettings->ucMenuSensitivity=100; //eGameSetting_Sensitivity_InMenu
		pGameSettings->ucInterfaceOpacity=80; //eGameSetting_Sensitivity_InMenu
		pGameSettings->usBitmaskValues|=0x0200; //eGameSetting_DisplaySplitscreenGamertags - on
		pGameSettings->usBitmaskValues|=0x0400; //eGameSetting_Hints - on
		pGameSettings->usBitmaskValues|=0x1000; //eGameSetting_Autosave - 2
		pGameSettings->usBitmaskValues|=0x8000; //eGameSetting_Tooltips - on
		pGameSettings->uiBitmaskValues=0L; // reset
		pGameSettings->uiBitmaskValues|=GAMESETTING_CLOUDS;					//eGameSetting_Clouds - on
		pGameSettings->uiBitmaskValues|=GAMESETTING_ONLINE;					//eGameSetting_GameSetting_Online - on
		pGameSettings->uiBitmaskValues|=GAMESETTING_FRIENDSOFFRIENDS;		//eGameSetting_GameSetting_FriendsOfFriends - on
		pGameSettings->uiBitmaskValues|=GAMESETTING_DISPLAYUPDATEMSG;		//eGameSetting_DisplayUpdateMessage (counter)
		pGameSettings->uiBitmaskValues&=~GAMESETTING_BEDROCKFOG;			//eGameSetting_BedrockFog - off
		pGameSettings->uiBitmaskValues|=GAMESETTING_DISPLAYHUD;				//eGameSetting_DisplayHUD - on
		pGameSettings->uiBitmaskValues|=GAMESETTING_DISPLAYHAND;			//eGameSetting_DisplayHand - on
		pGameSettings->uiBitmaskValues|=GAMESETTING_CUSTOMSKINANIM;			//eGameSetting_CustomSkinAnim - on
		pGameSettings->uiBitmaskValues|=GAMESETTING_DEATHMESSAGES;			//eGameSetting_DeathMessages - on
		pGameSettings->uiBitmaskValues|=(GAMESETTING_UISIZE&0x00000800);				// uisize 2
		pGameSettings->uiBitmaskValues|=(GAMESETTING_UISIZE_SPLITSCREEN&0x00004000);	// splitscreen ui size 3
		pGameSettings->uiBitmaskValues|=GAMESETTING_ANIMATEDCHARACTER;		//eGameSetting_AnimatedCharacter - on

		// TU12
		// favorite skins added, but only set in TU12 - set to FFs
		for(int i=0;i<MAX_FAVORITE_SKINS;i++)
		{
			pGameSettings->uiFavoriteSkinA[i]=0xFFFFFFFF;
		}
		pGameSettings->ucCurrentFavoriteSkinPos=0;
		// Added a bitmask in TU13 to enable/disable display of the Mash-up pack worlds in the saves list
		pGameSettings->uiMashUpPackWorldsDisplay = 0xFFFFFFFF;

		// PS3DEC13
		pGameSettings->uiBitmaskValues&=~GAMESETTING_PS3EULAREAD;		//eGameSetting_PS3_EULA_Read - off

		// PS3 1.05 - added Greek
		pGameSettings->ucLanguage = MINECRAFT_LANGUAGE_DEFAULT; // use the system language

		// PS Vita - network mode added
		pGameSettings->uiBitmaskValues&=~GAMESETTING_PSVITANETWORKMODEADHOC;		//eGameSetting_PSVita_NetworkModeAdhoc - off


		// Tutorials for most menus, and a few other things
		pGameSettings->ucTutorialCompletion[0] = 0xFF;
		pGameSettings->ucTutorialCompletion[1] = 0xFF;
		pGameSettings->ucTutorialCompletion[2] = 0xF;

		// Has gone halfway through the tutorial
		pGameSettings->ucTutorialCompletion[28] |= 1<<0;
	}
}
void				C_4JProfile::SetTrialTextStringTable(CXuiStringTable *pStringTable,int iAccept,int iReject) {}
void				C_4JProfile::SetTrialAwardText(eAwardType AwardType,int iTitle,int iText) {}
int					C_4JProfile::GetLockedProfile() { return 0; }
void				C_4JProfile::SetLockedProfile(int iProf) {}
bool				C_4JProfile::IsSignedIn(int iQuadrant) { return ( iQuadrant == 0); }
bool				C_4JProfile::IsSignedInLive(int iProf) { return true; }
bool				C_4JProfile::IsGuest(int iQuadrant) { return false; }
uint32_t				C_4JProfile::RequestSignInUI(bool bFromInvite,bool bLocalGame,bool bNoGuestsAllowed,bool bMultiplayerSignIn,bool bAddUser, int( *Func)(void*,const bool, const int iPad),void* lpParam,int iQuadrant) { return 0; }
uint32_t				C_4JProfile::DisplayOfflineProfile(int( *Func)(void*,const bool, const int iPad),void* lpParam,int iQuadrant)  { return 0; }
uint32_t				C_4JProfile::RequestConvertOfflineToGuestUI(int( *Func)(void*,const bool, const int iPad),void* lpParam,int iQuadrant) { return 0; }
void				C_4JProfile::SetPrimaryPlayerChanged(bool bVal) {}
bool				C_4JProfile::QuerySigninStatus(void) { return true; }
void				C_4JProfile::GetXUID(int iPad, PlayerUID *pXuid,bool bOnlineXuid) {*pXuid = 0xe000d45248242f2e; }
BOOL				C_4JProfile::AreXUIDSEqual(PlayerUID xuid1,PlayerUID xuid2) { return false; }
BOOL				C_4JProfile::XUIDIsGuest(PlayerUID xuid) { return false; }
bool				C_4JProfile::AllowedToPlayMultiplayer(int iProf) { return true; }

#if defined(__ORBIS__)
bool				C_4JProfile::GetChatAndContentRestrictions(int iPad, bool thisQuadrantOnly, bool *pbChatRestricted,bool *pbContentRestricted,int *piAge)
{
	if(pbChatRestricted) *pbChatRestricted = false;
	if(pbContentRestricted) *pbContentRestricted = false;
	if(piAge) *piAge = 100;
	return true;
}
#endif

void				C_4JProfile::StartTrialGame() {}
void				C_4JProfile::AllowedPlayerCreatedContent(int iPad, bool thisQuadrantOnly, BOOL *allAllowed, BOOL *friendsAllowed) {}
BOOL				C_4JProfile::CanViewPlayerCreatedContent(int iPad, bool thisQuadrantOnly, PPlayerUID pXuids, uint32_t dwXuidCount ) { return true; }
bool				C_4JProfile::GetProfileAvatar(int iPad,int( *Func)(void* lpParam,uint8_t* pbThumbnail,uint32_t dwThumbnailBytes), void* lpParam) { return false; }
void				C_4JProfile::CancelProfileAvatarRequest() {}
int					C_4JProfile::GetPrimaryPad() { return 0; }
void				C_4JProfile::SetPrimaryPad(int iPad) {}
#ifdef _DURANGO
char fakeGamerTag[32] = "PlayerName";
void				SetFakeGamertag(char *name){ strcpy_s(fakeGamerTag, name); }
char*				C_4JProfile::GetGamertag(int iPad){ return fakeGamerTag; }
#else
char*				C_4JProfile::GetGamertag(int iPad){ return "PlayerName"; }
std::wstring				C_4JProfile::GetDisplayName(int iPad){ return L"PlayerName"; }
#endif
bool				C_4JProfile::IsFullVersion() { return s_bProfileIsFullVersion; }
void				C_4JProfile::SetSignInChangeCallback(void ( *Func)(void*, bool, unsigned int),void* lpParam) {}
void				C_4JProfile::SetNotificationsCallback(void ( *Func)(void*, uint32_t, unsigned int),void* lpParam) {}
bool				C_4JProfile::RegionIsNorthAmerica(void) { return false; }
bool				C_4JProfile::LocaleIsUSorCanada(void) { return false; }
HRESULT				C_4JProfile::GetLiveConnectionStatus() { return S_OK; }
bool				C_4JProfile::IsSystemUIDisplayed() { return false; }
void				C_4JProfile::SetProfileReadErrorCallback(void ( *Func)(void*), void* lpParam) {}
int( *defaultOptionsCallback)(void*,C_4JProfile::PROFILESETTINGS *, const int iPad) = NULL;
void* lpProfileParam = NULL;
int					C_4JProfile::SetDefaultOptionsCallback(int( *Func)(void*,PROFILESETTINGS *, const int iPad),void* lpParam)
{
	defaultOptionsCallback = Func;
	lpProfileParam = lpParam;
	return 0;
}
int					C_4JProfile::SetOldProfileVersionCallback(int( *Func)(void*,unsigned char *, const unsigned short,const int),void* lpParam) { return 0; }

// To store the dashboard preferences for controller flipped, etc.
C_4JProfile::PROFILESETTINGS ProfileSettingsA[XUSER_MAX_COUNT];

C_4JProfile::PROFILESETTINGS *	C_4JProfile::GetDashboardProfileSettings(int iPad) { return &ProfileSettingsA[iPad]; }
void				C_4JProfile::WriteToProfile(int iQuadrant, bool bGameDefinedDataChanged, bool bOverride5MinuteLimitOnProfileWrites) {}
void				C_4JProfile::ForceQueuedProfileWrites(int iPad) {}
void				*C_4JProfile::GetGameDefinedProfileData(int iQuadrant)
{
	// 4J Stu - Don't reset the options when we call this!!
	//defaultOptionsCallback(lpProfileParam, (C_4JProfile::PROFILESETTINGS *)profileData[iQuadrant], iQuadrant);
	//pApp->SetDefaultOptions(pSettings,iPad);

	return profileData[iQuadrant];
}
void				C_4JProfile::ResetProfileProcessState() {}
void				C_4JProfile::Tick( void ) {}
void				C_4JProfile::RegisterAward(int iAwardNumber,int iGamerconfigID, eAwardType eType, bool bLeaderboardAffected, 
	CXuiStringTable*pStringTable, int iTitleStr, int iTextStr, int iAcceptStr, char *pszThemeName, unsigned int ulThemeSize) {}
int					C_4JProfile::GetAwardId(int iAwardNumber) { return 0; }
eAwardType			C_4JProfile::GetAwardType(int iAwardNumber) { return eAwardType_Achievement; }
bool				C_4JProfile::CanBeAwarded(int iQuadrant, int iAwardNumber) { return false; }
void				C_4JProfile::Award(int iQuadrant, int iAwardNumber, bool bForce) {}
bool				C_4JProfile::IsAwardsFlagSet(int iQuadrant, int iAward) { return false; }
void				C_4JProfile::RichPresenceInit(int iPresenceCount, int iContextCount) {}
void				C_4JProfile::RegisterRichPresenceContext(int iGameConfigContextID) {}
void				C_4JProfile::SetRichPresenceContextValue(int iPad,int iContextID, int iVal) {}
void				C_4JProfile::SetCurrentGameActivity(int iPad,int iNewPresence, bool bSetOthersToIdle) {}
void				C_4JProfile::DisplayFullVersionPurchase(bool bRequired, int iQuadrant, int iUpsellParam) {}
void				C_4JProfile::SetUpsellCallback(void ( *Func)(void* lpParam, eUpsellType type, eUpsellResponse response, int iUserData),void* lpParam) {}
void				C_4JProfile::SetDebugFullOverride(bool bVal) {s_bProfileIsFullVersion = bVal;}
void				C_4JProfile::ShowProfileCard(int iPad, PlayerUID targetUid) {}

/////////////////////////////////////////////// Storage library
//#ifdef _WINDOWS64
// TODO???
#if defined(__linux__)
C4JStorage::C4JStorage() {}
void								C4JStorage::Tick() {}
C4JStorage::EMessageResult			C4JStorage::RequestMessageBox(uint32_t uiTitle, uint32_t uiText, uint32_t *uiOptionA,uint32_t uiOptionC, uint32_t dwPad, int( *Func)(void*,int,const C4JStorage::EMessageResult),void* lpParam, C4JStringTable *pStringTable, wchar_t *pwchFormatString,uint32_t dwFocusButton) { return C4JStorage::EMessage_Undefined; }
C4JStorage::EMessageResult			C4JStorage::GetMessageBoxResult()  { return C4JStorage::EMessage_Undefined; }
bool								C4JStorage::SetSaveDevice(int( *Func)(void*,const bool),void* lpParam, bool bForceResetOfSaveDevice) { return true; }
void								C4JStorage::Init(const wchar_t* pwchDefaultSaveName,char *pszSavePackName,int iMinimumSaveSize, int( *Func)(void*, const ESavingMessage, int),void* lpParam) {}
void								C4JStorage::ResetSaveData() {}
void								C4JStorage::SetDefaultSaveNameForKeyboardDisplay(const wchar_t* pwchDefaultSaveName) {}
void								C4JStorage::SetSaveTitle(const wchar_t* pwchDefaultSaveName) {}
const wchar_t*								C4JStorage::GetSaveTitle() { return L""; }
bool								C4JStorage::GetSaveUniqueNumber(int32_t *piVal) { return true; }
bool								C4JStorage::GetSaveUniqueFilename(char *pszName) { return true; }
void								C4JStorage::SetSaveUniqueFilename(char *szFilename) { }
void								C4JStorage::SetState(ESaveGameControlState eControlState,int( *Func)(void*,const bool),void* lpParam) {}
void								C4JStorage::SetSaveDisabled(bool bDisable) {}
bool								C4JStorage::GetSaveDisabled(void) { return false; }
unsigned int						C4JStorage::GetSaveSize() { return 0; }
void								C4JStorage::GetSaveData(void *pvData,unsigned int *pulBytes) {}
void*								C4JStorage::AllocateSaveData(unsigned int ulBytes) { return new char[ulBytes]; }
void								C4JStorage::SaveSaveData(unsigned int ulBytes,uint8_t* pbThumbnail,uint32_t cbThumbnail,uint8_t* pbTextData, uint32_t dwTextLen) {}
void								C4JStorage::CopySaveDataToNewSave(uint8_t* pbThumbnail,uint32_t cbThumbnail,wchar_t *wchNewName,int ( *Func)(void* lpParam, bool), void* lpParam) {}
void								C4JStorage::SetSaveDeviceSelected(unsigned int uiPad,bool bSelected) {}
bool								C4JStorage::GetSaveDeviceSelected(unsigned int iPad) { return true; }
C4JStorage::ELoadGameStatus			C4JStorage::DoesSaveExist(bool *pbExists) { return C4JStorage::ELoadGame_Idle; }
bool								C4JStorage::EnoughSpaceForAMinSaveGame() { return true; }
void								C4JStorage::SetSaveMessageVPosition(float fY) {}
//C4JStorage::ESGIStatus				C4JStorage::GetSavesInfo(int iPad,bool ( *Func)(void*, int, CACHEINFOSTRUCT *, int, HRESULT),void* lpParam,char *pszSavePackName) { return C4JStorage::ESGIStatus_Idle; }
C4JStorage::ESaveGameState			C4JStorage::GetSavesInfo(int iPad,int ( *Func)(void* lpParam,SAVE_DETAILS *pSaveDetails,const bool),void* lpParam,char *pszSavePackName) { return C4JStorage::ESaveGame_Idle; }

void								C4JStorage::GetSaveCacheFileInfo(uint32_t dwFile,XCONTENT_DATA &xContentData) {}
void								C4JStorage::GetSaveCacheFileInfo(uint32_t dwFile,	uint8_t* *ppbImageData, uint32_t *pdwImageBytes) {}
C4JStorage::ESaveGameState			C4JStorage::LoadSaveData(PSAVE_INFO pSaveInfo,int( *Func)(void* lpParam,const bool, const bool), void* lpParam) {return C4JStorage::ESaveGame_Idle;}
C4JStorage::EDeleteGameStatus		C4JStorage::DeleteSaveData(PSAVE_INFO pSaveInfo,int( *Func)(void* lpParam,const bool), void* lpParam) { return C4JStorage::EDeleteGame_Idle; }
PSAVE_DETAILS						C4JStorage::ReturnSavesInfo() {return NULL;}

void								C4JStorage::RegisterMarketplaceCountsCallback(int ( *Func)(void* lpParam, C4JStorage::DLC_TMS_DETAILS *, int), void* lpParam ) {}
void								C4JStorage::SetDLCPackageRoot(char *pszDLCRoot) {}
C4JStorage::EDLCStatus				C4JStorage::GetDLCOffers(int iPad,int( *Func)(void*, int, uint32_t, int),void* lpParam, uint32_t dwOfferTypesBitmaskT) { return C4JStorage::EDLC_Idle; }
uint32_t								C4JStorage::CancelGetDLCOffers() { return 0; }
void								C4JStorage::ClearDLCOffers() {}
XMARKETPLACE_CONTENTOFFER_INFO&		C4JStorage::GetOffer(uint32_t dw) { static XMARKETPLACE_CONTENTOFFER_INFO retval = {0}; return retval; }
int									C4JStorage::GetOfferCount() { return 0; }
uint32_t								C4JStorage::InstallOffer(int iOfferIDC,uint64_t *ullOfferIDA,int( *Func)(void*, int, int),void* lpParam, bool bTrial) { return 0; }
uint32_t								C4JStorage::GetAvailableDLCCount( int iPad) { return 0; }
XCONTENT_DATA&						C4JStorage::GetDLC(uint32_t dw) { static XCONTENT_DATA retval = {0}; return retval; }
C4JStorage::EDLCStatus				C4JStorage::GetInstalledDLC(int iPad,int( *Func)(void*, int, int),void* lpParam) { return C4JStorage::EDLC_Idle; }
uint32_t								C4JStorage::MountInstalledDLC(int iPad,uint32_t dwDLC,int( *Func)(void*, int, uint32_t,uint32_t),void* lpParam,const char* szMountDrive) { return 0; }
uint32_t								C4JStorage::UnmountInstalledDLC(const char* szMountDrive) { return 0; }
C4JStorage::ETMSStatus				C4JStorage::ReadTMSFile(int iQuadrant,eGlobalStorage eStorageFacility,C4JStorage::eTMS_FileType eFileType, wchar_t *pwchFilename,uint8_t **ppBuffer,uint32_t *pdwBufferSize,int( *Func)(void*, wchar_t *,int, bool, int),void* lpParam, int iAction) { return C4JStorage::ETMSStatus_Idle; }
bool								C4JStorage::WriteTMSFile(int iQuadrant,eGlobalStorage eStorageFacility,wchar_t *pwchFilename,uint8_t *pBuffer,uint32_t dwBufferSize) { return true; }
bool								C4JStorage::DeleteTMSFile(int iQuadrant,eGlobalStorage eStorageFacility,wchar_t *pwchFilename) { return true; }
void								C4JStorage::StoreTMSPathName(wchar_t *pwchName) {}
unsigned int						C4JStorage::CRC(unsigned char *buf, int len) { return 0; }

struct PTMSPP_FILEDATA;
C4JStorage::ETMSStatus				C4JStorage::TMSPP_ReadFile(int iPad,C4JStorage::eGlobalStorage eStorageFacility,C4JStorage::eTMS_FILETYPEVAL eFileTypeVal,const char* szFilename,int( *Func)(void*,int,int,PTMSPP_FILEDATA, const char*)/*=NULL*/,void* lpParam/*=NULL*/, int iUserData/*=0*/) {return C4JStorage::ETMSStatus_Idle;}
#endif // _WINDOWS64

#endif // __PS3__

/////////////////////////////////////////////////////// Sentient manager

HRESULT CSentientManager::Init() { return S_OK; }
HRESULT CSentientManager::Tick() { return S_OK; }
HRESULT CSentientManager::Flush() { return S_OK; }
BOOL CSentientManager::RecordPlayerSessionStart(uint32_t dwUserId) { return true; }
BOOL CSentientManager::RecordPlayerSessionExit(uint32_t dwUserId, int exitStatus) { return true; }
BOOL CSentientManager::RecordHeartBeat(uint32_t dwUserId) { return true; }
BOOL CSentientManager::RecordLevelStart(uint32_t dwUserId, ESen_FriendOrMatch friendsOrMatch, ESen_CompeteOrCoop competeOrCoop, int difficulty, uint32_t numberOfLocalPlayers, uint32_t numberOfOnlinePlayers) { return true; }
BOOL CSentientManager::RecordLevelExit(uint32_t dwUserId, ESen_LevelExitStatus levelExitStatus) { return true; }
BOOL CSentientManager::RecordLevelSaveOrCheckpoint(uint32_t dwUserId, int32_t saveOrCheckPointID, int32_t saveSizeInBytes) { return true; }
BOOL CSentientManager::RecordLevelResume(uint32_t dwUserId, ESen_FriendOrMatch friendsOrMatch, ESen_CompeteOrCoop competeOrCoop, int difficulty, uint32_t numberOfLocalPlayers, uint32_t numberOfOnlinePlayers, int32_t saveOrCheckPointID)  { return true; }
BOOL CSentientManager::RecordPauseOrInactive(uint32_t dwUserId)  { return true; }
BOOL CSentientManager::RecordUnpauseOrActive(uint32_t dwUserId) { return true; }
BOOL CSentientManager::RecordMenuShown(uint32_t dwUserId, int32_t menuID, int32_t optionalMenuSubID) { return true; }
BOOL CSentientManager::RecordAchievementUnlocked(uint32_t dwUserId, int32_t achievementID, int32_t achievementGamerscore) { return true; }
BOOL CSentientManager::RecordMediaShareUpload(uint32_t dwUserId, ESen_MediaDestination mediaDestination, ESen_MediaType mediaType) { return true; }
BOOL CSentientManager::RecordUpsellPresented(uint32_t dwUserId, ESen_UpsellID upsellId, int32_t marketplaceOfferID) { return true; }
BOOL CSentientManager::RecordUpsellResponded(uint32_t dwUserId, ESen_UpsellID upsellId, int32_t marketplaceOfferID, ESen_UpsellOutcome upsellOutcome) { return true; }
BOOL CSentientManager::RecordPlayerDiedOrFailed(uint32_t dwUserId, int32_t lowResMapX, int32_t lowResMapY, int32_t lowResMapZ, int32_t mapID, int32_t playerWeaponID, int32_t enemyWeaponID, ETelemetryChallenges enemyTypeID) { return true; }
BOOL CSentientManager::RecordEnemyKilledOrOvercome(uint32_t dwUserId, int32_t lowResMapX, int32_t lowResMapY, int32_t lowResMapZ, int32_t mapID, int32_t playerWeaponID, int32_t enemyWeaponID, ETelemetryChallenges enemyTypeID) { return true; }
BOOL CSentientManager::RecordSkinChanged(uint32_t dwUserId, uint32_t dwSkinId) { return true; }
BOOL CSentientManager::RecordBanLevel(uint32_t dwUserId) { return true; }
BOOL CSentientManager::RecordUnBanLevel(uint32_t dwUserId) { return true; }
int32_t CSentientManager::GetMultiplayerInstanceID() { return 0; }
int32_t CSentientManager::GenerateMultiplayerInstanceId() { return 0; }
void CSentientManager::SetMultiplayerInstanceId(int32_t value) {}

////////////////////////////////////////////////////////  Stats counter

/*
StatsCounter::StatsCounter() {}
void StatsCounter::award(Stat *stat, unsigned int difficulty, unsigned int count) {}
bool StatsCounter::hasTaken(Achievement *ach) { return true; }
bool StatsCounter::canTake(Achievement *ach) { return true; }
unsigned int StatsCounter::getValue(Stat *stat, unsigned int difficulty) { return 0; }
unsigned int StatsCounter::getTotalValue(Stat *stat) { return 0; }
void StatsCounter::tick(int player) {}
void StatsCounter::parse(void* data) {}
void StatsCounter::clear() {}
void StatsCounter::save(int player, bool force) {}
void StatsCounter::flushLeaderboards() {}
void StatsCounter::saveLeaderboards() {}
void StatsCounter::setupStatBoards() {}
#ifdef _DEBUG
void StatsCounter::WipeLeaderboards() {}
#endif
*/
