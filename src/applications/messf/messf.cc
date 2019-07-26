/* A RapidNet application. Generated by RapidNet compiler. */

#include "messf.h"
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
using namespace ns3::rapidnet::messf;

const string Messf::FINAL = "final";
const string Messf::LINK = "link";
const string Messf::MSG = "msg";
const string Messf::SOURCE = "source";

NS_LOG_COMPONENT_DEFINE ("Messf");
NS_OBJECT_ENSURE_REGISTERED (Messf);

TypeId
Messf::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::rapidnet::messf::Messf")
    .SetParent<RapidNetApplicationBase> ()
    .AddConstructor<Messf> ()
    ;
  return tid;
}

Messf::Messf()
{
  NS_LOG_FUNCTION_NOARGS ();
}

Messf::~Messf()
{
  NS_LOG_FUNCTION_NOARGS ();
}

void
Messf::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::DoDispose ();
}

void
Messf::StartApplication (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::StartApplication ();
  RAPIDNET_LOG_INFO("Messf Application Started");
}

void
Messf::StopApplication ()
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::StopApplication ();
  RAPIDNET_LOG_INFO("Messf Application Stopped");
}

void
Messf::InitDatabase ()
{
  //RapidNetApplicationBase::InitDatabase ();

  AddRelationWithKeys (FINAL, attrdeflist (
    attrdef ("final_attr1", IPV4),
    attrdef ("final_attr2", STR)));

  AddRelationWithKeys (LINK, attrdeflist (
    attrdef ("link_attr1", IPV4),
    attrdef ("link_attr2", IPV4)));

  AddRelationWithKeys (SOURCE, attrdeflist (
    attrdef ("source_attr1", IPV4),
    attrdef ("source_attr2", IPV4)));

}

void
Messf::DemuxRecv (Ptr<Tuple> tuple)
{
  RapidNetApplicationBase::DemuxRecv (tuple);

  if (IsInsertEvent (tuple, SOURCE))
    {
      R1Eca0Ins (tuple);
    }
  if (IsRecvEvent (tuple, MSG))
    {
      R2_eca (tuple);
    }
  if (IsRecvEvent (tuple, MSG))
    {
      R3_eca (tuple);
    }
}

void
Messf::R1Eca0Ins (Ptr<Tuple> source)
{
  RAPIDNET_LOG_INFO ("R1Eca0Ins triggered");

  Ptr<Tuple> result = source;

  result->Assign (Assignor::New ("TTL",
    ValueExpr::New (Int32Value::New (0))));

  result = result->Project (
    MSG,
    strlist ("source_attr1",
      "source_attr2",
      "source_attr3",
      "TTL"),
    strlist ("msg_attr1",
      "msg_attr2",
      "msg_attr3",
      "msg_attr4"));

  SendLocal (result);
}

void
Messf::R2_eca (Ptr<Tuple> msg)
{
  RAPIDNET_LOG_INFO ("R2_eca triggered");

  Ptr<RelationBase> result;

  result = GetRelation (LINK)->Join (
    msg,
    strlist ("link_attr1"),
    strlist ("msg_attr1"));

  result->Assign (Assignor::New ("TTL1",
    Operation::New (RN_PLUS,
      VarExpr::New ("msg_attr4"),
      ValueExpr::New (Int32Value::New (1)))));

  result->Assign (Assignor::New ("S",
    Operation::New (RN_TIMES,
      VarExpr::New ("link_attr3"),
      VarExpr::New ("msg_attr3"))));

  result = result->Select (Selector::New (
    Operation::New (RN_LT,
      VarExpr::New ("msg_attr4"),
      ValueExpr::New (Int32Value::New (5)))));

  result = result->Project (
    MSG,
    strlist ("link_attr2",
      "msg_attr2",
      "S",
      "TTL1",
      "link_attr2"),
    strlist ("msg_attr1",
      "msg_attr2",
      "msg_attr3",
      "msg_attr4",
      RN_DEST));

  Send (result);
}

void
Messf::R3_eca (Ptr<Tuple> msg)
{
  RAPIDNET_LOG_INFO ("R3_eca triggered");

  Ptr<Tuple> result = msg;

  result = result->Project (
    FINAL,
    strlist ("msg_attr1",
      "msg_attr2"),
    strlist ("final_attr1",
      "final_attr2"));

  Insert (result);
}

