#include "app_display.h"
#include "ugui.h"
#include "nrf_gfx_ext.h"
#include "images.h"

#define RSSI

UG_WINDOW window_1;
char m_summary_string1[64];
char m_summary_string2[64];

extern const nrf_lcd_t nrf_lcd_ili9341;
static const nrf_lcd_t * p_lcd = &nrf_lcd_ili9341;

char *display_string_phy[] = {"Coded", "1 Mbps", "2 Mbps", "MultiPhy"};

char *display_string_rssi_label[] = {"RSSI (LR):", "RSSI (1M):", "RSSI (2M):"};
char *display_string_speed_label[] = {"Speed (LR):", "Speed (1M):", "Speed (2M):"};
char *display_string_psr_label[] = {"PSR:", "PSR:", "PSR:"};

char *display_string_trip_phy_rssi_label[] = {"LB (LR):", "LB (1M):", "LB (2M):"};
char *display_string_tx_power[] = {"0 dBm", "4 dBm", "8 dBm"};
char *display_string_app_state[] = {"Idle", "Advertising", "Scanning", "Connected", "Disconnected"};
char *display_string_led_state[] = {"Off", "On"};
char *display_string_button_state[] = {"Off", "On"};
const UG_COLOR display_app_state_button_color[] = APP_STATE_COLORS;
const UG_COLOR display_app_state_button_font_color[] = APP_STATE_FONT_COLORS;
const UG_COLOR display_on_off_color[] = ON_OFF_COLORS;
const UG_COLOR display_on_off_font_color[] = ON_OFF_FONT_COLORS;

UG_GUI gui;
UG_TEXTBOX textbox_toggle_phy;
UG_TEXTBOX textbox_toggle_power;
UG_TEXTBOX textbox_toggle_adv_type; 
UG_TEXTBOX textbox_rssi_label[3];
UG_TEXTBOX textbox_psr_label;
UG_TEXTBOX textbox_rssi_number[3];
UG_TEXTBOX textbox_psr_number;
UG_TEXTBOX textbox_dbm_label;
UG_TEXTBOX textbox_percentage_label;
UG_TEXTBOX textbox_link_indicator;
UG_TEXTBOX textbox_led_label;
UG_TEXTBOX textbox_button_label;
UG_BUTTON phy_button;
UG_BUTTON power_button;
UG_BUTTON adv_button;
UG_BUTTON led_button;
UG_BUTTON button_button;
UG_IMAGE image_1;

static char sprintf_buf[64];
static char sprintf_psr[64];

#define MAX_OBJECTS 20

UG_OBJECT obj_buff_wnd_1[MAX_OBJECTS];

static app_display_content_t content_previous = {0};

void window_1_callback (UG_MESSAGE *msg)
{
        UNUSED_PARAMETER(msg);
}

void app_display_init(app_display_content_t *initial_state)
{
        content_previous = *initial_state;
        UG_Init(&gui, 240, 320, p_lcd);
}

void app_display_create_main_screen(app_display_content_t *content)
{
        
        UG_WindowCreate ( &window_1, obj_buff_wnd_1, MAX_OBJECTS, window_1_callback );
        
        UG_WindowSetTitleText (&window_1, content->main_title);
        UG_WindowSetTitleTextFont (&window_1, &FONT_10X16);
        UG_WindowSetTitleTextAlignment(&window_1, ALIGN_CENTER);

        
        UG_TextboxCreate(&window_1, &textbox_toggle_phy, TXB_ID_0, TXT_ID_0_X_LOCATION, TXT_ID_0_Y_LOCATION, TXT_ID_0_X_LOCATION+TXT_ID_0_WIDTH, TXT_ID_0_Y_LOCATION+TXT_ID_0_HEIGHT);
        UG_TextboxSetFont(&window_1, TXB_ID_0, &FONT_8X12);
        UG_TextboxSetText(&window_1, TXB_ID_0, "Btn 1: PHY");
        UG_TextboxSetForeColor (&window_1, TXB_ID_0, FONT_COLOR_TEXT );
        UG_TextboxSetBackColor (&window_1, TXB_ID_0, FILL_COLOR_TEXT );
        UG_TextboxSetAlignment (&window_1, TXB_ID_0, ALIGN_CENTER );

        
        UG_ButtonCreate(&window_1, &phy_button, BTN_ID_0, BTN_ID_0_X_LOCATION, BTN_ID_0_Y_LOCATION, BTN_ID_0_X_LOCATION+BTN_ID_0_WIDTH, BTN_ID_0_Y_LOCATION+BTN_ID_0_HEIGHT);
        UG_ButtonSetStyle(&window_1, BTN_ID_0, BTN_STYLE_3D|BTN_STYLE_USE_ALTERNATE_COLORS);
        UG_ButtonSetForeColor(&window_1, BTN_ID_0, FONT_COLOR_BUTTON);
        UG_ButtonSetBackColor(&window_1, BTN_ID_0, FILL_COLOR_BUTTON);
        UG_ButtonSetFont(&window_1, BTN_ID_0, &FONT_10X16);

        
        UG_TextboxCreate(&window_1, &textbox_toggle_power, TXB_ID_1, TXT_ID_1_X_LOCATION, TXT_ID_1_Y_LOCATION, TXT_ID_1_X_LOCATION+TXT_ID_1_WIDTH, TXT_ID_1_Y_LOCATION+TXT_ID_1_HEIGHT);
        UG_TextboxSetFont(&window_1, TXB_ID_1, &FONT_8X12);
        UG_TextboxSetText(&window_1, TXB_ID_1, "Btn 2: Power");
        UG_TextboxSetForeColor (&window_1, TXB_ID_1, FONT_COLOR_TEXT );
        UG_TextboxSetBackColor (&window_1, TXB_ID_1, FILL_COLOR_TEXT );
        UG_TextboxSetAlignment (&window_1, TXB_ID_1, ALIGN_CENTER );

        
        UG_ButtonCreate(&window_1, &power_button, BTN_ID_1, BTN_ID_1_X_LOCATION, BTN_ID_1_Y_LOCATION, BTN_ID_1_X_LOCATION+BTN_ID_1_WIDTH, BTN_ID_1_Y_LOCATION+BTN_ID_1_HEIGHT);
        UG_ButtonSetStyle(&window_1, BTN_ID_1, BTN_STYLE_3D|BTN_STYLE_USE_ALTERNATE_COLORS);
        UG_ButtonSetForeColor(&window_1, BTN_ID_1, FONT_COLOR_BUTTON);
        UG_ButtonSetBackColor(&window_1, BTN_ID_1, FILL_COLOR_BUTTON);
        UG_ButtonSetFont(&window_1, BTN_ID_1, &FONT_10X16);
        

        
        UG_TextboxCreate(&window_1, &textbox_toggle_adv_type, TXB_ID_2, TXT_ID_2_X_LOCATION, TXT_ID_2_Y_LOCATION, TXT_ID_2_X_LOCATION+TXT_ID_2_WIDTH, TXT_ID_2_Y_LOCATION+TXT_ID_2_HEIGHT);
        UG_TextboxSetFont(&window_1, TXB_ID_2, &FONT_8X12);
        UG_TextboxSetText(&window_1, TXB_ID_2, "Btn 3: App state");
        UG_TextboxSetForeColor (&window_1, TXB_ID_2, FONT_COLOR_TEXT );
        UG_TextboxSetBackColor (&window_1, TXB_ID_2, FILL_COLOR_TEXT );
        UG_TextboxSetAlignment (&window_1, TXB_ID_2, ALIGN_CENTER );

        
        UG_ButtonCreate(&window_1, &adv_button, BTN_ID_2, BTN_ID_2_X_LOCATION, BTN_ID_2_Y_LOCATION, BTN_ID_2_X_LOCATION+BTN_ID_2_WIDTH, BTN_ID_2_Y_LOCATION+BTN_ID_2_HEIGHT);
        UG_ButtonSetStyle(&window_1, BTN_ID_2, BTN_STYLE_3D|BTN_STYLE_USE_ALTERNATE_COLORS);
        UG_ButtonSetFont(&window_1, BTN_ID_2, &FONT_10X16);



























        
        UG_TextboxCreate(&window_1, &textbox_rssi_label[0], TXB_ID_3, TXT_ID_3_X_LOCATION, TXT_ID_3_Y_LOCATION, TXT_ID_3_X_LOCATION+TXT_ID_3_WIDTH, TXT_ID_3_Y_LOCATION+TXT_ID_3_HEIGHT);
        UG_TextboxSetFont(&window_1, TXB_ID_3, &FONT_8X12);
        UG_TextboxSetText(&window_1, TXB_ID_3, display_string_trip_phy_rssi_label[0]);
        UG_TextboxSetForeColor (&window_1, TXB_ID_3, FONT_COLOR_TEXT );
        UG_TextboxSetBackColor (&window_1, TXB_ID_3, 0x0000 );
        UG_TextboxSetAlignment (&window_1, TXB_ID_3, ALIGN_CENTER );

        UG_TextboxCreate(&window_1, &textbox_rssi_label[1], TXB_ID_4, TXT_ID_4_X_LOCATION, TXT_ID_4_Y_LOCATION, TXT_ID_4_X_LOCATION+TXT_ID_4_WIDTH, TXT_ID_4_Y_LOCATION+TXT_ID_4_HEIGHT);
        UG_TextboxSetFont(&window_1, TXB_ID_4, &FONT_8X12);
        UG_TextboxSetText(&window_1, TXB_ID_4, display_string_trip_phy_rssi_label[1]);
        UG_TextboxSetForeColor (&window_1, TXB_ID_4, FONT_COLOR_TEXT );
        UG_TextboxSetBackColor (&window_1, TXB_ID_4, 0x0000 );
        UG_TextboxSetAlignment (&window_1, TXB_ID_4, ALIGN_CENTER );

        UG_TextboxCreate(&window_1, &textbox_rssi_label[2], TXB_ID_5, TXT_ID_5_X_LOCATION, TXT_ID_5_Y_LOCATION, TXT_ID_5_X_LOCATION+TXT_ID_5_WIDTH, TXT_ID_5_Y_LOCATION+TXT_ID_5_HEIGHT);
        UG_TextboxSetFont(&window_1, TXB_ID_5, &FONT_8X12);
        UG_TextboxSetText(&window_1, TXB_ID_5, display_string_trip_phy_rssi_label[2]);
        UG_TextboxSetForeColor (&window_1, TXB_ID_5, FONT_COLOR_TEXT );
        UG_TextboxSetBackColor (&window_1, TXB_ID_5, 0x0000 );
        UG_TextboxSetAlignment (&window_1, TXB_ID_5, ALIGN_CENTER );

        
        UG_TextboxCreate(&window_1, &textbox_rssi_number[0], TXB_ID_6, TXT_ID_6_X_LOCATION, TXT_ID_6_Y_LOCATION, TXT_ID_6_X_LOCATION+TXT_ID_6_WIDTH, TXT_ID_6_Y_LOCATION+TXT_ID_6_HEIGHT);
        UG_TextboxSetFont(&window_1, TXB_ID_6, &FONT_8X12);
        UG_TextboxSetText(&window_1, TXB_ID_6, "Disconnected");
        UG_TextboxSetForeColor (&window_1, TXB_ID_6, FONT_COLOR_TEXT );
        UG_TextboxSetBackColor (&window_1, TXB_ID_6, 0x0000 );
        UG_TextboxSetAlignment (&window_1, TXB_ID_6, ALIGN_CENTER );

        UG_TextboxCreate(&window_1, &textbox_rssi_number[1], TXB_ID_7, TXT_ID_7_X_LOCATION, TXT_ID_7_Y_LOCATION, TXT_ID_7_X_LOCATION+TXT_ID_7_WIDTH, TXT_ID_7_Y_LOCATION+TXT_ID_7_HEIGHT);
        UG_TextboxSetFont(&window_1, TXB_ID_7, &FONT_8X12);
        UG_TextboxSetText(&window_1, TXB_ID_7, "Disconnected");
        UG_TextboxSetForeColor (&window_1, TXB_ID_7, FONT_COLOR_TEXT );
        UG_TextboxSetBackColor (&window_1, TXB_ID_7, 0x0000 );
        UG_TextboxSetAlignment (&window_1, TXB_ID_7, ALIGN_CENTER );

        UG_TextboxCreate(&window_1, &textbox_rssi_number[2], TXB_ID_8, TXT_ID_8_X_LOCATION, TXT_ID_8_Y_LOCATION, TXT_ID_8_X_LOCATION+TXT_ID_8_WIDTH, TXT_ID_8_Y_LOCATION+TXT_ID_8_HEIGHT);
        UG_TextboxSetFont(&window_1, TXB_ID_8, &FONT_8X12);
        UG_TextboxSetText(&window_1, TXB_ID_8, "Disconnected");
        UG_TextboxSetForeColor (&window_1, TXB_ID_8, FONT_COLOR_TEXT );
        UG_TextboxSetBackColor (&window_1, TXB_ID_8, 0x0000 );
        UG_TextboxSetAlignment (&window_1, TXB_ID_8, ALIGN_CENTER );

#if 1
        
        UG_TextboxCreate(&window_1, &textbox_psr_label, TXB_ID_12, TXT_ID_12_X_LOCATION, TXT_ID_12_Y_LOCATION, TXT_ID_12_X_LOCATION+TXT_ID_4_WIDTH, TXT_ID_12_Y_LOCATION+TXT_ID_4_HEIGHT);
        UG_TextboxSetFont(&window_1, TXB_ID_12, &FONT_8X12);
        UG_TextboxSetText(&window_1, TXB_ID_12, "PSR: ");
        UG_TextboxSetForeColor (&window_1, TXB_ID_12, FONT_COLOR_TEXT );
        UG_TextboxSetBackColor (&window_1, TXB_ID_12, FILL_COLOR_TEXT );
        UG_TextboxSetAlignment (&window_1, TXB_ID_12, ALIGN_CENTER );

        
        UG_TextboxCreate(&window_1, &textbox_psr_number, TXB_ID_13, TXT_ID_13_X_LOCATION, TXT_ID_13_Y_LOCATION, TXT_ID_13_X_LOCATION+TXT_ID_6_WIDTH, TXT_ID_13_Y_LOCATION+TXT_ID_6_HEIGHT);
        UG_TextboxSetFont(&window_1, TXB_ID_13, &FONT_8X12);
        UG_TextboxSetText(&window_1, TXB_ID_13, "###");
        UG_TextboxSetForeColor (&window_1, TXB_ID_13, FONT_COLOR_TEXT );
        UG_TextboxSetBackColor (&window_1, TXB_ID_13, FILL_COLOR_TEXT );
        UG_TextboxSetAlignment (&window_1, TXB_ID_13, ALIGN_CENTER );

#endif

        UG_ImageCreate(&window_1, &image_1, IMG_ID_0, 0, 228, 30, 250);
        UG_ImageSetBMP(&window_1, IMG_ID_0, &bmp_nordicsemi);

        
        app_display_update_main_screen(content);

        
        UG_WindowShow( &window_1 );
}



void app_display_update_main_screen(app_display_content_t *content)
{
        static bool first_update = true;
        if(first_update || content->phy != content_previous.phy)
        {
                UG_ButtonSetText(&window_1, BTN_ID_0, display_string_phy[content->phy]);









                {


                        UG_TextboxSetText(&window_1, TXB_ID_4, display_string_rssi_label[APP_PHY_1M]);
                        UG_TextboxSetText(&window_1, TXB_ID_12, display_string_psr_label[APP_PHY_1M]);
                }
                UG_TextboxSetText(&window_1, TXB_ID_7, "Disconnected");
                UG_TextboxSetText(&window_1, TXB_ID_13, "Disconnected");
        }
        if(first_update || content->tx_power != content_previous.tx_power)
        {
                UG_ButtonSetText(&window_1, BTN_ID_1, display_string_tx_power[content->tx_power]);
        }
        if(first_update || content->app_state != content_previous.app_state)
        {
                UG_ButtonSetBackColor(&window_1, BTN_ID_2, display_app_state_button_color[content->app_state]);
                UG_ButtonSetForeColor(&window_1, BTN_ID_2, display_app_state_button_font_color[content->app_state]);
                UG_ButtonSetText(&window_1, BTN_ID_2, display_string_app_state[content->app_state]);

                if(content->app_state == APP_STATE_CONNECTED)
                {
                        UG_TextboxShow(&window_1, TXB_ID_4);
                        UG_TextboxShow(&window_1, TXB_ID_7);
                        UG_TextboxShow(&window_1, TXB_ID_12);
                        UG_TextboxShow(&window_1, TXB_ID_13); 

















                        {
                                UG_TextboxSetBackColor(&window_1, TXB_ID_4, RGB_888_TO_565(0x0ADD00));
                                UG_TextboxSetBackColor(&window_1, TXB_ID_7, RGB_888_TO_565(0x0ADD00));

                                UG_TextboxSetBackColor(&window_1, TXB_ID_12, RGB_888_TO_565(0x0ADD00));
                                UG_TextboxSetBackColor(&window_1, TXB_ID_13, RGB_888_TO_565(0x0ADD00));
                        }
                }
                else
                {
                        UG_TextboxHide(&window_1, TXB_ID_3);
                        UG_TextboxHide(&window_1, TXB_ID_6);
                        UG_TextboxHide(&window_1, TXB_ID_4);
                        UG_TextboxHide(&window_1, TXB_ID_5);
                        UG_TextboxHide(&window_1, TXB_ID_7);
                        UG_TextboxHide(&window_1, TXB_ID_8);

                        UG_TextboxHide(&window_1, TXB_ID_12);
                        UG_TextboxHide(&window_1, TXB_ID_13);
                }
        }












        static int rx_sensitivity[] = {-103, -95, -92};
        static uint32_t link_budget_colors[] = {0xEF0000, 0xfe6c00, 0xfdc700, 0xe2e500, 0xc6f700, 0x5ee900, 0x0ADD00};
        static int link_budget, link_color;
























        {
                if(first_update || content->rssi[0] != content_previous.rssi[0])
                {
                        link_budget = (int)content->rssi[0] - rx_sensitivity[content->phy];
                        
                        link_color = RGB_888_TO_565(link_budget < 35 ? link_budget_colors[link_budget / 5] : 0x0ADD00);

#ifdef RSSI
                        sprintf(sprintf_buf, "%i dBm", (int)content->rssi[0]);
                        UG_TextboxSetBackColor(&window_1, TXB_ID_4, link_color);
                        UG_TextboxSetBackColor(&window_1, TXB_ID_7, link_color);
                        UG_TextboxSetText(&window_1, TXB_ID_7, content->rssi[0] != 0 ? sprintf_buf : "-");
#else
                        sprintf(sprintf_buf, "%i kbps", (int)content->throughput_kbps);
                        UG_TextboxSetBackColor(&window_1, TXB_ID_4, link_color);
                        UG_TextboxSetBackColor(&window_1, TXB_ID_7, link_color);
                        UG_TextboxSetText(&window_1, TXB_ID_7, sprintf_buf);

#endif
                        sprintf(sprintf_psr, "%3d% %", (int)content->psr);
                        UG_TextboxSetBackColor(&window_1, TXB_ID_12, link_color);
                        UG_TextboxSetBackColor(&window_1, TXB_ID_13, link_color);
                        UG_TextboxSetText(&window_1, TXB_ID_13, sprintf_psr);

                }
        }
        first_update = false;
        content_previous = *content;
}

void app_display_update(void)
{
        UG_Update();
}
