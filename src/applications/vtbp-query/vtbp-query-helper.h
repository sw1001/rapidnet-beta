#ifndef VTBPQUERY_HELPER_H
#define VTBPQUERY_HELPER_H

#include "ns3/rapidnet-application-helper.h"
#include "vtbp-query.h"

namespace ns3 {
namespace rapidnet {
namespace vtbpquery {

class VtbpQuery;

class VtbpQueryHelper: public RapidNetApplicationHelper
{
public:
  VtbpQueryHelper ()
  {
    m_factory.SetTypeId (VtbpQuery::GetTypeId ());
  }
  virtual ~VtbpQueryHelper ()
  {
  }

protected:
  Ptr<RapidNetApplicationBase> CreateNewApplication ()
  {
    return m_factory.Create<VtbpQuery> ();
  }
};

} // namespace vtbpquery
} // namespace rapidnet
} // namespace ns3

#endif // VTBPQUERY_HELPER_H

