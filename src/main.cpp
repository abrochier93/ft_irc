#include "Libs.hpp"
#include "Server.hpp"

int main()
{
	Server serveur("123");

	serveur.init();
	serveur.listenForEvents();

	return (0);
}

