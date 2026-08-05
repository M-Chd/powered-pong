#include "networkManager.h"

using namespace pong::net;

namespace Network
{
	void NetworkManager::teardown()
	{
		if (client)
		{
			client->Disconnect();
			client = nullptr;
		}
		if (server)
		{
			server->Stop();
			server = nullptr;
		}
	}

	void NetworkManager::processMessages()
	{
		if (server)
		{
			server->Update(-1,false);
		}
		if (client)
		{
			client->processIncoming();
		}
	}

	void NetworkManager::broadcastGameState(const NetGameState& n)
	{
		message<MessageType> msg;
		msg.header.id = MessageType::GameState;
		msg << n;
		server->MessageAllClients(msg);
	}

	void NetworkManager::sendInput(const Core::PlayerInputState& input)
	{
		if (client) client->sendInput(input);
	}

	bool NetworkManager::pollMatchStart(int& slotOut)
	{
		return client ? client->pollMatchStart(slotOut) : false;
	}

	bool NetworkManager::pollMatchEnded()
	{
		return client ? client->pollMatchEnded() : false;
	}

	Core::PlayerInputState NetworkManager::getRemoteInput(int slot)
	{
		return server ? server->getInputSlot(slot) : Core::PlayerInputState{};
	}

	ConnectionState NetworkManager::getConnectionState() const
	{
		return client ? client->getConnectionState() : ConnectionState::NotConnected;
	}

	bool NetworkManager::pollGameState(NetGameState& out)
	{
		return client ? client->pollGameState(out) : false;
	}

	void NetworkManager::startHost(uint16_t port)
	{
		activePort = port;
		server = std::make_unique<GameServer>(activePort);
		server->Start();
	}

	void NetworkManager::joinServer(const std::string& ip, uint16_t port)
	{
		client = std::make_unique<GameClient>();
		client->Connect(ip, port);
		client->sendJoinMatch();
	}

	void NetworkManager::connectLocalClient()
	{
		client = std::make_unique<GameClient>();
		client->Connect("127.0.0.1", activePort);
	}
}