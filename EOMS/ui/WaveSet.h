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

#define  PANEL_WS                         1       /* callback function: OnPanelWaveSet */
#define  PANEL_WS_COMMANDBUTTON           2       /* control type: command, callback function: OnWaveSetSaveBtn */
#define  PANEL_WS_SPLITTER                3       /* control type: splitter, callback function: (none) */
#define  PANEL_WS_NUMERIC_FREQUENCY       4       /* control type: numeric, callback function: (none) */
#define  PANEL_WS_NUMERIC_CH2OFFSET       5       /* control type: numeric, callback function: (none) */
#define  PANEL_WS_NUMERIC_CH1OFFSET       6       /* control type: numeric, callback function: (none) */
#define  PANEL_WS_NUMERIC_LOW             7       /* control type: numeric, callback function: (none) */
#define  PANEL_WS_NUMERIC_HIGH            8       /* control type: numeric, callback function: (none) */
#define  PANEL_WS_TEXTMSG                 9       /* control type: textMsg, callback function: (none) */
#define  PANEL_WS_TEXTBOX                 10      /* control type: textBox, callback function: (none) */
#define  PANEL_WS_TEXTMSG_2               11      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnPanelWaveSet(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnWaveSetSaveBtn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
