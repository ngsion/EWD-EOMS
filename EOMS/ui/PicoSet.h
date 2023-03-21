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

#define  PANEL_PSET                       1
#define  PANEL_PSET_STRING_BATCH          2       /* control type: string, callback function: (none) */
#define  PANEL_PSET_NUMERIC_INTERVAL      3       /* control type: numeric, callback function: (none) */
#define  PANEL_PSET_NUMERIC_VSPAN         4       /* control type: numeric, callback function: (none) */
#define  PANEL_PSET_NUMERIC_VMIN          5       /* control type: numeric, callback function: (none) */
#define  PANEL_PSET_NUMERIC_VMAX          6       /* control type: numeric, callback function: (none) */
#define  PANEL_PSET_COMMANDBUTTON         7       /* control type: command, callback function: OnNextBtn */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnNextBtn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
