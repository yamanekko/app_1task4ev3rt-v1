#include "ev3api.h"
#include "syssvc/serial.h"	// for Bluetooth(log)
#include "app.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

#include "mruby.h"
#include "mruby/irep.h"
#include "mruby/string.h"

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_MEDIUM)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

/* メインタスク */
void main_task(intptr_t unused)
{
	/* LCD画面にログを表示 */
	ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
  ev3_lcd_draw_string("app_1task", 0, CALIB_FONT_HEIGHT*1);

	static mrb_state *mrb = NULL;
	mrb_value ret;

	mrb = mrb_open();

	mrbc_context *context = mrbc_context_new(mrb);
	memfile_t memfile;
	ER ercd = ev3_memfile_load("/ev3rt/apps/main_task.rb", &memfile);
	if (ercd != E_OK) {
		ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
		ev3_lcd_draw_string("load error main_task.rb", 0, 10);
		ext_tsk();
	}

	ret = mrb_load_nstring_cxt(mrb, memfile.buffer, memfile.filesz, context);
	if(mrb->exc){
		if(!mrb_undef_p(ret)){	//エラーを表示するための処理。LCDとbluetooth両方に出力
			ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
			ev3_lcd_draw_string("mruby exec ERR", 0, CALIB_FONT_HEIGHT * 1);
			mrb_value s = mrb_funcall(mrb, mrb_obj_value(mrb->exc), "inspect", 0);
			if (mrb_string_p(s)) {
				int line_max = 30;
				int cnt = (RSTRING_LEN(s) + (line_max - 1)) / line_max;
				int i = 0;
				int current_line = 1;
				char *pos = mrb_str_to_cstr(mrb, s);
				for(i = 0; i < cnt; i++ ){
					current_line += 2;
					ev3_lcd_draw_string(pos, 0, CALIB_FONT_HEIGHT * current_line);
					pos += line_max;
				}
			} else {
				ev3_lcd_draw_string("error unknown", 0, CALIB_FONT_HEIGHT * 3);
			}
		}
	}

	mrb_close(mrb);
	ext_tsk();
}

int _fini(void){
	return 0;
}
