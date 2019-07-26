#ifndef VITERBIQUERY_HELPER_H
#define VITERBIQUERY_HELPER_H

#include "ns3/rapidnet-application-helper.h"
#include "viterbi-query.h"

namespace ns3 {
namespace rapidnet {
namespace viterbiquery {

class ViterbiQuery;

class ViterbiQueryHelper: public RapidNetApplicationHelper
{
public:
  ViterbiQueryHelper ()
  {
    m_factory.SetTypeId (ViterbiQuery::GetTypeId ());
  }
  virtual ~ViterbiQueryHelper ()
  {
  }

protected:
  Ptr<RapidNetApplicationBase> CreateNewApplication ()
  {
    return m_factory.Create<ViterbiQuery> ();
  }
};

} // namespace viterbiquery
} // namespace rapidnet
} // namespace ns3

#endif // VITERBIQUERY_HELPER_H

