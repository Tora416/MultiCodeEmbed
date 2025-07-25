//------------------------------------------------------------------------------
//
// THIS SOFTWARE IS PROVIDED AS IS. THE JAVAPOS WORKING GROUP MAKES NO
// REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
// NON-INFRINGEMENT.  INDIVIDUAL OR CORPORATE MEMBERS OF THE JAVAPOS
// WORKING GROUP SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED AS A RESULT
// OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
//
// BeltBeanInfo.java - Bean information for the JavaPOS Belt
//    device control
//
//------------------------------------------------------------------------------

package jpos;

import java.beans.*;
import java.lang.reflect.*;

public class BeltBeanInfo
  extends SimpleBeanInfo
{
  public BeanDescriptor getBeanDescriptor()
  {
    return new BeanDescriptor(jpos.Belt.class);
  }

  public PropertyDescriptor makeProperty(String propertyName)
    throws IntrospectionException
  {
    return new PropertyDescriptor(propertyName, jpos.Belt.class);
  }

  public PropertyDescriptor[] getPropertyDescriptors()
  {
    try
    {
      PropertyDescriptor[] properties =
      {
        // Capabilities
        makeProperty("CapAutoStopBackward"),
        makeProperty("CapAutoStopBackwardItemCount"),
        makeProperty("CapAutoStopForward"),
        makeProperty("CapAutoStopForwardItemCount"),
        makeProperty("CapCompareFirmwareVersion"),
        makeProperty("CapLightBarrierBackward"),
        makeProperty("CapLightBarrierForward"),
        makeProperty("CapMoveBackward"),
        makeProperty("CapPowerReporting"),
        makeProperty("CapRealTimeData"),
        makeProperty("CapSecurityFlapBackward"),
        makeProperty("CapSecurityFlapForward"),
        makeProperty("CapSpeedStepsBackward"),
        makeProperty("CapSpeedStepsForward"),
        makeProperty("CapStatisticsReporting"),
        makeProperty("CapUpdateFirmware"),
        makeProperty("CapUpdateStatistics"),

        // Properties
        makeProperty("AutoStopBackward"),
        makeProperty("AutoStopBackwardDelayTime"),
        makeProperty("AutoStopBackwardItemCount"),
        makeProperty("AutoStopForward"),
        makeProperty("AutoStopForwardDelayTime"),
        makeProperty("AutoStopForwardItemCount"),
        makeProperty("LightBarrierBackwardInterrupted"),
        makeProperty("LightBarrierForwardInterrupted"),
        makeProperty("MotionStatus"),
        makeProperty("PowerNotify"),
        makeProperty("PowerState"),
        makeProperty("SecurityFlapBackwardOpened"),
        makeProperty("SecurityFlapForwardOpened")
      };

      return properties;
    }
    catch(Exception e)
    {
      return super.getPropertyDescriptors();
    }
  }

  public EventSetDescriptor makeEvent(String eventName)
    throws IntrospectionException, ClassNotFoundException
  {
    String listener = "jpos.events." + eventName + "Listener";
    return new EventSetDescriptor(jpos.Belt.class,
                                  eventName,
                                  Class.forName(listener),
                                  eventName + "Occurred");
  }

  public EventSetDescriptor[] getEventSetDescriptors()
  {
    try
    {
      EventSetDescriptor[] events =
      {
        makeEvent("DirectIO"),
        makeEvent("StatusUpdate")
      };

      return events;
    }
    catch(Exception e)
    {
      return super.getEventSetDescriptors();
    }
  }
}
