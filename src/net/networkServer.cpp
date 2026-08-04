#include "networkServer.h"

using namespace pong::net;

namespace Network
{
	void GameServer::OnMessage(std::shared_ptr<connection<MessageType>> client,
		message<MessageType>& msg)
	{
		switch (msg.header.id)	
		{
		case MessageType::JoinMatch:
		{

			if (connectedPlayer >= 2)
			{
				message<MessageType> deny;
				deny.header.id = MessageType::ServerDeny;
				MessageClient(client, deny);
				break;
			}

			int slot = (connectedPlayer == 0) ? 1 : 2;
			connectionToSlots[client->getID()] = slot;
			connectedPlayer++;

			message<MessageType> accept;
			accept.header.id = MessageType::ServerAccept;
			MessageClient(client, accept);

			if (connectedPlayer == 2)
			{
				for (auto& [connId, playerSlot] : connectionToSlots)
				{
					message<MessageType> start;
					start.header.id = MessageType::MatchStart;
					start << playerSlot;
					MessageClient(FindConnectionById(connId), start);
				}
			}
			break;
		}
		case MessageType::PlayerInput:
		{
			Core::PlayerInputState input;
			msg >> input;
			latestInputs[client->getID()] = input;
			break;
		}
			
		default:
			break;
		}
	}

	void GameServer::OnClientDisconnect(std::shared_ptr<connection<MessageType>> client)
	{
		uint32_t id = client->getID();

		if (connectionToSlots.count(id))
		{
			connectedPlayer--;
			connectionToSlots.erase(id);
		}

		latestInputs.erase(id);

		pong::net::message<MessageType> notify;
		notify.header.id = MessageType::MatchEnd;
		MessageAllClients(notify);
	}

	bool GameServer::OnClientConnect(std::shared_ptr<connection<MessageType>> client)
	{
		if (connectedPlayer >= 2)
			return false;

		return true;
	}

	Core::PlayerInputState GameServer::getInputSlot(int slot)
	{
		for (auto& [connId, s] : connectionToSlots)
		{
			if (s == slot)
			{
				return latestInputs[connId];
			}
		}
		return {};
	}
}