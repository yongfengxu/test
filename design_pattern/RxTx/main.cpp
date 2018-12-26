#include "Client.h"
#include "Server.h"


int main()
{
	Server* server = new Server();
	Client* client = new Client(*server);

	server->setTx(*client);

	client->getRx().startReq(10);


	server->print();

	server->getTx()->onStartRsp(server->getValue());
}
