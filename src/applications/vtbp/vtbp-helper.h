#ifndef VTBP_HELPER_H
#define VTBP_HELPER_H

#include "ns3/rapidnet-application-helper.h"
#include "vtbp.h"

namespace ns3 {
namespace rapidnet {
namespace vtbp {

class Vtbp;

class VtbpHelper: public RapidNetApplicationHelper
{
public:
  VtbpHelper ()
  {
    m_factory.SetTypeId (Vtbp::GetTypeId ());
  }
  virtual ~VtbpHelper ()
  {
  }

protected:
  Ptr<RapidNetApplicationBase> CreateNewApplication ()
  {
    return m_factory.Create<Vtbp> ();
  }
};

} // namespace vtbp
} // namespace rapidnet
} // namespace ns3

#endif // VTBP_HELPER_H

