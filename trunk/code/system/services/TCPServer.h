/*
 * TCPServer.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Jeff
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include "global_defs.h"
#include "AManagedTask.h"
#include "TCPSession.h"

template <class /*TCPSession*/ SessionClass>
class TCPServer : public AManagedTask
{
public:
   TCPServer(int max_conn, int backlog);
   void Run();
   bool Start(uint32_t addr, uint16_t port);
   void Stop();
   bool IsActive();
   virtual ~TCPServer();
};

#endif /* TCPSERVER_H_ */
