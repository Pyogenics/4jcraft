#pragma once


#include "Packet.h"
#include "../../../Minecraft.Client/Rendering/Models/Model.h"
#include "../../../Minecraft.Client/Rendering/Models/SkinBox.h"

class DLCSkinFile;

class TextureAndGeometryPacket : public Packet, public std::enable_shared_from_this<TextureAndGeometryPacket>
{
public:
	std::wstring textureName;
	uint32_t dwSkinID;
	uint8_t* pbData;
	uint32_t dwTextureBytes;
	SKIN_BOX *BoxDataA;
	uint32_t dwBoxC;
	unsigned int uiAnimOverrideBitmask;

	TextureAndGeometryPacket();
	~TextureAndGeometryPacket();
	TextureAndGeometryPacket(const std::wstring &textureName, uint8_t* pbData, uint32_t dwBytes); 
	TextureAndGeometryPacket(const std::wstring &textureName, uint8_t* pbData, uint32_t dwBytes, DLCSkinFile *pDLCSkinFile); 
	TextureAndGeometryPacket(const std::wstring &textureName, uint8_t* pbData, uint32_t dwBytes, std::vector<SKIN_BOX *> *pvSkinBoxes, unsigned int uiAnimOverrideBitmask); 

	virtual void handle(PacketListener *listener);
	virtual void read(DataInputStream *dis);
	virtual void write(DataOutputStream *dos);
	virtual int getEstimatedSize();

public:
	static std::shared_ptr<Packet> create() { return std::shared_ptr<Packet>(new TextureAndGeometryPacket()); }
	virtual int getId() { return 160; }
};
