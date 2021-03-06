/* A RapidNet application. Generated by RapidNet compiler. */

#include "vtbp-query.h"
#include <cstdlib>
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/type-ids.h"
#include "ns3/rapidnet-types.h"
#include "ns3/rapidnet-utils.h"
#include "ns3/assignor.h"
#include "ns3/selector.h"
#include "ns3/rapidnet-functions.h"

using namespace std;
using namespace ns3;
using namespace ns3::rapidnet;
using namespace ns3::rapidnet::vtbpquery;

const string VtbpQuery::PRETURN = "pReturn";
const string VtbpQuery::PERIODIC = "periodic";
const string VtbpQuery::PROVQUERY = "provQuery";
const string VtbpQuery::Q1_ECAPERIODIC = "q1_ecaperiodic";
const string VtbpQuery::RECORDS = "records";
const string VtbpQuery::TUPLE = "tuple";

NS_LOG_COMPONENT_DEFINE ("VtbpQuery");
NS_OBJECT_ENSURE_REGISTERED (VtbpQuery);

TypeId
VtbpQuery::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::rapidnet::vtbpquery::VtbpQuery")
    .SetParent<RapidNetApplicationBase> ()
    .AddConstructor<VtbpQuery> ()
    ;
  return tid;
}

VtbpQuery::VtbpQuery()
{
  NS_LOG_FUNCTION_NOARGS ();
}

VtbpQuery::~VtbpQuery()
{
  NS_LOG_FUNCTION_NOARGS ();
}

void
VtbpQuery::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::DoDispose ();
}

void
VtbpQuery::StartApplication (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::StartApplication ();
  m_event_q1_ecaperiodic=
    Simulator::Schedule (Seconds (0), &VtbpQuery::Q1_ecaperiodic, this);
  m_count_q1_ecaperiodic = 0;
  RAPIDNET_LOG_INFO("VtbpQuery Application Started");
}

void
VtbpQuery::StopApplication ()
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::StopApplication ();
  Simulator::Cancel(m_event_q1_ecaperiodic);
  RAPIDNET_LOG_INFO("VtbpQuery Application Stopped");
}

void
VtbpQuery::InitDatabase ()
{
  //RapidNetApplicationBase::InitDatabase ();

  AddRelationWithKeys (RECORDS, attrdeflist (
    attrdef ("records_attr1", IPV4),
    attrdef ("records_attr2", ID),
    attrdef ("records_attr3", ID)));

  AddRelationWithKeys (TUPLE, attrdeflist (
    attrdef ("tuple_attr1", IPV4),
    attrdef ("tuple_attr2", STR)));

}

void
VtbpQuery::DemuxRecv (Ptr<Tuple> tuple)
{
  RapidNetApplicationBase::DemuxRecv (tuple);

  if (IsRecvEvent (tuple, Q1_ECAPERIODIC))
    {
      Q1_eca (tuple);
    }
  if (IsRecvEvent (tuple, PRETURN))
    {
      Q2_eca (tuple);
    }
}

void
VtbpQuery::Q1_ecaperiodic ()
{
  RAPIDNET_LOG_INFO ("Q1_ecaperiodic triggered");

  SendLocal (tuple (Q1_ECAPERIODIC, attrlist (
    attr ("q1_ecaperiodic_attr1", Ipv4Value, GetAddress ()),
    attr ("q1_ecaperiodic_attr2", Int32Value, rand ()))));

  if (++m_count_q1_ecaperiodic < 2)
    {
      m_event_q1_ecaperiodic = Simulator::Schedule (Seconds(4),
        &VtbpQuery::Q1_ecaperiodic, this);
    }
}

void
VtbpQuery::Q1_eca (Ptr<Tuple> q1_ecaperiodic)
{
  RAPIDNET_LOG_INFO ("Q1_eca triggered");

  Ptr<RelationBase> result;

  result = GetRelation (TUPLE)->Join (
    q1_ecaperiodic,
    strlist ("tuple_attr1"),
    strlist ("q1_ecaperiodic_attr1"));

  result->Assign (Assignor::New ("UID",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          Operation::New (RN_PLUS,
            Operation::New (RN_PLUS,
              Operation::New (RN_PLUS,
                Operation::New (RN_PLUS,
                  Operation::New (RN_PLUS,
                    VarExpr::New ("tuple_attr2"),
                    VarExpr::New ("tuple_attr3")),
                  ValueExpr::New (StrValue::New (","))),
                VarExpr::New ("tuple_attr4")),
              ValueExpr::New (StrValue::New (","))),
            VarExpr::New ("tuple_attr5")),
          ValueExpr::New (StrValue::New (","))),
        VarExpr::New ("tuple_attr6")))));

  result->Assign (Assignor::New ("Time",
    FNow::New (
)));

  result->Assign (Assignor::New ("QID",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          ValueExpr::New (StrValue::New ("")),
          VarExpr::New ("UID")),
        VarExpr::New ("Time")))));

  result->Assign (Assignor::New ("P",
    FAppend::New (
      ValueExpr::New (StrValue::New ("")))));

  result = result->Project (
    PROVQUERY,
    strlist ("tuple_attr3",
      "QID",
      "UID",
      "P",
      "q1_ecaperiodic_attr1",
      "tuple_attr3"),
    strlist ("provQuery_attr1",
      "provQuery_attr2",
      "provQuery_attr3",
      "provQuery_attr4",
      "provQuery_attr5",
      RN_DEST));

  Send (result);
}

void
VtbpQuery::Q2_eca (Ptr<Tuple> pReturn)
{
  RAPIDNET_LOG_INFO ("Q2_eca triggered");

  Ptr<Tuple> result = pReturn;

  result = result->Project (
    RECORDS,
    strlist ("pReturn_attr1",
      "pReturn_attr2",
      "pReturn_attr3",
      "pReturn_attr4"),
    strlist ("records_attr1",
      "records_attr2",
      "records_attr3",
      "records_attr4"));

  Insert (result);
}

