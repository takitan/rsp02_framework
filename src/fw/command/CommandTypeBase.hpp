#pragma once

namespace rsp{
namespace rsp02{
namespace fw{
namespace command{

template<typename T>
struct CommandTypeBase_t
{
	using align = rsp::rsp02::fw::util::align;
	using dst_t = typename T::dst_t;
	using type_t = typename T::type_t;
	using len_t = typename T::len_t;
	dst_t destination;
	type_t type;
	len_t length;

	CommandTypeBase_t(){}
	CommandTypeBase_t(dst_t dst, type_t typ, len_t len) :
		destination(dst), type(typ), length(len){}

	CommandTypeBase_t(const T &tlv) :
		destination(tlv.destination), type(tlv.type), length(tlv.length){}
	CommandTypeBase_t(const T* &tlv) :
		destination(tlv->destination), type(tlv->type), length(tlv->length){}
	CommandTypeBase_t(T &tlv) :
		destination(tlv.destination), type(tlv.type), length(tlv.length){}
	CommandTypeBase_t(T* &tlv) :
		destination(tlv->destination), type(tlv->type), length(tlv->length){}
};

}
}
}
}
