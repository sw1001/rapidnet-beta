#ifndef TRUST_HELPER_H
#define TRUST_HELPER_H

#include "ns3/rapidnet-application-helper.h"
#include "trust.h"

namespace ns3 {
namespace rapidnet {
namespace trust {

class Trust;

class TrustHelper: public RapidNetApplicationHelper
{
public:
  TrustHelper ()
  {
    m_factory.SetTypeId (Trust::GetTypeId ());
  }
  virtual ~TrustHelper ()
  {
  }

protected:
  Ptr<RapidNetApplicationBase> CreateNewApplication ()
  {
    return m_factory.Create<Trust> ();
  }
};

} // namespace trust
} // namespace rapidnet
} // namespace ns3

#endif // TRUST_HELPER_H

