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

namespace pong
{
	namespace net
	{
		template<typename T>
		struct message_header
		{
			T id{};
			uint32_t size = 0;
		};

		template<typename T>
		struct message
		{
			message_header<T> header{};
			std::vector<uint8_t> body;

			size_t size()
			{
				return sizeof(message_header<T>) + body.size();
			}

			friend std::ostream& operator << (std::ostream& os, const message<T>& msg)
			{
				os << "ID: " << int(msg.header.id) << " Size: " << msg.header.size;
				return os;
			}

			template<typename DataType>
			friend message<T>& operator << (message<T>& msg, const DataType& data)
			{
				static_assert(std::is_standard_layout<DataType>::value, "This Data is too complex to be pushed.");

				size_t i = msg.body.size();

				msg.body.resize(msg.body.size() + sizeof(DataType));

				std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

				msg.header.size = static_cast<uint32_t>(msg.body.size());

				return msg;
			}

			template<typename DataType>
			friend message<T>& operator >> (message<T>& msg, DataType& data)
			{
				static_assert(std::is_standard_layout<DataType>::value, "This Data is too complex to be pushed.");

				size_t i = msg.body.size() - sizeof(DataType);

				std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

				msg.body.resize(i);

				msg.header.size = static_cast<uint32_t>(msg.body.size());

				return msg;
			}
		};

		//forward declaration for connection
		template<typename T>
		class connection;

		template<typename T>
		struct owned_message
		{
			std::shared_ptr<connection<T>> remote{ nullptr };
			message<T> msg;

			friend std::ostream& operator<<(std::ostream& os, const owned_message<T>& msg)
			{
				os << msg.msg;
				return os;
			}
		};
	}
}