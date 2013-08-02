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
   TCPSession();
   virtual void Reset() = 0;
   void OnConnect(int sockfd) { Reset(); SocketNum = sockfd; }
   virtual bool Poll() = 0;
   virtual void OnDisconnect() = 0;
   virtual ~TCPSession() { }

protected:
   int SocketNum;
};

#endif /* TCPSESSION_H_ */
