#include <iostream>

#include <pong_net.h>

enum class CustomMsgTypes : uint32_t
{
	ServerAccept,
	ServerDeny,
	ServerPing,
	MessageAll,
	ServerMessage
};

class CustomClient : public pong::net::client_interface<CustomMsgTypes>
{
	
};

int main()
{
	CustomClient c;
	c.Connect("127.0.0.1", 6000);
	return 0;
}