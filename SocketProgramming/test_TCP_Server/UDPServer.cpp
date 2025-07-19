#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main()
{
	try
	{
		boost::asio::io_context io_context;

		udp::socket socket(io_context, udp::endpoint(udp::v4(), 12345));

		std::cout << "UDP 서버가 포트 12345에서 대기 중입니다..." << std::endl;
	
		while (true)
		{
			char data[1024];
			udp::endpoint sender_endpoint;
			boost::system::error_code error;

			size_t length = socket.receive_from(boost::asio::buffer(data),
				sender_endpoint, 0, error);

			if (error && error != boost::asio::error::message_size)
			{
				throw boost::system::system_error(error);
			}

			std::cout << "수신한 메시지: " << std::string(data, length) << std::endl;

			socket.send_to(boost::asio::buffer(data, length), sender_endpoint, 0, error);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "예외 발생 : " << e.what() << std::endl;
	}

	return 0;
}