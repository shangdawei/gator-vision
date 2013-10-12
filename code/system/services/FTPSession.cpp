/*
 * FTPSession.cpp
 *
 *  Created on: Jul 16, 2013
 *      Author: Jeff
 */

#include "FTPSession.h"


bool FTPSession::Poll()
{
   bool stay_alive = false;

   write(SocketNum, "421 Hello World!\n", 17);

   return stay_alive;
}


FTPSession::~FTPSession()
{

}
