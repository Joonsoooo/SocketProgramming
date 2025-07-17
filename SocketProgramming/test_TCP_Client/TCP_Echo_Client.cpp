#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
	try
	{
		boost::asio::io_context io_context;

		tcp::resolver resolver(io_context);
		tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "12345");

		tcp::socket socket(io_context);
		boost::asio::connect(socket, endpoints);

		std::string message;
		while (std::getline(std::cin, message))
		{
			message += "\n";
			boost::asio::write(socket, boost::asio::buffer(message));

			boost::asio::streambuf buf;
			boost::asio::read_until(socket, buf, "\n");

			std::istream is(&buf);
			std::string reply;
			std::getline(is, reply);
			std::cout << "Reply: " << reply << std::endl;

		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
	}

	return 0;
}