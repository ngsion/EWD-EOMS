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

#define  PANEL                            1       /* callback function: OnPanelCV */
#define  PANEL_COMMANDBUTTON              2       /* control type: command, callback function: OnStartCVBtn */
#define  PANEL_COMMANDBUTTON_2            3       /* control type: command, callback function: OnCVBack */
#define  PANEL_TIMER_CV                   4       /* control type: timer, callback function: UpdateTimerCV */
#define  PANEL_GRAPH                      5       /* control type: graph, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnCVBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnPanelCV(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnStartCVBtn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK UpdateTimerCV(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
