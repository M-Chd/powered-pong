/*
	MMO Client/Server Framework using ASIO
	"Happy Birthday Mrs Javidx9!" - javidx9

	Videos:
	Part #1: https://youtu.be/2hNdkYInj4g
	Part #2: https://youtu.be/UbjxGvrDrbw

	License (OLC-3)
	~~~~~~~~~~~~~~~

	Copyright 2018 - 2020 OneLoneCoder.com

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	1. Redistributions or derivations of source code must retain the above
	copyright notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce
	the above copyright notice. This list of conditions and the following
	disclaimer must be reproduced in the documentation and/or other
	materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its
	contributors may be used to endorse or promote products derived
	from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	Links
	~~~~~
	YouTube:	https://www.youtube.com/javidx9
	Discord:	https://discord.gg/WhwHUMV
	Twitter:	https://www.twitter.com/javidx9
	Twitch:		https://www.twitch.tv/javidx9
	GitHub:		https://www.github.com/onelonecoder
	Homepage:	https://www.onelonecoder.com

	Author
	~~~~~~
	David Barr, aka javidx9, ©OneLoneCoder 2019, 2020
*/

#pragma once

#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"
#include "net_connection.h"

namespace pong
{
	namespace net
	{
		template<typename T>
		class server_interface
		{
		public:
			server_interface(uint16_t port)
				: m_asioAcceptor(m_asioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
			{

			}

			virtual ~server_interface()
			{
				Stop();
			}

			bool Start()
			{
				try
				{
					WaitForClientConnection();
					m_threadContext = std::thread([this]() {m_asioContext.run(); });
				}
				catch (std::exception e)
				{
					std::cerr << "[SERVER] Exception: " << e.what() << "\n";
					return false;
				}

				printf("[SERVER] Started!\n");
				return true;
			}

			void Stop()
			{
				m_asioContext.stop();

				if (m_threadContext.joinable()) m_threadContext.join();
				
				printf("[SERVER] Stopped!\n");
			}

			void WaitForClientConnection()
			{
				m_asioAcceptor.async_accept(
					[this](std::error_code ec, asio::ip::tcp::socket socket)
					{
						if (!ec)
						{
							std::cout << "[SERVER] New Connection: " << socket.remote_endpoint() << "\n";

							std::shared_ptr<connection<T>> newconn =
								std::make_shared<connection<T>>(connection<T>::owner::server,
									m_asioContext, std::move(socket), m_qMessagesIn);

							if (OnClientConnect(newconn))
							{
								m_deqConnection.push_back(std::move(newconn));
								m_deqConnection.back()->ConnectToClient(this,nIdCounter++);
								std::cout << "[" << m_deqConnection.back()->getID() << "] Connection approved!" << "\n";
							}
							else
							{
								printf("[---] Connection denied!\n");
							}
						}
						else
						{
							std::cout << "[SERVER] New Connection Error: " << ec.message() << "\n";
						}

						WaitForClientConnection();
					}
				);
			}

			void MessageClient(std::shared_ptr<connection<T>> client, const message<T>& msg)
			{
				if (client && client->IsConnected())
				{
					client->Send(msg);
				}
				else
				{
					OnClientDisconnect(client);
					client.reset();
					m_deqConnection.erase(
						std::remove(m_deqConnection.begin(), m_deqConnection.end(), client), m_deqConnection.end());

				}
			}

			void MessageAllClients(const message<T>& msg, std::shared_ptr<connection<T>> pIgnoreClient = nullptr)
			{
				bool bInvalidClientExists = false;

				for (auto& client : m_deqConnection)
				{
					if (client && client->IsConnected())
					{
						if (client != pIgnoreClient)
						{
							client->Send(msg);
						}
					}
					else
					{
						OnClientDisconnect(client);
						client.reset();
						bInvalidClientExists = true;
					}

					if (bInvalidClientExists)
					{
						m_deqConnection.erase(
							std::remove(m_deqConnection.begin(), m_deqConnection.end(), client), m_deqConnection.end());
					}
				}
			}

			void Update(size_t nMaxMessages = -1, bool bWait = false)
			{
				if (bWait) m_qMessagesIn.wait();

				size_t nMessageCount = 0;
				while (nMessageCount < nMaxMessages && !m_qMessagesIn.empty())
				{
					auto msg = m_qMessagesIn.pop_front();
					OnMessage(msg.remote, msg.msg);
					nMessageCount++;
				}
			}

			std::shared_ptr<connection<T>> FindConnectionById(uint32_t id)
			{
				for (auto& conn : m_deqConnection)
				{
					if (conn && conn->getID() == id)
						return conn;
				}
				return nullptr;
			}

		protected:

			//function to be implemented
			virtual bool OnClientConnect(std::shared_ptr<connection<T>> client)
			{
				return false;
			}

			virtual void OnClientDisconnect(std::shared_ptr<connection<T>> client)
			{

			}

			virtual void OnMessage(std::shared_ptr<connection<T>> client, message<T>& msg)
			{

			}

		protected:
			tsqueue<owned_message<T>> m_qMessagesIn;
			asio::io_context m_asioContext;
			std::deque <std::shared_ptr<connection<T>>> m_deqConnection;
			std::thread m_threadContext;
			asio::ip::tcp::acceptor m_asioAcceptor;
			uint32_t nIdCounter = 10000;
		};
	}
}