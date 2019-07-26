#ifndef VITERBI_HELPER_H
#define VITERBI_HELPER_H

#include "ns3/rapidnet-application-helper.h"
#include "viterbi.h"

namespace ns3 {
namespace rapidnet {
namespace viterbi {

class Viterbi;

class ViterbiHelper: public RapidNetApplicationHelper
{
public:
  ViterbiHelper ()
  {
    m_factory.SetTypeId (Viterbi::GetTypeId ());
  }
  virtual ~ViterbiHelper ()
  {
  }

protected:
  Ptr<RapidNetApplicationBase> CreateNewApplication ()
  {
    return m_factory.Create<Viterbi> ();
  }
};

} // namespace viterbi
} // namespace rapidnet
} // namespace ns3

#endif // VITERBI_HELPER_H

