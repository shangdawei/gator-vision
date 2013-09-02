/*
 * TCPServer.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Jeff
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include "global_defs.h"
#include <vector>
#include <string.h>
#include <sys/socket.h>
#include "AManagedTask.h"
#include "TCPSession.h"



enum TCPServerState
{
   SRVR_NOT_STARTED,
   SRVR_BIND,
   SRVR_LISTENING,
   SRVR_FULL,
   SRVR_KILL
};

template <class /*TCPSession*/ SessionClass>
class TCPServer : public AManagedTask
{
public:
   TCPServer(int max_conn, int backlog);
   void Run();
   bool Start(uint32_t addr, uint16_t port);
   void Stop();
   bool IsActive();
   int NumActiveSessions();
   virtual ~TCPServer();

private:
   static const portTickType POLL_INTERVAL_MS = 5;

   void AcceptClient();
   void PollClients();
   void DisconnectAll();
   bool InitListener();

   std::vector<SessionClass> ClientSessions;

   int ListenerSocket;
   int MaxSessions;
   int ListenerBacklog;
   uint32_t ServerAddress;
   uint16_t ServerPort;
   bool ServerIsActive;
   enum TCPServerState State;
};




// Needed to separate template definitions from declarations
#include "TCPServer.cpp"

#endif /* TCPSERVER_H_ */
