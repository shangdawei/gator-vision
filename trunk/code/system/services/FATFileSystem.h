/*
 * FATFileSystem.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Jeff
 */

#ifndef FATFILESYSTEM_H_
#define FATFILESYSTEM_H_

#include "FileSystem.h"

class FATFileSystem : public FileSystem
{
public:
   FATFileSystem();
   virtual ~FATFileSystem();
};

#endif /* FATFILESYSTEM_H_ */
