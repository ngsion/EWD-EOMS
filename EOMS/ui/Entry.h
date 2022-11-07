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
#define  PANEL_RADIOBUTTON_WAVE           2       /* control type: radioButton, callback function: OnRadioWave */
#define  PANEL_CHECKBOX_LCR               3       /* control type: radioButton, callback function: (none) */
#define  PANEL_RADIOBUTTON_LCR            4       /* control type: radioButton, callback function: OnRadioLCR */
#define  PANEL_CHECKBOX_PICO              5       /* control type: radioButton, callback function: (none) */
#define  PANEL_RADIOBUTTON_PICO           6       /* control type: radioButton, callback function: OnRadioPico */
#define  PANEL_COMMANDBUTTON              7       /* control type: command, callback function: OnOkBtn */
#define  PANEL_LED_WAVE                   8       /* control type: LED, callback function: (none) */
#define  PANEL_LED_LCR                    9       /* control type: LED, callback function: (none) */
#define  PANEL_LED_PICO                   10      /* control type: LED, callback function: (none) */
#define  PANEL_TEXTBOX_PICO               11      /* control type: textBox, callback function: (none) */
#define  PANEL_TEXTBOX_LCR                12      /* control type: textBox, callback function: (none) */
#define  PANEL_TEXTBOX_ADMESY             13      /* control type: textBox, callback function: (none) */
#define  PANEL_TEXTBOX_WAVE               14      /* control type: textBox, callback function: (none) */
#define  PANEL_TEXTMSG                    15      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_2                  16      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_3                  17      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_4                  18      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_5                  19      /* control type: textMsg, callback function: (none) */
#define  PANEL_LED_ADMESY                 20      /* control type: LED, callback function: (none) */
#define  PANEL_TEXTMSG_6                  21      /* control type: textMsg, callback function: (none) */


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
