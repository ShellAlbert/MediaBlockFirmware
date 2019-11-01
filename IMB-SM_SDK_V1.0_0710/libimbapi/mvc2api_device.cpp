#include "imbsdk/mvc2api_device.h"

namespace mvc2
{

	//MvcDeviceBase implementation
	bool MvcDeviceBase::operator==(const MvcDeviceBase* other) const
	{
		return ((other->getDeviceIndex() == this->getDeviceIndex()) &&
			(other->getDeviceType() == this->getDeviceType()));
	}

	//MvcDevice implementation
	MvcDevice& MvcDevice::operator=(const MvcDevice& other)
	{
		this->m_Index = other.m_Index;
		this->m_DevType = other.m_DevType;
		if (this->m_DevicePriv)
			delete this->m_DevicePriv;
		if (other.m_DevicePriv)
			this->m_DevicePriv = new int(10);
		else
			this->m_DevicePriv = NULL;

		return *this;
	}

	MvcDevice::operator bool() const
	{
		return (m_DevicePriv ? true : false);
	}


	TMmRc MvcDevice::getDeviceState() const
	{
		return 0;
	}

	uint32_t MvcDevice::getUID() const
	{
		return 0;
	}

}
