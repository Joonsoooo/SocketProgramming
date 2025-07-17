#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
	try
	{
		boost::asio::io_context io_context;

		tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));
		std::cout << "Server is listening on port 12345..." << std::endl;

		while (true)
		{
			tcp::socket socket(io_context);
			acceptor.accept(socket);

			boost::asio::streambuf buf;
			boost::asio::read_until(socket, buf, "\n");

			std::istream is(&buf);
			std::string message;
			std::getline(is, message);
			std::cout << "Received : " << message << std::endl;

			boost::asio::write(socket, boost::asio::buffer(message + "\n"));
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}