/*
 * TCPServer.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Jeff
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include "AManagedTask.h"
#include "TCPSession.h"

template <TCPSession SessionClass>
class TCPServer : public AManagedTask
{
public:
   TCPServer();
   virtual ~TCPServer();
};

#endif /* TCPSERVER_H_ */
