#include <link/iwp.hpp>
#include <link/iwp_internal.hpp>

namespace llarp
{
  namespace iwp
  {
    std::unique_ptr< ILinkLayer >
    NewServerFromRouter(AbstractRouter*)
    {
      // TODO: implement me
      return nullptr;
    }

    std::unique_ptr< ILinkLayer >
    NewServer(llarp::Crypto*, const SecretKey&, llarp::GetRCFunc,
              llarp::LinkMessageHandler, llarp::SessionEstablishedHandler,
              llarp::SessionRenegotiateHandler, llarp::SignBufferFunc,
              llarp::TimeoutHandler, llarp::SessionClosedHandler)
    {
      // TODO: implement me
      return nullptr;
    }
  }  // namespace iwp
}  // namespace llarp
