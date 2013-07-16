/*
 * USBMassStorage.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Jeff
 */

#ifndef USBMASSSTORAGE_H_
#define USBMASSSTORAGE_H_

#include "USBDevice.h"

class USBMassStorage : USBDevice
{
public:
   USBMassStorage();
   virtual ~USBMassStorage();
};

#endif /* USBMASSSTORAGE_H_ */
