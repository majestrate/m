#include <util/json.hpp>
#include <util/string_view.hpp>

#include <cstring>
#include <string>
#include <vector>

namespace llarp
{
  namespace json
  {
    struct RapidJSONParser : public IParser
    {
      RapidJSONParser(size_t contentSize) : m_Buf(contentSize + 1), m_Offset(0)
      {
      }

      std::vector< char > m_Buf;
      size_t m_Offset;

      bool
      FeedData(const char* buf, size_t sz)
      {
        if(m_Offset + sz > m_Buf.size() - 1)
          return false;
        memcpy(m_Buf.data() + m_Offset, buf, sz);
        m_Offset += sz;
        m_Buf[m_Offset] = 0;
        return true;
      }

      Result
      Parse(Document& obj) const
      {
        if(m_Offset < m_Buf.size() - 1)
          return eNeedData;
        obj.Parse(m_Buf.data());
        if(obj.HasParseError())
          return eParseError;
        return eDone;
      }
    };

    IParser*
    MakeParser(size_t contentSize)
    {
      return new RapidJSONParser(contentSize);
    }

    void
    ToString(const json::Document& val, std::ostream& out)
    {
      Stream s(out);
      rapidjson::Writer< Stream > writer(s);
      val.Accept(writer);
    }

  }  // namespace json
}  // namespace llarp
