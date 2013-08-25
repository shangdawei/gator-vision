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
   void Reset();
   bool Poll();
   void OnDisconnect();
};

#endif /* FTPSESSION_H_ */
