#pragma once
namespace rsp{
namespace rsp02{
namespace fw{
namespace time{

typedef long (*TimeProvider_t)(void);

extern TimeProvider_t TimeProvider;

}
}
}
}
