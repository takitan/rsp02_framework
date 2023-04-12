#pragma once
#include <cstdint>

struct TLVmessage_t
{
	typedef uint8_t type_t;
	typedef uint8_t dest_t;
	typedef uint16_t len_t;

	dest_t destination;
	type_t type;
	len_t length;
	uint8_t pValue[];
};

enum class EType : TLVmessage_t::type_t
{
	Null = 0,
	RequestPing = 1,
};

enum class EDestination : TLVmessage_t::dest_t
{
	Null = 0,
	Ground = 1,
};

struct MissionTLV
{
	EDestination destination;
	EType type;
	uint16_t length;
	uint8_t pValue[];
};
