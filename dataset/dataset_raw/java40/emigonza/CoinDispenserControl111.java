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
// CoinDispenserControl111
//
//   Interface definining all new capabilities, properties and
//   methods that are specific to Coin Dispenser for release 1.11.
//
// Modification history
// ------------------------------------------------------------------
// 2007-Jan-04 JavaPOS Release 1.11                                BS
/////////////////////////////////////////////////////////////////////

package jpos;

import jpos.events.*;

public interface CoinDispenserControl111 extends CoinDispenserControl110
{
  // Methods
  public void    adjustCashCounts(String cashCounts)
                     throws JposException;
  public void    readCashCounts(String[] cashCounts,
                                boolean[] discrepancy)
                     throws JposException;
}