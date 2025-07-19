#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main()
{
	try
	{
		boost::asio::io_context io_context;

		//udp::socket socket(io_context);

		udp::socket socket(io_context, udp::endpoint(udp::v4(), 0));

		udp::endpoint server_endpoint(boost::asio::ip::make_address("127.0.0.1"), 12345);

		
		std::string message;
		while (std::getline(std::cin, message))
		{
			message += "\n";
			boost::system::error_code error;

			socket.send_to(boost::asio::buffer(message), server_endpoint, 0, error);
		
			char data[1024];
			udp::endpoint sender_endpoint;

			size_t length = socket.receive_from(boost::asio::buffer(data), sender_endpoint, 0, error);

			std::cout << "서버로부터 에코된 메시지 : " << std::string(data, length) << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "예외 발생 : " << e.what() << std::endl;
	}

	return 0;
}