/////////////////////////////////////////////////////////////////////
//
// THIS SOFTWARE IS PROVIDED AS IS. THE JAVAPOS WORKING GROUP MAKES NO 
// REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE, 
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR 
// NON-INFRINGEMENT.  INDIVIDUAL OR CORPORATE MEMBERS OF THE JAVAPOS 
// WORKING GROUP SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED AS A RESULT
// OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
// 
// OutputCompleteEvent
//
//   Class defining the Output Complete Event generated by JavaPOS 
//   device controls.
//
// Modification history
// ------------------------------------------------------------------
// 98-02-18 JavaPOS Release 1.2                                   BS
//
/////////////////////////////////////////////////////////////////////

package jpos.events;

public class OutputCompleteEvent extends JposEvent
{
    public OutputCompleteEvent(Object source, int outputID)
    {
        super(source);

        this.outputID = outputID;
    }

    public int getOutputID()
    {
        return(outputID);
    }

    protected int outputID;
}