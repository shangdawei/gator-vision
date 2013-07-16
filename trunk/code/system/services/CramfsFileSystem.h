/*
 * CramfsFileSystem.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Jeff
 */

#ifndef CRAMFSFILESYSTEM_H_
#define CRAMFSFILESYSTEM_H_

#include "FileSystem.h"

class CramfsFileSystem : public FileSystem
{
public:
   CramfsFileSystem();
   virtual ~CramfsFileSystem();
};

#endif /* CRAMFSFILESYSTEM_H_ */
