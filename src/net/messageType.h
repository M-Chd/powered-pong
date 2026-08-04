#pragma once

namespace Network
{
	enum class MessageType
	{
		// Connexion
        ServerAccept,
        ServerDeny,
        Ping,
        Disconnect,

        // Lobby
        JoinMatch,
        LeaveMatch,
        MatchStart,
        MatchEnd,

        // Player inputs
        PlayerInput,

        // GameState
        GameState,

        // Synchronisation
        ScoreUpdate,
        RoundStart,
        ItemSpawn,
        EffectApplied
	};
}