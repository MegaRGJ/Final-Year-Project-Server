#include "stdafx.h"
#include "Serialisation32Bit.h"

int Serialisation32Bit::DeserialisePacketType(char* byteArray)
{
	return (int)(byteArray[0] | byteArray[1] | byteArray[2] | byteArray[3]);
}

ClientPositionPacket Serialisation32Bit::DeserialisePositionPacket(char* byteArray)
{
	ClientPositionPacket* PacketTemp = new ClientPositionPacket();
	memcpy(PacketTemp, byteArray + 4, sizeof(ClientPositionPacket));
	ClientPositionPacket Packet = *PacketTemp;

	delete PacketTemp;
	return Packet;
}

ClientConnectPacket Serialisation32Bit::DeserialiseConnectPacket(char* byteArray)
{
	ClientConnectPacket* PacketTemp = new ClientConnectPacket();
	memcpy(PacketTemp, byteArray + 4, sizeof(ClientConnectPacket));
	ClientConnectPacket Packet = *PacketTemp;

	delete PacketTemp;
	return Packet;
}

ClientDisconnectPacket Serialisation32Bit::DeserialiseDisconnectPacket(char* byteArray)
{
	ClientDisconnectPacket* PacketTemp = new ClientDisconnectPacket();
	memcpy(PacketTemp, byteArray + 4, sizeof(ClientDisconnectPacket));
	ClientDisconnectPacket Packet = *PacketTemp;

	delete PacketTemp;
	return Packet;
}

void Serialisation32Bit::Serialise(ServerPacket& packet, SendBuffer& buffer)
{
	packet.Serialise(buffer);
}

void ServerAcknowledgmentPacket::Serialise(SendBuffer& buffer)
{
	memcpy(buffer.Buffer, &ACKNOWLEDGMENT_ID, sizeof(ACKNOWLEDGMENT_ID));
	memcpy(buffer.Buffer + 4, this, sizeof(ServerAcknowledgmentPacket));
	*buffer.size = 8;
}
void ServerPlayerPacket::Serialise(SendBuffer& buffer)
{	
	memcpy(buffer.Buffer, &PLAYER_ID, sizeof(PLAYER_ID));
	memcpy(buffer.Buffer + 4, this, sizeof(ServerPlayerPacket));
	
	*buffer.size = 72;
}

