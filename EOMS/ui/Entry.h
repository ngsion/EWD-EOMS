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
#define  PANEL_CHECKBOX_PICO_DATA         2       /* control type: radioButton, callback function: (none) */
#define  PANEL_CHECKBOX_LCR_DATA          3       /* control type: radioButton, callback function: (none) */
#define  PANEL_COMMANDBUTTON              4       /* control type: command, callback function: OnOkBtn */
#define  PANEL_TEXTBOX_PICO               5       /* control type: textBox, callback function: (none) */
#define  PANEL_TEXTBOX_LCR                6       /* control type: textBox, callback function: (none) */
#define  PANEL_TEXTBOX_WAVE               7       /* control type: textBox, callback function: (none) */
#define  PANEL_TEXTBOX_ADMESY             8       /* control type: textBox, callback function: (none) */
#define  PANEL_TEXTMSG_3                  9       /* control type: textMsg, callback function: (none) */
#define  PANEL_COMMANDBUTTON_REFRESH      10      /* control type: command, callback function: OnRefreshBtn */
#define  PANEL_RING_PICO                  11      /* control type: ring, callback function: OnPicoRing */
#define  PANEL_RING_LCR                   12      /* control type: ring, callback function: OnLCRRing */
#define  PANEL_RING_WAVE                  13      /* control type: ring, callback function: OnWaveRing */
#define  PANEL_RING_ADMESY                14      /* control type: ring, callback function: OnAdmesy */
#define  PANEL_CHECKBOX_PICO_SRC          15      /* control type: radioButton, callback function: (none) */
#define  PANEL_CHECKBOX_LCR_SRC           16      /* control type: radioButton, callback function: (none) */
#define  PANEL_CHECKBOX_WAVE_SRC          17      /* control type: radioButton, callback function: (none) */
#define  PANEL_LED_PICO                   18      /* control type: LED, callback function: (none) */
#define  PANEL_LED_LCR                    19      /* control type: LED, callback function: (none) */
#define  PANEL_LED_WAVE                   20      /* control type: LED, callback function: (none) */
#define  PANEL_LED_ADMESY                 21      /* control type: LED, callback function: (none) */
#define  PANEL_COMMANDBUTTON_WAVESET      22      /* control type: command, callback function: OnWAVESet */
#define  PANEL_COMMANDBUTTON_LCRSET       23      /* control type: command, callback function: OnLCRSet */
#define  PANEL_COMMANDBUTTON_PICOSET      24      /* control type: command, callback function: OnPicoSet */
#define  PANEL_TEXTMSG_4                  25      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnAdmesy(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnLCRRing(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnLCRSet(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnOkBtn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnPicoRing(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnPicoSet(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnRefreshBtn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnWaveRing(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnWAVESet(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
