#include "networkClient.h"

using namespace pong::net;

namespace Network
{
	void GameClient::processIncoming()
	{
		while (!Incoming().empty())
		{
			auto owned = Incoming().pop_front();
			auto& msg = owned.msg;

			switch (msg.header.id)
			{
			case MessageType::ServerAccept:
				connState = ConnectionState::Connected;
				break;

			case MessageType::ServerDeny:
				connState = ConnectionState::Failed;
				break;

			case MessageType::MatchStart:
			{
				int slot;
				msg >> slot;
				assignedSlot = slot;
				break;
			}

			case MessageType::GameState:
			{
				NetGameState state;
				msg >> state;
				latestState = state;
				break;
			}

			case MessageType::MatchEnd:
				matchEndedFlag = true;
				break;

			default:
				break;
			}
		}
	}

	bool GameClient::pollMatchStart(int& slotOut)
	{
		if (!assignedSlot.has_value())
			return false;

		slotOut = *assignedSlot;
		assignedSlot.reset();
		return true;
	}

	bool GameClient::pollGameState(NetGameState& out)
	{
		if (!latestState.has_value())
			return false;

		out = *latestState;
		return true;
	}

	bool GameClient::pollMatchEnded()
	{
		if (!matchEndedFlag)
			return false;

		matchEndedFlag = false;
		return true;
	}

	void GameClient::sendJoinMatch()
	{
		message<MessageType> msg;
		msg.header.id = MessageType::JoinMatch;
		m_connection->Send(msg);
	}

	void GameClient::sendInput(const Core::PlayerInputState& input)
	{
		message<MessageType> msg;
		msg.header.id = MessageType::PlayerInput;
		msg << input;
		m_connection->Send(msg);
	}

	ConnectionState GameClient::getConnectionState()
	{
		if (connState == ConnectionState::Connected && !IsConnected())
			return ConnectionState::Failed;

		return connState;
	}
}