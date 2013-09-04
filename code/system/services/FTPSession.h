/*
 * FTPSession.h
 *
 *  Created on: Jul 16, 2013
 *      Author: Jeff
 */

#ifndef FTPSESSION_H_
#define FTPSESSION_H_

#include "TCPSession.h"

class FTPSession: public TCPSession
{
public:
   FTPSession(int sockfd) : TCPSession(sockfd) { }
   bool Poll();
   ~FTPSession();
};

#endif /* FTPSESSION_H_ */
