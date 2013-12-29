/*
 * HotMountManager.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Jeff
 */

#ifndef HOTMOUNTMANAGER_H_
#define HOTMOUNTMANAGER_H_

#include "AManagedTask.h"
#include "FATFileSystem.h"

class HotMountManager : public AManagedTask
{
public:
   HotMountManager();
   virtual ~HotMountManager();

private:
   FATFileSystem * FatFS;
};

#endif /* HOTMOUNTMANAGER_H_ */
