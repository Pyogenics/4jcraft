#pragma once


#include "Packet.h"

class TexturePacket : public Packet, public std::enable_shared_from_this<TexturePacket>
{
public:
	std::wstring textureName;
	uint8_t* pbData;
	uint32_t dwBytes;

	TexturePacket();
	~TexturePacket(); 
	TexturePacket(const std::wstring &textureName, uint8_t* pbData, uint32_t dwBytes);

	virtual void handle(PacketListener *listener);
	virtual void read(DataInputStream *dis);
	virtual void write(DataOutputStream *dos);
	virtual int getEstimatedSize();

public:
	static std::shared_ptr<Packet> create() { return std::shared_ptr<Packet>(new TexturePacket()); }
	virtual int getId() { return 154; }
};