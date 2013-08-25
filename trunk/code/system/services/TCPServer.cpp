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
   MaxSessions = max_conn;
   ListenerBacklog = backlog;
   ServerIsActive = false;
   ServerAddress = 0;
   ServerPort = 0;
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
         ListenerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
         if (ListenerSocket < 0)
         {
            // Could not make a new socket
            ServerIsActive = false;
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
               ServerIsActive = false;
            }
            else
            {
               // Binding completed successfully
               // Start listening
               if ( -1 == listen( ListenerSocket, ListenerBacklog ) )
               {
                  // Could not listen on the bound address and port
                  close(ListenerSocket);
                  ServerIsActive = false;
               }
               else
               {
                  State = SRVR_LISTENING;
               }
            }
         }

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
            // Poll each of the client sessions
            PollClients();
         }

         // If the number of connected clients reaches the max, stop listening

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

         break;

      default:
         ServerIsActive = false;
         ServerAddress = 0;
         ServerPort = 0;
         State = SRVR_NOT_STARTED;
         break;

         // Listen on a port

         // Accept connections

         // Manage session lifetimes

         // Poll active connections
      }

      Delay(5);
   }
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

