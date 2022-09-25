/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_COMMANDBUTTON              2       /* control type: command, callback function: onOKBtb */
#define  PANEL_COMMANDBUTTON_2            3       /* control type: command, callback function: onStopBtn */
#define  PANEL_COMMANDBUTTON_ID           4       /* control type: command, callback function: OnIDBtn */
#define  PANEL_TIMER                      5       /* control type: timer, callback function: UpdateTimer */
#define  PANEL_STRIPCHART_TOP             6       /* control type: strip, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnIDBtn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onOKBtb(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onStopBtn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK UpdateTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
