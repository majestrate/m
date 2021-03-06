#ifndef __ABYSS_SERVER_HPP__
#define __ABYSS_SERVER_HPP__

#include <ev/ev.h>
#include <util/json.hpp>
#include <util/logic.hpp>
#include <util/string_view.hpp>
#include <util/time.hpp>

#include <list>
#include <memory>
#include <string>
#include <unordered_map>

namespace abyss
{
  namespace httpd
  {
    struct ConnImpl;

    struct IRPCHandler
    {
      using Method_t = std::string;
      using Params   = llarp::json::Value;
      using Response = llarp::json::Writer;

      IRPCHandler(ConnImpl* impl);

      virtual bool
      HandleJSONRPC(Method_t method, const Params& params,
                    Response& response) = 0;

      virtual ~IRPCHandler();

      bool
      ShouldClose(llarp_time_t now) const;

     private:
      ConnImpl* m_Impl;
    };

    struct BaseReqHandler
    {
      BaseReqHandler(llarp_time_t req_timeout);
      ~BaseReqHandler();

      bool
      ServeAsync(llarp_ev_loop* loop, llarp::Logic* logic,
                 const sockaddr* bindaddr);

      void
      RemoveConn(IRPCHandler* handler);

      /// close the handler and acceptor
      void
      Close();

      llarp_time_t
      now() const
      {
        return llarp_ev_loop_time_now_ms(m_loop);
      }

     protected:
      virtual IRPCHandler*
      CreateHandler(ConnImpl* connimpl) = 0;

     private:
      static void
      OnTick(llarp_tcp_acceptor*);

      void
      Tick();

      static void
      OnAccept(struct llarp_tcp_acceptor*, struct llarp_tcp_conn*);

      llarp_ev_loop* m_loop;
      llarp::Logic* m_Logic;
      llarp_tcp_acceptor m_acceptor;
      std::list< std::unique_ptr< IRPCHandler > > m_Conns;
      llarp_time_t m_ReqTimeout;
    };
  }  // namespace httpd
}  // namespace abyss

#endif
