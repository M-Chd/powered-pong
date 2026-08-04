#pragma once

#include "netCommon.h"

namespace Network
{
	class GameServer : public pong::net::server_interface<MessageType>
	{
	public:
		GameServer(uint16_t port) : server_interface(port) {}
	protected:
		bool OnClientConnect(std::shared_ptr<pong::net::connection<MessageType>> client) override;
		void OnClientDisconnect(std::shared_ptr<pong::net::connection<MessageType>> client) override;
		void OnMessage(std::shared_ptr<pong::net::connection<MessageType>> client,
		               pong::net::message<MessageType>& msg) override;
	public:
		Core::PlayerInputState getInputSlot(int slot);
	private:
		std::unordered_map<uint32_t, Core::PlayerInputState> latestInputs;
		std::unordered_map<uint32_t, int> connectionToSlots;
		int connectedPlayer{ 0 };
	};
}
