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

#define  PANEL                            1       /* callback function: OnPanel */
#define  PANEL_STRING                     2       /* control type: string, callback function: (none) */
#define  PANEL_STRING_2                   3       /* control type: string, callback function: (none) */
#define  PANEL_STRING_3                   4       /* control type: string, callback function: (none) */
#define  PANEL_RADIOBUTTON_WAVE           5       /* control type: radioButton, callback function: OnRadioWave */
#define  PANEL_CHECKBOX_LCR               6       /* control type: radioButton, callback function: (none) */
#define  PANEL_RADIOBUTTON_LCR            7       /* control type: radioButton, callback function: OnRadioLCR */
#define  PANEL_CHECKBOX_PICO              8       /* control type: radioButton, callback function: (none) */
#define  PANEL_RADIOBUTTON_PICO           9       /* control type: radioButton, callback function: OnRadioPico */
#define  PANEL_STRING_4                   10      /* control type: string, callback function: (none) */
#define  PANEL_STRING_5                   11      /* control type: string, callback function: (none) */
#define  PANEL_COMMANDBUTTON              12      /* control type: command, callback function: OnOkBtn */
#define  PANEL_LED_WAVE                   13      /* control type: LED, callback function: (none) */
#define  PANEL_LED_LCR                    14      /* control type: LED, callback function: (none) */
#define  PANEL_LED_PICO                   15      /* control type: LED, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnOkBtn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnRadioLCR(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnRadioPico(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnRadioWave(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
