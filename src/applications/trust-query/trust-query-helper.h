#ifndef TRUSTQUERY_HELPER_H
#define TRUSTQUERY_HELPER_H

#include "ns3/rapidnet-application-helper.h"
#include "trust-query.h"

namespace ns3 {
namespace rapidnet {
namespace trustquery {

class TrustQuery;

class TrustQueryHelper: public RapidNetApplicationHelper
{
public:
  TrustQueryHelper ()
  {
    m_factory.SetTypeId (TrustQuery::GetTypeId ());
  }
  virtual ~TrustQueryHelper ()
  {
  }

protected:
  Ptr<RapidNetApplicationBase> CreateNewApplication ()
  {
    return m_factory.Create<TrustQuery> ();
  }
};

} // namespace trustquery
} // namespace rapidnet
} // namespace ns3

#endif // TRUSTQUERY_HELPER_H

