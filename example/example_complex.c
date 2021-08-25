
#include <rtthread.h>
#include <board.h>

#include "arm_2d.h"
#include "arm_2d_helper.h"
#include "lcd_printf.h"

/* GLCD RGB color definitions */
#define GLCD_COLOR_BLACK        0x0000  /*   0,   0,   0 */
#define GLCD_COLOR_NAVY         0x000F  /*   0,   0, 128 */
#define GLCD_COLOR_DARK_GREEN   0x03E0  /*   0, 128,   0 */
#define GLCD_COLOR_DARK_CYAN    0x03EF  /*   0, 128, 128 */
#define GLCD_COLOR_MAROON       0x7800  /* 128,   0,   0 */
#define GLCD_COLOR_PURPLE       0x780F  /* 128,   0, 128 */
#define GLCD_COLOR_OLIVE        0x7BE0  /* 128, 128,   0 */
#define GLCD_COLOR_LIGHT_GREY   0xC618  /* 192, 192, 192 */
#define GLCD_COLOR_DARK_GREY    0x7BEF  /* 128, 128, 128 */
#define GLCD_COLOR_BLUE         0x001F  /*   0,   0, 255 */
#define GLCD_COLOR_GREEN        0x07E0  /*   0, 255,   0 */
#define GLCD_COLOR_CYAN         0x07FF  /*   0, 255, 255 */
#define GLCD_COLOR_RED          0xF800  /* 255,   0,   0 */
#define GLCD_COLOR_MAGENTA      0xF81F  /* 255,   0, 255 */
#define GLCD_COLOR_YELLOW       0xFFE0  /* 255, 255, 0   */
#define GLCD_COLOR_WHITE        0xFFFF  /* 255, 255, 255 */

/* declare dog tile */
declare_tile(c_tiledog);

static arm_2d_helper_pfb_t s_tPFBHelper;

extern int32_t GLCD_DrawBitmap (uint32_t x,
        uint32_t y,
        uint32_t width,
        uint32_t height,
        const uint8_t *bitmap);

static
IMPL_PFB_ON_LOW_LV_RENDERING(__pfb_render_handler)
{
    const arm_2d_tile_t *ptTile = &(ptPFB->tTile);

    ARM_2D_UNUSED(pTarget);
    ARM_2D_UNUSED(bIsNewFrame);

    GLCD_DrawBitmap(ptTile->tRegion.tLocation.iX,
                    ptTile->tRegion.tLocation.iY,
                    ptTile->tRegion.tSize.iWidth,
                    ptTile->tRegion.tSize.iHeight,
                    ptTile->pchBuffer);

    arm_2d_helper_pfb_report_rendering_complete(&s_tPFBHelper,
                                                (arm_2d_pfb_t *)ptPFB);
}

static uint32_t iWidth = 0;

void timeout_entry(void *p)
{
    iWidth++;
    if (iWidth > (2 * c_tiledog.tRegion.tSize.iWidth))
        iWidth = 0;
}

static
IMPL_PFB_ON_DRAW(__pfb_draw_handler)
{
    ARM_2D_UNUSED(pTarget);
    assert(NULL != ptTile);

    arm_2d_rgb16_fill_colour(ptTile, NULL, GLCD_COLOR_WHITE);

    arm_2d_region_t tTargetRegion = c_tiledog.tRegion;
    arm_2d_region_t tBarRegion;

    if (bIsNewFrame) {

    }

    tTargetRegion.tLocation.iX = (LCD_WIDTH - c_tiledog.tRegion.tSize.iWidth) / 2 - (c_tiledog.tRegion.tSize.iWidth / 2);
    tTargetRegion.tLocation.iY = (LCD_HEIGHT - c_tiledog.tRegion.tSize.iHeight) / 2;

    arm_2d_rgb16_tile_copy(&c_tiledog, ptTile, &tTargetRegion, ARM_2D_CP_MODE_COPY);

    tTargetRegion.tLocation.iX += c_tiledog.tRegion.tSize.iWidth;

    arm_2d_rgb16_tile_copy(&c_tiledog, ptTile, &tTargetRegion, ARM_2D_CP_MODE_COPY | ARM_2D_CP_MODE_X_MIRROR);
    arm_2d_rgb565_fill_colour_with_alpha(ptTile, &tTargetRegion, (arm_2d_color_rgb565_t){GLCD_COLOR_WHITE}, (uint_fast8_t)((255.0 / 120) * iWidth));

    tTargetRegion.tLocation.iX = (LCD_WIDTH - c_tiledog.tRegion.tSize.iWidth) / 2 - (c_tiledog.tRegion.tSize.iWidth / 2);
    tTargetRegion.tLocation.iY = (LCD_HEIGHT - c_tiledog.tRegion.tSize.iHeight) / 2;
    tTargetRegion.tLocation.iY += (c_tiledog.tRegion.tSize.iHeight + 10);
    tTargetRegion.tLocation.iX -= 1;
    tTargetRegion.tLocation.iY -= 1;
    tTargetRegion.tSize.iHeight = 12;
    tTargetRegion.tSize.iWidth = c_tiledog.tRegion.tSize.iWidth * 2 + 2;
    arm_2d_rgb16_fill_colour(ptTile,  &tTargetRegion, GLCD_COLOR_LIGHT_GREY);

    tTargetRegion = c_tiledog.tRegion;
    tTargetRegion.tLocation.iX = (LCD_WIDTH - c_tiledog.tRegion.tSize.iWidth) / 2 - (c_tiledog.tRegion.tSize.iWidth / 2);
    tTargetRegion.tLocation.iY = (LCD_HEIGHT - c_tiledog.tRegion.tSize.iHeight) / 2;
    tTargetRegion.tLocation.iY += (c_tiledog.tRegion.tSize.iHeight + 10);
    tTargetRegion.tSize.iHeight = 10;
    tTargetRegion.tSize.iWidth  = iWidth;

    arm_2d_rgb16_fill_colour(ptTile,  &tTargetRegion, GLCD_COLOR_GREEN);

    tTargetRegion.tLocation.iX += iWidth;
    tTargetRegion.tSize.iWidth = c_tiledog.tRegion.tSize.iWidth * 2 - iWidth;

    arm_2d_rgb16_fill_colour(ptTile,  &tTargetRegion, GLCD_COLOR_WHITE);

    tBarRegion.tLocation.iX  = 0;
    tBarRegion.tLocation.iY  = LCD_HEIGHT - 8*2;
    tBarRegion.tSize.iHeight = (2 * 8);
    tBarRegion.tSize.iWidth  = LCD_WIDTH;

    arm_2d_rgb16_fill_colour(ptTile, &tBarRegion, GLCD_COLOR_BLACK);

    //! print info
    lcd_text_location(LCD_HEIGHT / 8 - 2, 0);

    lcd_printf("Dog1...Dog1...Dog1...Dog1...\n");
    lcd_printf("Dog2...Dog2...Dog2...Dog2...Dog2...\n");

    return arm_fsm_rt_cpl;
}

static
IMPL_PFB_ON_DRAW(__pfb_draw_background_handler)
{
    ARM_2D_UNUSED(pTarget);
    ARM_2D_UNUSED(bIsNewFrame);

    arm_2d_rgb16_fill_colour(ptTile, NULL, GLCD_COLOR_WHITE);

    return arm_fsm_rt_cpl;
}

void display_task(void)
{
    /*! define dirty regions */
    IMPL_ARM_2D_REGION_LIST(s_tDirtyRegions, static const)

        /* a region for the dog */
        ADD_REGION_TO_LIST(s_tDirtyRegions,
            .tLocation = {(LCD_WIDTH - 150) /2,
                          (LCD_HEIGHT - 150) / 2},
            .tSize = {
                .iWidth = 150,
                .iHeight = 150,
            },
        ),

        /* a region for the status bar on the bottom of the screen */
        ADD_LAST_REGION_TO_LIST(s_tDirtyRegions,
            .tLocation = {0,LCD_HEIGHT - 8*2},
            .tSize = {
                .iWidth = LCD_WIDTH,
                .iHeight = 8*2,
            },
        ),

    END_IMPL_ARM_2D_REGION_LIST()


    /*! define the partial-flushing area */

    //! call partial framebuffer helper service
    while(arm_fsm_rt_cpl != arm_2d_helper_pfb_task(
                                &s_tPFBHelper,
                                NULL));
                                //(arm_2d_region_list_item_t *)s_tDirtyRegions));

    //! update performance info
}

void arm_2d_complex(void)
{
    rt_timer_t t;
    arm_irq_safe {
        arm_2d_init();
    }

    t = rt_timer_create("t", timeout_entry, RT_NULL, 100, RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);
    if (t == RT_NULL)
    {
        rt_kprintf("Arm-2D create timer failed!\n");
        return;
    }
    rt_timer_start(t);

    //! initialize FPB helper
    if (ARM_2D_HELPER_PFB_INIT(
            &s_tPFBHelper,                 //!< FPB Helper object
            LCD_WIDTH,                      //!< screen width
            LCD_HEIGHT,                     //!< screen height
            uint16_t,                       //!< colour date type
            LCD_WIDTH,                      //!< PFB block width
            8,                              //!< PFB block height
            1,                              //!< number of PFB in the PFB pool
            {
                .evtOnLowLevelRendering = {
                    //! callback for low level rendering
                    .fnHandler = &__pfb_render_handler,
                },
                .evtOnDrawing = {
                    //! callback for drawing GUI
                    .fnHandler = &__pfb_draw_background_handler,
                },
            }
        ) < 0) {
        //! error detected
        assert(false);
    }

    //! draw background first
    while(arm_fsm_rt_cpl != arm_2d_helper_pfb_task(&s_tPFBHelper,NULL));

    //! update draw function
    ARM_2D_HELPER_PFB_UPDATE_ON_DRAW_HANDLER(   &s_tPFBHelper,
                                                &__pfb_draw_handler);

    while (1) {
        display_task();
    }
}
MSH_CMD_EXPORT(arm_2d_complex, Arm-2D complex example.);
