/*
 * TCPSession.h
 *
 *  Created on: Jul 16, 2013
 *      Author: Jeff
 */

#ifndef TCPSESSION_H_
#define TCPSESSION_H_

#include "lwip/sockets.h"

class TCPSession
{
public:
   TCPSession() { SocketNum = -1; }
   TCPSession(int sockfd) { SocketNum = sockfd; }
   virtual bool Poll() = 0;
   virtual ~TCPSession() { }
   int GetSocketNum() { return SocketNum; }

protected:
   int SocketNum;

};

#endif /* TCPSESSION_H_ */
