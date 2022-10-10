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

#define  PANEL                            1       /* callback function: OnPanelLC */
#define  PANEL_STRIPCHART                 2       /* control type: strip, callback function: (none) */
#define  PANEL_COMMANDBUTTON              3       /* control type: command, callback function: OnStartBtn */
#define  PANEL_COMMANDBUTTON_2            4       /* control type: command, callback function: OnBack */
#define  PANEL_TIMER_LC                   5       /* control type: timer, callback function: UpdateTimerLC */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnPanelLC(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnStartBtn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK UpdateTimerLC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
