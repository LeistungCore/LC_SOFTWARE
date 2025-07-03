#include "../../lv_examples.h"
#if LV_USE_IMG && LV_BUILD_EXAMPLES


void lv_example_img_1(void)
{
	   LV_IMG_DECLARE(beacker_1 );
    	lv_obj_t * img1 = lv_img_create(lv_scr_act());
       lv_img_set_src(img1, &beacker_1 );
       lv_obj_align(img1, LV_ALIGN_TOP_LEFT, 20, 15);
       lv_obj_set_size(img1, 148, 50);

       LV_IMG_DECLARE(ethernet );
       lv_obj_t * img2 = lv_img_create(lv_scr_act());
       lv_img_set_src(img2, &ethernet );
       lv_obj_align(img2, LV_ALIGN_TOP_RIGHT, -5, 30);
       lv_obj_set_size(img2, 80, 33);


}






#endif
