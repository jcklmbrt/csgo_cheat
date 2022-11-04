
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_IHANDLEENTITY_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_IHANDLEENTITY_HPP_

#include "source_sdk/public/basehandle.hpp"

struct IHandleEntity
{
	virtual ~IHandleEntity() {}
	virtual void SetRefEHandle( const CBaseHandle &handle ) = 0;
	virtual const CBaseHandle& GetRefEHandle() const = 0;
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_IHANDLEENTITY_HPP_
