/////////////////////////////////////////////////////////////////////
//
// This software is provided "AS IS".  The JavaPOS working group (including
// each of the Corporate members, contributors and individuals)  MAKES NO
// REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NON-INFRINGEMENT. The JavaPOS working group shall not be liable for
// any damages suffered as a result of using, modifying or distributing this
// software or its derivatives.Permission to use, copy, modify, and distribute
// the software and its documentation for any purpose is hereby granted.
//
// RemoteOrderDisplayService19
//
//   Interface definining all new capabilities, properties and
//                                                                 1.9
// Modification history
// ------------------------------------------------------------------
//                             1.9
/////////////////////////////////////////////////////////////////////

package jpos.services;

import jpos.*;

public interface RemoteOrderDisplayService19
  extends RemoteOrderDisplayService18
{
  // Capabilities
  public boolean getCapCompareFirmwareVersion() throws JposException;
  public boolean getCapUpdateFirmware() throws JposException;

  // Methods
  public void    compareFirmwareVersion(String firmwareFileName, int[] result)
                     throws JposException;
  public void    updateFirmware(String firmwareFileName)
                     throws JposException;
}