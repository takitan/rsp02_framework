#include "rsp02.hpp"

bool str2dst( const char* str, EDestination& dst)
{
	if( strcasecmp( str, "Null")==0){ dst = EDestination::Null; return true;}
	if( strcasecmp( str, "Ground")==0){ dst = EDestination::Ground; return true;}
	if( strcasecmp( str, "Rx")==0){ dst = EDestination::Rx; return true;}
	if( strcasecmp( str, "Tx1")==0){ dst = EDestination::Tx1; return true;}
	if( strcasecmp( str, "Tx2")==0){ dst = EDestination::Tx2; return true;}
	if( strcasecmp( str, "CDH")==0){ dst = EDestination::CDH; return true;}
	if( strcasecmp( str, "Mission")==0){ dst = EDestination::Mission; return true;}
	if( strcasecmp( str, "ParentLora")==0){ dst = EDestination::ParentLora; return true;}
	if( strcasecmp( str, "Child1")==0){ dst = EDestination::Child1; return true;}
	if( strcasecmp( str, "Child2")==0){ dst = EDestination::Child2; return true;}
	return false;
}

bool dst2str(const EDestination dst, const char* str)
{
	switch( dst)
	{
		case EDestination::Null: str = "Null"; return true;
		case EDestination::Ground: str = "Ground"; return true;
		case EDestination::Rx: str = "Rx"; return true;
		case EDestination::Tx1: str = "Tx1"; return true;
		case EDestination::Tx2: str = "Tx2"; return true;
		case EDestination::CDH: str = "CDH"; return true;
		case EDestination::Mission: str = "Mission"; return true;
		case EDestination::ParentLora: str = "ParentLora"; return true;
		case EDestination::Child1: str = "Child1"; return true;
		case EDestination::Child2: str = "Child2"; return true;
		default: return true;
	}
}
