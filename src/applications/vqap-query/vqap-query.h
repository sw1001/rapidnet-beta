/* A RapidNet application. Generated by RapidNet compiler. */

#ifndef VQAPQUERY_H
#define VQAPQUERY_H

#include <string>
#include <iostream>
#include "ns3/ptr.h"
#include "ns3/event-id.h"
#include "ns3/ipv4-address.h"
#include "ns3/rapidnet-header.h"
#include "ns3/relation-base.h"
#include "ns3/database.h"
#include "ns3/rapidnet-application-base.h"
#include "ns3/aggregator.h"
#include "ns3/aggwrap.h"

using namespace std;
using namespace ns3;

namespace ns3 {

class Socket;
class Packet;

namespace rapidnet {
namespace vqapquery {

class VqapQuery : public RapidNetApplicationBase
{
public:
  static const string PRETURN;
  static const string PERIODIC;
  static const string PROVQUERY;
  static const string Q1_ECAPERIODIC;
  static const string RECORDS;
  static const string TUPLE;

  static TypeId GetTypeId (void);

  VqapQuery ();

  virtual ~VqapQuery ();

protected:

  virtual void DoDispose (void);

  virtual void StartApplication (void);

  virtual void StopApplication (void);

  virtual void InitDatabase (void);

  virtual void DemuxRecv (Ptr<Tuple> tuple);

  virtual void Q1_ecaperiodic ();

  virtual void Q1_eca (Ptr<Tuple> q1_ecaperiodic);

  virtual void Q2_eca (Ptr<Tuple> pReturn);

  uint32_t m_count_q1_ecaperiodic;
  EventId m_event_q1_ecaperiodic;
};

} // namespace vqapquery
} // namespace rapidnet
} // namespace ns3

#endif // VQAPQUERY_H
