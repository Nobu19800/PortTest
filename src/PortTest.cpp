// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  PortTest.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "PortTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const porttest_spec[] =
#else
static const char* porttest_spec[] =
#endif
  {
    "implementation_id", "PortTest",
    "type_name",         "PortTest",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PortTest::PortTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_port_count(0)
    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PortTest::~PortTest()
{
}



RTC::ReturnCode_t PortTest::onInitialize()
{
    addTimedLongPort();
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers

  
  // Set OutPort buffer

  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PortTest::onFinalize()
{
    
    for (auto& port : m_port_list)
    {
        removeInPort(port->m_inIn);
        delete port;
    }
    
  return RTC::RTC_OK;
}



//RTC::ReturnCode_t PortTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PortTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PortTest::onActivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PortTest::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PortTest::onExecute(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PortTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PortTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PortTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PortTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PortTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

TimedLongPort* PortTest::addTimedLongPort()
{
    std::string name = "inport_" + std::to_string(m_port_count);
    m_port_count++;
    TimedLongPort* port = new TimedLongPort(name);
    port->m_inIn.addConnectorListener(RTC::ConnectorListenerType::ON_CONNECT,
        new ConnListener(this));
    //port->m_inIn.addConnectorListener(RTC::ConnectorListenerType::ON_DISCONNECT,
    //    new DisConnListener(this, port));

    addInPort(name.c_str(), port->m_inIn);
    m_port_list.push_back(port);

    return port;
}
/*
void PortTest::removeTimedLongPort(TimedLongPort* port)
{
    m_port_list.erase(std::remove(m_port_list.begin(), m_port_list.end(), port), m_port_list.end());
    removeInPort(port->m_inIn);
    //delete port;
}
*/

RTC::ConnectorListener::ReturnCode ConnListener::operator()(RTC::ConnectorInfo& info)
{
    if(!m_created)
    {
        m_comp->addTimedLongPort();
    }
    m_created = true;
    
    return NO_CHANGE;
}

/*
RTC::ConnectorListener::ReturnCode DisConnListener::operator()(RTC::ConnectorInfo& info)
{
    m_comp->removeTimedLongPort(m_port);
    return NO_CHANGE;
}
*/



extern "C"
{
 
  void PortTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(porttest_spec);
    manager->registerFactory(profile,
                             RTC::Create<PortTest>,
                             RTC::Delete<PortTest>);
  }
  
}
