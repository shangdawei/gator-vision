/*
 * TCPServer.cpp
 *
 *  Created on: Jul 15, 2013
 *      Author: Jeff
 */

// Since this is just a template, the template definition (below) needs to be included in the header file
#ifdef TCPSERVER_H_

template <class /*TCPSession*/ SessionClass>
TCPServer<SessionClass>::TCPServer(int max_conn, int backlog)
{
   State = SRVR_NOT_STARTED;
   MaxSessions = max_conn;
   ListenerBacklog = backlog;
   ServerIsActive = false;
   ServerAddress = 0;
   ServerPort = 0;

   // Allocate memory for the client sessions once on init
   ClientSessions.reserve(max_conn);
}

template <class /*TCPSession*/ SessionClass>
void TCPServer<SessionClass>::Run()
{
   while (true)
   {
      // State machine to handle the server
      switch (State)
      {
      case SRVR_NOT_STARTED:
         // Idle state waits for the server to be started
         if (ServerIsActive)
         {
            State = SRVR_BIND;
         }
         break;

      case SRVR_BIND:

         // Create, bind, and listen the listener socket
         ServerIsActive = InitListener();

         if (ServerIsActive)
         {
            // Poll each of the client sessions
            PollClients();
            State = SRVR_LISTENING;
         }
         else
         {
            // Disconnect all connected clients
            DisconnectAll();
            State = SRVR_NOT_STARTED;
         }

         break;

      case SRVR_LISTENING:

         if (!ServerIsActive)
         {
            // Disconnect all connected clients
            DisconnectAll();
            State = SRVR_NOT_STARTED;
         }
         else
         {
            // Accept incoming connections
            AcceptClient();

            // Poll each of the client sessions
            PollClients();
         }

         // If the number of connected clients reaches the max, stop listening
         if (NumActiveSessions() >= MaxSessions)
         {
            close(ListenerSocket);
            State = SRVR_FULL;
         }

         break;

      case SRVR_FULL:

         if (!ServerIsActive)
         {
            // Disconnect all connected clients
            DisconnectAll();
            State = SRVR_NOT_STARTED;
         }
         else
         {
            // Poll each of the client sessions
            PollClients();
         }

         // If the number of connected clients is less than the max, then bind and listen for connections again
         if (NumActiveSessions() < MaxSessions)
         {
            State = SRVR_BIND;
         }

         break;

      default:
         ServerIsActive = false;
         ServerAddress = 0;
         ServerPort = 0;
         State = SRVR_NOT_STARTED;
         break;

      }

      Delay(POLL_INTERVAL_MS);
   }
}


template <class /*TCPSession*/ SessionClass>
int TCPServer<SessionClass>::NumActiveSessions()
{
   return ClientSessions.size();
}


template <class /*TCPSession*/ SessionClass>
bool TCPServer<SessionClass>::InitListener()
{
   bool retval;

   ListenerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if (ListenerSocket < 0)
   {
      // Could not make a new socket
      retval = false;
   }
   else
   {
      // Made the new listener socket
      // Bind it to a port
      struct sockaddr_in serv_addr;

      (void)memset(&serv_addr, 0, sizeof(serv_addr));
      serv_addr.sin_family = AF_INET;
      serv_addr.sin_port = htons(ServerPort);
      serv_addr.sin_addr.s_addr = htonl(ServerAddress);

      if ( -1 == bind( ListenerSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr) ) )
      {
         // Could not bind to that address and port
         close(ListenerSocket);
         retval = false;
      }
      else
      {
         // Binding completed successfully
         // Start listening
         if ( -1 == listen( ListenerSocket, ListenerBacklog ) )
         {
            // Could not listen on the bound address and port
            close(ListenerSocket);
            retval = false;
         }
         else
         {
            retval = true;
         }
      }
   }

   return retval;

}


template <class /*TCPSession*/ SessionClass>
void TCPServer<SessionClass>::AcceptClient()
{
   // Set the nonblocking flag on the listener socket
   int sck_flags;
   int err;
   int accepted_sck;
   struct sockaddr cliaddr;
   socklen_t addrlen;

   sck_flags = fcntl(ListenerSocket, F_GETFL, 0);
   sck_flags |= O_NONBLOCK;
   err = fcntl(ListenerSocket, F_SETFL, sck_flags);
   if (0 == err)
   {
      // Setting listener to non-blocking succeeded
      // See if we can accept another connection
      if (NumActiveSessions() < MaxSessions)
      {
         // Haven't reached the max number of client sessions yet
         // Try to accept an incoming client connection
         accepted_sck = accept(ListenerSocket, &cliaddr, &addrlen);
         if (accepted_sck >= 0)
         {
            // Accepted an incoming connection
            // Add session to list so we can start polling it
            ClientSessions.push_back(SessionClass(accepted_sck));
         }
      }
   }


}

template <class /*TCPSession*/ SessionClass>
void TCPServer<SessionClass>::PollClients()
{
   // Loop through each session in the vector
   typename std::vector<SessionClass>::iterator i = ClientSessions.begin();
   while ( i != ClientSessions.end() )
   {
      bool keep_alive = (*i).Poll();

      if (keep_alive)
      {
         i++;
      }
      else
      {
         i = ClientSessions.erase(i);
      }

   }
}


template <class /*TCPSession*/ SessionClass>
void TCPServer<SessionClass>::DisconnectAll()
{
   ClientSessions.clear();
}

template <class /*TCPSession*/ SessionClass>
bool TCPServer<SessionClass>::Start(uint32_t addr, uint16_t port)
{
   bool started = false;

   if (!ServerIsActive)
   {
      ServerIsActive = true;
      ServerAddress = addr;
      ServerPort = port;
      started = true;
   }

   return started;
}


template <class /*TCPSession*/ SessionClass>
void TCPServer<SessionClass>::Stop()
{
   ServerIsActive = false;
}


template <class /*TCPSession*/ SessionClass>
bool TCPServer<SessionClass>::IsActive()
{
   return ServerIsActive;
}

template <class /*TCPSession*/ SessionClass>
TCPServer<SessionClass>::~TCPServer()
{
   // TODO Auto-generated destructor stub
}

#endif

