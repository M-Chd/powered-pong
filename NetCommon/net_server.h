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
					};
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
				}

				if (bInvalidClientExists)
				{
					m_deqConnection.erase(
						std::remove(m_deqConnection.begin(), m_deqConnection.end(), client), m_deqConnection.end());
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