/*
 * USBHumanInterface.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Jeff
 */

#ifndef USBHUMANINTERFACE_H_
#define USBHUMANINTERFACE_H_

#include "USBDevice.h"

class USBHumanInterface: public USBDevice
{
public:
   USBHumanInterface();
   virtual ~USBHumanInterface();
};

#endif /* USBHUMANINTERFACE_H_ */
