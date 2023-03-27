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

#define  PANEL_LCRS                       1       /* callback function: OnPanelLCRSet */
#define  PANEL_LCRS_STRING_LCRBATCH       2       /* control type: string, callback function: (none) */
#define  PANEL_LCRS_NUMERIC_LCRINTERVAL   3       /* control type: numeric, callback function: (none) */
#define  PANEL_LCRS_COMMANDBUTTON         4       /* control type: command, callback function: OnLCRSaveBtn */
#define  PANEL_LCRS_NUMERIC_LCRMAX        5       /* control type: numeric, callback function: (none) */
#define  PANEL_LCRS_NUMERIC_LCRMIN        6       /* control type: numeric, callback function: (none) */
#define  PANEL_LCRS_NUMERIC_LCRSTEP       7       /* control type: numeric, callback function: (none) */
#define  PANEL_LCRS_TEXTBOX               8       /* control type: textBox, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnLCRSaveBtn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnPanelLCRSet(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
