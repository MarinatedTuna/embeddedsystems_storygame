#include "rims.h"

//Name: Joseph Tibog (861203955)
//Email: jtibo002@ucr.edu
//Google doc link: https://docs.google.com/document/d/1m1xEyVdAE5bkmSFg7CMELBodlzQRLfrseenogJ99mjw/edit?usp=sharing

int display_lives = 0; 
int trigger_life_loss = 0; //use to decrement lives remaining
int lives = 3; //init
int score = 0; //increment by 150 for every correct answer. 100 for getting through last chapter (MAX 1000) if user picks a chapter, reset score to 0 to prevent cheating.

//It's possible to only get 100 points if someone decides to only read the last chapter.

//int chapter1_completed = 0;
//int chapter2_completed = 0;
//int chapter3_completed = 0;
//int chapter4_completed = 0; //no choices here (EXCEPT GIRLFRIEND ROUTES)
//int chapter5_jeffroute = 0;
//int chapter5_frankroute = 0;
//int chapter5_brianroute = 0;
//int chapter5_elenaroute = 0;

//display lives on B0, B1, B2
//display chapters on B3, B4, B5, B6, B7

volatile int TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}

enum Life_States {Life_SMStart, Life_Init, Life_Display} Life_State;

enum MainGame_States {MainGame_SMStart, MainGame_Menu1, MainGame_Menu2, MainGame_Chapter1_Dialogue0, MainGame_Chapter1_WaitOff0, MainGame_Chapter1_WaitOn0, MainGame_Chapter1_Dialogue1, MainGame_Chapter1_WaitOff1, MainGame_Chapter1_WaitOn1, MainGame_Chapter1_Dialogue2, MainGame_Chapter1_WaitOff2, MainGame_Chapter1_WaitOn2, MainGame_Chapter1_Dialogue3, MainGame_Chapter1_WaitOff3, MainGame_Chapter1_WaitOn3, MainGame_Chapter1_Dialogue4, MainGame_Chapter1_WaitOff4, MainGame_Chapter1_WaitOn4, MainGame_Chapter1_Dialogue5a, MainGame_Chapter1_WaitOff5a, MainGame_Chapter1_WaitOn5a, MainGame_Chapter1_Dialogue5b, MainGame_Chapter1_WaitOff5b, MainGame_Chapter1_WaitOn5b, MainGame_Chapter1_Dialogue5c, MainGame_Chapter1_WaitOff5c, MainGame_Chapter1_WaitOn5c, MainGame_Chapter1_Dialogue5d, MainGame_Chapter1_WaitOff5d, MainGame_Chapter1_WaitOn5d, MainGame_Chapter1_Dialogue5e, MainGame_Chapter1_WaitOff5e, MainGame_Chapter1_WaitOn5e, MainGame_Chapter1_Dialogue5f, MainGame_Chapter1_WaitOff5f, MainGame_Chapter1_WaitOn5f, MainGame_Chapter1_Dialogue5g, MainGame_Chapter1_WaitOff5g, MainGame_Chapter1_WaitOn5g, MainGame_Chapter1_Dialogue6a, MainGame_Chapter1_WaitOff6a, MainGame_Chapter1_WaitOn6a, MainGame_Chapter1_Dialogue6b, MainGame_Chapter1_WaitOff6b, MainGame_Chapter1_WaitOn6b, MainGame_Chapter1_Dialogue6c, MainGame_Chapter1_WaitOff6c, MainGame_Chapter1_WaitOn6c, MainGame_Chapter1_Dialogue6d, MainGame_Chapter1_WaitOff6d, MainGame_Chapter1_WaitOn6d, MainGame_Chapter1_Dialogue6e, MainGame_Chapter1_WaitOff6e, MainGame_Chapter1_WaitOn6e, MainGame_Chapter1_Dialogue6f, MainGame_Chapter1_WaitOff6f, MainGame_Chapter1_WaitOn6f, MainGame_Chapter1_Dialogue6g, MainGame_Chapter1_WaitOff6g, MainGame_Chapter1_WaitOn6g, MainGame_Chapter1_Dialogue7, MainGame_Chapter1_WaitOff7, MainGame_Chapter1_WaitOn7, MainGame_Chapter1_Dialogue8, MainGame_Chapter1_WaitOff8, MainGame_Chapter1_WaitOn8, MainGame_Chapter1_Dialogue9, MainGame_Chapter1_WaitOff9, MainGame_Chapter1_WaitOn9, MainGame_Chapter1_Dialogue10, MainGame_Chapter1_WaitOff10, MainGame_Chapter1_WaitOn10, MainGame_Chapter1_Dialogue11, MainGame_Chapter1_WaitOff11, MainGame_Chapter1_WaitOn11, MainGame_Chapter1_Dialogue12, MainGame_Chapter1_WaitOff12, MainGame_Chapter1_WaitOn12, MainGame_Chapter1_Dialogue13, MainGame_Chapter1_WaitOff13, MainGame_Chapter1_WaitOn13, MainGame_Chapter1_Dialogue14, MainGame_Chapter1_WaitOff14, MainGame_Chapter1_WaitOn14, MainGame_Chapter1_Dialogue15, MainGame_Chapter1_WaitOff15, MainGame_Chapter1_WaitOn15, MainGame_Chapter1_Dialogue16a, MainGame_Chapter1_WaitOff16a, MainGame_Chapter1_WaitOn16a, MainGame_Chapter1_Dialogue16b, MainGame_Chapter1_WaitOff16b, MainGame_Chapter1_WaitOn16b, MainGame_Chapter1_Dialogue16c, MainGame_Chapter1_WaitOff16c, MainGame_Chapter1_WaitOn16c, MainGame_Chapter1_Dialogue16d, MainGame_Chapter1_WaitOff16d, MainGame_Chapter1_WaitOn16d, MainGame_Chapter1_Dialogue16e, MainGame_Chapter1_WaitOff16e, MainGame_Chapter1_WaitOn16e, MainGame_Chapter1_Dialogue16f, MainGame_Chapter1_WaitOff16f, MainGame_Chapter1_WaitOn16f, MainGame_Chapter1_Dialogue17a, MainGame_Chapter1_WaitOff17a, MainGame_Chapter1_WaitOn17a, MainGame_Chapter1_Dialogue17b, MainGame_Chapter1_WaitOff17b, MainGame_Chapter1_WaitOn17b, MainGame_Chapter1_Dialogue17c, MainGame_Chapter1_WaitOff17c, MainGame_Chapter1_WaitOn17c, MainGame_Chapter1_Dialogue17d, MainGame_Chapter1_WaitOff17d, MainGame_Chapter1_WaitOn17d, MainGame_Chapter1_Dialogue17e, MainGame_Chapter1_WaitOff17e, MainGame_Chapter1_WaitOn17e, MainGame_Chapter1_Dialogue17f, MainGame_Chapter1_WaitOff17f, MainGame_Chapter1_WaitOn17f, MainGame_Chapter1_Dialogue18, MainGame_Chapter1_WaitOff18, MainGame_Chapter1_WaitOn18, MainGame_Chapter1_Dialogue19, MainGame_Chapter1_WaitOff19, MainGame_Chapter1_WaitOn19, MainGame_Chapter1_Dialogue20, MainGame_Chapter1_WaitOff20, MainGame_Chapter1_WaitOn20, MainGame_Chapter1_Dialogue21, MainGame_Chapter1_WaitOff21, MainGame_Chapter1_WaitOn21, MainGame_Chapter1_Dialogue22, MainGame_Chapter1_WaitOff22, MainGame_Chapter1_WaitOn22, MainGame_Chapter1_Dialogue23, MainGame_Chapter1_WaitOff23, MainGame_Chapter1_WaitOn23, MainGame_Chapter1_Dialogue24, MainGame_Chapter1_WaitOff24, MainGame_Chapter1_WaitOn24, MainGame_Chapter1_Dialogue25, MainGame_Chapter1_WaitOff25, MainGame_Chapter1_WaitOn25, MainGame_Chapter1_Dialogue26, MainGame_Chapter1_WaitOff26, MainGame_Chapter1_WaitOn26, MainGame_Chapter1_Dialogue27, MainGame_Chapter1_WaitOff27, MainGame_Chapter1_WaitOn27, MainGame_Chapter1_Dialogue28, MainGame_Chapter1_WaitOff28, MainGame_Chapter1_WaitOn28, MainGame_Chapter1_Dialogue29, MainGame_Chapter1_WaitOff29, MainGame_Chapter1_WaitOn29, MainGame_Chapter1_Dialogue30, MainGame_Chapter1_WaitOff30, MainGame_Chapter1_WaitOn30, MainGame_Chapter1_Dialogue31, MainGame_Chapter1_WaitOff31, MainGame_Chapter1_WaitOn31, MainGame_Chapter1_Dialogue32, MainGame_Chapter1_WaitOff32, MainGame_Chapter1_WaitOn32, MainGame_Chapter1_Dialogue33, MainGame_Chapter1_WaitOff33, MainGame_Chapter1_WaitOn33, MainGame_Chapter1_Dialogue34, MainGame_Chapter1_WaitOff34, MainGame_Chapter1_WaitOn34, MainGame_Chapter1_Dialogue35, MainGame_Chapter1_WaitOff35, MainGame_Chapter1_WaitOn35, MainGame_Chapter1_Dialogue36, MainGame_Chapter1_WaitOff36, MainGame_Chapter1_WaitOn36, MainGame_Chapter1_Dialogue37, MainGame_Chapter1_WaitOff37, MainGame_Chapter1_WaitOn37, MainGame_Chapter1_Dialogue38, MainGame_Chapter1_WaitOff38, MainGame_Chapter1_WaitOn38, MainGame_Chapter1_Dialogue39, MainGame_Chapter1_WaitOff39, MainGame_Chapter1_WaitOn39, MainGame_Chapter1_Dialogue40, MainGame_Chapter1_WaitOff40, MainGame_Chapter1_WaitOn40, MainGame_Chapter1_Dialogue41, MainGame_Chapter1_WaitOff41, MainGame_Chapter1_WaitOn41, MainGame_Chapter1_Dialogue42, MainGame_Chapter1_WaitOff42, MainGame_Chapter1_WaitOn42, MainGame_Chapter2_Dialogue0, MainGame_Chapter2_WaitOff0, MainGame_Chapter2_WaitOn0, MainGame_Chapter2_Dialogue1, MainGame_Chapter2_WaitOff1, MainGame_Chapter2_WaitOn1, MainGame_Chapter2_Dialogue2, MainGame_Chapter2_WaitOff2, MainGame_Chapter2_WaitOn2, MainGame_Chapter2_Dialogue3, MainGame_Chapter2_WaitOff3, MainGame_Chapter2_WaitOn3, MainGame_Chapter2_Dialogue4, MainGame_Chapter2_WaitOff4, MainGame_Chapter2_WaitOn4, MainGame_Chapter2_Dialogue5, MainGame_Chapter2_WaitOff5, MainGame_Chapter2_WaitOn5, MainGame_Chapter2_Dialogue6, MainGame_Chapter2_WaitOff6, MainGame_Chapter2_WaitOn6, MainGame_Chapter2_Dialogue7, MainGame_Chapter2_WaitOff7, MainGame_Chapter2_WaitOn7, MainGame_Chapter2_Dialogue8, MainGame_Chapter2_WaitOff8, MainGame_Chapter2_WaitOn8, MainGame_Chapter2_Dialogue9, MainGame_Chapter2_WaitOff9, MainGame_Chapter2_WaitOn9, MainGame_Chapter2_Dialogue10, MainGame_Chapter2_WaitOff10, MainGame_Chapter2_WaitOn10, MainGame_Chapter2_Dialogue11, MainGame_Chapter2_WaitOff11, MainGame_Chapter2_WaitOn11, MainGame_Chapter2_Dialogue12, MainGame_Chapter2_WaitOff12, MainGame_Chapter2_WaitOn12, MainGame_Chapter2_Dialogue13, MainGame_Chapter2_WaitOff13, MainGame_Chapter2_WaitOn13, MainGame_Chapter2_Dialogue14, MainGame_Chapter2_WaitOff14, MainGame_Chapter2_WaitOn14, MainGame_Chapter2_Dialogue15, MainGame_Chapter2_WaitOff15, MainGame_Chapter2_WaitOn15, MainGame_Chapter2_Dialogue16, MainGame_Chapter2_WaitOff16, MainGame_Chapter2_WaitOn16, MainGame_Chapter2_Dialogue17, MainGame_Chapter2_WaitOff17, MainGame_Chapter2_WaitOn17, MainGame_Chapter2_Dialogue18, MainGame_Chapter2_WaitOff18, MainGame_Chapter2_WaitOn18, MainGame_Chapter2_Dialogue19, MainGame_Chapter2_WaitOff19, MainGame_Chapter2_WaitOn19, MainGame_Chapter2_Dialogue20a, MainGame_Chapter2_WaitOff20a, MainGame_Chapter2_WaitOn20a, MainGame_Chapter2_Dialogue20b, MainGame_Chapter2_WaitOff20b, MainGame_Chapter2_WaitOn20b, MainGame_Chapter2_Dialogue20c, MainGame_Chapter2_WaitOff20c, MainGame_Chapter2_WaitOn20c, MainGame_Chapter2_Dialogue20d, MainGame_Chapter2_WaitOff20d, MainGame_Chapter2_WaitOn20d, MainGame_Chapter2_Dialogue20e, MainGame_Chapter2_WaitOff20e, MainGame_Chapter2_WaitOn20e, MainGame_Chapter2_Dialogue20f, MainGame_Chapter2_WaitOff20f, MainGame_Chapter2_WaitOn20f, MainGame_Chapter2_Dialogue21a, MainGame_Chapter2_WaitOff21a, MainGame_Chapter2_WaitOn21a, MainGame_Chapter2_Dialogue21b, MainGame_Chapter2_WaitOff21b, MainGame_Chapter2_WaitOn21b, MainGame_Chapter2_Dialogue21c, MainGame_Chapter2_WaitOff21c, MainGame_Chapter2_WaitOn21c, MainGame_Chapter2_Dialogue21d, MainGame_Chapter2_WaitOff21d, MainGame_Chapter2_WaitOn21d, MainGame_Chapter2_Dialogue21e, MainGame_Chapter2_WaitOff21e, MainGame_Chapter2_WaitOn21e, MainGame_Chapter2_Dialogue21f, MainGame_Chapter2_WaitOff21f, MainGame_Chapter2_WaitOn21f, MainGame_Chapter2_Dialogue22, MainGame_Chapter2_WaitOff22, MainGame_Chapter2_WaitOn22, MainGame_Chapter2_Dialogue23, MainGame_Chapter2_WaitOff23, MainGame_Chapter2_WaitOn23, MainGame_Chapter2_Dialogue24, MainGame_Chapter2_WaitOff24, MainGame_Chapter2_WaitOn24, MainGame_Chapter2_Dialogue25, MainGame_Chapter2_WaitOff25, MainGame_Chapter2_WaitOn25, MainGame_Chapter2_Dialogue26, MainGame_Chapter2_WaitOff26, MainGame_Chapter2_WaitOn26, MainGame_Chapter2_Dialogue27, MainGame_Chapter2_WaitOff27, MainGame_Chapter2_WaitOn27, MainGame_Chapter2_Dialogue28, MainGame_Chapter2_WaitOff28, MainGame_Chapter2_WaitOn28, MainGame_Chapter2_Dialogue29, MainGame_Chapter2_WaitOff29, MainGame_Chapter2_WaitOn29, MainGame_Chapter2_Dialogue30, MainGame_Chapter2_WaitOff30, MainGame_Chapter2_WaitOn30, MainGame_Chapter2_Dialogue31, MainGame_Chapter2_WaitOff31, MainGame_Chapter2_WaitOn31, MainGame_Chapter2_Dialogue32, MainGame_Chapter2_WaitOff32, MainGame_Chapter2_WaitOn32, MainGame_Chapter2_Dialogue33, MainGame_Chapter2_WaitOff33, MainGame_Chapter2_WaitOn33, MainGame_Chapter2_Dialogue34, MainGame_Chapter2_WaitOff34, MainGame_Chapter2_WaitOn34, MainGame_Chapter2_Dialogue35, MainGame_Chapter2_WaitOff35, MainGame_Chapter2_WaitOn35, MainGame_Chapter2_Dialogue36, MainGame_Chapter2_WaitOff36, MainGame_Chapter2_WaitOn36, MainGame_Chapter2_Dialogue37, MainGame_Chapter2_WaitOff37, MainGame_Chapter2_WaitOn37, MainGame_Chapter2_Dialogue38, MainGame_Chapter2_WaitOff38, MainGame_Chapter2_WaitOn38, MainGame_Chapter2_Dialogue39, MainGame_Chapter2_WaitOff39, MainGame_Chapter2_WaitOn39, MainGame_Chapter2_Dialogue40, MainGame_Chapter2_WaitOff40, MainGame_Chapter2_WaitOn40, MainGame_Chapter2_Dialogue41, MainGame_Chapter2_WaitOff41, MainGame_Chapter2_WaitOn41, MainGame_Chapter2_Dialogue42a, MainGame_Chapter2_WaitOff42a, MainGame_Chapter2_WaitOn42a, MainGame_Chapter2_Dialogue42b, MainGame_Chapter2_WaitOff42b, MainGame_Chapter2_WaitOn42b, MainGame_Chapter2_Dialogue42c, MainGame_Chapter2_WaitOff42c, MainGame_Chapter2_WaitOn42c, MainGame_Chapter2_Dialogue42d, MainGame_Chapter2_WaitOff42d, MainGame_Chapter2_WaitOn42d, MainGame_Chapter2_Dialogue42e, MainGame_Chapter2_WaitOff42e, MainGame_Chapter2_WaitOn42e, MainGame_Chapter2_Dialogue42f, MainGame_Chapter2_WaitOff42f, MainGame_Chapter2_WaitOn42f, MainGame_Chapter2_Dialogue43a, MainGame_Chapter2_WaitOff43a, MainGame_Chapter2_WaitOn43a, MainGame_Chapter2_Dialogue43b, MainGame_Chapter2_WaitOff43b, MainGame_Chapter2_WaitOn43b, MainGame_Chapter2_Dialogue43c, MainGame_Chapter2_WaitOff43c, MainGame_Chapter2_WaitOn43c, MainGame_Chapter2_Dialogue43d, MainGame_Chapter2_WaitOff43d, MainGame_Chapter2_WaitOn43d, MainGame_Chapter2_Dialogue43e, MainGame_Chapter2_WaitOff43e, MainGame_Chapter2_WaitOn43e, MainGame_Chapter2_Dialogue43f, MainGame_Chapter2_WaitOff43f, MainGame_Chapter2_WaitOn43f, MainGame_Chapter2_Dialogue44, MainGame_Chapter2_WaitOff44, MainGame_Chapter2_WaitOn44, MainGame_Chapter2_Dialogue45, MainGame_Chapter2_WaitOff45, MainGame_Chapter2_WaitOn45, MainGame_Chapter2_Dialogue46, MainGame_Chapter2_WaitOff46, MainGame_Chapter2_WaitOn46, MainGame_Chapter2_Dialogue47, MainGame_Chapter2_WaitOff47, MainGame_Chapter2_WaitOn47, MainGame_Chapter2_Dialogue48, MainGame_Chapter2_WaitOff48, MainGame_Chapter2_WaitOn48, MainGame_Chapter2_Dialogue49, MainGame_Chapter2_WaitOff49, MainGame_Chapter2_WaitOn49, MainGame_Chapter2_Dialogue50, MainGame_Chapter2_WaitOff50, MainGame_Chapter2_WaitOn50, MainGame_Chapter2_Dialogue51, MainGame_Chapter2_WaitOff51, MainGame_Chapter2_WaitOn51, MainGame_Chapter2_Dialogue52, MainGame_Chapter2_WaitOff52, MainGame_Chapter2_WaitOn52, MainGame_Chapter2_Dialogue53, MainGame_Chapter2_WaitOff53, MainGame_Chapter2_WaitOn53, MainGame_Chapter2_Dialogue54, MainGame_Chapter2_WaitOff54, MainGame_Chapter2_WaitOn54, MainGame_Chapter2_Dialogue55, MainGame_Chapter2_WaitOff55, MainGame_Chapter2_WaitOn55, MainGame_Chapter2_Dialogue56, MainGame_Chapter2_WaitOff56, MainGame_Chapter2_WaitOn56, MainGame_Chapter2_Dialogue57, MainGame_Chapter2_WaitOff57, MainGame_Chapter2_WaitOn57, MainGame_Chapter2_Dialogue58, MainGame_Chapter2_WaitOff58, MainGame_Chapter2_WaitOn58, MainGame_Chapter2_Dialogue59, MainGame_Chapter2_WaitOff59, MainGame_Chapter2_WaitOn59, MainGame_Chapter2_Dialogue60, MainGame_Chapter2_WaitOff60, MainGame_Chapter2_WaitOn60, MainGame_Chapter2_Dialogue61, MainGame_Chapter2_WaitOff61, MainGame_Chapter2_WaitOn61, MainGame_Chapter2_Dialogue62, MainGame_Chapter2_WaitOff62, MainGame_Chapter2_WaitOn62, MainGame_Chapter2_Dialogue63, MainGame_Chapter2_WaitOff63, MainGame_Chapter2_WaitOn63, MainGame_Chapter2_Dialogue64, MainGame_Chapter2_WaitOff64, MainGame_Chapter2_WaitOn64, MainGame_Chapter2_Dialogue65, MainGame_Chapter2_WaitOff65, MainGame_Chapter2_WaitOn65, MainGame_Chapter2_Dialogue66, MainGame_Chapter2_WaitOff66, MainGame_Chapter2_WaitOn66, MainGame_Chapter2_Dialogue67, MainGame_Chapter2_WaitOff67, MainGame_Chapter2_WaitOn67, MainGame_Chapter2_Dialogue68, MainGame_Chapter2_WaitOff68, MainGame_Chapter2_WaitOn68, MainGame_Chapter2_Dialogue69, MainGame_Chapter2_WaitOff69, MainGame_Chapter2_WaitOn69, MainGame_Chapter2_Dialogue70, MainGame_Chapter2_WaitOff70, MainGame_Chapter2_WaitOn70, MainGame_Chapter2_Dialogue71, MainGame_Chapter2_WaitOff71, MainGame_Chapter2_WaitOn71, MainGame_Chapter2_Dialogue72, MainGame_Chapter2_WaitOff72, MainGame_Chapter2_WaitOn72, MainGame_Chapter2_Dialogue73, MainGame_Chapter2_WaitOff73, MainGame_Chapter2_WaitOn73, MainGame_Chapter2_Dialogue74, MainGame_Chapter2_WaitOff74, MainGame_Chapter2_WaitOn74, MainGame_Chapter2_Dialogue75, MainGame_Chapter2_WaitOff75, MainGame_Chapter2_WaitOn75, MainGame_Chapter2_Dialogue76, MainGame_Chapter2_WaitOff76, MainGame_Chapter2_WaitOn76, MainGame_Chapter3_Dialogue0, MainGame_Chapter3_WaitOff0, MainGame_Chapter3_WaitOn0, MainGame_Chapter3_Dialogue1, MainGame_Chapter3_WaitOff1, MainGame_Chapter3_WaitOn1, MainGame_Chapter3_Dialogue2, MainGame_Chapter3_WaitOff2, MainGame_Chapter3_WaitOn2, MainGame_Chapter3_Dialogue3, MainGame_Chapter3_WaitOff3, MainGame_Chapter3_WaitOn3, MainGame_Chapter3_Dialogue4, MainGame_Chapter3_WaitOff4, MainGame_Chapter3_WaitOn4, MainGame_Chapter3_Dialogue5, MainGame_Chapter3_WaitOff5, MainGame_Chapter3_WaitOn5, MainGame_Chapter3_Dialogue6, MainGame_Chapter3_WaitOff6, MainGame_Chapter3_WaitOn6, MainGame_Chapter3_Dialogue7, MainGame_Chapter3_WaitOff7, MainGame_Chapter3_WaitOn7, MainGame_Chapter3_Dialogue8, MainGame_Chapter3_WaitOff8, MainGame_Chapter3_WaitOn8, MainGame_Chapter3_Dialogue9, MainGame_Chapter3_WaitOff9, MainGame_Chapter3_WaitOn9, MainGame_Chapter3_Dialogue10, MainGame_Chapter3_WaitOff10, MainGame_Chapter3_WaitOn10, MainGame_Chapter3_Dialogue11, MainGame_Chapter3_WaitOff11, MainGame_Chapter3_WaitOn11, MainGame_Chapter3_Dialogue12, MainGame_Chapter3_WaitOff12, MainGame_Chapter3_WaitOn12, MainGame_Chapter3_Dialogue13, MainGame_Chapter3_WaitOff13, MainGame_Chapter3_WaitOn13, MainGame_Chapter3_Dialogue14, MainGame_Chapter3_WaitOff14, MainGame_Chapter3_WaitOn14, MainGame_Chapter3_Dialogue15, MainGame_Chapter3_WaitOff15, MainGame_Chapter3_WaitOn15, MainGame_Chapter3_Dialogue16, MainGame_Chapter3_WaitOff16, MainGame_Chapter3_WaitOn16, MainGame_Chapter3_Dialogue17, MainGame_Chapter3_WaitOff17, MainGame_Chapter3_WaitOn17, MainGame_Chapter3_Dialogue18, MainGame_Chapter3_WaitOff18, MainGame_Chapter3_WaitOn18, MainGame_Chapter3_Dialogue19, MainGame_Chapter3_WaitOff19, MainGame_Chapter3_WaitOn19, MainGame_Chapter3_Dialogue20, MainGame_Chapter3_WaitOff20, MainGame_Chapter3_WaitOn20, MainGame_Chapter3_Dialogue21, MainGame_Chapter3_WaitOff21, MainGame_Chapter3_WaitOn21, MainGame_Chapter3_Dialogue22, MainGame_Chapter3_WaitOff22, MainGame_Chapter3_WaitOn22, MainGame_Chapter3_Dialogue23, MainGame_Chapter3_WaitOff23, MainGame_Chapter3_WaitOn23, MainGame_Chapter3_Dialogue24, MainGame_Chapter3_WaitOff24, MainGame_Chapter3_WaitOn24, MainGame_Chapter3_Dialogue25, MainGame_Chapter3_WaitOff25, MainGame_Chapter3_WaitOn25, MainGame_Chapter3_Dialogue26, MainGame_Chapter3_WaitOff26, MainGame_Chapter3_WaitOn26, MainGame_Chapter3_Dialogue27, MainGame_Chapter3_WaitOff27, MainGame_Chapter3_WaitOn27, MainGame_Chapter3_Dialogue28, MainGame_Chapter3_WaitOff28, MainGame_Chapter3_WaitOn28, MainGame_Chapter3_Dialogue29, MainGame_Chapter3_WaitOff29, MainGame_Chapter3_WaitOn29, MainGame_Chapter3_Dialogue30, MainGame_Chapter3_WaitOff30, MainGame_Chapter3_WaitOn30, MainGame_Chapter3_Dialogue31, MainGame_Chapter3_WaitOff31, MainGame_Chapter3_WaitOn31, MainGame_Chapter3_Dialogue32, MainGame_Chapter3_WaitOff32, MainGame_Chapter3_WaitOn32, MainGame_Chapter3_Dialogue33, MainGame_Chapter3_WaitOff33, MainGame_Chapter3_WaitOn33, MainGame_Chapter3_Dialogue34, MainGame_Chapter3_WaitOff34, MainGame_Chapter3_WaitOn34, MainGame_Chapter3_Dialogue35, MainGame_Chapter3_WaitOff35, MainGame_Chapter3_WaitOn35, MainGame_Chapter3_Dialogue36a, MainGame_Chapter3_WaitOff36a, MainGame_Chapter3_WaitOn36a, MainGame_Chapter3_Dialogue36b, MainGame_Chapter3_WaitOff36b, MainGame_Chapter3_WaitOn36b, MainGame_Chapter3_Dialogue36c, MainGame_Chapter3_WaitOff36c, MainGame_Chapter3_WaitOn36c, MainGame_Chapter3_Dialogue36d, MainGame_Chapter3_WaitOff36d, MainGame_Chapter3_WaitOn36d, MainGame_Chapter3_Dialogue36e, MainGame_Chapter3_WaitOff36e, MainGame_Chapter3_WaitOn36e, MainGame_Chapter3_Dialogue36f, MainGame_Chapter3_WaitOff36f, MainGame_Chapter3_WaitOn36f, MainGame_Chapter3_Dialogue37a, MainGame_Chapter3_WaitOff37a, MainGame_Chapter3_WaitOn37a, MainGame_Chapter3_Dialogue37b, MainGame_Chapter3_WaitOff37b, MainGame_Chapter3_WaitOn37b, MainGame_Chapter3_Dialogue37c, MainGame_Chapter3_WaitOff37c, MainGame_Chapter3_WaitOn37c, MainGame_Chapter3_Dialogue37d, MainGame_Chapter3_WaitOff37d, MainGame_Chapter3_WaitOn37d, MainGame_Chapter3_Dialogue37e, MainGame_Chapter3_WaitOff37e, MainGame_Chapter3_WaitOn37e, MainGame_Chapter3_Dialogue37f, MainGame_Chapter3_WaitOff37f, MainGame_Chapter3_WaitOn37f, MainGame_Chapter3_Dialogue38, MainGame_Chapter3_WaitOff38, MainGame_Chapter3_WaitOn38, MainGame_Chapter3_Dialogue39, MainGame_Chapter3_WaitOff39, MainGame_Chapter3_WaitOn39, MainGame_Chapter3_Dialogue40, MainGame_Chapter3_WaitOff40, MainGame_Chapter3_WaitOn40, MainGame_Chapter3_Dialogue41, MainGame_Chapter3_WaitOff41, MainGame_Chapter3_WaitOn41, MainGame_Chapter3_Dialogue42, MainGame_Chapter3_WaitOff42, MainGame_Chapter3_WaitOn42, MainGame_Chapter3_Dialogue43, MainGame_Chapter3_WaitOff43, MainGame_Chapter3_WaitOn43, MainGame_Chapter3_Dialogue45, MainGame_Chapter3_WaitOff45, MainGame_Chapter3_WaitOn45, MainGame_Chapter3_Dialogue46, MainGame_Chapter3_WaitOff46, MainGame_Chapter3_WaitOn46, MainGame_Chapter3_Dialogue47, MainGame_Chapter3_WaitOff47, MainGame_Chapter3_WaitOn47, MainGame_Chapter3_Dialogue48, MainGame_Chapter3_WaitOff48, MainGame_Chapter3_WaitOn48, MainGame_Chapter3_Dialogue49, MainGame_Chapter3_WaitOff49, MainGame_Chapter3_WaitOn49, MainGame_Chapter3_Dialogue50, MainGame_Chapter3_WaitOff50, MainGame_Chapter3_WaitOn50, MainGame_Chapter3_Dialogue51, MainGame_Chapter3_WaitOff51, MainGame_Chapter3_WaitOn51, MainGame_Chapter3_Dialogue52, MainGame_Chapter3_WaitOff52, MainGame_Chapter3_WaitOn52, MainGame_Chapter3_Dialogue53, MainGame_Chapter3_WaitOff53, MainGame_Chapter3_WaitOn53, MainGame_Chapter3_Dialogue54, MainGame_Chapter3_WaitOff54, MainGame_Chapter3_WaitOn54, MainGame_Chapter3_Dialogue55, MainGame_Chapter3_WaitOff55, MainGame_Chapter3_WaitOn55, MainGame_Chapter3_Dialogue56, MainGame_Chapter3_WaitOff56, MainGame_Chapter3_WaitOn56, MainGame_Chapter3_Dialogue58, MainGame_Chapter3_WaitOff58, MainGame_Chapter3_WaitOn58, MainGame_Chapter3_Dialogue59, MainGame_Chapter3_WaitOff59, MainGame_Chapter3_WaitOn59, MainGame_Chapter3_Dialogue60, MainGame_Chapter3_WaitOff60, MainGame_Chapter3_WaitOn60, MainGame_Chapter3_Dialogue61, MainGame_Chapter3_WaitOff61, MainGame_Chapter3_WaitOn61, MainGame_Chapter3_Dialogue62, MainGame_Chapter3_WaitOff62, MainGame_Chapter3_WaitOn62, MainGame_Chapter3_Dialogue63, MainGame_Chapter3_WaitOff63, MainGame_Chapter3_WaitOn63, MainGame_Chapter3_Dialogue64, MainGame_Chapter3_WaitOff64, MainGame_Chapter3_WaitOn64, MainGame_Chapter3_Dialogue65, MainGame_Chapter3_WaitOff65, MainGame_Chapter3_WaitOn65, MainGame_Chapter3_Dialogue66, MainGame_Chapter3_WaitOff66, MainGame_Chapter3_WaitOn66, MainGame_Chapter3_Dialogue67, MainGame_Chapter3_WaitOff67, MainGame_Chapter3_WaitOn67, MainGame_Chapter3_Dialogue68, MainGame_Chapter3_WaitOff68, MainGame_Chapter3_WaitOn68, MainGame_Chapter3_Dialogue69, MainGame_Chapter3_WaitOff69, MainGame_Chapter3_WaitOn69, MainGame_Chapter3_Dialogue70, MainGame_Chapter3_WaitOff70, MainGame_Chapter3_WaitOn70, MainGame_Chapter3_Dialogue71, MainGame_Chapter3_WaitOff71, MainGame_Chapter3_WaitOn71, MainGame_Chapter3_Dialogue72, MainGame_Chapter3_WaitOff72, MainGame_Chapter3_WaitOn72, MainGame_Chapter3_Dialogue73, MainGame_Chapter3_WaitOff73, MainGame_Chapter3_WaitOn73, MainGame_Chapter3_Dialogue74, MainGame_Chapter3_WaitOff74, MainGame_Chapter3_WaitOn74, MainGame_Chapter3_Dialogue75, MainGame_Chapter3_WaitOff75, MainGame_Chapter3_WaitOn75, MainGame_Chapter3_Dialogue76a, MainGame_Chapter3_WaitOff76a, MainGame_Chapter3_WaitOn76a, MainGame_Chapter3_Dialogue76b, MainGame_Chapter3_WaitOff76b, MainGame_Chapter3_WaitOn76b, MainGame_Chapter3_Dialogue76c, MainGame_Chapter3_WaitOff76c, MainGame_Chapter3_WaitOn76c, MainGame_Chapter3_Dialogue76d, MainGame_Chapter3_WaitOff76d, MainGame_Chapter3_WaitOn76d, MainGame_Chapter3_Dialogue76e, MainGame_Chapter3_WaitOff76e, MainGame_Chapter3_WaitOn76e, MainGame_Chapter3_Dialogue76f, MainGame_Chapter3_WaitOff76f, MainGame_Chapter3_WaitOn76f, MainGame_Chapter3_Dialogue77a, MainGame_Chapter3_WaitOff77a, MainGame_Chapter3_WaitOn77a, MainGame_Chapter3_Dialogue77b, MainGame_Chapter3_WaitOff77b, MainGame_Chapter3_WaitOn77b, MainGame_Chapter3_Dialogue77c, MainGame_Chapter3_WaitOff77c, MainGame_Chapter3_WaitOn77c, MainGame_Chapter3_Dialogue77d, MainGame_Chapter3_WaitOff77d, MainGame_Chapter3_WaitOn77d, MainGame_Chapter3_Dialogue77e, MainGame_Chapter3_WaitOff77e, MainGame_Chapter3_WaitOn77e, MainGame_Chapter3_Dialogue77f, MainGame_Chapter3_WaitOff77f, MainGame_Chapter3_WaitOn77f, MainGame_Chapter3_Dialogue78, MainGame_Chapter3_WaitOff78, MainGame_Chapter3_WaitOn78, MainGame_Chapter3_Dialogue79, MainGame_Chapter3_WaitOff79, MainGame_Chapter3_WaitOn79, MainGame_Chapter3_Dialogue80, MainGame_Chapter3_WaitOff80, MainGame_Chapter3_WaitOn80, MainGame_Chapter3_Dialogue81, MainGame_Chapter3_WaitOff81, MainGame_Chapter3_WaitOn81, MainGame_Chapter3_Dialogue82, MainGame_Chapter3_WaitOff82, MainGame_Chapter3_WaitOn82, MainGame_Chapter3_Dialogue83, MainGame_Chapter3_WaitOff83, MainGame_Chapter3_WaitOn83, MainGame_Chapter3_Dialogue85, MainGame_Chapter3_WaitOff85, MainGame_Chapter3_WaitOn85, MainGame_Chapter3_Dialogue86, MainGame_Chapter3_WaitOff86, MainGame_Chapter3_WaitOn86, MainGame_Chapter3_Dialogue87, MainGame_Chapter3_WaitOff87, MainGame_Chapter3_WaitOn87, MainGame_Chapter3_Dialogue88, MainGame_Chapter3_WaitOff88, MainGame_Chapter3_WaitOn88, MainGame_Chapter3_Dialogue89, MainGame_Chapter3_WaitOff89, MainGame_Chapter3_WaitOn89, MainGame_Chapter3_Dialogue90, MainGame_Chapter3_WaitOff90, MainGame_Chapter3_WaitOn90, MainGame_Chapter3_Dialogue91, MainGame_Chapter3_WaitOff91, MainGame_Chapter3_WaitOn91, MainGame_Chapter3_Dialogue92, MainGame_Chapter3_WaitOff92, MainGame_Chapter3_WaitOn92, MainGame_Chapter3_Dialogue93, MainGame_Chapter3_WaitOff93, MainGame_Chapter3_WaitOn93, MainGame_Chapter3_Dialogue94, MainGame_Chapter3_WaitOff94, MainGame_Chapter3_WaitOn94, MainGame_Chapter3_Dialogue95, MainGame_Chapter3_WaitOff95, MainGame_Chapter3_WaitOn95, MainGame_Chapter3_Dialogue96, MainGame_Chapter3_WaitOff96, MainGame_Chapter3_WaitOn96, MainGame_Chapter3_Dialogue97, MainGame_Chapter3_WaitOff97, MainGame_Chapter3_WaitOn97, MainGame_Chapter3_Dialogue98, MainGame_Chapter3_WaitOff98, MainGame_Chapter3_WaitOn98, MainGame_Chapter3_Dialogue99, MainGame_Chapter3_WaitOff99, MainGame_Chapter3_WaitOn99, MainGame_Chapter3_Dialogue100, MainGame_Chapter3_WaitOff100, MainGame_Chapter3_WaitOn100, MainGame_Chapter3_Dialogue101, MainGame_Chapter3_WaitOff101, MainGame_Chapter3_WaitOn101, MainGame_Chapter3_Dialogue102, MainGame_Chapter3_WaitOff102, MainGame_Chapter3_WaitOn102, MainGame_Chapter3_Dialogue103, MainGame_Chapter3_WaitOff103, MainGame_Chapter3_WaitOn103, MainGame_Chapter3_Dialogue104, MainGame_Chapter3_WaitOff104, MainGame_Chapter3_WaitOn104, MainGame_Chapter4_Dialogue0, MainGame_Chapter4_WaitOff0, MainGame_Chapter4_WaitOn0, MainGame_Chapter4_Dialogue1, MainGame_Chapter4_WaitOff1, MainGame_Chapter4_WaitOn1, MainGame_Chapter4_Dialogue2, MainGame_Chapter4_WaitOff2, MainGame_Chapter4_WaitOn2, MainGame_Chapter4_Dialogue3, MainGame_Chapter4_WaitOff3, MainGame_Chapter4_WaitOn3, MainGame_Chapter4_Dialogue4, MainGame_Chapter4_WaitOff4, MainGame_Chapter4_WaitOn4, MainGame_Chapter4_Dialogue5, MainGame_Chapter4_WaitOff5, MainGame_Chapter4_WaitOn5, MainGame_Chapter4_Dialogue6, MainGame_Chapter4_WaitOff6, MainGame_Chapter4_WaitOn6, MainGame_Chapter4_Dialogue7, MainGame_Chapter4_WaitOff7, MainGame_Chapter4_WaitOn7, MainGame_Chapter4_Dialogue8, MainGame_Chapter4_WaitOff8, MainGame_Chapter4_WaitOn8, MainGame_Chapter4_Dialogue9, MainGame_Chapter4_WaitOff9, MainGame_Chapter4_WaitOn9, MainGame_Chapter4_Dialogue10, MainGame_Chapter4_WaitOff10, MainGame_Chapter4_WaitOn10, MainGame_Chapter4_Dialogue11, MainGame_Chapter4_WaitOff11, MainGame_Chapter4_WaitOn11, MainGame_Chapter4_Dialogue12, MainGame_Chapter4_WaitOff12, MainGame_Chapter4_WaitOn12, MainGame_Chapter4_Dialogue13, MainGame_Chapter4_WaitOff13, MainGame_Chapter4_WaitOn13, MainGame_Chapter4_Dialogue14, MainGame_Chapter4_WaitOff14, MainGame_Chapter4_WaitOn14, MainGame_Chapter4_Dialogue15, MainGame_Chapter4_WaitOff15, MainGame_Chapter4_WaitOn15, MainGame_Chapter4_Dialogue16, MainGame_Chapter4_WaitOff16, MainGame_Chapter4_WaitOn16, MainGame_Chapter4_Dialogue17, MainGame_Chapter4_WaitOff17, MainGame_Chapter4_WaitOn17, MainGame_Chapter4_Dialogue18, MainGame_Chapter4_WaitOff18, MainGame_Chapter4_WaitOn18, MainGame_Chapter4_Dialogue19, MainGame_Chapter4_WaitOff19, MainGame_Chapter4_WaitOn19, MainGame_Chapter4_Dialogue20, MainGame_Chapter4_WaitOff20, MainGame_Chapter4_WaitOn20, MainGame_Chapter4_Dialogue21, MainGame_Chapter4_WaitOff21, MainGame_Chapter4_WaitOn21, MainGame_Chapter4_Dialogue22, MainGame_Chapter4_WaitOff22, MainGame_Chapter4_WaitOn22, MainGame_Chapter4_Dialogue23, MainGame_Chapter4_WaitOff23, MainGame_Chapter4_WaitOn23, MainGame_Chapter4_Dialogue24, MainGame_Chapter4_WaitOff24, MainGame_Chapter4_WaitOn24, MainGame_Chapter4_Dialogue25, MainGame_Chapter4_WaitOff25, MainGame_Chapter4_WaitOn25, MainGame_Chapter4_Dialogue26, MainGame_Chapter4_WaitOff26, MainGame_Chapter4_WaitOn26, MainGame_Chapter4_Dialogue27, MainGame_Chapter4_WaitOff27, MainGame_Chapter4_WaitOn27, MainGame_Chapter4_Dialogue28, MainGame_Chapter4_WaitOff28, MainGame_Chapter4_WaitOn28, MainGame_Chapter4_Dialogue29, MainGame_Chapter4_WaitOff29, MainGame_Chapter4_WaitOn29, MainGame_Chapter4_Dialogue30, MainGame_Chapter4_WaitOff30, MainGame_Chapter4_WaitOn30, MainGame_Chapter4_Dialogue31, MainGame_Chapter4_WaitOff31, MainGame_Chapter4_WaitOn31, MainGame_Chapter4_Dialogue32, MainGame_Chapter4_WaitOff32, MainGame_Chapter4_WaitOn32, MainGame_Chapter4_Dialogue33, MainGame_Chapter4_WaitOff33, MainGame_Chapter4_WaitOn33, MainGame_Chapter4_Dialogue34, MainGame_Chapter4_WaitOff34, MainGame_Chapter4_WaitOn34, MainGame_Chapter4_Dialogue35, MainGame_Chapter4_WaitOff35, MainGame_Chapter4_WaitOn35, MainGame_Chapter4_Dialogue36, MainGame_Chapter4_WaitOff36, MainGame_Chapter4_WaitOn36, MainGame_Chapter4_Dialogue37, MainGame_Chapter4_WaitOff37, MainGame_Chapter4_WaitOn37, MainGame_Chapter4_Dialogue38, MainGame_Chapter4_WaitOff38, MainGame_Chapter4_WaitOn38, MainGame_Chapter4_Dialogue39, MainGame_Chapter4_WaitOff39, MainGame_Chapter4_WaitOn39, MainGame_Chapter4_Dialogue40, MainGame_Chapter4_WaitOff40, MainGame_Chapter4_WaitOn40, MainGame_Chapter4_Dialogue41, MainGame_Chapter4_WaitOff41, MainGame_Chapter4_WaitOn41, MainGame_Chapter4_Dialogue42, MainGame_Chapter4_WaitOff42, MainGame_Chapter4_WaitOn42, MainGame_Chapter4_Dialogue43, MainGame_Chapter4_WaitOff43, MainGame_Chapter4_WaitOn43, MainGame_Chapter4_Dialogue44, MainGame_Chapter4_WaitOff44, MainGame_Chapter4_WaitOn44, MainGame_Chapter4_Dialogue45, MainGame_Chapter4_WaitOff45, MainGame_Chapter4_WaitOn45, MainGame_Chapter4_Dialogue46, MainGame_Chapter4_WaitOff46, MainGame_Chapter4_WaitOn46, MainGame_Chapter4_Dialogue47, MainGame_Chapter4_WaitOff47, MainGame_Chapter4_WaitOn47, MainGame_Chapter4_Dialogue48, MainGame_Chapter4_WaitOff48, MainGame_Chapter4_WaitOn48, MainGame_Chapter4_Dialogue49, MainGame_Chapter4_WaitOff49, MainGame_Chapter4_WaitOn49, MainGame_Chapter4_Dialogue50, MainGame_Chapter4_WaitOff50, MainGame_Chapter4_WaitOn50, MainGame_Chapter4_Dialogue51, MainGame_Chapter4_WaitOff51, MainGame_Chapter4_WaitOn51, MainGame_Chapter4_Dialogue52, MainGame_Chapter4_WaitOff52, MainGame_Chapter4_WaitOn52, MainGame_Chapter4_Dialogue53, MainGame_Chapter4_WaitOff53, MainGame_Chapter4_WaitOn53, MainGame_Chapter4_Dialogue54, MainGame_Chapter4_WaitOff54, MainGame_Chapter4_WaitOn54, MainGame_Chapter4_Dialogue55, MainGame_Chapter4_WaitOff55, MainGame_Chapter4_WaitOn55, MainGame_Chapter4_Dialogue56, MainGame_Chapter4_WaitOff56, MainGame_Chapter4_WaitOn56, MainGame_Chapter4_Dialogue57, MainGame_Chapter4_WaitOff57, MainGame_Chapter4_WaitOn57, MainGame_Chapter4_Dialogue58, MainGame_Chapter4_WaitOff58, MainGame_Chapter4_WaitOn58, MainGame_GameOver_Init, MainGame_GameOver, MainGame_GameOver_WaitOff, MainGame_GameOver_WaitOn} MainGame_State;

//input buffer overflow. use new state machine!
//using ch4_line58 to get chapter 1

void TickFct_LifeDisplay(){
   switch(Life_State){ //Transitions
      case Life_SMStart:
         Life_State = Life_Init;
         break;
      case Life_Init:
         if(display_lives == 0){
            Life_State = Life_Init;    
         }
         else if(display_lives == 1){
            Life_State = Life_Display;    
         }
         else{
            Life_State = Life_Init; 
         }
         break;
      case Life_Display:
         if(display_lives == 1){
            Life_State = Life_Display;             
         }
         else if(display_lives == 0){
            Life_State = Life_Init;    
         }
         else{
            Life_State = Life_Init;    
         }
         break;
      default:
         break;  
    } //now show chapter numbers via B3, B4, B5, B6, B7
    //option to display lives or display chapter number
    switch(Life_State){ //State actions
       case Life_SMStart:
          break;
       case Life_Init:
          if(lives == 3){
             B0 = B1 = B2 = 1;
             //B3 = B4 = B5 = B6 = B7 = 0;
          }
          else if(lives == 2){
             B0 = B1 = 1;
             B2 = 0;
             //B2 = B3 = B4 = B5 = B6 = B7 = 0;
          }
          else if(lives == 1){
             B0 = 1;
             B1 = B2 = 0;
             //B1 = B2 = B3 = B4 = B5 = B6 = B7 = 0;
          }
          else if(lives == 0){
             B0 = B1 = B2 = 0; 
             MainGame_State = MainGame_GameOver_Init;
             lives = 3;
          }
          break;
       case Life_Display:
          if(trigger_life_loss == 1){
             printf("\nYou lost a life!\n");    
             lives = lives - 1;
          }
          printf("\nLives remaining: %d\n", lives);
          break;
       default:
          break;
    }
}


enum MainGame2_States {MainGame2_Init, MainGame2_Chapter4_Dialogue59, MainGame2_Chapter4_WaitOff59, MainGame2_Chapter4_WaitOn59, MainGame2_Chapter4_Dialogue60, MainGame2_Chapter4_WaitOff60, MainGame2_Chapter4_WaitOn60, MainGame2_Chapter4_Dialogue61, MainGame2_Chapter4_WaitOff61, MainGame2_Chapter4_WaitOn61, MainGame2_Chapter4_Dialogue62, MainGame2_Chapter4_WaitOff62, MainGame2_Chapter4_WaitOn62, MainGame2_Chapter4_Dialogue63, MainGame2_Chapter4_WaitOff63, MainGame2_Chapter4_WaitOn63, MainGame2_Chapter4_Dialogue64, MainGame2_Chapter4_WaitOff64, MainGame2_Chapter4_WaitOn64, MainGame2_Chapter4_Dialogue65, MainGame2_Chapter4_WaitOff65, MainGame2_Chapter4_WaitOn65, MainGame2_Chapter4_Dialogue66, MainGame2_Chapter4_WaitOff66, MainGame2_Chapter4_WaitOn66, MainGame2_Chapter4_Dialogue67, MainGame2_Chapter4_WaitOff67, MainGame2_Chapter4_WaitOn67, MainGame2_Chapter4_Dialogue68, MainGame2_Chapter4_WaitOff68, MainGame2_Chapter4_WaitOn68, MainGame2_Chapter4_Dialogue69, MainGame2_Chapter4_WaitOff69, MainGame2_Chapter4_WaitOn69, MainGame2_Chapter4_Dialogue70, MainGame2_Chapter4_WaitOff70, MainGame2_Chapter4_WaitOn70, MainGame2_Chapter4_Dialogue71, MainGame2_Chapter4_WaitOff71, MainGame2_Chapter4_WaitOn71, MainGame2_JeffRoute_Dialogue0, MainGame2_JeffRoute_WaitOff0, MainGame2_JeffRoute_WaitOn0, MainGame2_BrianRoute_Dialogue0, MainGame2_BrianRoute_WaitOff0, MainGame2_BrianRoute_WaitOn0, MainGame2_FrankRoute_Dialogue0, MainGame2_FrankRoute_WaitOff0, MainGame2_FrankRoute_WaitOn0, MainGame2_ElenaRoute_Dialogue0, MainGame2_ElenaRoute_WaitOff0, MainGame2_ElenaRoute_WaitOn0, MainGame2_JeffRoute_Dialogue1, MainGame2_JeffRoute_WaitOff1, MainGame2_JeffRoute_WaitOn1, MainGame2_JeffRoute_Dialogue2, MainGame2_JeffRoute_WaitOff2, MainGame2_JeffRoute_WaitOn2, MainGame2_JeffRoute_Dialogue3, MainGame2_JeffRoute_WaitOff3, MainGame2_JeffRoute_WaitOn3, MainGame2_JeffRoute_Dialogue4, MainGame2_JeffRoute_WaitOff4, MainGame2_JeffRoute_WaitOn4, MainGame2_JeffRoute_Dialogue5, MainGame2_JeffRoute_WaitOff5, MainGame2_JeffRoute_WaitOn5, MainGame2_JeffRoute_Dialogue6, MainGame2_JeffRoute_WaitOff6, MainGame2_JeffRoute_WaitOn6, MainGame2_JeffRoute_Dialogue7, MainGame2_JeffRoute_WaitOff7, MainGame2_JeffRoute_WaitOn7, MainGame2_JeffRoute_Dialogue8, MainGame2_JeffRoute_WaitOff8, MainGame2_JeffRoute_WaitOn8, MainGame2_JeffRoute_Dialogue9, MainGame2_JeffRoute_WaitOff9, MainGame2_JeffRoute_WaitOn9, MainGame2_JeffRoute_Dialogue10, MainGame2_JeffRoute_WaitOff10, MainGame2_JeffRoute_WaitOn10, MainGame2_BrianRoute_Dialogue1, MainGame2_BrianRoute_WaitOff1, MainGame2_BrianRoute_WaitOn1, MainGame2_BrianRoute_Dialogue2, MainGame2_BrianRoute_WaitOff2, MainGame2_BrianRoute_WaitOn2, MainGame2_BrianRoute_Dialogue3, MainGame2_BrianRoute_WaitOff3, MainGame2_BrianRoute_WaitOn3, MainGame2_BrianRoute_Dialogue4, MainGame2_BrianRoute_WaitOff4, MainGame2_BrianRoute_WaitOn4, MainGame2_BrianRoute_Dialogue5, MainGame2_BrianRoute_WaitOff5, MainGame2_BrianRoute_WaitOn5, MainGame2_BrianRoute_Dialogue6, MainGame2_BrianRoute_WaitOff6, MainGame2_BrianRoute_WaitOn6, MainGame2_BrianRoute_Dialogue7, MainGame2_BrianRoute_WaitOff7, MainGame2_BrianRoute_WaitOn7, MainGame2_BrianRoute_Dialogue8, MainGame2_BrianRoute_WaitOff8, MainGame2_BrianRoute_WaitOn8, MainGame2_BrianRoute_Dialogue9, MainGame2_BrianRoute_WaitOff9, MainGame2_BrianRoute_WaitOn9, MainGame2_BrianRoute_Dialogue10, MainGame2_BrianRoute_WaitOff10, MainGame2_BrianRoute_WaitOn10, MainGame2_FrankRoute_Dialogue1, MainGame2_FrankRoute_WaitOff1, MainGame2_FrankRoute_WaitOn1, MainGame2_FrankRoute_Dialogue2, MainGame2_FrankRoute_WaitOff2, MainGame2_FrankRoute_WaitOn2, MainGame2_FrankRoute_Dialogue3, MainGame2_FrankRoute_WaitOff3, MainGame2_FrankRoute_WaitOn3, MainGame2_FrankRoute_Dialogue4, MainGame2_FrankRoute_WaitOff4, MainGame2_FrankRoute_WaitOn4, MainGame2_FrankRoute_Dialogue5, MainGame2_FrankRoute_WaitOff5, MainGame2_FrankRoute_WaitOn5, MainGame2_FrankRoute_Dialogue6, MainGame2_FrankRoute_WaitOff6, MainGame2_FrankRoute_WaitOn6, MainGame2_FrankRoute_Dialogue7, MainGame2_FrankRoute_WaitOff7, MainGame2_FrankRoute_WaitOn7, MainGame2_FrankRoute_Dialogue8, MainGame2_FrankRoute_WaitOff8, MainGame2_FrankRoute_WaitOn8, MainGame2_FrankRoute_Dialogue9, MainGame2_FrankRoute_WaitOff9, MainGame2_FrankRoute_WaitOn9, MainGame2_FrankRoute_Dialogue10, MainGame2_FrankRoute_WaitOff10, MainGame2_FrankRoute_WaitOn10, MainGame2_ElenaRoute_Dialogue1, MainGame2_ElenaRoute_WaitOff1, MainGame2_ElenaRoute_WaitOn1, MainGame2_ElenaRoute_Dialogue2, MainGame2_ElenaRoute_WaitOff2, MainGame2_ElenaRoute_WaitOn2, MainGame2_ElenaRoute_Dialogue3, MainGame2_ElenaRoute_WaitOff3, MainGame2_ElenaRoute_WaitOn3, MainGame2_ElenaRoute_Dialogue4, MainGame2_ElenaRoute_WaitOff4, MainGame2_ElenaRoute_WaitOn4, MainGame2_ElenaRoute_Dialogue5, MainGame2_ElenaRoute_WaitOff5, MainGame2_ElenaRoute_WaitOn5, MainGame2_ElenaRoute_Dialogue6, MainGame2_ElenaRoute_WaitOff6, MainGame2_ElenaRoute_WaitOn6, MainGame2_ElenaRoute_Dialogue7, MainGame2_ElenaRoute_WaitOff7, MainGame2_ElenaRoute_WaitOn7, MainGame2_ElenaRoute_Dialogue8, MainGame2_ElenaRoute_WaitOff8, MainGame2_ElenaRoute_WaitOn8, MainGame2_ElenaRoute_Dialogue9, MainGame2_ElenaRoute_WaitOff9, MainGame2_ElenaRoute_WaitOn9, MainGame2_ElenaRoute_Dialogue10, MainGame2_ElenaRoute_WaitOff10, MainGame2_ElenaRoute_WaitOn10, MainGame2_EndScreen, MainGame2_EndScreen_WaitOff, MainGame2_EndScreen_WaitOn} MainGame2_State;

void TickFct_MainGame2(){
   switch(MainGame2_State){ //Transition
      case MainGame2_Init:
         if(MainGame_State != MainGame_Chapter4_WaitOn57){
            MainGame2_State = MainGame2_Init;    
         }
         else{
            MainGame2_State = MainGame2_Chapter4_Dialogue59;  
         }
         break;
      case MainGame2_Chapter4_Dialogue59:
         MainGame2_State = MainGame2_Chapter4_WaitOff59;
         break;
      case MainGame2_Chapter4_WaitOff59:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_WaitOff59;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_Chapter4_WaitOn59;
         }
         break;
      case MainGame2_Chapter4_WaitOn59:
         if(A0 == 0){
            MainGame2_State = MainGame2_Chapter4_WaitOn59;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_Dialogue60;     
         }
         break;
      case MainGame2_Chapter4_Dialogue60:
         MainGame2_State = MainGame2_Chapter4_WaitOff60;
         break;
      case MainGame2_Chapter4_WaitOff60:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_WaitOff60;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_Chapter4_WaitOn60;
         }
         break;
      case MainGame2_Chapter4_WaitOn60:
         if(A0 == 0){
            MainGame2_State = MainGame2_Chapter4_WaitOn60;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_Dialogue61;     
         }
         break;
       case MainGame2_Chapter4_Dialogue61:
         MainGame2_State = MainGame2_Chapter4_WaitOff61;
         break;
      case MainGame2_Chapter4_WaitOff61:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_WaitOff61;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_Chapter4_WaitOn61;
         }
         break;
      case MainGame2_Chapter4_WaitOn61:
         if(A0 == 0){
            MainGame2_State = MainGame2_Chapter4_WaitOn61;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_Dialogue62;     
         }
         break;        
      case MainGame2_Chapter4_Dialogue62:
         MainGame2_State = MainGame2_Chapter4_WaitOff62;
         break;
      case MainGame2_Chapter4_WaitOff62:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_WaitOff62;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_Chapter4_WaitOn62;
         }
         break;
      case MainGame2_Chapter4_WaitOn62:
         if(A0 == 0){
            MainGame2_State = MainGame2_Chapter4_WaitOn62;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_Dialogue63;     
         }
         break;
      case MainGame2_Chapter4_Dialogue63:
         MainGame2_State = MainGame2_Chapter4_WaitOff63;
         break;
      case MainGame2_Chapter4_WaitOff63:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_WaitOff63;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_Chapter4_WaitOn63;
         }
         break;
      case MainGame2_Chapter4_WaitOn63:
         if(A0 == 0){
            MainGame2_State = MainGame2_Chapter4_WaitOn63;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_Dialogue64;     
         }
         break;
      case MainGame2_Chapter4_Dialogue64:
         MainGame2_State = MainGame2_Chapter4_WaitOff64;
         break;
      case MainGame2_Chapter4_WaitOff64:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_WaitOff64;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_Chapter4_WaitOn64;
         }
         break;
      case MainGame2_Chapter4_WaitOn64:
         if(A0 == 0){
            MainGame2_State = MainGame2_Chapter4_WaitOn64;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_Dialogue65;     
         }
         break;
      case MainGame2_Chapter4_Dialogue65:
         MainGame2_State = MainGame2_Chapter4_WaitOff65;
         break;
      case MainGame2_Chapter4_WaitOff65:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_WaitOff65;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_Chapter4_WaitOn65;
         }
         break;
      case MainGame2_Chapter4_WaitOn65:
         if(A0 == 0){
            MainGame2_State = MainGame2_Chapter4_WaitOn65;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_Dialogue66;     
         }
         break;
      case MainGame2_Chapter4_Dialogue66:
         MainGame2_State = MainGame2_Chapter4_WaitOff66;
         break;
      case MainGame2_Chapter4_WaitOff66:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_WaitOff66;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_Chapter4_WaitOn66;
         }
         break;
      case MainGame2_Chapter4_WaitOn66:
         if(A0 == 0){
            MainGame2_State = MainGame2_Chapter4_WaitOn66;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_Dialogue67;     
         }
         break;
      case MainGame2_Chapter4_Dialogue67:
         MainGame2_State = MainGame2_Chapter4_WaitOff67;
         break;
      case MainGame2_Chapter4_WaitOff67:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_WaitOff67;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_Chapter4_WaitOn67;
         }
         break;
      case MainGame2_Chapter4_WaitOn67:
         if(A0 == 0){
            MainGame2_State = MainGame2_Chapter4_WaitOn67;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_Dialogue68;     
         }
         break;
      case MainGame2_Chapter4_Dialogue68:
         MainGame2_State = MainGame2_Chapter4_WaitOff68;
         break;
      case MainGame2_Chapter4_WaitOff68:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_WaitOff68;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_Chapter4_WaitOn68;
         }
         break;
      case MainGame2_Chapter4_WaitOn68:
         if(A0 == 0){
            MainGame2_State = MainGame2_Chapter4_WaitOn68;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_Dialogue69;     
         }
         break;
      case MainGame2_Chapter4_Dialogue69:
         MainGame2_State = MainGame2_Chapter4_WaitOff69;
         break;
      case MainGame2_Chapter4_WaitOff69:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_WaitOff69;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_Chapter4_WaitOn69;
         }
         break;
      case MainGame2_Chapter4_WaitOn69:
         if(A0 == 0){
            MainGame2_State = MainGame2_Chapter4_WaitOn69;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_Dialogue70;     
         }
         break;
      case MainGame2_Chapter4_Dialogue70:
         MainGame2_State = MainGame2_Chapter4_WaitOff70;
         break;
      case MainGame2_Chapter4_WaitOff70:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_WaitOff70;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_Chapter4_WaitOn70;
         }
         break;
      case MainGame2_Chapter4_WaitOn70:
         if(A0 == 0){
            MainGame2_State = MainGame2_Chapter4_WaitOn70;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_Dialogue71;     
         }
         break;
      case MainGame2_Chapter4_Dialogue71:
         MainGame2_State = MainGame2_Chapter4_WaitOff71;
         break;
      case MainGame2_Chapter4_WaitOff71:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_Chapter4_WaitOff71;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_Chapter4_WaitOn71;
         }
         break;
      case MainGame2_Chapter4_WaitOn71:
         if(A4 == 0 && A5 == 0 && A6 == 0 && A7 == 0){
            MainGame2_State = MainGame2_Chapter4_WaitOn71;            
         }
         else if(A4 == 1 && A5 == 0 && A6 == 0 && A7 == 0){
            B3 = B4 = B5 = B6 = B7 = 1; //chapter 5
            MainGame2_State = MainGame2_JeffRoute_Dialogue0;            
         }
         else if(A4 == 0 && A5 == 1 && A6 == 0 && A7 == 0){
            B3 = B4 = B5 = B6 = B7 = 1; //chapter 5
            MainGame2_State = MainGame2_BrianRoute_Dialogue0;            
         }
         else if(A4 == 0 && A5 == 0 && A6 == 1 && A7 == 0){
            B3 = B4 = B5 = B6 = B7 = 1; //chapter 5
            MainGame2_State = MainGame2_FrankRoute_Dialogue0;            
         }
         else if(A4 == 0 && A5 == 0 && A6 == 0 && A7 == 1){
            B3 = B4 = B5 = B6 = B7 = 1; //chapter 5
            MainGame2_State = MainGame2_ElenaRoute_Dialogue0;            
         }
         break;
      case MainGame2_JeffRoute_Dialogue0:
         MainGame2_State = MainGame2_JeffRoute_WaitOff0;
         break;
      case MainGame2_JeffRoute_WaitOff0:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_WaitOff0;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_JeffRoute_WaitOn0;
         }
         break;
      case MainGame2_JeffRoute_WaitOn0:
         if(A0 == 0){
            MainGame2_State = MainGame2_JeffRoute_WaitOn0;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_Dialogue1;     
         }
         break;
      case MainGame2_JeffRoute_Dialogue1:
         MainGame2_State = MainGame2_JeffRoute_WaitOff1;
         break;
      case MainGame2_JeffRoute_WaitOff1:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_WaitOff1;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_JeffRoute_WaitOn1;
         }
         break;
      case MainGame2_JeffRoute_WaitOn1:
         if(A0 == 0){
            MainGame2_State = MainGame2_JeffRoute_WaitOn1;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_Dialogue2;     
         }
         break;
      case MainGame2_JeffRoute_Dialogue2:
         MainGame2_State = MainGame2_JeffRoute_WaitOff2;
         break;
      case MainGame2_JeffRoute_WaitOff2:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_WaitOff2;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_JeffRoute_WaitOn2;
         }
         break;
      case MainGame2_JeffRoute_WaitOn2:
         if(A0 == 0){
            MainGame2_State = MainGame2_JeffRoute_WaitOn2;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_Dialogue3;     
         }
         break;
      case MainGame2_JeffRoute_Dialogue3:
         MainGame2_State = MainGame2_JeffRoute_WaitOff3;
         break;
      case MainGame2_JeffRoute_WaitOff3:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_WaitOff3;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_JeffRoute_WaitOn3;
         }
         break;
      case MainGame2_JeffRoute_WaitOn3:
         if(A0 == 0){
            MainGame2_State = MainGame2_JeffRoute_WaitOn3;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_Dialogue4;     
         }
         break;
      case MainGame2_JeffRoute_Dialogue4:
         MainGame2_State = MainGame2_JeffRoute_WaitOff4;
         break;
      case MainGame2_JeffRoute_WaitOff4:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_WaitOff4;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_JeffRoute_WaitOn4;
         }
         break;
      case MainGame2_JeffRoute_WaitOn4:
         if(A0 == 0){
            MainGame2_State = MainGame2_JeffRoute_WaitOn4;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_Dialogue5;     
         }
         break;
      case MainGame2_JeffRoute_Dialogue5:
         MainGame2_State = MainGame2_JeffRoute_WaitOff5;
         break;
      case MainGame2_JeffRoute_WaitOff5:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_WaitOff5;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_JeffRoute_WaitOn5;
         }
         break;
      case MainGame2_JeffRoute_WaitOn5:
         if(A0 == 0){
            MainGame2_State = MainGame2_JeffRoute_WaitOn5;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_Dialogue6;     
         }
         break;
      case MainGame2_JeffRoute_Dialogue6:
         MainGame2_State = MainGame2_JeffRoute_WaitOff6;
         break;
      case MainGame2_JeffRoute_WaitOff6:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_WaitOff6;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_JeffRoute_WaitOn6;
         }
         break;
      case MainGame2_JeffRoute_WaitOn6:
         if(A0 == 0){
            MainGame2_State = MainGame2_JeffRoute_WaitOn6;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_Dialogue7;     
         }
         break;
      case MainGame2_JeffRoute_Dialogue7:
         MainGame2_State = MainGame2_JeffRoute_WaitOff7;
         break;
      case MainGame2_JeffRoute_WaitOff7:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_WaitOff7;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_JeffRoute_WaitOn7;
         }
         break;
      case MainGame2_JeffRoute_WaitOn7:
         if(A0 == 0){
            MainGame2_State = MainGame2_JeffRoute_WaitOn7;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_Dialogue8;     
         }
         break;
      case MainGame2_JeffRoute_Dialogue8:
         MainGame2_State = MainGame2_JeffRoute_WaitOff8;
         break;
      case MainGame2_JeffRoute_WaitOff8:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_WaitOff8;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_JeffRoute_WaitOn8;
         }
         break;
      case MainGame2_JeffRoute_WaitOn8:
         if(A0 == 0){
            MainGame2_State = MainGame2_JeffRoute_WaitOn8;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_Dialogue9;     
         }
         break;
      case MainGame2_JeffRoute_Dialogue9:
         MainGame2_State = MainGame2_JeffRoute_WaitOff9;
         break;
      case MainGame2_JeffRoute_WaitOff9:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_WaitOff9;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_JeffRoute_WaitOn9;
         }
         break;
      case MainGame2_JeffRoute_WaitOn9:
         if(A0 == 0){
            MainGame2_State = MainGame2_JeffRoute_WaitOn9;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_Dialogue10;     
         }
         break;
      case MainGame2_JeffRoute_Dialogue10:
         MainGame2_State = MainGame2_JeffRoute_WaitOff10;
         break;
      case MainGame2_JeffRoute_WaitOff10:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_JeffRoute_WaitOff10;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_JeffRoute_WaitOn10;
         }
         break;
      case MainGame2_JeffRoute_WaitOn10:
         if(A0 == 0){
            MainGame2_State = MainGame2_JeffRoute_WaitOn10;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_EndScreen;     
         }
         break;
      case MainGame2_BrianRoute_Dialogue0:
         MainGame2_State = MainGame2_BrianRoute_WaitOff0;
         break;
      case MainGame2_BrianRoute_WaitOff0:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_WaitOff0;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_BrianRoute_WaitOn0;
         }
         break;
      case MainGame2_BrianRoute_WaitOn0:
         if(A0 == 0){
            MainGame2_State = MainGame2_BrianRoute_WaitOn0;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_Dialogue1;     
         }
         break;
      case MainGame2_BrianRoute_Dialogue1:
         MainGame2_State = MainGame2_BrianRoute_WaitOff1;
         break;
      case MainGame2_BrianRoute_WaitOff1:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_WaitOff1;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_BrianRoute_WaitOn1;
         }
         break;
      case MainGame2_BrianRoute_WaitOn1:
         if(A0 == 0){
            MainGame2_State = MainGame2_BrianRoute_WaitOn1;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_Dialogue2;     
         }
         break;
      case MainGame2_BrianRoute_Dialogue2:
         MainGame2_State = MainGame2_BrianRoute_WaitOff2;
         break;
      case MainGame2_BrianRoute_WaitOff2:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_WaitOff2;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_BrianRoute_WaitOn2;
         }
         break;
      case MainGame2_BrianRoute_WaitOn2:
         if(A0 == 0){
            MainGame2_State = MainGame2_BrianRoute_WaitOn2;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_Dialogue3;     
         }
         break;
      case MainGame2_BrianRoute_Dialogue3:
         MainGame2_State = MainGame2_BrianRoute_WaitOff3;
         break;
      case MainGame2_BrianRoute_WaitOff3:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_WaitOff3;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_BrianRoute_WaitOn3;
         }
         break;
      case MainGame2_BrianRoute_WaitOn3:
         if(A0 == 0){
            MainGame2_State = MainGame2_BrianRoute_WaitOn3;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_Dialogue4;     
         }
         break;
      case MainGame2_BrianRoute_Dialogue4:
         MainGame2_State = MainGame2_BrianRoute_WaitOff4;
         break;
      case MainGame2_BrianRoute_WaitOff4:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_WaitOff4;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_BrianRoute_WaitOn4;
         }
         break;
      case MainGame2_BrianRoute_WaitOn4:
         if(A0 == 0){
            MainGame2_State = MainGame2_BrianRoute_WaitOn4;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_Dialogue5;     
         }
         break;
      case MainGame2_BrianRoute_Dialogue5:
         MainGame2_State = MainGame2_BrianRoute_WaitOff5;
         break;
      case MainGame2_BrianRoute_WaitOff5:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_WaitOff5;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_BrianRoute_WaitOn5;
         }
         break;
      case MainGame2_BrianRoute_WaitOn5:
         if(A0 == 0){
            MainGame2_State = MainGame2_BrianRoute_WaitOn5;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_Dialogue6;     
         }
         break;
      case MainGame2_BrianRoute_Dialogue6:
         MainGame2_State = MainGame2_BrianRoute_WaitOff6;
         break;
      case MainGame2_BrianRoute_WaitOff6:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_WaitOff6;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_BrianRoute_WaitOn6;
         }
         break;
      case MainGame2_BrianRoute_WaitOn6:
         if(A0 == 0){
            MainGame2_State = MainGame2_BrianRoute_WaitOn6;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_Dialogue7;     
         }
         break;
      case MainGame2_BrianRoute_Dialogue7:
         MainGame2_State = MainGame2_BrianRoute_WaitOff7;
         break;
      case MainGame2_BrianRoute_WaitOff7:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_WaitOff7;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_BrianRoute_WaitOn7;
         }
         break;
      case MainGame2_BrianRoute_WaitOn7:
         if(A0 == 0){
            MainGame2_State = MainGame2_BrianRoute_WaitOn7;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_Dialogue8;     
         }
         break;
      case MainGame2_BrianRoute_Dialogue8:
         MainGame2_State = MainGame2_BrianRoute_WaitOff8;
         break;
      case MainGame2_BrianRoute_WaitOff8:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_WaitOff8;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_BrianRoute_WaitOn8;
         }
         break;
      case MainGame2_BrianRoute_WaitOn8:
         if(A0 == 0){
            MainGame2_State = MainGame2_BrianRoute_WaitOn8;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_Dialogue9;     
         }
         break;
      case MainGame2_BrianRoute_Dialogue9:
         MainGame2_State = MainGame2_BrianRoute_WaitOff9;
         break;
      case MainGame2_BrianRoute_WaitOff9:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_WaitOff9;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_BrianRoute_WaitOn9;
         }
         break;
      case MainGame2_BrianRoute_WaitOn9:
         if(A0 == 0){
            MainGame2_State = MainGame2_BrianRoute_WaitOn9;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_Dialogue10;     
         }
         break;
      case MainGame2_BrianRoute_Dialogue10:
         MainGame2_State = MainGame2_BrianRoute_WaitOff10;
         break;
      case MainGame2_BrianRoute_WaitOff10:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_BrianRoute_WaitOff10;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_BrianRoute_WaitOn10;
         }
         break;
      case MainGame2_BrianRoute_WaitOn10:
         if(A0 == 0){
            MainGame2_State = MainGame2_BrianRoute_WaitOn10;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_EndScreen;     
         }
         break;
      case MainGame2_FrankRoute_Dialogue0:
         MainGame2_State = MainGame2_FrankRoute_WaitOff0;
         break;
      case MainGame2_FrankRoute_WaitOff0:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_WaitOff0;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_FrankRoute_WaitOn0;
         }
         break;
      case MainGame2_FrankRoute_WaitOn0:
         if(A0 == 0){
            MainGame2_State = MainGame2_FrankRoute_WaitOn0;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_Dialogue1;     
         }
         break;
      case MainGame2_FrankRoute_Dialogue1:
         MainGame2_State = MainGame2_FrankRoute_WaitOff1;
         break;
      case MainGame2_FrankRoute_WaitOff1:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_WaitOff1;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_FrankRoute_WaitOn1;
         }
         break;
      case MainGame2_FrankRoute_WaitOn1:
         if(A0 == 0){
            MainGame2_State = MainGame2_FrankRoute_WaitOn1;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_Dialogue2;     
         }
         break;
      case MainGame2_FrankRoute_Dialogue2:
         MainGame2_State = MainGame2_FrankRoute_WaitOff2;
         break;
      case MainGame2_FrankRoute_WaitOff2:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_WaitOff2;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_FrankRoute_WaitOn2;
         }
         break;
      case MainGame2_FrankRoute_WaitOn2:
         if(A0 == 0){
            MainGame2_State = MainGame2_FrankRoute_WaitOn2;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_Dialogue3;     
         }
         break;
      case MainGame2_FrankRoute_Dialogue3:
         MainGame2_State = MainGame2_FrankRoute_WaitOff3;
         break;
      case MainGame2_FrankRoute_WaitOff3:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_WaitOff3;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_FrankRoute_WaitOn3;
         }
         break;
      case MainGame2_FrankRoute_WaitOn3:
         if(A0 == 0){
            MainGame2_State = MainGame2_FrankRoute_WaitOn3;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_Dialogue4;     
         }
         break;
      case MainGame2_FrankRoute_Dialogue4:
         MainGame2_State = MainGame2_FrankRoute_WaitOff4;
         break;
      case MainGame2_FrankRoute_WaitOff4:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_WaitOff4;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_FrankRoute_WaitOn4;
         }
         break;
      case MainGame2_FrankRoute_WaitOn4:
         if(A0 == 0){
            MainGame2_State = MainGame2_FrankRoute_WaitOn4;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_Dialogue5;     
         }
         break;
      case MainGame2_FrankRoute_Dialogue5:
         MainGame2_State = MainGame2_FrankRoute_WaitOff5;
         break;
      case MainGame2_FrankRoute_WaitOff5:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_WaitOff5;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_FrankRoute_WaitOn5;
         }
         break;
      case MainGame2_FrankRoute_WaitOn5:
         if(A0 == 0){
            MainGame2_State = MainGame2_FrankRoute_WaitOn5;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_Dialogue6;     
         }
         break;
      case MainGame2_FrankRoute_Dialogue6:
         MainGame2_State = MainGame2_FrankRoute_WaitOff6;
         break;
      case MainGame2_FrankRoute_WaitOff6:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_WaitOff6;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_FrankRoute_WaitOn6;
         }
         break;
      case MainGame2_FrankRoute_WaitOn6:
         if(A0 == 0){
            MainGame2_State = MainGame2_FrankRoute_WaitOn6;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_Dialogue7;     
         }
         break;
      case MainGame2_FrankRoute_Dialogue7:
         MainGame2_State = MainGame2_FrankRoute_WaitOff7;
         break;
      case MainGame2_FrankRoute_WaitOff7:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_WaitOff7;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_FrankRoute_WaitOn7;
         }
         break;
      case MainGame2_FrankRoute_WaitOn7:
         if(A0 == 0){
            MainGame2_State = MainGame2_FrankRoute_WaitOn7;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_Dialogue8;     
         }
         break;
      case MainGame2_FrankRoute_Dialogue8:
         MainGame2_State = MainGame2_FrankRoute_WaitOff8;
         break;
      case MainGame2_FrankRoute_WaitOff8:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_WaitOff8;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_FrankRoute_WaitOn8;
         }
         break;
      case MainGame2_FrankRoute_WaitOn8:
         if(A0 == 0){
            MainGame2_State = MainGame2_FrankRoute_WaitOn8;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_Dialogue9;     
         }
         break;
      case MainGame2_FrankRoute_Dialogue9:
         MainGame2_State = MainGame2_FrankRoute_WaitOff9;
         break;
      case MainGame2_FrankRoute_WaitOff9:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_WaitOff9;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_FrankRoute_WaitOn9;
         }
         break;
      case MainGame2_FrankRoute_WaitOn9:
         if(A0 == 0){
            MainGame2_State = MainGame2_FrankRoute_WaitOn9;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_Dialogue10;     
         }
         break;
      case MainGame2_FrankRoute_Dialogue10:
         MainGame2_State = MainGame2_FrankRoute_WaitOff10;
         break;
      case MainGame2_FrankRoute_WaitOff10:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_FrankRoute_WaitOff10;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_FrankRoute_WaitOn10;
         }
         break;
      case MainGame2_FrankRoute_WaitOn10:
         if(A0 == 0){
            MainGame2_State = MainGame2_FrankRoute_WaitOn10;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_EndScreen;     
         }
         break;
      case MainGame2_ElenaRoute_Dialogue0:
         MainGame2_State = MainGame2_ElenaRoute_WaitOff0;
         break;
      case MainGame2_ElenaRoute_WaitOff0:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_WaitOff0;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_ElenaRoute_WaitOn0;
         }
         break;
      case MainGame2_ElenaRoute_WaitOn0:
         if(A0 == 0){
            MainGame2_State = MainGame2_ElenaRoute_WaitOn0;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_Dialogue1;     
         }
         break;
      case MainGame2_ElenaRoute_Dialogue1:
         MainGame2_State = MainGame2_ElenaRoute_WaitOff1;
         break;
      case MainGame2_ElenaRoute_WaitOff1:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_WaitOff1;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_ElenaRoute_WaitOn1;
         }
         break;
      case MainGame2_ElenaRoute_WaitOn1:
         if(A0 == 0){
            MainGame2_State = MainGame2_ElenaRoute_WaitOn1;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_Dialogue2;     
         }
         break;
      case MainGame2_ElenaRoute_Dialogue2:
         MainGame2_State = MainGame2_ElenaRoute_WaitOff2;
         break;
      case MainGame2_ElenaRoute_WaitOff2:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_WaitOff2;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_ElenaRoute_WaitOn2;
         }
         break;
      case MainGame2_ElenaRoute_WaitOn2:
         if(A0 == 0){
            MainGame2_State = MainGame2_ElenaRoute_WaitOn2;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_Dialogue3;     
         }
         break;
      case MainGame2_ElenaRoute_Dialogue3:
         MainGame2_State = MainGame2_ElenaRoute_WaitOff3;
         break;
      case MainGame2_ElenaRoute_WaitOff3:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_WaitOff3;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_ElenaRoute_WaitOn3;
         }
         break;
      case MainGame2_ElenaRoute_WaitOn3:
         if(A0 == 0){
            MainGame2_State = MainGame2_ElenaRoute_WaitOn3;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_Dialogue4;     
         }
         break;
      case MainGame2_ElenaRoute_Dialogue4:
         MainGame2_State = MainGame2_ElenaRoute_WaitOff4;
         break;
      case MainGame2_ElenaRoute_WaitOff4:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_WaitOff4;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_ElenaRoute_WaitOn4;
         }
         break;
      case MainGame2_ElenaRoute_WaitOn4:
         if(A0 == 0){
            MainGame2_State = MainGame2_ElenaRoute_WaitOn4;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_Dialogue5;     
         }
         break;
      case MainGame2_ElenaRoute_Dialogue5:
         MainGame2_State = MainGame2_ElenaRoute_WaitOff5;
         break;
      case MainGame2_ElenaRoute_WaitOff5:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_WaitOff5;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_ElenaRoute_WaitOn5;
         }
         break;
      case MainGame2_ElenaRoute_WaitOn5:
         if(A0 == 0){
            MainGame2_State = MainGame2_ElenaRoute_WaitOn5;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_Dialogue6;     
         }
         break;
      case MainGame2_ElenaRoute_Dialogue6:
         MainGame2_State = MainGame2_ElenaRoute_WaitOff6;
         break;
      case MainGame2_ElenaRoute_WaitOff6:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_WaitOff6;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_ElenaRoute_WaitOn6;
         }
         break;
      case MainGame2_ElenaRoute_WaitOn6:
         if(A0 == 0){
            MainGame2_State = MainGame2_ElenaRoute_WaitOn6;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_Dialogue7;     
         }
         break;
      case MainGame2_ElenaRoute_Dialogue7:
         MainGame2_State = MainGame2_ElenaRoute_WaitOff7;
         break;
      case MainGame2_ElenaRoute_WaitOff7:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_WaitOff7;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_ElenaRoute_WaitOn7;
         }
         break;
      case MainGame2_ElenaRoute_WaitOn7:
         if(A0 == 0){
            MainGame2_State = MainGame2_ElenaRoute_WaitOn7;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_Dialogue8;     
         }
         break;
      case MainGame2_ElenaRoute_Dialogue8:
         MainGame2_State = MainGame2_ElenaRoute_WaitOff8;
         break;
      case MainGame2_ElenaRoute_WaitOff8:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_WaitOff8;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_ElenaRoute_WaitOn8;
         }
         break;
      case MainGame2_ElenaRoute_WaitOn8:
         if(A0 == 0){
            MainGame2_State = MainGame2_ElenaRoute_WaitOn8;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_Dialogue9;     
         }
         break;
      case MainGame2_ElenaRoute_Dialogue9:
         MainGame2_State = MainGame2_ElenaRoute_WaitOff9;
         break;
      case MainGame2_ElenaRoute_WaitOff9:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_WaitOff9;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_ElenaRoute_WaitOn9;
         }
         break;
      case MainGame2_ElenaRoute_WaitOn9:
         if(A0 == 0){
            MainGame2_State = MainGame2_ElenaRoute_WaitOn9;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_Dialogue10;     
         }
         break;
      case MainGame2_ElenaRoute_Dialogue10:
         MainGame2_State = MainGame2_ElenaRoute_WaitOff10;
         break;
      case MainGame2_ElenaRoute_WaitOff10:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_ElenaRoute_WaitOff10;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_ElenaRoute_WaitOn10;
         }
         break;
      case MainGame2_ElenaRoute_WaitOn10:
         if(A0 == 0){
            MainGame2_State = MainGame2_ElenaRoute_WaitOn10;            
         }
         else if(A0 == 1){
            MainGame2_State = MainGame2_EndScreen;     
         }
         break;
      case MainGame2_EndScreen:
         MainGame2_State = MainGame2_EndScreen_WaitOff;
         break;
      case MainGame2_EndScreen_WaitOff:
         //display_lives = 0;
         if(A0 == 1){
            MainGame2_State = MainGame2_EndScreen_WaitOff;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame2_State = MainGame2_EndScreen_WaitOn;
         }
         break;
      case MainGame2_EndScreen_WaitOn:
         if(A0 == 0){
            MainGame2_State = MainGame2_EndScreen_WaitOn;            
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter4_Dialogue58;
            MainGame2_State = MainGame2_Init;     
         }
         break;

      default:
         break;
   } //debug by having temporary starting position
   
   switch(MainGame2_State){ //State actions
      case MainGame2_Init:
         break;
      case MainGame2_Chapter4_Dialogue59:
         printf("\n\n");
         //printf("Successfully broke INPUT BUFFER limit!! :D\n"); //comment later
         printf("You opened your heart and listened to everyone's fallen hopes and dreams. You felt them and share with them your own fallen hopes and dreams as well.");         
         break;
      case MainGame2_Chapter4_WaitOff59:
         break;
      case MainGame2_Chapter4_WaitOn59:
         break;
      case MainGame2_Chapter4_Dialogue60:
         printf("\n\n");
         printf("And then slowly but surely, even as you struggled within, you converted their fallen hopes and dreams back into the light that they once were.");         
         break;
      case MainGame2_Chapter4_WaitOff60:
         break;
      case MainGame2_Chapter4_WaitOn60:
         break;
      case MainGame2_Chapter4_Dialogue61:
         printf("\n\n");
         printf("And released an explosion of light towards the sky!");         
         break;
      case MainGame2_Chapter4_WaitOff61:
         break;
      case MainGame2_Chapter4_WaitOn61:
         break;
      case MainGame2_Chapter4_Dialogue62:
         printf("\n\n");
         printf("And then snowflakes of light began to fall around you.");         
         break;
      case MainGame2_Chapter4_WaitOff62:
         break;
      case MainGame2_Chapter4_WaitOn62:
         break;
      case MainGame2_Chapter4_Dialogue63:
         printf("\n\n");
         printf("And with that, people started appearing left and right. Many were confused, some bewildered, others lost. Some people asked you what on earth was going on.");         
         break;
      case MainGame2_Chapter4_WaitOff63:
         break;
      case MainGame2_Chapter4_WaitOn63:
         break;
      case MainGame2_Chapter4_Dialogue64:
         printf("\n\n");
         printf("Asriel: \"You were all asleep for a while but now you're awake :)\"");         
         break;
      case MainGame2_Chapter4_WaitOff64:
         break;
      case MainGame2_Chapter4_WaitOn64:
         break;
      case MainGame2_Chapter4_Dialogue65:
         printf("\n\n");
         printf("The CS gang was amazed, although since you were all exhausted, you were still sitting on the ground panting.");         
         break;
      case MainGame2_Chapter4_WaitOff65:
         break;
      case MainGame2_Chapter4_WaitOn65:
         break;
      case MainGame2_Chapter4_Dialogue66:
         printf("\n\n");
         printf("Elena: \"Finally... We're free to go back.\"");         
         break;
      case MainGame2_Chapter4_WaitOff66:
         break;
      case MainGame2_Chapter4_WaitOn66:
         break;
      case MainGame2_Chapter4_Dialogue67:
         printf("\n\n");
         printf("As if on cue, all 5 of you, along with the millions of people who were rematerializing, were teleporting by the handful back into the real world.");         
         break;
      case MainGame2_Chapter4_WaitOff67:
         break;
      case MainGame2_Chapter4_WaitOn67:
         break;
      case MainGame2_Chapter4_Dialogue68:
         printf("\n\n");
         printf("Many weeks have passed since the incident. After coming back from the shadow realm, it took a while to adjust to the fact that back in the real world, you couldn't use magic unlike in video games... and in the shadow realm. You also decided that everyone ought to readjust to normal life before confessing your feelings to one of the girls.");         
         break;
      case MainGame2_Chapter4_WaitOff68:
         break;
      case MainGame2_Chapter4_WaitOn68:
         break;
      case MainGame2_Chapter4_Dialogue69:
         printf("\n\n");
         printf("Now you felt that it was the right time to ask. The truth was, you already knew in your heart who you wanted to go out with. Now it was only a matter of time before you let your feelings be known to the girl of your dreams.");         
         break;
      case MainGame2_Chapter4_WaitOff69:
         break;
      case MainGame2_Chapter4_WaitOn69:
         break;
      case MainGame2_Chapter4_Dialogue70:
         printf("\n\n");
         printf("Asriel: (The girl I want to ask out is...)");         
         break;
      case MainGame2_Chapter4_WaitOff70:
         break;
      case MainGame2_Chapter4_WaitOn70:
         break;
      case MainGame2_Chapter4_Dialogue71:
         printf("\n\n");
         printf("A4 - Jeff\n");  
         printf("A5 - Brian\n"); 
         printf("A6 - Frank\n"); 
         printf("A7 - Elena\n");    
         break;
      case MainGame2_Chapter4_WaitOff71:
         break;
      case MainGame2_Chapter4_WaitOn71:
         break;
      case MainGame2_JeffRoute_Dialogue0:
         printf("\n\n");
         printf("Jeff Route begin! :D \n\n");  
         
         printf("Jeff: \"Hey babe. I really appreciate you for always being there for me. I hope we can make a lot of memories together.\"");  
         break;
      case MainGame2_JeffRoute_WaitOff0:
         break;
      case MainGame2_JeffRoute_WaitOn0:
         break;
      case MainGame2_BrianRoute_Dialogue0:
         printf("\n\n");
         printf("Brian Route begin! :D \n\n");  
         
         printf("Brian was cuddling against you as you were waiting in line entering the Sydney Opera House.");  
         break;
      case MainGame2_BrianRoute_WaitOff0:
         break;
      case MainGame2_BrianRoute_WaitOn0:
         break;
      case MainGame2_FrankRoute_Dialogue0:
         printf("\n\n");
         printf("Frank Route begin! :D \n\n");  
         
         printf("Frank laid her head on your shoulder as she was updating zyBooks. You were both seated on a chair with your feet up while on a cruise ship through the Caribbean.");  
         break;
      case MainGame2_FrankRoute_WaitOff0:
         break;
      case MainGame2_FrankRoute_WaitOn0:
         break;
      case MainGame2_ElenaRoute_Dialogue0:
         printf("\n\n");
         printf("Elena Route begin! :D \n\n");  
         
         printf("Elena: \"Idiot! I don't even know why I fell in love with you!\"\n");  
         printf("She says this as you were throwing snowballs at each other. Since you were in Ukraine, it was the perfect time to relax and let loose.");  
         break;
      case MainGame2_ElenaRoute_WaitOff0:
         break;
      case MainGame2_ElenaRoute_WaitOn0:
         break;
      case MainGame2_JeffRoute_Dialogue1:
         printf("\n\n");
         printf("Asriel: \"I'll always be there for you Jeffrey McDaniel. I'll make you the happiest girl alive I promise. :)\"");  
         break;
      case MainGame2_JeffRoute_WaitOff1:
         break;
      case MainGame2_JeffRoute_WaitOn1:
         break;
      case MainGame2_JeffRoute_Dialogue2:
         printf("\n\n");
         printf("You say this as you're riding roadsters in the middle of Death Valley. Where you can run wild and free in your vehicles and share many intimate moments where no one was watching.");  
         break;
      case MainGame2_JeffRoute_WaitOff2:
         break;
      case MainGame2_JeffRoute_WaitOn2:
         break;
     case MainGame2_JeffRoute_Dialogue3:
         printf("\n\n");
         printf("Jeff: \"It's so hot outside because we're out in the Nevadan desert.\"");  
         break;
      case MainGame2_JeffRoute_WaitOff3:
         break;
      case MainGame2_JeffRoute_WaitOn3:
         break;
      case MainGame2_JeffRoute_Dialogue4:
         printf("\n\n");
         printf("Jeff: \"It's guess you can say we're on hot wheels :p\"");  
         break;
      case MainGame2_JeffRoute_WaitOff4:
         break;
      case MainGame2_JeffRoute_WaitOn4:
         break;
      case MainGame2_JeffRoute_Dialogue5:
         printf("\n\n");
         printf("Her humor was so bad but you couldn't help but laugh because you loved her so much, it didn't matter what she said at all.");  
         break;
      case MainGame2_JeffRoute_WaitOff5:
         break;
      case MainGame2_JeffRoute_WaitOn5:
         break;
      case MainGame2_JeffRoute_Dialogue6:
         printf("\n\n");
         printf("Jeff: \"Hey Asriel?\"");  
         break;
      case MainGame2_JeffRoute_WaitOff6:
         break;
      case MainGame2_JeffRoute_WaitOn6:
         break;
      case MainGame2_JeffRoute_Dialogue7:
         printf("\n\n");
         printf("Asriel: \"Yeah?\"");  
         break;
      case MainGame2_JeffRoute_WaitOff7:
         break;
      case MainGame2_JeffRoute_WaitOn7:
         break;
      case MainGame2_JeffRoute_Dialogue8:
         printf("\n\n");
         printf("Jeff: \"Promise me that no matter what happens in the future, we'll always be there to love and support each other through thick and thin. That we'll be able to travel a lot of places and make many heartfelt memories.\"\n");  
         printf("Jeff says this as she was skidding through the sand trying to put dirt in your eye (Spiderman reference btw lol) but failed miserably since you were a skilled driver."); 
         break;
      case MainGame2_JeffRoute_WaitOff8:
         break;
      case MainGame2_JeffRoute_WaitOn8:
         break;
      case MainGame2_JeffRoute_Dialogue9:
         printf("\n\n");
         printf("Asriel: \"Of course! I'll always be here to love you and I'll be your crying shoulder to lean on if you have any problems in life. \"");  
         break;
      case MainGame2_JeffRoute_WaitOff9:
         break;
      case MainGame2_JeffRoute_WaitOn9:
         break;
      case MainGame2_JeffRoute_Dialogue10:
         printf("\n\n");
         printf("Jeff: \"Aww~\"\n");  
         printf("You and your girlfriend continue talking about life, your hopes and dreams, and of course you geeked out about state machines from cs120b. She always added in a lot of jokes which were super cheesy but you laughed anyways. You hoped to spend many amazing, lovely years with the one and only, Jeffrey McDaniel."); 
         break;
      case MainGame2_JeffRoute_WaitOff10:
         break;
      case MainGame2_JeffRoute_WaitOn10:
         break;
      case MainGame2_BrianRoute_Dialogue1:
         printf("\n\n");
         printf("Brian: \"It's been a while since I've been to the orchestra down under in Sydney. I'm glad that I'm able to spend it with the love of my life for the first time though mate.\"");  
         break;
      case MainGame2_BrianRoute_WaitOff1:
         break;
      case MainGame2_BrianRoute_WaitOn1:
         break;
      case MainGame2_BrianRoute_Dialogue2:
         printf("\n\n");
         printf("Asriel: \"Of course hehe. And who would put me in the right place for asking dumb questions other than you?\"");  
         break;
      case MainGame2_BrianRoute_WaitOff2:
         break;
      case MainGame2_BrianRoute_WaitOn2:
         break;
      case MainGame2_BrianRoute_Dialogue3:
         printf("\n\n");
         printf("Brian: \"God save the queen of course. I always secretly enjoyed yelling at you for asking simple things like what's a for loop in cs10.\"");  
         break;
      case MainGame2_BrianRoute_WaitOff3:
         break;
      case MainGame2_BrianRoute_WaitOn3:
         break;
      case MainGame2_BrianRoute_Dialogue4:
         printf("\n\n");
         printf("Asriel: \"You're like the Australian version of Gordon Ramsay lol\"");  
         break;
      case MainGame2_BrianRoute_WaitOff4:
         break;
      case MainGame2_BrianRoute_WaitOn4:
         break;
      case MainGame2_BrianRoute_Dialogue5:
         printf("\n\n");
         printf("Brian sighed but she knew very well that she enjoyed your cheesy humor. After waiting for a few more minutes, you were inside the orchestra listening to some calm, authentic music.");  
         break;
      case MainGame2_BrianRoute_WaitOff5:
         break;
      case MainGame2_BrianRoute_WaitOn5:
         break;
      case MainGame2_BrianRoute_Dialogue6:
         printf("\n\n");
         printf("Brian: \"We should go to the Philippines after this btw. I love the nature there and there's also Koalas in some provinces.\"");  
         break;
      case MainGame2_BrianRoute_WaitOff6:
         break;
      case MainGame2_BrianRoute_WaitOn6:
         break;
      case MainGame2_BrianRoute_Dialogue7:
         printf("\n\n");
         printf("You smiled at her.");  
         break;
      case MainGame2_BrianRoute_WaitOff7:
         break;
      case MainGame2_BrianRoute_WaitOn7:
         break;
      case MainGame2_BrianRoute_Dialogue8:
         printf("\n\n");
         printf("Asriel: \"I promise we'll travel there and a bunch of places. As long as it's with you, I'll make you the happiest girl alive and take you wherever you want to go.\"");  
         break;
      case MainGame2_BrianRoute_WaitOff8:
         break;
      case MainGame2_BrianRoute_WaitOn8:
         break;
      case MainGame2_BrianRoute_Dialogue9:
         printf("\n\n");
         printf("Brian wasn't really expressive when it came to words of affirmation but she did show her love through acts of service.. and harsh reprimands. And that was more than enough for you for she was the best thing that ever happened in your life.");  
         break;
      case MainGame2_BrianRoute_WaitOff9:
         break;
      case MainGame2_BrianRoute_WaitOn9:
         break;
      case MainGame2_BrianRoute_Dialogue10:
         printf("\n\n");
         printf("And as you continued listening to the orchestra, Brian leaned against your shoulder and she held your hand. Together, you were forming many new memories through love of music and travel and you hoped that there would be many more years of happy memories to come, no matter what the ups and downs may be.");  
         break;
      case MainGame2_BrianRoute_WaitOff10:
         break;
      case MainGame2_BrianRoute_WaitOn10:
         break;
      case MainGame2_FrankRoute_Dialogue1:
         printf("\n\n");
         printf("Your girlfriend was in a Zoom meeting.\n"); 
         printf("Frank: \"Okay gang! :D Today I'm proud to announce that I will be launching a global version of zyBooks that will be used and loved by many people around the world. With the help of my old friend and my boyfriend, we were able to successfully launch to over 120 countries all over the world!\"");  
         break;
      case MainGame2_FrankRoute_WaitOff1:
         break;
      case MainGame2_FrankRoute_WaitOn1:
         break;
      case MainGame2_FrankRoute_Dialogue2:
         printf("\n\n");
         printf("Asriel: \"Congrats Coconut! :)\"");  
         break;
      case MainGame2_FrankRoute_WaitOff2:
         break;
      case MainGame2_FrankRoute_WaitOn2:
         break;
      case MainGame2_FrankRoute_Dialogue3:
         printf("\n\n");
         printf("You gave each other cute and unique labels from fruits. Wait is coconut a fruit?");  
         break;
      case MainGame2_FrankRoute_WaitOff3:
         break;
      case MainGame2_FrankRoute_WaitOn3:
         break;
      case MainGame2_FrankRoute_Dialogue4:
         printf("\n\n");
         printf("Frank: \"Thanks Kiwi! :D\"");  
         break;
      case MainGame2_FrankRoute_WaitOff4:
         break;
      case MainGame2_FrankRoute_WaitOn4:
         break;
      case MainGame2_FrankRoute_Dialogue5:
         printf("\n\n");
         printf("You felt the ocean breeze as the cruise ship was travelling and inhaled the fresh sea salt. Life felt good being with the girl of your dreams and you felt grateful that she shared a passion that she cared so deeply about with you and that you were very involved with it.");  
         break;
      case MainGame2_FrankRoute_WaitOff5:
         break;
      case MainGame2_FrankRoute_WaitOn5:
         break;
      case MainGame2_FrankRoute_Dialogue6:
         printf("\n\n");
         printf("Frank: \"Btw Kiwi, I have a surprise for you! ;D\"");  
         break;
      case MainGame2_FrankRoute_WaitOff6:
         break;
      case MainGame2_FrankRoute_WaitOn6:
         break;
      case MainGame2_FrankRoute_Dialogue7:
         printf("\n\n");
         printf("Asriel: \"Oho? What is it? :o\"");  
         break;
      case MainGame2_FrankRoute_WaitOff7:
         break;
      case MainGame2_FrankRoute_WaitOn7:
         break;
      case MainGame2_FrankRoute_Dialogue8:
         printf("\n\n");
         printf("Frank: \"I made you a robot dog with the power to identify objects via KNN algorithm! :D\"");  
         break;
      case MainGame2_FrankRoute_WaitOff8:
         break;
      case MainGame2_FrankRoute_WaitOn8:
         break;
      case MainGame2_FrankRoute_Dialogue9:
         printf("\n\n");
         printf("Asriel: \"Aww~ that's sweet of you. Thank you Coconut!\"");  
         break;
      case MainGame2_FrankRoute_WaitOff9:
         break;
      case MainGame2_FrankRoute_WaitOn9:
         break;
      case MainGame2_FrankRoute_Dialogue10:
         printf("\n\n");
         printf("Your new robot dog ran towards you and you decided to pet and cuddle it. Frank did the same thing as well. It also had the ability to fly like Goddard from Jimmy Neutron which was pretty epic actually. Overall, you were grateful that you were able to spend lots of time with your amazing, ambitious girlfriend. You looked forward to spending more time with her and building a brighter future together.");  
         break;
      case MainGame2_FrankRoute_WaitOff10:
         break;
      case MainGame2_FrankRoute_WaitOn10:
         break;
      case MainGame2_ElenaRoute_Dialogue1:
         printf("\n\n");
         printf("Asriel: \"Guess we're breaking up?\"\n");
         printf("You say this jokingly of course and Elena laughed.");
         break;
       case MainGame2_ElenaRoute_WaitOff1:
         break;
      case MainGame2_ElenaRoute_WaitOn1:
         break;
      case MainGame2_ElenaRoute_Dialogue2:
         printf("\n\n");
         printf("Elena: \"You're stuck with me for the rest of your life!\"\n");
         printf("She threw an even larger snowball at you and you were hit point blank. Ouch.");
         break;
      case MainGame2_ElenaRoute_WaitOff2:
         break;
      case MainGame2_ElenaRoute_WaitOn2:
         break;
      case MainGame2_ElenaRoute_Dialogue3:
         printf("\n\n");
         printf("Asriel: \"Hey no fair I wasn't concentrating!\"\n");
         printf("Elena laughed before putting yet another tsundere front.");
         break;
      case MainGame2_ElenaRoute_WaitOff3:
         break;
      case MainGame2_ElenaRoute_WaitOn3:
         break;
      case MainGame2_ElenaRoute_Dialogue4:
         printf("\n\n");
         printf("Elena: \"Btw, I hacked into a tank using RSA decryption. Wanna test fire a tank in the middle of the snowy forest?\"");
         break;
      case MainGame2_ElenaRoute_WaitOff4:
         break;
      case MainGame2_ElenaRoute_WaitOn4:
         break;
      case MainGame2_ElenaRoute_Dialogue5:
         printf("\n\n");
         printf("Asriel: \"You did what now?! :o\"");
         break;
      case MainGame2_ElenaRoute_WaitOff5:
         break;
      case MainGame2_ElenaRoute_WaitOn5:
         break;
      case MainGame2_ElenaRoute_Dialogue6:
         printf("\n\n");
         printf("Elena: \"Cmon! I know you want to try it. You're very bad at being tsundere btw lol\"");
         break;
      case MainGame2_ElenaRoute_WaitOff6:
         break;
      case MainGame2_ElenaRoute_WaitOn6:
         break;
      case MainGame2_ElenaRoute_Dialogue7:
         printf("\n\n");
         printf("You roll your eyes and laugh. Despite all her banterous remarks, you couldn't help but fall deeper in love with her. It was this side of who she was that made you fall in love with her to begin with. You wanted to cherish these moments and make many more happy memories with her. With that in mind, you followed her to the tank she found.");
         break;
      case MainGame2_ElenaRoute_WaitOff7:
         break;
      case MainGame2_ElenaRoute_WaitOn7:
         break;
      case MainGame2_ElenaRoute_Dialogue8:
         printf("\n\n");
         printf("Elena: \"Ahahahahaha!!\"\n");
         printf("There was a lot of playfully evil laughter in her voice as you both got in the tank. Of course she was the one who fired the shells to all the trees around, causing a loud noise each time the shells hit a tree.");
         break;
      case MainGame2_ElenaRoute_WaitOff8:
         break;
      case MainGame2_ElenaRoute_WaitOn8:
         break;
      case MainGame2_ElenaRoute_Dialogue9:
         printf("\n\n");
         printf("Elena: \"You try now!\"");
         break;
      case MainGame2_ElenaRoute_WaitOff9:
         break;
      case MainGame2_ElenaRoute_WaitOn9:
         break;
      case MainGame2_ElenaRoute_Dialogue10:
         printf("\n\n");
         printf("You fired a bunch of shells while turning the head of the tank rapidly. You were enjoying the chaos and laughed with her as the trees came down from every shot. You hoped to have a bright future with her where she was always in your life, no matter what. Because you knew that whenever you felt weak, she would always be there to lift you up again and support you along the way.");
         break;
      case MainGame2_ElenaRoute_WaitOff10:
         break;
      case MainGame2_ElenaRoute_WaitOn10:
         break;
      case MainGame2_EndScreen:
         printf("\n\nCongratulations! You finished Jeff Dating Sim Part 2! :D I hope you enjoyed this story and if you are single (I am too atm at the time the game was made), I hope you will be able to find someone who you will love and cherish and will love and cherish you back the same way. And if you are already in a relationship, I hope you will be able to make more happy memories together and that you'll find ways to spend time with each other despite the pandemic. Thank you again for playing! ^_^\n\n");
         
         printf("Total score earned after finishing story: %d", score);
         printf("\n\n");
         score = 0;
         lives = 3;
         printf("Press A0 to start over again if you want to reread and/or get a better score :)");
         break;
      case MainGame2_EndScreen_WaitOff:
         break;
      case MainGame2_EndScreen_WaitOn:
         break;
      default:
         break;
   }
}

void TickFct_MainGame(){
   switch(MainGame_State){ //Transitions
      case MainGame_SMStart:
         MainGame_State = MainGame_Menu1;
         break;
      case MainGame_Menu1:
         MainGame_State = MainGame_Menu2;
         break;
      case MainGame_Menu2:
         //printf("here0\n");
         if(A0 == 1 && A1 == 0 && A2 == 0){
            //printf("here\n"); 
            display_lives = 1;
            MainGame_State = MainGame_Chapter1_Dialogue0;
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Menu2;    
         }
         break;
      case MainGame_Chapter1_Dialogue0:
         display_lives = 0;
         B3 = 1; //chapter 1
         B4 = B5 = B6 = B7 = 0;
         MainGame_State = MainGame_Chapter1_WaitOff0;
         break;
      case MainGame_Chapter1_WaitOff0:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff0;    
         }
         else if(A0 == 0){
            //printf("check1\n");
            MainGame_State = MainGame_Chapter1_WaitOn0;
         }
         break;
      case MainGame_Chapter1_WaitOn0:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn0;            
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue1;    
         }
         break;
      case MainGame_Chapter1_Dialogue1:
         MainGame_State = MainGame_Chapter1_WaitOff1;
         break;
      case MainGame_Chapter1_WaitOff1:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff1;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn1;
         }
         break;
      case MainGame_Chapter1_WaitOn1:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn1;            
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue2;    
         }
         break;
      case MainGame_Chapter1_Dialogue2:
         display_lives = 0;
         MainGame_State = MainGame_Chapter1_WaitOff2;
         break;
      case MainGame_Chapter1_WaitOff2:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff2;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn2;
         }
         break;
      case MainGame_Chapter1_WaitOn2:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn2;            
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue3;    
         }
         break;
      case MainGame_Chapter1_Dialogue3:
         display_lives = 0;
         MainGame_State = MainGame_Chapter1_WaitOff3;
         break;
      case MainGame_Chapter1_WaitOff3:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff3;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn3;
         }
         break;
      case MainGame_Chapter1_WaitOn3:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn3;            
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue4;    
         }
         break;
      case MainGame_Chapter1_Dialogue4:
         display_lives = 0;
         MainGame_State = MainGame_Chapter1_WaitOff4;
         break;
      case MainGame_Chapter1_WaitOff4:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff4;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn4;
         }
         break;
      case MainGame_Chapter1_WaitOn4:
         if(A1 == 0 && A2 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn4;            
         }
         else if(A1 == 1 && A2 == 0){
            MainGame_State = MainGame_Chapter1_Dialogue5a;    
         }
         else if(A1 == 0 && A2 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue6a;    
         }
         break;
      case MainGame_Chapter1_Dialogue5a:
         trigger_life_loss = 1;
         display_lives = 1;
         
         //if(lives == 0){
         //   MainGame_State = MainGame_GameOver;   
         //}
         
         MainGame_State = MainGame_Chapter1_WaitOff5a;
         break;
      case MainGame_Chapter1_WaitOff5a:
         //display_lives = 0;
         trigger_life_loss = 0;
         display_lives = 0;
         
         //if(lives == 0){
            //MainGame_State = MainGame_GameOver;   
         //}
         
         if(A1 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff5a;    
         }
         else if(A1 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter1_WaitOn5a;
         }
         break;
      case MainGame_Chapter1_WaitOn5a:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn5a;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter1_Dialogue5b;    
         }
         break;
      case MainGame_Chapter1_Dialogue5b:
         //if(lives == 0){
            //MainGame_State = MainGame_GameOver;   
         //}
         MainGame_State = MainGame_Chapter1_WaitOff5b;
         break;
      case MainGame_Chapter1_WaitOff5b:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff5b;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn5b;
         }
         break;
      case MainGame_Chapter1_WaitOn5b:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn5b;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue5c;    
         }
         break;
      case MainGame_Chapter1_Dialogue5c:
         MainGame_State = MainGame_Chapter1_WaitOff5c;
         break;
      case MainGame_Chapter1_WaitOff5c:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff5c;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn5c;
         }
         break;
      case MainGame_Chapter1_WaitOn5c:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn5c;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue5d;    
         }
         break;
      case MainGame_Chapter1_Dialogue5d:
         MainGame_State = MainGame_Chapter1_WaitOff5d;
         break;
      case MainGame_Chapter1_WaitOff5d:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff5d;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn5d;
         }
         break;
      case MainGame_Chapter1_WaitOn5d:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn5d;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue5e;    
         }
         break;
      case MainGame_Chapter1_Dialogue5e:
         MainGame_State = MainGame_Chapter1_WaitOff5e;
         break;
      case MainGame_Chapter1_WaitOff5e:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff5e;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn5e;
         }
         break;
      case MainGame_Chapter1_WaitOn5e:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn5e;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue5f;    
         }
         break;
      case MainGame_Chapter1_Dialogue5f:
         MainGame_State = MainGame_Chapter1_WaitOff5f;
         break;
      case MainGame_Chapter1_WaitOff5f:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff5f;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn5f;
         }
         break;
      case MainGame_Chapter1_WaitOn5f:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn5f;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue5g;    
         }
         break;
      case MainGame_Chapter1_Dialogue5g:
         MainGame_State = MainGame_Chapter1_WaitOff5g;
         break;
      case MainGame_Chapter1_WaitOff5g:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff5g;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn5g;
         }
         break;
      case MainGame_Chapter1_WaitOn5g:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn5g;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue7;    
         }
         break;
      case MainGame_Chapter1_Dialogue6a:
         //trigger_life_loss = 1;
         //display_lives = 1;
         score = score + 150;
         MainGame_State = MainGame_Chapter1_WaitOff6a;
         break;
      case MainGame_Chapter1_WaitOff6a:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A2 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff6a;    
         }
         else if(A2 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter1_WaitOn6a;
         }
         break;
      case MainGame_Chapter1_WaitOn6a:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn6a;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter1_Dialogue6b;    
         }
         break;
      case MainGame_Chapter1_Dialogue6b:
         MainGame_State = MainGame_Chapter1_WaitOff6b;
         break;
      case MainGame_Chapter1_WaitOff6b:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff6b;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn6b;
         }
         break;
      case MainGame_Chapter1_WaitOn6b:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn6b;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue6c;    
         }
         break;
      case MainGame_Chapter1_Dialogue6c:
         MainGame_State = MainGame_Chapter1_WaitOff6c;
         break;
      case MainGame_Chapter1_WaitOff6c:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff6c;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn6c;
         }
         break;
      case MainGame_Chapter1_WaitOn6c:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn6c;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue6d;    
         }
         break;
      case MainGame_Chapter1_Dialogue6d:
         MainGame_State = MainGame_Chapter1_WaitOff6d;
         break;
      case MainGame_Chapter1_WaitOff6d:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff6d;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn6d;
         }
         break;
      case MainGame_Chapter1_WaitOn6d:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn6d;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue6e;    
         }
         break;
      case MainGame_Chapter1_Dialogue6e:
         MainGame_State = MainGame_Chapter1_WaitOff6e;
         break;
      case MainGame_Chapter1_WaitOff6e:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff6e;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn6e;
         }
         break;
      case MainGame_Chapter1_WaitOn6e:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn6e;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue6f;    
         }
         break;
      case MainGame_Chapter1_Dialogue6f:
         MainGame_State = MainGame_Chapter1_WaitOff6f;
         break;
      case MainGame_Chapter1_WaitOff6f:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff6f;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn6f;
         }
         break;
      case MainGame_Chapter1_WaitOn6f:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn6f;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue6g;    
         }
         break;
      case MainGame_Chapter1_Dialogue6g:
         MainGame_State = MainGame_Chapter1_WaitOff6g;
         break;
      case MainGame_Chapter1_WaitOff6g:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff6g;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn6g;
         }
         break;
      case MainGame_Chapter1_WaitOn6g:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn6g;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue7;    
         }
         break;
     case MainGame_Chapter1_Dialogue7:
         display_lives = 0;
         MainGame_State = MainGame_Chapter1_WaitOff7;
         break;
      case MainGame_Chapter1_WaitOff7:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff7;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn7;
         }
         break;
      case MainGame_Chapter1_WaitOn7:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn7;            
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue8;    
         }
         break;
    case MainGame_Chapter1_Dialogue8:
         display_lives = 0;
         MainGame_State = MainGame_Chapter1_WaitOff8;
         break;
      case MainGame_Chapter1_WaitOff8:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff8;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn8;
         }
         break;
      case MainGame_Chapter1_WaitOn8:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn8;            
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue9;    
         }
         break;
      case MainGame_Chapter1_Dialogue9:
         display_lives = 0;
         MainGame_State = MainGame_Chapter1_WaitOff9;
         break;
      case MainGame_Chapter1_WaitOff9:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff9;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn9;
         }
         break;
      case MainGame_Chapter1_WaitOn9:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn9;            
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue10;    
         }
         break;
     case MainGame_Chapter1_Dialogue10:
         display_lives = 0;
         MainGame_State = MainGame_Chapter1_WaitOff10;
         break;
      case MainGame_Chapter1_WaitOff10:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff10;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn10;
         }
         break;
      case MainGame_Chapter1_WaitOn10:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn10;            
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue11;    
         }
         break;
     case MainGame_Chapter1_Dialogue11:
         display_lives = 0;
         MainGame_State = MainGame_Chapter1_WaitOff11;
         break;
      case MainGame_Chapter1_WaitOff11:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff11;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn11;
         }
         break;
      case MainGame_Chapter1_WaitOn11:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn11;            
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue12;    
         }
         break;
     case MainGame_Chapter1_Dialogue12:
         display_lives = 0;
         MainGame_State = MainGame_Chapter1_WaitOff12;
         break;
      case MainGame_Chapter1_WaitOff12:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff12;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn12;
         }
         break;
      case MainGame_Chapter1_WaitOn12:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn12;            
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue13;    
         }
         break;
     case MainGame_Chapter1_Dialogue13:
         display_lives = 0;
         MainGame_State = MainGame_Chapter1_WaitOff13;
         break;
      case MainGame_Chapter1_WaitOff13:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff13;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn13;
         }
         break;
      case MainGame_Chapter1_WaitOn13:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn13;            
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue14;    
         }
         break;
     case MainGame_Chapter1_Dialogue14:
         display_lives = 0;
         MainGame_State = MainGame_Chapter1_WaitOff14;
         break;
      case MainGame_Chapter1_WaitOff14:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff14;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn14;
         }
         break;
      case MainGame_Chapter1_WaitOn14:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn14;            
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue15;    
         }
         break;
      case MainGame_Chapter1_Dialogue15:
         display_lives = 0;
         MainGame_State = MainGame_Chapter1_WaitOff15;
         break;
      case MainGame_Chapter1_WaitOff15:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff15;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn15;
         }
         break;
      case MainGame_Chapter1_WaitOn15:
         if(A1 == 0 && A2 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn15;            
         }
         else if(A1 == 1 && A2 == 0){
            MainGame_State = MainGame_Chapter1_Dialogue16a;    
         }
         else if(A1 == 0 && A2 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue17a;    
         }
         break;
      case MainGame_Chapter1_Dialogue16a:
         //trigger_life_loss = 1;
         //display_lives = 1;
         score = score + 150;
         MainGame_State = MainGame_Chapter1_WaitOff16a;
         break;
      case MainGame_Chapter1_WaitOff16a:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A1 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff16a;    
         }
         else if(A1 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter1_WaitOn16a;
         }
         break;
      case MainGame_Chapter1_WaitOn16a:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn16a;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter1_Dialogue16b;    
         }
         break;
     case MainGame_Chapter1_Dialogue16b:
         MainGame_State = MainGame_Chapter1_WaitOff16b;
         break;
      case MainGame_Chapter1_WaitOff16b:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff16b;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn16b;
         }
         break;
      case MainGame_Chapter1_WaitOn16b:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn16b;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue16c;    
         }
         break;
     case MainGame_Chapter1_Dialogue16c:
         MainGame_State = MainGame_Chapter1_WaitOff16c;
         break;
      case MainGame_Chapter1_WaitOff16c:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff16c;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn16c;
         }
         break;
      case MainGame_Chapter1_WaitOn16c:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn16c;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue16d;    
         }
         break;
     case MainGame_Chapter1_Dialogue16d:
         MainGame_State = MainGame_Chapter1_WaitOff16d;
         break;
      case MainGame_Chapter1_WaitOff16d:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff16d;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn16d;
         }
         break;
      case MainGame_Chapter1_WaitOn16d:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn16d;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue16e;    
         }
         break;  
     case MainGame_Chapter1_Dialogue16e:
         MainGame_State = MainGame_Chapter1_WaitOff16e;
         break;
      case MainGame_Chapter1_WaitOff16e:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff16e;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn16e;
         }
         break;
      case MainGame_Chapter1_WaitOn16e:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn16e;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue16f;    
         }
         break;
     case MainGame_Chapter1_Dialogue16f:
         MainGame_State = MainGame_Chapter1_WaitOff16f;
         break;
      case MainGame_Chapter1_WaitOff16f:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff16f;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn16f;
         }
         break;
      case MainGame_Chapter1_WaitOn16f:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn16f;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue18;    
         }
         break;
      case MainGame_Chapter1_Dialogue17a:
         trigger_life_loss = 1;
         display_lives = 1;
         
         if(lives == 0){
            MainGame_State = MainGame_GameOver;   
         }
         
         MainGame_State = MainGame_Chapter1_WaitOff17a;
         break;
      case MainGame_Chapter1_WaitOff17a:
         display_lives = 0;
         trigger_life_loss = 0;
         //display_lives = 1;
         if(A1 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff17a;    
         }
         else if(A1 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter1_WaitOn17a;
         }
         break;
      case MainGame_Chapter1_WaitOn17a:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn17a;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter1_Dialogue17b;    
         }
         break;
    case MainGame_Chapter1_Dialogue17b:
         MainGame_State = MainGame_Chapter1_WaitOff17b;
         break;
      case MainGame_Chapter1_WaitOff17b:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff17b;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn17b;
         }
         break;
      case MainGame_Chapter1_WaitOn17b:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn17b;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue17c;    
         }
         break;
    case MainGame_Chapter1_Dialogue17c:
         MainGame_State = MainGame_Chapter1_WaitOff17c;
         break;
      case MainGame_Chapter1_WaitOff17c:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff17c;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn17c;
         }
         break;
      case MainGame_Chapter1_WaitOn17c:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn17c;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue17d;    
         }
         break;
    case MainGame_Chapter1_Dialogue17d:
         MainGame_State = MainGame_Chapter1_WaitOff17d;
         break;
      case MainGame_Chapter1_WaitOff17d:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff17d;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn17d;
         }
         break;
      case MainGame_Chapter1_WaitOn17d:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn17d;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue17e;    
         }
         break;
    case MainGame_Chapter1_Dialogue17e:
         MainGame_State = MainGame_Chapter1_WaitOff17e;
         break;
      case MainGame_Chapter1_WaitOff17e:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff17e;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn17e;
         }
         break;
      case MainGame_Chapter1_WaitOn17e:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn17e;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue17f;    
         }
         break;
    case MainGame_Chapter1_Dialogue17f:
         MainGame_State = MainGame_Chapter1_WaitOff17f;
         break;
      case MainGame_Chapter1_WaitOff17f:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff17f;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn17f;
         }
         break;
      case MainGame_Chapter1_WaitOn17f:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn17f;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue18;    
         }
         break;
   case MainGame_Chapter1_Dialogue18:
         MainGame_State = MainGame_Chapter1_WaitOff18;
         break;
      case MainGame_Chapter1_WaitOff18:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff18;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn18;
         }
         break;
      case MainGame_Chapter1_WaitOn18:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn18;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue19;    
         }
         break;
   case MainGame_Chapter1_Dialogue19:
         MainGame_State = MainGame_Chapter1_WaitOff19;
         break;
      case MainGame_Chapter1_WaitOff19:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff19;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn19;
         }
         break;
      case MainGame_Chapter1_WaitOn19:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn19;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue20;    
         }
         break;
   case MainGame_Chapter1_Dialogue20:
         MainGame_State = MainGame_Chapter1_WaitOff20;
         break;
      case MainGame_Chapter1_WaitOff20:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff20;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn20;
         }
         break;
      case MainGame_Chapter1_WaitOn20:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn20;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue21;    
         }
         break;
   case MainGame_Chapter1_Dialogue21:
         MainGame_State = MainGame_Chapter1_WaitOff21;
         break;
      case MainGame_Chapter1_WaitOff21:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff21;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn21;
         }
         break;
      case MainGame_Chapter1_WaitOn21:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn21;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue22;    
         }
         break;
   case MainGame_Chapter1_Dialogue22:
         MainGame_State = MainGame_Chapter1_WaitOff22;
         break;
      case MainGame_Chapter1_WaitOff22:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff22;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn22;
         }
         break;
      case MainGame_Chapter1_WaitOn22:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn22;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue23;    
         }
         break;
   case MainGame_Chapter1_Dialogue23:
         MainGame_State = MainGame_Chapter1_WaitOff23;
         break;
      case MainGame_Chapter1_WaitOff23:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff23;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn23;
         }
         break;
      case MainGame_Chapter1_WaitOn23:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn23;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue24;    
         }
         break;
   case MainGame_Chapter1_Dialogue24:
         MainGame_State = MainGame_Chapter1_WaitOff24;
         break;
      case MainGame_Chapter1_WaitOff24:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff24;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn24;
         }
         break;
      case MainGame_Chapter1_WaitOn24:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn24;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue25;    
         }
         break;
   case MainGame_Chapter1_Dialogue25:
         MainGame_State = MainGame_Chapter1_WaitOff25;
         break;
      case MainGame_Chapter1_WaitOff25:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff25;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn25;
         }
         break;
      case MainGame_Chapter1_WaitOn25:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn25;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue26;    
         }
         break;
   case MainGame_Chapter1_Dialogue26:
         MainGame_State = MainGame_Chapter1_WaitOff26;
         break;
      case MainGame_Chapter1_WaitOff26:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff26;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn26;
         }
         break;
      case MainGame_Chapter1_WaitOn26:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn26;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue27;    
         }
         break;
   case MainGame_Chapter1_Dialogue27:
         MainGame_State = MainGame_Chapter1_WaitOff27;
         break;
      case MainGame_Chapter1_WaitOff27:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff27;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn27;
         }
         break;
      case MainGame_Chapter1_WaitOn27:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn27;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue28;    
         }
         break;
   case MainGame_Chapter1_Dialogue28:
         MainGame_State = MainGame_Chapter1_WaitOff28;
         break;
      case MainGame_Chapter1_WaitOff28:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff28;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn28;
         }
         break;
      case MainGame_Chapter1_WaitOn28:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn28;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue29;    
         }
         break;
   case MainGame_Chapter1_Dialogue29:
         MainGame_State = MainGame_Chapter1_WaitOff29;
         break;
      case MainGame_Chapter1_WaitOff29:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff29;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn29;
         }
         break;
      case MainGame_Chapter1_WaitOn29:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn29;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue30;    
         }
         break;
   case MainGame_Chapter1_Dialogue30:
         MainGame_State = MainGame_Chapter1_WaitOff30;
         break;
      case MainGame_Chapter1_WaitOff30:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff30;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn30;
         }
         break;
      case MainGame_Chapter1_WaitOn30:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn30;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue31;    
         }
         break;
   case MainGame_Chapter1_Dialogue31:
         MainGame_State = MainGame_Chapter1_WaitOff31;
         break;
      case MainGame_Chapter1_WaitOff31:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff31;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn31;
         }
         break;
      case MainGame_Chapter1_WaitOn31:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn31;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue32;    
         }
         break;
   case MainGame_Chapter1_Dialogue32:
         MainGame_State = MainGame_Chapter1_WaitOff32;
         break;
      case MainGame_Chapter1_WaitOff32:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff32;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn32;
         }
         break;
      case MainGame_Chapter1_WaitOn32:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn32;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue33;    
         }
         break;
   case MainGame_Chapter1_Dialogue33:
         MainGame_State = MainGame_Chapter1_WaitOff33;
         break;
      case MainGame_Chapter1_WaitOff33:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff33;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn33;
         }
         break;
      case MainGame_Chapter1_WaitOn33:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn33;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue34;    
         }
         break;
   case MainGame_Chapter1_Dialogue34:
         MainGame_State = MainGame_Chapter1_WaitOff34;
         break;
      case MainGame_Chapter1_WaitOff34:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff34;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn34;
         }
         break;
      case MainGame_Chapter1_WaitOn34:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn34;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue35;    
         }
         break;
   case MainGame_Chapter1_Dialogue35:
         MainGame_State = MainGame_Chapter1_WaitOff35;
         break;
      case MainGame_Chapter1_WaitOff35:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff35;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn35;
         }
         break;
      case MainGame_Chapter1_WaitOn35:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn35;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue36;    
         }
         break;
   case MainGame_Chapter1_Dialogue36:
         MainGame_State = MainGame_Chapter1_WaitOff36;
         break;
      case MainGame_Chapter1_WaitOff36:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff36;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn36;
         }
         break;
      case MainGame_Chapter1_WaitOn36:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn36;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue37;    
         }
         break;
   case MainGame_Chapter1_Dialogue37:
         MainGame_State = MainGame_Chapter1_WaitOff37;
         break;
      case MainGame_Chapter1_WaitOff37:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff37;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn37;
         }
         break;
      case MainGame_Chapter1_WaitOn37:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn37;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue38;    
         }
         break;
   case MainGame_Chapter1_Dialogue38:
         MainGame_State = MainGame_Chapter1_WaitOff38;
         break;
      case MainGame_Chapter1_WaitOff38:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff38;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn38;
         }
         break;
      case MainGame_Chapter1_WaitOn38:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn38;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue39;    
         }
         break;
   case MainGame_Chapter1_Dialogue39:
         MainGame_State = MainGame_Chapter1_WaitOff39;
         break;
      case MainGame_Chapter1_WaitOff39:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff39;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn39;
         }
         break;
      case MainGame_Chapter1_WaitOn39:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn39;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue40;    
         }
         break;
   case MainGame_Chapter1_Dialogue40:
         MainGame_State = MainGame_Chapter1_WaitOff40;
         break;
      case MainGame_Chapter1_WaitOff40:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff40;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn40;
         }
         break;
      case MainGame_Chapter1_WaitOn40:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn40;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue41;    
         }
         break;
      case MainGame_Chapter1_Dialogue41:
         MainGame_State = MainGame_Chapter1_WaitOff41;
         break;
      case MainGame_Chapter1_WaitOff41:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff41;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn41;
         }
         break;
      case MainGame_Chapter1_WaitOn41:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn41;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter1_Dialogue42;    
         }
         break;
      case MainGame_Chapter1_Dialogue42:
         MainGame_State = MainGame_Chapter1_WaitOff42;
         break;
      case MainGame_Chapter1_WaitOff42:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter1_WaitOff42;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn42;
         }
         break;
      case MainGame_Chapter1_WaitOn42:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter1_WaitOn42;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue0;    
         }
         break;
      case MainGame_Chapter2_Dialogue0:
         B3 = B4 = 1; //chapter 2
         B5 = B6 = B7 = 0;
         MainGame_State = MainGame_Chapter2_WaitOff0;
         break;
      case MainGame_Chapter2_WaitOff0:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff0;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn0;
         }
         break;
      case MainGame_Chapter2_WaitOn0:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn0;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue1;    
         }
         break;
      case MainGame_Chapter2_Dialogue1:
         MainGame_State = MainGame_Chapter2_WaitOff1;
         break;
      case MainGame_Chapter2_WaitOff1:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff1;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn1;
         }
         break;
      case MainGame_Chapter2_WaitOn1:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn1;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue2;    
         }
         break;      
      case MainGame_Chapter2_Dialogue2:
         MainGame_State = MainGame_Chapter2_WaitOff2;
         break;
      case MainGame_Chapter2_WaitOff2:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff2;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn2;
         }
         break;
      case MainGame_Chapter2_WaitOn2:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn2;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue3;    
         }
         break;
      case MainGame_Chapter2_Dialogue3:
         MainGame_State = MainGame_Chapter2_WaitOff3;
         break;
      case MainGame_Chapter2_WaitOff3:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff3;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn3;
         }
         break;
      case MainGame_Chapter2_WaitOn3:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn3;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue4;    
         }
         break;
      case MainGame_Chapter2_Dialogue4:
         MainGame_State = MainGame_Chapter2_WaitOff4;
         break;
      case MainGame_Chapter2_WaitOff4:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff4;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn4;
         }
         break;
      case MainGame_Chapter2_WaitOn4:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn4;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue5;    
         }
         break;
      case MainGame_Chapter2_Dialogue5:
         MainGame_State = MainGame_Chapter2_WaitOff5;
         break;
      case MainGame_Chapter2_WaitOff5:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff5;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn5;
         }
         break;
      case MainGame_Chapter2_WaitOn5:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn5;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue6;    
         }
         break;
      case MainGame_Chapter2_Dialogue6:
         MainGame_State = MainGame_Chapter2_WaitOff6;
         break;
      case MainGame_Chapter2_WaitOff6:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff6;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn6;
         }
         break;
      case MainGame_Chapter2_WaitOn6:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn6;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue7;    
         }
         break;
      case MainGame_Chapter2_Dialogue7:
         MainGame_State = MainGame_Chapter2_WaitOff7;
         break;
      case MainGame_Chapter2_WaitOff7:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff7;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn7;
         }
         break;
      case MainGame_Chapter2_WaitOn7:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn7;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue8;    
         }
         break;
      case MainGame_Chapter2_Dialogue8:
         MainGame_State = MainGame_Chapter2_WaitOff8;
         break;
      case MainGame_Chapter2_WaitOff8:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff8;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn8;
         }
         break;
      case MainGame_Chapter2_WaitOn8:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn8;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue9;    
         }
         break;
      case MainGame_Chapter2_Dialogue9:
         MainGame_State = MainGame_Chapter2_WaitOff9;
         break;
      case MainGame_Chapter2_WaitOff9:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff9;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn9;
         }
         break;
      case MainGame_Chapter2_WaitOn9:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn9;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue10;    
         }
         break;
      case MainGame_Chapter2_Dialogue10:
         MainGame_State = MainGame_Chapter2_WaitOff10;
         break;
      case MainGame_Chapter2_WaitOff10:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff10;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn10;
         }
         break;
      case MainGame_Chapter2_WaitOn10:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn10;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue11;    
         }
         break;
      case MainGame_Chapter2_Dialogue11:
         MainGame_State = MainGame_Chapter2_WaitOff11;
         break;
      case MainGame_Chapter2_WaitOff11:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff11;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn11;
         }
         break;
      case MainGame_Chapter2_WaitOn11:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn11;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue12;    
         }
         break;
      case MainGame_Chapter2_Dialogue12:
         MainGame_State = MainGame_Chapter2_WaitOff12;
         break;
      case MainGame_Chapter2_WaitOff12:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff12;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn12;
         }
         break;
      case MainGame_Chapter2_WaitOn12:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn12;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue13;    
         }
         break;
      case MainGame_Chapter2_Dialogue13:
         MainGame_State = MainGame_Chapter2_WaitOff13;
         break;
      case MainGame_Chapter2_WaitOff13:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff13;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn13;
         }
         break;
      case MainGame_Chapter2_WaitOn13:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn13;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue14;    
         }
         break;
      case MainGame_Chapter2_Dialogue14:
         MainGame_State = MainGame_Chapter2_WaitOff14;
         break;
      case MainGame_Chapter2_WaitOff14:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff14;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn14;
         }
         break;
      case MainGame_Chapter2_WaitOn14:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn14;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue15;    
         }
         break;
      case MainGame_Chapter2_Dialogue15:
         MainGame_State = MainGame_Chapter2_WaitOff15;
         break;
      case MainGame_Chapter2_WaitOff15:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff15;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn15;
         }
         break;
      case MainGame_Chapter2_WaitOn15:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn15;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue16;    
         }
         break;
      case MainGame_Chapter2_Dialogue16:
         MainGame_State = MainGame_Chapter2_WaitOff16;
         break;
      case MainGame_Chapter2_WaitOff16:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff16;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn16;
         }
         break;
      case MainGame_Chapter2_WaitOn16:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn16;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue17;    
         }
         break;
      case MainGame_Chapter2_Dialogue17:
         MainGame_State = MainGame_Chapter2_WaitOff17;
         break;
      case MainGame_Chapter2_WaitOff17:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff17;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn17;
         }
         break;
      case MainGame_Chapter2_WaitOn17:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn17;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue18;    
         }
         break;
      case MainGame_Chapter2_Dialogue18:
         MainGame_State = MainGame_Chapter2_WaitOff18;
         break;
      case MainGame_Chapter2_WaitOff18:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff18;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn18;
         }
         break;
      case MainGame_Chapter2_WaitOn18:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn18;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue19;    
         }
         break;
      case MainGame_Chapter2_Dialogue19:
         MainGame_State = MainGame_Chapter2_WaitOff19;
         break;
      case MainGame_Chapter2_WaitOff19:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff19;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn19;
         }
         break;
      case MainGame_Chapter2_WaitOn19:
         if(A1 == 0 && A2 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn19;           
         }
         else if(A1 == 1 && A2 == 0){
            MainGame_State = MainGame_Chapter2_Dialogue20a;    
         }
         else if(A1 == 0 && A2 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue21a;    
         }
         break;
      case MainGame_Chapter2_Dialogue20a:
         display_lives = 1;
         trigger_life_loss = 1;
         
         if(lives == 0){
            MainGame_State = MainGame_GameOver;    
         }
         
         MainGame_State = MainGame_Chapter2_WaitOff20a;
         break;
      case MainGame_Chapter2_WaitOff20a:
         display_lives = 0;
         trigger_life_loss = 0;
         //display_lives = 1;
         if(A1 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff20a;    
         }
         else if(A1 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn20a;
         }
         break;
      case MainGame_Chapter2_WaitOn20a:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn20a;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue20b;    
         }
         break;
      case MainGame_Chapter2_Dialogue20b:
         MainGame_State = MainGame_Chapter2_WaitOff20b;
         break;
      case MainGame_Chapter2_WaitOff20b:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff20b;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn20b;
         }
         break;
      case MainGame_Chapter2_WaitOn20b:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn20b;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue20c;    
         }
         break;
      case MainGame_Chapter2_Dialogue20c:
         MainGame_State = MainGame_Chapter2_WaitOff20c;
         break;
      case MainGame_Chapter2_WaitOff20c:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff20c;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn20c;
         }
         break;
      case MainGame_Chapter2_WaitOn20c:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn20c;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue20d;    
         }
         break;
      case MainGame_Chapter2_Dialogue20d:
         MainGame_State = MainGame_Chapter2_WaitOff20d;
         break;
      case MainGame_Chapter2_WaitOff20d:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff20d;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn20d;
         }
         break;
      case MainGame_Chapter2_WaitOn20d:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn20d;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue20e;    
         }
         break;
      case MainGame_Chapter2_Dialogue20e:
         MainGame_State = MainGame_Chapter2_WaitOff20e;
         break;
      case MainGame_Chapter2_WaitOff20e:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff20e;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn20e;
         }
         break;
      case MainGame_Chapter2_WaitOn20e:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn20e;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue20f;    
         }
         break;
     case MainGame_Chapter2_Dialogue20f:
         MainGame_State = MainGame_Chapter2_WaitOff20f;
         break;
      case MainGame_Chapter2_WaitOff20f:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff20f;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn20f;
         }
         break;
      case MainGame_Chapter2_WaitOn20f:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn20f;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue22;    
         }
         break;
      case MainGame_Chapter2_Dialogue21a:
         score = score + 150;
         MainGame_State = MainGame_Chapter2_WaitOff21a;
         break;
      case MainGame_Chapter2_WaitOff21a:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A2 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff21a;    
         }
         else if(A2 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn21a;
         }
         break;
      case MainGame_Chapter2_WaitOn21a:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn21a;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue21b;    
         }
         break;
     case MainGame_Chapter2_Dialogue21b:
         MainGame_State = MainGame_Chapter2_WaitOff21b;
         break;
      case MainGame_Chapter2_WaitOff21b:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff21b;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn21b;
         }
         break;
      case MainGame_Chapter2_WaitOn21b:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn21b;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue21c;    
         }
         break;
     case MainGame_Chapter2_Dialogue21c:
         MainGame_State = MainGame_Chapter2_WaitOff21c;
         break;
      case MainGame_Chapter2_WaitOff21c:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff21c;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn21c;
         }
         break;
      case MainGame_Chapter2_WaitOn21c:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn21c;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue21d;    
         }
         break;
     case MainGame_Chapter2_Dialogue21d:
         MainGame_State = MainGame_Chapter2_WaitOff21d;
         break;
      case MainGame_Chapter2_WaitOff21d:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff21d;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn21d;
         }
         break;
      case MainGame_Chapter2_WaitOn21d:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn21d;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue21e;    
         }
         break;
     case MainGame_Chapter2_Dialogue21e:
         MainGame_State = MainGame_Chapter2_WaitOff21e;
         break;
      case MainGame_Chapter2_WaitOff21e:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff21e;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn21e;
         }
         break;
      case MainGame_Chapter2_WaitOn21e:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn21e;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue21f;    
         }
         break;
     case MainGame_Chapter2_Dialogue21f:
         MainGame_State = MainGame_Chapter2_WaitOff21f;
         break;
      case MainGame_Chapter2_WaitOff21f:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff21f;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn21f;
         }
         break;
      case MainGame_Chapter2_WaitOn21f:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn21f;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue22;    
         }
         break;
     case MainGame_Chapter2_Dialogue22:
         MainGame_State = MainGame_Chapter2_WaitOff22;
         break;
      case MainGame_Chapter2_WaitOff22:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff22;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn22;
         }
         break;
      case MainGame_Chapter2_WaitOn22:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn22;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue23;    
         }
         break;
     case MainGame_Chapter2_Dialogue23:
         MainGame_State = MainGame_Chapter2_WaitOff23;
         break;
      case MainGame_Chapter2_WaitOff23:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff23;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn23;
         }
         break;
      case MainGame_Chapter2_WaitOn23:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn23;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue24;    
         }
         break;
     case MainGame_Chapter2_Dialogue24:
         MainGame_State = MainGame_Chapter2_WaitOff24;
         break;
      case MainGame_Chapter2_WaitOff24:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff24;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn24;
         }
         break;
      case MainGame_Chapter2_WaitOn24:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn24;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue25;    
         }
         break;
     case MainGame_Chapter2_Dialogue25:
         MainGame_State = MainGame_Chapter2_WaitOff25;
         break;
      case MainGame_Chapter2_WaitOff25:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff25;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn25;
         }
         break;
      case MainGame_Chapter2_WaitOn25:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn25;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue26;    
         }
         break;      
      case MainGame_Chapter2_Dialogue26:
         MainGame_State = MainGame_Chapter2_WaitOff26;
         break;
      case MainGame_Chapter2_WaitOff26:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff26;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn26;
         }
         break;
      case MainGame_Chapter2_WaitOn26:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn26;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue27;    
         }
         break;
     case MainGame_Chapter2_Dialogue27:
         MainGame_State = MainGame_Chapter2_WaitOff27;
         break;
      case MainGame_Chapter2_WaitOff27:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff27;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn27;
         }
         break;
      case MainGame_Chapter2_WaitOn27:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn27;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue28;    
         }
         break;
     case MainGame_Chapter2_Dialogue28:
         MainGame_State = MainGame_Chapter2_WaitOff28;
         break;
      case MainGame_Chapter2_WaitOff28:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff28;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn28;
         }
         break;
      case MainGame_Chapter2_WaitOn28:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn28;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue29;    
         }
         break;
     case MainGame_Chapter2_Dialogue29:
         MainGame_State = MainGame_Chapter2_WaitOff29;
         break;
      case MainGame_Chapter2_WaitOff29:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff29;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn29;
         }
         break;
      case MainGame_Chapter2_WaitOn29:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn29;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue30;    
         }
         break;
     case MainGame_Chapter2_Dialogue30:
         MainGame_State = MainGame_Chapter2_WaitOff30;
         break;
      case MainGame_Chapter2_WaitOff30:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff30;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn30;
         }
         break;
      case MainGame_Chapter2_WaitOn30:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn30;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue31;    
         }
         break;
     case MainGame_Chapter2_Dialogue31:
         MainGame_State = MainGame_Chapter2_WaitOff31;
         break;
      case MainGame_Chapter2_WaitOff31:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff31;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn31;
         }
         break;
      case MainGame_Chapter2_WaitOn31:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn31;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue32;    
         }
         break;
     case MainGame_Chapter2_Dialogue32:
         MainGame_State = MainGame_Chapter2_WaitOff32;
         break;
      case MainGame_Chapter2_WaitOff32:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff32;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn32;
         }
         break;
      case MainGame_Chapter2_WaitOn32:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn32;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue33;    
         }
         break;
     case MainGame_Chapter2_Dialogue33:
         MainGame_State = MainGame_Chapter2_WaitOff33;
         break;
      case MainGame_Chapter2_WaitOff33:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff33;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn33;
         }
         break;
      case MainGame_Chapter2_WaitOn33:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn33;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue34;    
         }
         break;
     case MainGame_Chapter2_Dialogue34:
         MainGame_State = MainGame_Chapter2_WaitOff34;
         break;
      case MainGame_Chapter2_WaitOff34:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff34;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn34;
         }
         break;
      case MainGame_Chapter2_WaitOn34:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn34;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue35;    
         }
         break;
     case MainGame_Chapter2_Dialogue35:
         MainGame_State = MainGame_Chapter2_WaitOff35;
         break;
      case MainGame_Chapter2_WaitOff35:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff35;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn35;
         }
         break;
      case MainGame_Chapter2_WaitOn35:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn35;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue36;    
         }
         break;
     case MainGame_Chapter2_Dialogue36:
         MainGame_State = MainGame_Chapter2_WaitOff36;
         break;
      case MainGame_Chapter2_WaitOff36:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff36;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn36;
         }
         break;
      case MainGame_Chapter2_WaitOn36:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn36;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue37;    
         }
         break;
     case MainGame_Chapter2_Dialogue37:
         MainGame_State = MainGame_Chapter2_WaitOff37;
         break;
      case MainGame_Chapter2_WaitOff37:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff37;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn37;
         }
         break;
      case MainGame_Chapter2_WaitOn37:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn37;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue38;    
         }
         break;
     case MainGame_Chapter2_Dialogue38:
         MainGame_State = MainGame_Chapter2_WaitOff38;
         break;
      case MainGame_Chapter2_WaitOff38:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff38;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn38;
         }
         break;
      case MainGame_Chapter2_WaitOn38:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn38;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue39;    
         }
         break;
     case MainGame_Chapter2_Dialogue39:
         MainGame_State = MainGame_Chapter2_WaitOff39;
         break;
      case MainGame_Chapter2_WaitOff39:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff39;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn39;
         }
         break;
      case MainGame_Chapter2_WaitOn39:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn39;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue40;    
         }
         break;
     case MainGame_Chapter2_Dialogue40:
         MainGame_State = MainGame_Chapter2_WaitOff40;
         break;
      case MainGame_Chapter2_WaitOff40:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff40;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn40;
         }
         break;
      case MainGame_Chapter2_WaitOn40:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn40;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue41;    
         }
         break;
     case MainGame_Chapter2_Dialogue41:
         MainGame_State = MainGame_Chapter2_WaitOff41;
         break;
      case MainGame_Chapter2_WaitOff41:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff41;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn41;
         }
         break;
      case MainGame_Chapter2_WaitOn41:
         if(A1 == 0 && A2 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn41;           
         }
         else if(A1 == 1 && A2 == 0){
            MainGame_State = MainGame_Chapter2_Dialogue42a;    
         }
         else if(A1 == 0 && A2 == 1){
            MainGame_State = MainGame_Chapter2_Dialogue43a;    
         }
         break;
      case MainGame_Chapter2_Dialogue42a:
         score = score + 150;
         MainGame_State = MainGame_Chapter2_WaitOff42a;
         break;      
      case MainGame_Chapter2_WaitOff42a:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A1 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff42a;    
         }
         else if(A1 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn42a;
         }
         break;
      case MainGame_Chapter2_WaitOn42a:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn42a;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue42b;    
         }
         break;
      case MainGame_Chapter2_Dialogue42b:
         MainGame_State = MainGame_Chapter2_WaitOff42b;
         break;
      case MainGame_Chapter2_WaitOff42b:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff42b;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn42b;
         }
         break;
      case MainGame_Chapter2_WaitOn42b:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn42b;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue42c;    
         }
         break;
      case MainGame_Chapter2_Dialogue42c:
         MainGame_State = MainGame_Chapter2_WaitOff42c;
         break;
      case MainGame_Chapter2_WaitOff42c:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff42c;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn42c;
         }
         break;
      case MainGame_Chapter2_WaitOn42c:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn42c;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue42d;    
         }
         break;
      case MainGame_Chapter2_Dialogue42d:
         MainGame_State = MainGame_Chapter2_WaitOff42d;
         break;
      case MainGame_Chapter2_WaitOff42d:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff42d;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn42d;
         }
         break;
      case MainGame_Chapter2_WaitOn42d:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn42d;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue42e;    
         }
         break;
      case MainGame_Chapter2_Dialogue42e:
         MainGame_State = MainGame_Chapter2_WaitOff42e;
         break;
      case MainGame_Chapter2_WaitOff42e:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff42e;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn42e;
         }
         break;
      case MainGame_Chapter2_WaitOn42e:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn42e;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue42f;    
         }
         break;
      case MainGame_Chapter2_Dialogue42f:
         MainGame_State = MainGame_Chapter2_WaitOff42f;
         break;
      case MainGame_Chapter2_WaitOff42f:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff42f;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn42f;
         }
         break;
      case MainGame_Chapter2_WaitOn42f:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn42f;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue44;    
         }
         break;
      case MainGame_Chapter2_Dialogue43a:
         display_lives = 1;
         trigger_life_loss = 1;
         
         if(lives == 0){
            MainGame_State = MainGame_GameOver;    
         }
         
         MainGame_State = MainGame_Chapter2_WaitOff43a;
         break; 
      case MainGame_Chapter2_WaitOff43a:
         display_lives = 0;
         trigger_life_loss = 0;
         //display_lives = 1;
         if(A2 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff43a;    
         }
         else if(A2 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn43a;
         }
         break;
      case MainGame_Chapter2_WaitOn43a:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn43a;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue43b;    
         }
         break;
     case MainGame_Chapter2_Dialogue43b:
         MainGame_State = MainGame_Chapter2_WaitOff43b;
         break; 
      case MainGame_Chapter2_WaitOff43b:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff43b;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn43b;
         }
         break;
      case MainGame_Chapter2_WaitOn43b:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn43b;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue43c;    
         }
         break;
     case MainGame_Chapter2_Dialogue43c:
         MainGame_State = MainGame_Chapter2_WaitOff43c;
         break; 
      case MainGame_Chapter2_WaitOff43c:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff43c;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn43c;
         }
         break;
      case MainGame_Chapter2_WaitOn43c:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn43c;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue43d;    
         }
         break;
     case MainGame_Chapter2_Dialogue43d:
         MainGame_State = MainGame_Chapter2_WaitOff43d;
         break; 
      case MainGame_Chapter2_WaitOff43d:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff43d;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn43d;
         }
         break;
      case MainGame_Chapter2_WaitOn43d:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn43d;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue43e;    
         }
         break;
     case MainGame_Chapter2_Dialogue43e:
         MainGame_State = MainGame_Chapter2_WaitOff43e;
         break; 
      case MainGame_Chapter2_WaitOff43e:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff43e;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn43e;
         }
         break;
      case MainGame_Chapter2_WaitOn43e:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn43e;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue43f;    
         }
         break;
     case MainGame_Chapter2_Dialogue43f:
         MainGame_State = MainGame_Chapter2_WaitOff43f;
         break; 
      case MainGame_Chapter2_WaitOff43f:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff43f;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn43f;
         }
         break;
      case MainGame_Chapter2_WaitOn43f:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn43f;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue44;    
         }
         break;
     case MainGame_Chapter2_Dialogue44:
         MainGame_State = MainGame_Chapter2_WaitOff44;
         break; 
      case MainGame_Chapter2_WaitOff44:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff44;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn44;
         }
         break;
      case MainGame_Chapter2_WaitOn44:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn44;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue45;    
         }
         break;
     case MainGame_Chapter2_Dialogue45:
         MainGame_State = MainGame_Chapter2_WaitOff45;
         break; 
      case MainGame_Chapter2_WaitOff45:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff45;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn45;
         }
         break;
      case MainGame_Chapter2_WaitOn45:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn45;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue46;    
         }
         break;
     case MainGame_Chapter2_Dialogue46:
         MainGame_State = MainGame_Chapter2_WaitOff46;
         break; 
      case MainGame_Chapter2_WaitOff46:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff46;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn46;
         }
         break;
      case MainGame_Chapter2_WaitOn46:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn46;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue47;    
         }
         break;
     case MainGame_Chapter2_Dialogue47:
         MainGame_State = MainGame_Chapter2_WaitOff47;
         break; 
      case MainGame_Chapter2_WaitOff47:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff47;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn47;
         }
         break;
      case MainGame_Chapter2_WaitOn47:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn47;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue48;    
         }
         break;
     case MainGame_Chapter2_Dialogue48:
         MainGame_State = MainGame_Chapter2_WaitOff48;
         break; 
      case MainGame_Chapter2_WaitOff48:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff48;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn48;
         }
         break;
      case MainGame_Chapter2_WaitOn48:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn48;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue49;    
         }
         break;
     case MainGame_Chapter2_Dialogue49:
         MainGame_State = MainGame_Chapter2_WaitOff49;
         break; 
      case MainGame_Chapter2_WaitOff49:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff49;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn49;
         }
         break;
      case MainGame_Chapter2_WaitOn49:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn49;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue50;    
         }
         break;
     case MainGame_Chapter2_Dialogue50:
         MainGame_State = MainGame_Chapter2_WaitOff50;
         break; 
      case MainGame_Chapter2_WaitOff50:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff50;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn50;
         }
         break;
      case MainGame_Chapter2_WaitOn50:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn50;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue51;    
         }
         break;
     case MainGame_Chapter2_Dialogue51:
         MainGame_State = MainGame_Chapter2_WaitOff51;
         break; 
      case MainGame_Chapter2_WaitOff51:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff51;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn51;
         }
         break;
      case MainGame_Chapter2_WaitOn51:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn51;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue52;    
         }
         break;
     case MainGame_Chapter2_Dialogue52:
         MainGame_State = MainGame_Chapter2_WaitOff52;
         break; 
      case MainGame_Chapter2_WaitOff52:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff52;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn52;
         }
         break;
      case MainGame_Chapter2_WaitOn52:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn52;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue53;    
         }
         break;
      case MainGame_Chapter2_Dialogue53:
         MainGame_State = MainGame_Chapter2_WaitOff53;
         break; 
      case MainGame_Chapter2_WaitOff53:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff53;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn53;
         }
         break;
      case MainGame_Chapter2_WaitOn53:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn53;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue54;    
         }
         break;
     case MainGame_Chapter2_Dialogue54:
         MainGame_State = MainGame_Chapter2_WaitOff54;
         break; 
      case MainGame_Chapter2_WaitOff54:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff54;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn54;
         }
         break;
      case MainGame_Chapter2_WaitOn54:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn54;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue55;    
         }
         break;
     case MainGame_Chapter2_Dialogue55:
         MainGame_State = MainGame_Chapter2_WaitOff55;
         break; 
      case MainGame_Chapter2_WaitOff55:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff55;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn55;
         }
         break;
      case MainGame_Chapter2_WaitOn55:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn55;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue56;    
         }
         break;
     case MainGame_Chapter2_Dialogue56:
         MainGame_State = MainGame_Chapter2_WaitOff56;
         break; 
      case MainGame_Chapter2_WaitOff56:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff56;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn56;
         }
         break;
      case MainGame_Chapter2_WaitOn56:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn56;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue57;    
         }
         break;
     case MainGame_Chapter2_Dialogue57:
         MainGame_State = MainGame_Chapter2_WaitOff57;
         break; 
      case MainGame_Chapter2_WaitOff57:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff57;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn57;
         }
         break;
      case MainGame_Chapter2_WaitOn57:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn57;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue58;    
         }
         break;
     case MainGame_Chapter2_Dialogue58:
         MainGame_State = MainGame_Chapter2_WaitOff58;
         break; 
      case MainGame_Chapter2_WaitOff58:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff58;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn58;
         }
         break;
      case MainGame_Chapter2_WaitOn58:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn58;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue59;    
         }
         break;
     case MainGame_Chapter2_Dialogue59:
         MainGame_State = MainGame_Chapter2_WaitOff59;
         break; 
      case MainGame_Chapter2_WaitOff59:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff59;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn59;
         }
         break;
      case MainGame_Chapter2_WaitOn59:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn59;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue60;    
         }
         break;
      case MainGame_Chapter2_Dialogue60:
         MainGame_State = MainGame_Chapter2_WaitOff60;
         break;
      case MainGame_Chapter2_WaitOff60:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff60;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn60;
         }
         break;
      case MainGame_Chapter2_WaitOn60:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn60;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue61;    
         }
         break; 
      case MainGame_Chapter2_Dialogue61:
         MainGame_State = MainGame_Chapter2_WaitOff61;
         break; 
      case MainGame_Chapter2_WaitOff61:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff61;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn61;
         }
         break;
      case MainGame_Chapter2_WaitOn61:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn61;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue62;    
         }
         break;
     case MainGame_Chapter2_Dialogue62:
         MainGame_State = MainGame_Chapter2_WaitOff62;
         break; 
      case MainGame_Chapter2_WaitOff62:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff62;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn62;
         }
         break;
      case MainGame_Chapter2_WaitOn62:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn62;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue63;    
         }
         break;
     case MainGame_Chapter2_Dialogue63:
         MainGame_State = MainGame_Chapter2_WaitOff63;
         break; 
      case MainGame_Chapter2_WaitOff63:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff63;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn63;
         }
         break;
      case MainGame_Chapter2_WaitOn63:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn63;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue64;    
         }
         break;
      case MainGame_Chapter2_Dialogue64:
         MainGame_State = MainGame_Chapter2_WaitOff64;
         break; 
      case MainGame_Chapter2_WaitOff64:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff64;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn64;
         }
         break;
      case MainGame_Chapter2_WaitOn64:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn64;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue65;    
         }
         break;
     case MainGame_Chapter2_Dialogue65:
         MainGame_State = MainGame_Chapter2_WaitOff65;
         break; 
      case MainGame_Chapter2_WaitOff65:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff65;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn65;
         }
         break;
      case MainGame_Chapter2_WaitOn65:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn65;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue66;    
         }
         break;
     case MainGame_Chapter2_Dialogue66:
         MainGame_State = MainGame_Chapter2_WaitOff66;
         break; 
      case MainGame_Chapter2_WaitOff66:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff66;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn66;
         }
         break;
      case MainGame_Chapter2_WaitOn66:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn66;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue67;    
         }
         break;
     case MainGame_Chapter2_Dialogue67:
         MainGame_State = MainGame_Chapter2_WaitOff67;
         break; 
      case MainGame_Chapter2_WaitOff67:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff67;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn67;
         }
         break;
      case MainGame_Chapter2_WaitOn67:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn67;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue68;    
         }
         break;
      case MainGame_Chapter2_Dialogue68:
         MainGame_State = MainGame_Chapter2_WaitOff68;
         break;         
      case MainGame_Chapter2_WaitOff68:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff68;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn68;
         }
         break;
      case MainGame_Chapter2_WaitOn68:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn68;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue69;    
         }
         break;
      case MainGame_Chapter2_Dialogue69:
         MainGame_State = MainGame_Chapter2_WaitOff69;
         break; 
      case MainGame_Chapter2_WaitOff69:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff69;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn69;
         }
         break;
      case MainGame_Chapter2_WaitOn69:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn69;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue70;    
         }
         break;
     case MainGame_Chapter2_Dialogue70:
         MainGame_State = MainGame_Chapter2_WaitOff70;
         break; 
      case MainGame_Chapter2_WaitOff70:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff70;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn70;
         }
         break;
      case MainGame_Chapter2_WaitOn70:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn70;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue71;    
         }
         break;
     case MainGame_Chapter2_Dialogue71:
         MainGame_State = MainGame_Chapter2_WaitOff71;
         break; 
      case MainGame_Chapter2_WaitOff71:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff71;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn71;
         }
         break;
      case MainGame_Chapter2_WaitOn71:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn71;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue72;    
         }
         break;
     case MainGame_Chapter2_Dialogue72:
         MainGame_State = MainGame_Chapter2_WaitOff72;
         break; 
      case MainGame_Chapter2_WaitOff72:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff72;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn72;
         }
         break;
      case MainGame_Chapter2_WaitOn72:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn72;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue73;    
         }
         break;
     case MainGame_Chapter2_Dialogue73:
         MainGame_State = MainGame_Chapter2_WaitOff73;
         break; 
      case MainGame_Chapter2_WaitOff73:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff73;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn73;
         }
         break;
      case MainGame_Chapter2_WaitOn73:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn73;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue74;    
         }
         break;
     case MainGame_Chapter2_Dialogue74:
         MainGame_State = MainGame_Chapter2_WaitOff74;
         break; 
      case MainGame_Chapter2_WaitOff74:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff74;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn74;
         }
         break;
      case MainGame_Chapter2_WaitOn74:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn74;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue75;    
         }
         break;
     case MainGame_Chapter2_Dialogue75:
         MainGame_State = MainGame_Chapter2_WaitOff75;
         break; 
      case MainGame_Chapter2_WaitOff75:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff75;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn75;
         }
         break;
      case MainGame_Chapter2_WaitOn75:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn75;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter2_Dialogue76;    
         }
         break;
     case MainGame_Chapter2_Dialogue76:
         MainGame_State = MainGame_Chapter2_WaitOff76;
         break; 
      case MainGame_Chapter2_WaitOff76:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter2_WaitOff76;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter2_WaitOn76;
         }
         break;
      case MainGame_Chapter2_WaitOn76:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter2_WaitOn76;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue0;    
         }
         break;
     case MainGame_Chapter3_Dialogue0:
         B3 = B4 = B5 = 1; //chapter 3
         B6 = B7 = 0;
         MainGame_State = MainGame_Chapter3_WaitOff0;
         break;
      case MainGame_Chapter3_WaitOff0:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff0;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn0;
         }
         break;
      case MainGame_Chapter3_WaitOn0:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn0;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue1;    
         }
         break;
      case MainGame_Chapter3_Dialogue1:
         MainGame_State = MainGame_Chapter3_WaitOff1;
         break;
      case MainGame_Chapter3_WaitOff1:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff1;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn1;
         }
         break;
      case MainGame_Chapter3_WaitOn1:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn1;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue2;    
         }
         break;      
      case MainGame_Chapter3_Dialogue2:
         MainGame_State = MainGame_Chapter3_WaitOff2;
         break;
      case MainGame_Chapter3_WaitOff2:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff2;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn2;
         }
         break;
      case MainGame_Chapter3_WaitOn2:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn2;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue3;    
         }
         break;
      case MainGame_Chapter3_Dialogue3:
         MainGame_State = MainGame_Chapter3_WaitOff3;
         break;
      case MainGame_Chapter3_WaitOff3:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff3;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn3;
         }
         break;
      case MainGame_Chapter3_WaitOn3:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn3;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue4;    
         }
         break;
      case MainGame_Chapter3_Dialogue4:
         MainGame_State = MainGame_Chapter3_WaitOff4;
         break;
      case MainGame_Chapter3_WaitOff4:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff4;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn4;
         }
         break;
      case MainGame_Chapter3_WaitOn4:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn4;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue5;    
         }
         break;
      case MainGame_Chapter3_Dialogue5:
         MainGame_State = MainGame_Chapter3_WaitOff5;
         break;
      case MainGame_Chapter3_WaitOff5:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff5;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn5;
         }
         break;
      case MainGame_Chapter3_WaitOn5:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn5;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue6;    
         }
         break;
      case MainGame_Chapter3_Dialogue6:
         MainGame_State = MainGame_Chapter3_WaitOff6;
         break;
      case MainGame_Chapter3_WaitOff6:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff6;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn6;
         }
         break;
      case MainGame_Chapter3_WaitOn6:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn6;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue7;    
         }
         break;
      case MainGame_Chapter3_Dialogue7:
         MainGame_State = MainGame_Chapter3_WaitOff7;
         break;
      case MainGame_Chapter3_WaitOff7:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff7;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn7;
         }
         break;
      case MainGame_Chapter3_WaitOn7:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn7;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue8;    
         }
         break;
      case MainGame_Chapter3_Dialogue8:
         MainGame_State = MainGame_Chapter3_WaitOff8;
         break;
      case MainGame_Chapter3_WaitOff8:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff8;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn8;
         }
         break;
      case MainGame_Chapter3_WaitOn8:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn8;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue9;    
         }
         break;
      case MainGame_Chapter3_Dialogue9:
         MainGame_State = MainGame_Chapter3_WaitOff9;
         break;
      case MainGame_Chapter3_WaitOff9:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff9;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn9;
         }
         break;
      case MainGame_Chapter3_WaitOn9:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn9;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue10;    
         }
         break;
      case MainGame_Chapter3_Dialogue10:
         MainGame_State = MainGame_Chapter3_WaitOff10;
         break;
      case MainGame_Chapter3_WaitOff10:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff10;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn10;
         }
         break;
      case MainGame_Chapter3_WaitOn10:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn10;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue11;    
         }
         break;
      case MainGame_Chapter3_Dialogue11:
         MainGame_State = MainGame_Chapter3_WaitOff11;
         break;
      case MainGame_Chapter3_WaitOff11:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff11;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn11;
         }
         break;
      case MainGame_Chapter3_WaitOn11:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn11;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue12;    
         }
         break;
      case MainGame_Chapter3_Dialogue12:
         MainGame_State = MainGame_Chapter3_WaitOff12;
         break;
      case MainGame_Chapter3_WaitOff12:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff12;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn12;
         }
         break;
      case MainGame_Chapter3_WaitOn12:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn12;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue13;    
         }
         break;      
      case MainGame_Chapter3_Dialogue13:
         MainGame_State = MainGame_Chapter3_WaitOff13;
         break;
      case MainGame_Chapter3_WaitOff13:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff13;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn13;
         }
         break;
      case MainGame_Chapter3_WaitOn13:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn13;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue14;    
         }
         break;
      case MainGame_Chapter3_Dialogue14:
         MainGame_State = MainGame_Chapter3_WaitOff14;
         break;
      case MainGame_Chapter3_WaitOff14:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff14;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn14;
         }
         break;
      case MainGame_Chapter3_WaitOn14:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn14;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue15;    
         }
         break;
      case MainGame_Chapter3_Dialogue15:
         MainGame_State = MainGame_Chapter3_WaitOff15;
         break;
      case MainGame_Chapter3_WaitOff15:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff15;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn15;
         }
         break;
      case MainGame_Chapter3_WaitOn15:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn15;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue16;    
         }
         break;
      case MainGame_Chapter3_Dialogue16:
         MainGame_State = MainGame_Chapter3_WaitOff16;
         break;
      case MainGame_Chapter3_WaitOff16:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff16;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn16;
         }
         break;
      case MainGame_Chapter3_WaitOn16:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn16;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue17;    
         }
         break;
      case MainGame_Chapter3_Dialogue17:
         MainGame_State = MainGame_Chapter3_WaitOff17;
         break;
      case MainGame_Chapter3_WaitOff17:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff17;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn17;
         }
         break;
      case MainGame_Chapter3_WaitOn17:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn17;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue18;    
         }
         break;
      case MainGame_Chapter3_Dialogue18:
         MainGame_State = MainGame_Chapter3_WaitOff18;
         break;
      case MainGame_Chapter3_WaitOff18:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff18;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn18;
         }
         break;
      case MainGame_Chapter3_WaitOn18:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn18;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue19;    
         }
         break;
      case MainGame_Chapter3_Dialogue19:
         MainGame_State = MainGame_Chapter3_WaitOff19;
         break;
      case MainGame_Chapter3_WaitOff19:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff19;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn19;
         }
         break;
      case MainGame_Chapter3_WaitOn19:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn19;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue20;    
         }
         break;
      case MainGame_Chapter3_Dialogue20:
         MainGame_State = MainGame_Chapter3_WaitOff20;
         break;
      case MainGame_Chapter3_WaitOff20:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff20;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn20;
         }
         break;
      case MainGame_Chapter3_WaitOn20:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn20;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue21;    
         }
         break;
      case MainGame_Chapter3_Dialogue21:
         MainGame_State = MainGame_Chapter3_WaitOff21;
         break;
      case MainGame_Chapter3_WaitOff21:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff21;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn21;
         }
         break;
      case MainGame_Chapter3_WaitOn21:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn21;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue22;    
         }
         break;      
      case MainGame_Chapter3_Dialogue22:
         MainGame_State = MainGame_Chapter3_WaitOff22;
         break;
      case MainGame_Chapter3_WaitOff22:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff22;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn22;
         }
         break;
      case MainGame_Chapter3_WaitOn22:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn22;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue23;    
         }
         break;
      case MainGame_Chapter3_Dialogue23:
         MainGame_State = MainGame_Chapter3_WaitOff23;
         break;
      case MainGame_Chapter3_WaitOff23:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff23;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn23;
         }
         break;
      case MainGame_Chapter3_WaitOn23:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn23;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue24;    
         }
         break;
      case MainGame_Chapter3_Dialogue24:
         MainGame_State = MainGame_Chapter3_WaitOff24;
         break;
      case MainGame_Chapter3_WaitOff24:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff24;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn24;
         }
         break;
      case MainGame_Chapter3_WaitOn24:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn24;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue25;    
         }
         break;
      case MainGame_Chapter3_Dialogue25:
         MainGame_State = MainGame_Chapter3_WaitOff25;
         break;
      case MainGame_Chapter3_WaitOff25:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff25;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn25;
         }
         break;
      case MainGame_Chapter3_WaitOn25:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn25;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue26;    
         }
         break;
      case MainGame_Chapter3_Dialogue26:
         MainGame_State = MainGame_Chapter3_WaitOff26;
         break;
      case MainGame_Chapter3_WaitOff26:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff26;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn26;
         }
         break;
      case MainGame_Chapter3_WaitOn26:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn26;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue27;    
         }
         break;
      case MainGame_Chapter3_Dialogue27:
         MainGame_State = MainGame_Chapter3_WaitOff27;
         break;
      case MainGame_Chapter3_WaitOff27:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff27;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn27;
         }
         break;
      case MainGame_Chapter3_WaitOn27:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn27;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue28;    
         }
         break;
      case MainGame_Chapter3_Dialogue28:
         MainGame_State = MainGame_Chapter3_WaitOff28;
         break;
      case MainGame_Chapter3_WaitOff28:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff28;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn28;
         }
         break;
      case MainGame_Chapter3_WaitOn28:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn28;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue29;    
         }
         break;
      case MainGame_Chapter3_Dialogue29:
         MainGame_State = MainGame_Chapter3_WaitOff29;
         break;
      case MainGame_Chapter3_WaitOff29:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff29;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn29;
         }
         break;
      case MainGame_Chapter3_WaitOn29:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn29;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue30;    
         }
         break;
      case MainGame_Chapter3_Dialogue30:
         MainGame_State = MainGame_Chapter3_WaitOff30;
         break;
      case MainGame_Chapter3_WaitOff30:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff30;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn30;
         }
         break;
      case MainGame_Chapter3_WaitOn30:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn30;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue31;    
         }
         break;
      case MainGame_Chapter3_Dialogue31:
         MainGame_State = MainGame_Chapter3_WaitOff31;
         break;
      case MainGame_Chapter3_WaitOff31:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff31;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn31;
         }
         break;
      case MainGame_Chapter3_WaitOn31:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn31;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue32;    
         }
         break;
      case MainGame_Chapter3_Dialogue32:
         MainGame_State = MainGame_Chapter3_WaitOff32;
         break;
      case MainGame_Chapter3_WaitOff32:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff32;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn32;
         }
         break;
      case MainGame_Chapter3_WaitOn32:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn32;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue33;    
         }
         break;
      case MainGame_Chapter3_Dialogue33:
         MainGame_State = MainGame_Chapter3_WaitOff33;
         break;
      case MainGame_Chapter3_WaitOff33:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff33;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn33;
         }
         break;
      case MainGame_Chapter3_WaitOn33:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn33;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue34;    
         }
         break;
      case MainGame_Chapter3_Dialogue34:
         MainGame_State = MainGame_Chapter3_WaitOff34;
         break;
      case MainGame_Chapter3_WaitOff34:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff34;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn34;
         }
         break;
      case MainGame_Chapter3_WaitOn34:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn34;           
         }
         else if(A0 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue35;    
         }
         break;
      case MainGame_Chapter3_Dialogue35:
         MainGame_State = MainGame_Chapter3_WaitOff35;
         break;
      case MainGame_Chapter3_WaitOff35:
         //display_lives = 0;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff35;    
         }
         else if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn35;
         }
         break;
      case MainGame_Chapter3_WaitOn35:
         if(A1 == 0 && A2 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn35;           
         }
         else if(A1 == 1 && A2 == 0){
            MainGame_State = MainGame_Chapter3_Dialogue36a;    
         }
         else if(A1 == 0 && A2 == 1){
            MainGame_State = MainGame_Chapter3_Dialogue37a;    
         }
         break;
      case MainGame_Chapter3_Dialogue36a:
         display_lives = 1;
         trigger_life_loss = 1;
         
         if(lives == 0){
            MainGame_State = MainGame_GameOver;    
         }
         
         MainGame_State = MainGame_Chapter3_WaitOff36a;
         break;      
      case MainGame_Chapter3_WaitOff36a:
         display_lives = 0;
         trigger_life_loss = 0;
         //display_lives = 1;
         if(A1 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff36a;    
         }
         else if(A1 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn36a;
         }
         break;
      case MainGame_Chapter3_WaitOn36a:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn36a;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue36b;    
         }
         break;
      case MainGame_Chapter3_Dialogue36b:
         MainGame_State = MainGame_Chapter3_WaitOff36b;
         break;      
      case MainGame_Chapter3_WaitOff36b:
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff36b;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn36b;
         }
         break;
      case MainGame_Chapter3_WaitOn36b:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn36b;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue36c;    
         }
         break;
      case MainGame_Chapter3_Dialogue36c:
         MainGame_State = MainGame_Chapter3_WaitOff36c;
         break;      
      case MainGame_Chapter3_WaitOff36c:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff36c;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn36c;
         }
         break;
      case MainGame_Chapter3_WaitOn36c:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn36c;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue36d;    
         }
         break;
      case MainGame_Chapter3_Dialogue36d:
         MainGame_State = MainGame_Chapter3_WaitOff36d;
         break;      
      case MainGame_Chapter3_WaitOff36d:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff36d;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn36d;
         }
         break;
      case MainGame_Chapter3_WaitOn36d:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn36d;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue36e;    
         }
         break;
      case MainGame_Chapter3_Dialogue36e:
         MainGame_State = MainGame_Chapter3_WaitOff36e;
         break;      
      case MainGame_Chapter3_WaitOff36e:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff36e;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn36e;
         }
         break;
      case MainGame_Chapter3_WaitOn36e:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn36e;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue36f;    
         }
         break;
      case MainGame_Chapter3_Dialogue36f:
         MainGame_State = MainGame_Chapter3_WaitOff36f;
         break;      
      case MainGame_Chapter3_WaitOff36f:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff36f;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn36f;
         }
         break;
      case MainGame_Chapter3_WaitOn36f:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn36f;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue38;    
         }
         break;
      case MainGame_Chapter3_Dialogue37a:
         score = score + 150;
         MainGame_State = MainGame_Chapter3_WaitOff37a;
         break;      
      case MainGame_Chapter3_WaitOff37a:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A2 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff37a;    
         }
         else if(A2 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn37a;
         }
         break;
      case MainGame_Chapter3_WaitOn37a:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn37a;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue37b;    
         }
         break;
      case MainGame_Chapter3_Dialogue37b:
         MainGame_State = MainGame_Chapter3_WaitOff37b;
         break;      
      case MainGame_Chapter3_WaitOff37b:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff37b;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn37b;
         }
         break;
      case MainGame_Chapter3_WaitOn37b:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn37b;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue37c;    
         }
         break;
      case MainGame_Chapter3_Dialogue37c:
         MainGame_State = MainGame_Chapter3_WaitOff37c;
         break;      
      case MainGame_Chapter3_WaitOff37c:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff37c;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn37c;
         }
         break;
      case MainGame_Chapter3_WaitOn37c:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn37c;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue37d;    
         }
         break;
      case MainGame_Chapter3_Dialogue37d:
         MainGame_State = MainGame_Chapter3_WaitOff37d;
         break;      
      case MainGame_Chapter3_WaitOff37d:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff37d;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn37d;
         }
         break;
      case MainGame_Chapter3_WaitOn37d:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn37d;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue37e;    
         }
         break;
      case MainGame_Chapter3_Dialogue37e:
         MainGame_State = MainGame_Chapter3_WaitOff37e;
         break;      
      case MainGame_Chapter3_WaitOff37e:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff37e;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn37e;
         }
         break;
      case MainGame_Chapter3_WaitOn37e:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn37e;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue37f;    
         }
         break;
      case MainGame_Chapter3_Dialogue37f:
         MainGame_State = MainGame_Chapter3_WaitOff37f;
         break;      
      case MainGame_Chapter3_WaitOff37f:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff37f;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn37f;
         }
         break;
      case MainGame_Chapter3_WaitOn37f:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn37f;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue38;    
         }
         break;
      case MainGame_Chapter3_Dialogue38:
         MainGame_State = MainGame_Chapter3_WaitOff38;
         break;      
      case MainGame_Chapter3_WaitOff38:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff38;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn38;
         }
         break;
      case MainGame_Chapter3_WaitOn38:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn38;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue39;    
         }
         break;
      case MainGame_Chapter3_Dialogue39:
         MainGame_State = MainGame_Chapter3_WaitOff39;
         break;      
      case MainGame_Chapter3_WaitOff39:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff39;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn39;
         }
         break;
      case MainGame_Chapter3_WaitOn39:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn39;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue40;    
         }
         break;
      case MainGame_Chapter3_Dialogue40:
         MainGame_State = MainGame_Chapter3_WaitOff40;
         break;      
      case MainGame_Chapter3_WaitOff40:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff40;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn40;
         }
         break;
      case MainGame_Chapter3_WaitOn40:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn40;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue41;    
         }
         break;
      case MainGame_Chapter3_Dialogue41:
         MainGame_State = MainGame_Chapter3_WaitOff41;
         break;      
      case MainGame_Chapter3_WaitOff41:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff41;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn41;
         }
         break;
      case MainGame_Chapter3_WaitOn41:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn41;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue42;    
         }
         break;
      case MainGame_Chapter3_Dialogue42:
         MainGame_State = MainGame_Chapter3_WaitOff42;
         break;      
      case MainGame_Chapter3_WaitOff42:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff42;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn42;
         }
         break;
      case MainGame_Chapter3_WaitOn42:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn42;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue43;    
         }
         break;
      case MainGame_Chapter3_Dialogue43:
         MainGame_State = MainGame_Chapter3_WaitOff43;
         break;      
      case MainGame_Chapter3_WaitOff43:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff43;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn43;
         }
         break;
      case MainGame_Chapter3_WaitOn43:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn43;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue45;    
         }
         break;
      case MainGame_Chapter3_Dialogue45:
         MainGame_State = MainGame_Chapter3_WaitOff45;
         break;      
      case MainGame_Chapter3_WaitOff45:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff45;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn45;
         }
         break;
      case MainGame_Chapter3_WaitOn45:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn45;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue46;    
         }
         break;
      case MainGame_Chapter3_Dialogue46:
         MainGame_State = MainGame_Chapter3_WaitOff46;
         break;      
      case MainGame_Chapter3_WaitOff46:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff46;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn46;
         }
         break;
      case MainGame_Chapter3_WaitOn46:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn46;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue47;    
         }
         break;
      case MainGame_Chapter3_Dialogue47:
         MainGame_State = MainGame_Chapter3_WaitOff47;
         break;      
      case MainGame_Chapter3_WaitOff47:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff47;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn47;
         }
         break;
      case MainGame_Chapter3_WaitOn47:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn47;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue48;    
         }
         break;
      case MainGame_Chapter3_Dialogue48:
         MainGame_State = MainGame_Chapter3_WaitOff48;
         break;      
      case MainGame_Chapter3_WaitOff48:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff48;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn48;
         }
         break;
      case MainGame_Chapter3_WaitOn48:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn48;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue49;    
         }
         break;
      case MainGame_Chapter3_Dialogue49:
         MainGame_State = MainGame_Chapter3_WaitOff49;
         break;      
      case MainGame_Chapter3_WaitOff49:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff49;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn49;
         }
         break;
      case MainGame_Chapter3_WaitOn49:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn49;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue50;    
         }
         break;
      case MainGame_Chapter3_Dialogue50:
         MainGame_State = MainGame_Chapter3_WaitOff50;
         break;      
      case MainGame_Chapter3_WaitOff50:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff50;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn50;
         }
         break;
      case MainGame_Chapter3_WaitOn50:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn50;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue51;    
         }
         break;
      case MainGame_Chapter3_Dialogue51:
         MainGame_State = MainGame_Chapter3_WaitOff51;
         break;      
      case MainGame_Chapter3_WaitOff51:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff51;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn51;
         }
         break;
      case MainGame_Chapter3_WaitOn51:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn51;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue52;    
         }
         break;
      case MainGame_Chapter3_Dialogue52:
         MainGame_State = MainGame_Chapter3_WaitOff52;
         break;      
      case MainGame_Chapter3_WaitOff52:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff52;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn52;
         }
         break;
      case MainGame_Chapter3_WaitOn52:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn52;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue53;    
         }
         break;
      case MainGame_Chapter3_Dialogue53:
         MainGame_State = MainGame_Chapter3_WaitOff53;
         break;      
      case MainGame_Chapter3_WaitOff53:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff53;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn53;
         }
         break;
      case MainGame_Chapter3_WaitOn53:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn53;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue54;    
         }
         break;
      case MainGame_Chapter3_Dialogue54:
         MainGame_State = MainGame_Chapter3_WaitOff54;
         break;      
      case MainGame_Chapter3_WaitOff54:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff54;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn54;
         }
         break;
      case MainGame_Chapter3_WaitOn54:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn54;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue55;    
         }
         break;
      case MainGame_Chapter3_Dialogue55:
         MainGame_State = MainGame_Chapter3_WaitOff55;
         break;      
      case MainGame_Chapter3_WaitOff55:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff55;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn55;
         }
         break;
      case MainGame_Chapter3_WaitOn55:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn55;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue56;    
         }
         break;
      case MainGame_Chapter3_Dialogue56:
         MainGame_State = MainGame_Chapter3_WaitOff56;
         break;      
      case MainGame_Chapter3_WaitOff56:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff56;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn56;
         }
         break;
      case MainGame_Chapter3_WaitOn56:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn56;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue58;    
         }
         break;
      case MainGame_Chapter3_Dialogue58:
         MainGame_State = MainGame_Chapter3_WaitOff58;
         break;      
      case MainGame_Chapter3_WaitOff58:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff58;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn58;
         }
         break;
      case MainGame_Chapter3_WaitOn58:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn58;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue59;    
         }
         break;
      case MainGame_Chapter3_Dialogue59:
         MainGame_State = MainGame_Chapter3_WaitOff59;
         break;      
      case MainGame_Chapter3_WaitOff59:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff59;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn59;
         }
         break;
      case MainGame_Chapter3_WaitOn59:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn59;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue60;    
         }
         break;
      case MainGame_Chapter3_Dialogue60:
         MainGame_State = MainGame_Chapter3_WaitOff60;
         break;      
      case MainGame_Chapter3_WaitOff60:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff60;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn60;
         }
         break;
      case MainGame_Chapter3_WaitOn60:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn60;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue61;    
         }
         break;
      case MainGame_Chapter3_Dialogue61:
         MainGame_State = MainGame_Chapter3_WaitOff61;
         break;      
      case MainGame_Chapter3_WaitOff61:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff61;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn61;
         }
         break;
      case MainGame_Chapter3_WaitOn61:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn61;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue62;    
         }
         break;
      case MainGame_Chapter3_Dialogue62:
         MainGame_State = MainGame_Chapter3_WaitOff62;
         break;      
      case MainGame_Chapter3_WaitOff62:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff62;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn62;
         }
         break;
      case MainGame_Chapter3_WaitOn62:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn62;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue63;    
         }
         break;
      case MainGame_Chapter3_Dialogue63:
         MainGame_State = MainGame_Chapter3_WaitOff63;
         break;      
      case MainGame_Chapter3_WaitOff63:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff63;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn63;
         }
         break;
      case MainGame_Chapter3_WaitOn63:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn63;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue64;    
         }
         break;    
      case MainGame_Chapter3_Dialogue64:
         MainGame_State = MainGame_Chapter3_WaitOff64;
         break;      
      case MainGame_Chapter3_WaitOff64:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff64;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn64;
         }
         break;
      case MainGame_Chapter3_WaitOn64:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn64;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue65;    
         }
         break;
      case MainGame_Chapter3_Dialogue65:
         MainGame_State = MainGame_Chapter3_WaitOff65;
         break;      
      case MainGame_Chapter3_WaitOff65:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff65;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn65;
         }
         break;
      case MainGame_Chapter3_WaitOn65:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn65;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue66;    
         }
         break;
      case MainGame_Chapter3_Dialogue66:
         MainGame_State = MainGame_Chapter3_WaitOff66;
         break;      
      case MainGame_Chapter3_WaitOff66:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff66;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn66;
         }
         break;
      case MainGame_Chapter3_WaitOn66:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn66;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue67;    
         }
         break;
      case MainGame_Chapter3_Dialogue67:
         MainGame_State = MainGame_Chapter3_WaitOff67;
         break;      
      case MainGame_Chapter3_WaitOff67:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff67;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn67;
         }
         break;
      case MainGame_Chapter3_WaitOn67:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn67;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue68;    
         }
         break;
      case MainGame_Chapter3_Dialogue68:
         MainGame_State = MainGame_Chapter3_WaitOff68;
         break;      
      case MainGame_Chapter3_WaitOff68:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff68;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn68;
         }
         break;
      case MainGame_Chapter3_WaitOn68:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn68;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue69;    
         }
         break;
      case MainGame_Chapter3_Dialogue69:
         MainGame_State = MainGame_Chapter3_WaitOff69;
         break;      
      case MainGame_Chapter3_WaitOff69:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff69;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn69;
         }
         break;
      case MainGame_Chapter3_WaitOn69:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn69;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue70;    
         }
         break;
      case MainGame_Chapter3_Dialogue70:
         MainGame_State = MainGame_Chapter3_WaitOff70;
         break;      
      case MainGame_Chapter3_WaitOff70:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff70;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn70;
         }
         break;
      case MainGame_Chapter3_WaitOn70:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn70;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue71;    
         }
         break;
      case MainGame_Chapter3_Dialogue71:
         MainGame_State = MainGame_Chapter3_WaitOff71;
         break;      
      case MainGame_Chapter3_WaitOff71:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff71;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn71;
         }
         break;
      case MainGame_Chapter3_WaitOn71:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn71;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue72;    
         }
         break;
      case MainGame_Chapter3_Dialogue72:
         MainGame_State = MainGame_Chapter3_WaitOff72;
         break;      
      case MainGame_Chapter3_WaitOff72:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff72;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn72;
         }
         break;
      case MainGame_Chapter3_WaitOn72:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn72;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue73;    
         }
         break;
      case MainGame_Chapter3_Dialogue73:
         MainGame_State = MainGame_Chapter3_WaitOff73;
         break;      
      case MainGame_Chapter3_WaitOff73:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff73;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn73;
         }
         break;
      case MainGame_Chapter3_WaitOn73:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn73;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue74;    
         }
         break;
      case MainGame_Chapter3_Dialogue74:
         MainGame_State = MainGame_Chapter3_WaitOff74;
         break;      
      case MainGame_Chapter3_WaitOff74:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff74;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn74;
         }
         break;
      case MainGame_Chapter3_WaitOn74:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn74;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue75;    
         }
         break;
      case MainGame_Chapter3_Dialogue75:
         MainGame_State = MainGame_Chapter3_WaitOff75;
         break;      
      case MainGame_Chapter3_WaitOff75:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff75;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn75;
         }
         break;
      case MainGame_Chapter3_WaitOn75:
         if(A1 == 0 && A2 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn75;     
         }
         else if(A1 == 1 && A2 == 0){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue76a;    
         }
         else if(A1 == 0 && A2 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue77a;    
         }
         break;
      case MainGame_Chapter3_Dialogue76a:
         //display_lives = 1;
         //trigger_life_loss = 1;
         score = score + 150;
         MainGame_State = MainGame_Chapter3_WaitOff76a;
         break;      
      case MainGame_Chapter3_WaitOff76a:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A1 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff76a;    
         }
         else if(A1 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn76a;
         }
         break;
      case MainGame_Chapter3_WaitOn76a:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn76a;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue76b;    
         }
         break;
      case MainGame_Chapter3_Dialogue76b:
         MainGame_State = MainGame_Chapter3_WaitOff76b;
         break;      
      case MainGame_Chapter3_WaitOff76b:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff76b;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn76b;
         }
         break;
      case MainGame_Chapter3_WaitOn76b:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn76b;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue76c;    
         }
         break;
      case MainGame_Chapter3_Dialogue76c:
         MainGame_State = MainGame_Chapter3_WaitOff76c;
         break;      
      case MainGame_Chapter3_WaitOff76c:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff76c;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn76c;
         }
         break;
      case MainGame_Chapter3_WaitOn76c:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn76c;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue76d;    
         }
         break;
      case MainGame_Chapter3_Dialogue76d:
         MainGame_State = MainGame_Chapter3_WaitOff76d;
         break;      
      case MainGame_Chapter3_WaitOff76d:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff76d;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn76d;
         }
         break;
      case MainGame_Chapter3_WaitOn76d:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn76d;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue76e;    
         }
         break;
      case MainGame_Chapter3_Dialogue76e:
         MainGame_State = MainGame_Chapter3_WaitOff76e;
         break;      
      case MainGame_Chapter3_WaitOff76e:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff76e;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn76e;
         }
         break;
      case MainGame_Chapter3_WaitOn76e:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn76e;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue76f;    
         }
         break;
      case MainGame_Chapter3_Dialogue76f:
         MainGame_State = MainGame_Chapter3_WaitOff76f;
         break;      
      case MainGame_Chapter3_WaitOff76f:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff76f;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn76f;
         }
         break;
      case MainGame_Chapter3_WaitOn76f:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn76f;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue78;    
         }
         break;
      case MainGame_Chapter3_Dialogue77a:
         display_lives = 1;
         trigger_life_loss = 1;
         
         if(lives == 0){
            MainGame_State = MainGame_GameOver;    
         }
         
         MainGame_State = MainGame_Chapter3_WaitOff77a;
         break;      
      case MainGame_Chapter3_WaitOff77a:
         display_lives = 0;
         trigger_life_loss = 0;
         //display_lives = 1;
         if(A2 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff77a;    
         }
         else if(A2 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn77a;
         }
         break;
      case MainGame_Chapter3_WaitOn77a:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn77a;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue77b;    
         }
         break;
      case MainGame_Chapter3_Dialogue77b:
         MainGame_State = MainGame_Chapter3_WaitOff77b;
         break;      
      case MainGame_Chapter3_WaitOff77b:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff77b;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn77b;
         }
         break;
      case MainGame_Chapter3_WaitOn77b:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn77b;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue77c;    
         }
         break;
      case MainGame_Chapter3_Dialogue77c:
         MainGame_State = MainGame_Chapter3_WaitOff77c;
         break;      
      case MainGame_Chapter3_WaitOff77c:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff77c;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn77c;
         }
         break;
      case MainGame_Chapter3_WaitOn77c:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn77c;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue77d;    
         }
         break;
      case MainGame_Chapter3_Dialogue77d:
         MainGame_State = MainGame_Chapter3_WaitOff77d;
         break;      
      case MainGame_Chapter3_WaitOff77d:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff77d;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn77d;
         }
         break;
      case MainGame_Chapter3_WaitOn77d:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn77d;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue77e;    
         }
         break;
      case MainGame_Chapter3_Dialogue77e:
         MainGame_State = MainGame_Chapter3_WaitOff77e;
         break;      
      case MainGame_Chapter3_WaitOff77e:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff77e;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn77e;
         }
         break;
      case MainGame_Chapter3_WaitOn77e:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn77e;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue77f;    
         }
         break;
      case MainGame_Chapter3_Dialogue77f:
         MainGame_State = MainGame_Chapter3_WaitOff77f;
         break;      
      case MainGame_Chapter3_WaitOff77f:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff77f;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn77f;
         }
         break;
      case MainGame_Chapter3_WaitOn77f:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn77f;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue78;    
         }
         break;
      case MainGame_Chapter3_Dialogue78:
         MainGame_State = MainGame_Chapter3_WaitOff78;
         break;      
      case MainGame_Chapter3_WaitOff78:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff78;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn78;
         }
         break;
      case MainGame_Chapter3_WaitOn78:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn78;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue79;    
         }
         break;
      case MainGame_Chapter3_Dialogue79:
         MainGame_State = MainGame_Chapter3_WaitOff79;
         break;      
      case MainGame_Chapter3_WaitOff79:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff79;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn79;
         }
         break;
      case MainGame_Chapter3_WaitOn79:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn79;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue80;    
         }
         break;
      case MainGame_Chapter3_Dialogue80:
         MainGame_State = MainGame_Chapter3_WaitOff80;
         break;      
      case MainGame_Chapter3_WaitOff80:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff80;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn80;
         }
         break;
      case MainGame_Chapter3_WaitOn80:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn80;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue81;    
         }
         break;
      case MainGame_Chapter3_Dialogue81:
         MainGame_State = MainGame_Chapter3_WaitOff81;
         break;      
      case MainGame_Chapter3_WaitOff81:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff81;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn81;
         }
         break;
      case MainGame_Chapter3_WaitOn81:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn81;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue82;    
         }
         break;
      case MainGame_Chapter3_Dialogue82:
         MainGame_State = MainGame_Chapter3_WaitOff82;
         break;      
      case MainGame_Chapter3_WaitOff82:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff82;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn82;
         }
         break;
      case MainGame_Chapter3_WaitOn82:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn82;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue83;    
         }
         break;
      case MainGame_Chapter3_Dialogue83:
         MainGame_State = MainGame_Chapter3_WaitOff83;
         break;      
      case MainGame_Chapter3_WaitOff83:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff83;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn83;
         }
         break;
      case MainGame_Chapter3_WaitOn83:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn83;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue85;    
         }
         break;
      case MainGame_Chapter3_Dialogue85:
         MainGame_State = MainGame_Chapter3_WaitOff85;
         break;      
      case MainGame_Chapter3_WaitOff85:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff85;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn85;
         }
         break;
      case MainGame_Chapter3_WaitOn85:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn85;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue86;    
         }
         break;
      case MainGame_Chapter3_Dialogue86:
         MainGame_State = MainGame_Chapter3_WaitOff86;
         break;      
      case MainGame_Chapter3_WaitOff86:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff86;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn86;
         }
         break;
      case MainGame_Chapter3_WaitOn86:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn86;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue87;    
         }
         break;
      case MainGame_Chapter3_Dialogue87:
         MainGame_State = MainGame_Chapter3_WaitOff87;
         break;      
      case MainGame_Chapter3_WaitOff87:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff87;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn87;
         }
         break;
      case MainGame_Chapter3_WaitOn87:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn87;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue88;    
         }
         break;
      case MainGame_Chapter3_Dialogue88:
         MainGame_State = MainGame_Chapter3_WaitOff88;
         break;      
      case MainGame_Chapter3_WaitOff88:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff88;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn88;
         }
         break;
      case MainGame_Chapter3_WaitOn88:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn88;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue89;    
         }
         break;
      case MainGame_Chapter3_Dialogue89:
         MainGame_State = MainGame_Chapter3_WaitOff89;
         break;      
      case MainGame_Chapter3_WaitOff89:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff89;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn89;
         }
         break;
      case MainGame_Chapter3_WaitOn89:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn89;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue90;    
         }
         break;
      case MainGame_Chapter3_Dialogue90:
         MainGame_State = MainGame_Chapter3_WaitOff91;
         break;      
      case MainGame_Chapter3_WaitOff91:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff91;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn91;
         }
         break;
      case MainGame_Chapter3_WaitOn91:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn91;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue92;    
         }
         break;
      case MainGame_Chapter3_Dialogue92:
         MainGame_State = MainGame_Chapter3_WaitOff92;
         break;      
      case MainGame_Chapter3_WaitOff92:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff92;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn92;
         }
         break;
      case MainGame_Chapter3_WaitOn92:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn92;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue93;    
         }
         break;
      case MainGame_Chapter3_Dialogue93:
         MainGame_State = MainGame_Chapter3_WaitOff93;
         break;      
      case MainGame_Chapter3_WaitOff93:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff93;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn93;
         }
         break;
      case MainGame_Chapter3_WaitOn93:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn93;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue94;    
         }
         break;
      case MainGame_Chapter3_Dialogue94:
         MainGame_State = MainGame_Chapter3_WaitOff94;
         break;      
      case MainGame_Chapter3_WaitOff94:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff94;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn94;
         }
         break;
      case MainGame_Chapter3_WaitOn94:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn94;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue95;    
         }
         break;
      case MainGame_Chapter3_Dialogue95:
         MainGame_State = MainGame_Chapter3_WaitOff95;
         break;      
      case MainGame_Chapter3_WaitOff95:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff95;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn95;
         }
         break;
      case MainGame_Chapter3_WaitOn95:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn95;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue96;    
         }
         break;
      case MainGame_Chapter3_Dialogue96:
         MainGame_State = MainGame_Chapter3_WaitOff96;
         break;      
      case MainGame_Chapter3_WaitOff96:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff96;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn96;
         }
         break;
      case MainGame_Chapter3_WaitOn96:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn96;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue97;    
         }
         break;
      case MainGame_Chapter3_Dialogue97:
         MainGame_State = MainGame_Chapter3_WaitOff97;
         break;      
      case MainGame_Chapter3_WaitOff97:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff97;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn97;
         }
         break;
      case MainGame_Chapter3_WaitOn97:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn97;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue98;    
         }
         break;
      case MainGame_Chapter3_Dialogue98:
         MainGame_State = MainGame_Chapter3_WaitOff98;
         break;      
      case MainGame_Chapter3_WaitOff98:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff98;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn98;
         }
         break;
      case MainGame_Chapter3_WaitOn98:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn98;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue99;    
         }
         break;
      case MainGame_Chapter3_Dialogue99:
         MainGame_State = MainGame_Chapter3_WaitOff99;
         break;      
      case MainGame_Chapter3_WaitOff99:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff99;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn99;
         }
         break;
      case MainGame_Chapter3_WaitOn99:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn99;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue100;    
         }
         break;
      case MainGame_Chapter3_Dialogue100:
         MainGame_State = MainGame_Chapter3_WaitOff100;
         break;      
      case MainGame_Chapter3_WaitOff100:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff100;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn100;
         }
         break;
      case MainGame_Chapter3_WaitOn100:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn100;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue101;    
         }
         break;
      case MainGame_Chapter3_Dialogue101:
         MainGame_State = MainGame_Chapter3_WaitOff101;
         break;      
      case MainGame_Chapter3_WaitOff101:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff101;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn101;
         }
         break;
      case MainGame_Chapter3_WaitOn101:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn101;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue102;    
         }
         break;
      case MainGame_Chapter3_Dialogue102:
         MainGame_State = MainGame_Chapter3_WaitOff102;
         break;      
      case MainGame_Chapter3_WaitOff102:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff102;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn102;
         }
         break;
      case MainGame_Chapter3_WaitOn102:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn102;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue103;    
         }
         break;
      case MainGame_Chapter3_Dialogue103:
         MainGame_State = MainGame_Chapter3_WaitOff103;
         break;      
      case MainGame_Chapter3_WaitOff103:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff103;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn103;
         }
         break;
      case MainGame_Chapter3_WaitOn103:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn103;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter3_Dialogue104;    
         }
         break;
      case MainGame_Chapter3_Dialogue104:
         MainGame_State = MainGame_Chapter3_WaitOff104;
         break;      
      case MainGame_Chapter3_WaitOff104:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter3_WaitOff104;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter3_WaitOn104;
         }
         break;
      case MainGame_Chapter3_WaitOn104:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter3_WaitOn104;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue0;    
         }
         break;
      case MainGame_Chapter4_Dialogue0:
         B3 = B4 = B5 = B6 = 1; //chapter 4
         B7 = 0;
         score = score + 100;
         MainGame_State = MainGame_Chapter4_WaitOff0;
         break;      
      case MainGame_Chapter4_WaitOff0:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff0;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn0;
         }
         break;
      case MainGame_Chapter4_WaitOn0:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn0;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue1;    
         }
         break;
      case MainGame_Chapter4_Dialogue1:
         MainGame_State = MainGame_Chapter4_WaitOff1;
         break;      
      case MainGame_Chapter4_WaitOff1:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff1;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn1;
         }
         break;
      case MainGame_Chapter4_WaitOn1:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn1;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue2;    
         }
         break;
      case MainGame_Chapter4_Dialogue2:
         MainGame_State = MainGame_Chapter4_WaitOff2;
         break;      
      case MainGame_Chapter4_WaitOff2:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff2;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn2;
         }
         break;
      case MainGame_Chapter4_WaitOn2:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn2;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue3;    
         }
         break;
      case MainGame_Chapter4_Dialogue3:
         MainGame_State = MainGame_Chapter4_WaitOff3;
         break;      
      case MainGame_Chapter4_WaitOff3:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff3;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn3;
         }
         break;
      case MainGame_Chapter4_WaitOn3:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn3;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue4;    
         }
         break;
      case MainGame_Chapter4_Dialogue4:
         MainGame_State = MainGame_Chapter4_WaitOff4;
         break;      
      case MainGame_Chapter4_WaitOff4:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff4;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn4;
         }
         break;
      case MainGame_Chapter4_WaitOn4:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn4;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue5;    
         }
         break;
      case MainGame_Chapter4_Dialogue5:
         MainGame_State = MainGame_Chapter4_WaitOff5;
         break;      
      case MainGame_Chapter4_WaitOff5:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff5;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn5;
         }
         break;
      case MainGame_Chapter4_WaitOn5:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn5;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue6;    
         }
         break;
      case MainGame_Chapter4_Dialogue6:
         MainGame_State = MainGame_Chapter4_WaitOff6;
         break;      
      case MainGame_Chapter4_WaitOff6:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff6;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn6;
         }
         break;
      case MainGame_Chapter4_WaitOn6:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn6;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue7;    
         }
         break;
      case MainGame_Chapter4_Dialogue7:
         MainGame_State = MainGame_Chapter4_WaitOff7;
         break;      
      case MainGame_Chapter4_WaitOff7:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff7;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn7;
         }
         break;
      case MainGame_Chapter4_WaitOn7:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn7;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue8;    
         }
         break;
      case MainGame_Chapter4_Dialogue8:
         MainGame_State = MainGame_Chapter4_WaitOff8;
         break;      
      case MainGame_Chapter4_WaitOff8:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff8;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn8;
         }
         break;
      case MainGame_Chapter4_WaitOn8:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn8;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue9;    
         }
         break;
      case MainGame_Chapter4_Dialogue9:
         MainGame_State = MainGame_Chapter4_WaitOff9;
         break;      
      case MainGame_Chapter4_WaitOff9:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff9;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn9;
         }
         break;
      case MainGame_Chapter4_WaitOn9:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn9;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue10;    
         }
         break;
      case MainGame_Chapter4_Dialogue10:
         MainGame_State = MainGame_Chapter4_WaitOff10;
         break;      
      case MainGame_Chapter4_WaitOff10:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff10;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn10;
         }
         break;
      case MainGame_Chapter4_WaitOn10:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn10;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue11;    
         }
         break;
      case MainGame_Chapter4_Dialogue11:
         MainGame_State = MainGame_Chapter4_WaitOff11;
         break;      
      case MainGame_Chapter4_WaitOff11:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff11;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn11;
         }
         break;
      case MainGame_Chapter4_WaitOn11:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn11;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue12;    
         }
         break;
      case MainGame_Chapter4_Dialogue12:
         MainGame_State = MainGame_Chapter4_WaitOff12;
         break;      
      case MainGame_Chapter4_WaitOff12:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff12;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn12;
         }
         break;
      case MainGame_Chapter4_WaitOn12:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn12;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue13;    
         }
         break;
      case MainGame_Chapter4_Dialogue13:
         MainGame_State = MainGame_Chapter4_WaitOff13;
         break;      
      case MainGame_Chapter4_WaitOff13:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff13;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn13;
         }
         break;
      case MainGame_Chapter4_WaitOn13:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn13;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue14;    
         }
         break;
      case MainGame_Chapter4_Dialogue14:
         MainGame_State = MainGame_Chapter4_WaitOff14;
         break;      
      case MainGame_Chapter4_WaitOff14:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff14;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn14;
         }
         break;
      case MainGame_Chapter4_WaitOn14:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn14;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue15;    
         }
         break;
      case MainGame_Chapter4_Dialogue15:
         MainGame_State = MainGame_Chapter4_WaitOff15;
         break;      
      case MainGame_Chapter4_WaitOff15:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff15;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn15;
         }
         break;
      case MainGame_Chapter4_WaitOn15:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn15;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue16;    
         }
         break;
      case MainGame_Chapter4_Dialogue16:
         MainGame_State = MainGame_Chapter4_WaitOff16;
         break;      
      case MainGame_Chapter4_WaitOff16:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff16;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn16;
         }
         break;
      case MainGame_Chapter4_WaitOn16:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn16;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue17;    
         }
         break;
      case MainGame_Chapter4_Dialogue17:
         MainGame_State = MainGame_Chapter4_WaitOff17;
         break;      
      case MainGame_Chapter4_WaitOff17:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff17;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn17;
         }
         break;
      case MainGame_Chapter4_WaitOn17:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn17;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue18;    
         }
         break;
      case MainGame_Chapter4_Dialogue18:
         MainGame_State = MainGame_Chapter4_WaitOff18;
         break;      
      case MainGame_Chapter4_WaitOff18:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff18;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn18;
         }
         break;
      case MainGame_Chapter4_WaitOn18:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn18;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue19;    
         }
         break;
      case MainGame_Chapter4_Dialogue19:
         MainGame_State = MainGame_Chapter4_WaitOff19;
         break;      
      case MainGame_Chapter4_WaitOff19:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff19;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn19;
         }
         break;
      case MainGame_Chapter4_WaitOn19:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn19;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue20;    
         }
         break;
      case MainGame_Chapter4_Dialogue20:
         MainGame_State = MainGame_Chapter4_WaitOff20;
         break;      
      case MainGame_Chapter4_WaitOff20:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff20;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn20;
         }
         break;
      case MainGame_Chapter4_WaitOn20:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn20;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue21;    
         }
         break;
      case MainGame_Chapter4_Dialogue21:
         MainGame_State = MainGame_Chapter4_WaitOff21;
         break;      
      case MainGame_Chapter4_WaitOff21:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff21;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn21;
         }
         break;
      case MainGame_Chapter4_WaitOn21:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn21;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue22;    
         }
         break;
      case MainGame_Chapter4_Dialogue22:
         MainGame_State = MainGame_Chapter4_WaitOff22;
         break;      
      case MainGame_Chapter4_WaitOff22:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff22;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn22;
         }
         break;
      case MainGame_Chapter4_WaitOn22:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn22;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue23;    
         }
         break;
      case MainGame_Chapter4_Dialogue23:
         MainGame_State = MainGame_Chapter4_WaitOff23;
         break;      
      case MainGame_Chapter4_WaitOff23:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff23;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn23;
         }
         break;
      case MainGame_Chapter4_WaitOn23:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn23;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue24;    
         }
         break;
      case MainGame_Chapter4_Dialogue24:
         MainGame_State = MainGame_Chapter4_WaitOff24;
         break;      
      case MainGame_Chapter4_WaitOff24:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff24;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn24;
         }
         break;
      case MainGame_Chapter4_WaitOn24:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn24;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue25;    
         }
         break;
      case MainGame_Chapter4_Dialogue25:
         MainGame_State = MainGame_Chapter4_WaitOff25;
         break;      
      case MainGame_Chapter4_WaitOff25:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff25;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn25;
         }
         break;
      case MainGame_Chapter4_WaitOn25:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn25;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue26;    
         }
         break;
      case MainGame_Chapter4_Dialogue26:
         MainGame_State = MainGame_Chapter4_WaitOff26;
         break;      
      case MainGame_Chapter4_WaitOff26:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff26;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn26;
         }
         break;
      case MainGame_Chapter4_WaitOn26:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn26;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue27;    
         }
         break;
      case MainGame_Chapter4_Dialogue27:
         MainGame_State = MainGame_Chapter4_WaitOff27;
         break;      
      case MainGame_Chapter4_WaitOff27:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff27;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn27;
         }
         break;
      case MainGame_Chapter4_WaitOn27:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn27;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue28;    
         }
         break;
      case MainGame_Chapter4_Dialogue28:
         MainGame_State = MainGame_Chapter4_WaitOff28;
         break;      
      case MainGame_Chapter4_WaitOff28:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff28;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn28;
         }
         break;
      case MainGame_Chapter4_WaitOn28:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn28;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue29;    
         }
         break;
      case MainGame_Chapter4_Dialogue29:
         MainGame_State = MainGame_Chapter4_WaitOff29;
         break;      
      case MainGame_Chapter4_WaitOff29:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff29;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn29;
         }
         break;
      case MainGame_Chapter4_WaitOn29:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn29;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue30;    
         }
         break;
      case MainGame_Chapter4_Dialogue30:
         MainGame_State = MainGame_Chapter4_WaitOff30;
         break;      
      case MainGame_Chapter4_WaitOff30:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff30;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn30;
         }
         break;
      case MainGame_Chapter4_WaitOn30:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn30;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue31;    
         }
         break;
      case MainGame_Chapter4_Dialogue31:
         MainGame_State = MainGame_Chapter4_WaitOff31;
         break;      
      case MainGame_Chapter4_WaitOff31:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff31;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn31;
         }
         break;
      case MainGame_Chapter4_WaitOn31:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn31;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue32;    
         }
         break;
      case MainGame_Chapter4_Dialogue32:
         MainGame_State = MainGame_Chapter4_WaitOff32;
         break;      
      case MainGame_Chapter4_WaitOff32:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff32;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn32;
         }
         break;
      case MainGame_Chapter4_WaitOn32:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn32;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue33;    
         }
         break;
      case MainGame_Chapter4_Dialogue33:
         MainGame_State = MainGame_Chapter4_WaitOff33;
         break;      
      case MainGame_Chapter4_WaitOff33:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff33;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn33;
         }
         break;
      case MainGame_Chapter4_WaitOn33:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn33;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue34;    
         }
         break;
      case MainGame_Chapter4_Dialogue34:
         MainGame_State = MainGame_Chapter4_WaitOff34;
         break;      
      case MainGame_Chapter4_WaitOff34:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff34;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn34;
         }
         break;
      case MainGame_Chapter4_WaitOn34:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn34;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue35;    
         }
         break;
      case MainGame_Chapter4_Dialogue35:
         MainGame_State = MainGame_Chapter4_WaitOff35;
         break;      
      case MainGame_Chapter4_WaitOff35:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff35;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn35;
         }
         break;
      case MainGame_Chapter4_WaitOn35:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn35;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue36;    
         }
         break;
      case MainGame_Chapter4_Dialogue36:
         MainGame_State = MainGame_Chapter4_WaitOff36;
         break;      
      case MainGame_Chapter4_WaitOff36:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff36;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn36;
         }
         break;
      case MainGame_Chapter4_WaitOn36:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn36;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue37;    
         }
         break;
      case MainGame_Chapter4_Dialogue37:
         MainGame_State = MainGame_Chapter4_WaitOff37;
         break;      
      case MainGame_Chapter4_WaitOff37:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff37;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn37;
         }
         break;
      case MainGame_Chapter4_WaitOn37:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn37;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue38;    
         }
         break;
      case MainGame_Chapter4_Dialogue38:
         MainGame_State = MainGame_Chapter4_WaitOff38;
         break;      
      case MainGame_Chapter4_WaitOff38:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff38;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn38;
         }
         break;
      case MainGame_Chapter4_WaitOn38:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn38;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue39;    
         }
         break;
      case MainGame_Chapter4_Dialogue39:
         MainGame_State = MainGame_Chapter4_WaitOff39;
         break;      
      case MainGame_Chapter4_WaitOff39:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff39;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn39;
         }
         break;
      case MainGame_Chapter4_WaitOn39:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn39;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue40;    
         }
         break;
      case MainGame_Chapter4_Dialogue40:
         MainGame_State = MainGame_Chapter4_WaitOff40;
         break;      
      case MainGame_Chapter4_WaitOff40:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff40;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn40;
         }
         break;
      case MainGame_Chapter4_WaitOn40:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn40;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue41;    
         }
         break;
      case MainGame_Chapter4_Dialogue41:
         MainGame_State = MainGame_Chapter4_WaitOff41;
         break;      
      case MainGame_Chapter4_WaitOff41:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff41;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn41;
         }
         break;
      case MainGame_Chapter4_WaitOn41:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn41;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue42;    
         }
         break;
      case MainGame_Chapter4_Dialogue42:
         MainGame_State = MainGame_Chapter4_WaitOff42;
         break;      
      case MainGame_Chapter4_WaitOff42:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff42;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn42;
         }
         break;
      case MainGame_Chapter4_WaitOn42:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn42;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue43;    
         }
         break;
      case MainGame_Chapter4_Dialogue43:
         MainGame_State = MainGame_Chapter4_WaitOff43;
         break;      
      case MainGame_Chapter4_WaitOff43:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff43;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn43;
         }
         break;
      case MainGame_Chapter4_WaitOn43:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn43;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue44;    
         }
         break;
      case MainGame_Chapter4_Dialogue44:
         MainGame_State = MainGame_Chapter4_WaitOff44;
         break;      
      case MainGame_Chapter4_WaitOff44:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff44;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn44;
         }
         break;
      case MainGame_Chapter4_WaitOn44:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn44;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue45;    
         }
         break;
      case MainGame_Chapter4_Dialogue45:
         MainGame_State = MainGame_Chapter4_WaitOff45;
         break;      
      case MainGame_Chapter4_WaitOff45:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff45;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn45;
         }
         break;
      case MainGame_Chapter4_WaitOn45:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn45;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue46;    
         }
         break;
      case MainGame_Chapter4_Dialogue46:
         MainGame_State = MainGame_Chapter4_WaitOff46;
         break;      
      case MainGame_Chapter4_WaitOff46:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff46;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn46;
         }
         break;
      case MainGame_Chapter4_WaitOn46:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn46;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue47;    
         }
         break;
      case MainGame_Chapter4_Dialogue47:
         MainGame_State = MainGame_Chapter4_WaitOff47;
         break;      
      case MainGame_Chapter4_WaitOff47:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff47;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn47;
         }
         break;
      case MainGame_Chapter4_WaitOn47:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn47;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue48;    
         }
         break;
      case MainGame_Chapter4_Dialogue48:
         MainGame_State = MainGame_Chapter4_WaitOff48;
         break;      
      case MainGame_Chapter4_WaitOff48:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff48;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn48;
         }
         break;
      case MainGame_Chapter4_WaitOn48:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn48;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue49;    
         }
         break;
      case MainGame_Chapter4_Dialogue49:
         MainGame_State = MainGame_Chapter4_WaitOff49;
         break;      
      case MainGame_Chapter4_WaitOff49:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff49;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn49;
         }
         break;
      case MainGame_Chapter4_WaitOn49:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn49;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue50;    
         }
         break;
      case MainGame_Chapter4_Dialogue50:
         MainGame_State = MainGame_Chapter4_WaitOff50;
         break;      
      case MainGame_Chapter4_WaitOff50:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff50;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn50;
         }
         break;
      case MainGame_Chapter4_WaitOn50:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn50;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue51;    
         }
         break;
      case MainGame_Chapter4_Dialogue51:
         MainGame_State = MainGame_Chapter4_WaitOff51;
         break;      
      case MainGame_Chapter4_WaitOff51:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff51;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn51;
         }
         break;
      case MainGame_Chapter4_WaitOn51:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn51;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue52;    
         }
         break;
      case MainGame_Chapter4_Dialogue52:
         MainGame_State = MainGame_Chapter4_WaitOff52;
         break;      
      case MainGame_Chapter4_WaitOff52:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff52;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn52;
         }
         break;
      case MainGame_Chapter4_WaitOn52:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn52;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue53;    
         }
         break;
      case MainGame_Chapter4_Dialogue53:
         MainGame_State = MainGame_Chapter4_WaitOff53;
         break;      
      case MainGame_Chapter4_WaitOff53:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff53;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn53;
         }
         break;
      case MainGame_Chapter4_WaitOn53:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn53;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue54;    
         }
         break;
      case MainGame_Chapter4_Dialogue54:
         MainGame_State = MainGame_Chapter4_WaitOff54;
         break;      
      case MainGame_Chapter4_WaitOff54:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff54;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn54;
         }
         break;
      case MainGame_Chapter4_WaitOn54:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn54;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue55;    
         }
         break;
      case MainGame_Chapter4_Dialogue55:
         MainGame_State = MainGame_Chapter4_WaitOff55;
         break;      
      case MainGame_Chapter4_WaitOff55:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff55;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn55;
         }
         break;
      case MainGame_Chapter4_WaitOn55:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn55;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue56;    
         }
         break;
      case MainGame_Chapter4_Dialogue56:
         MainGame_State = MainGame_Chapter4_WaitOff56;
         break;      
      case MainGame_Chapter4_WaitOff56:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff56;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn56;
         }
         break;
      case MainGame_Chapter4_WaitOn56:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn56;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_Dialogue57;    
         }
         break;
      case MainGame_Chapter4_Dialogue57:
         MainGame_State = MainGame_Chapter4_WaitOff57;
         break;      
      case MainGame_Chapter4_WaitOff57:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff57;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn57;
         }
         break;
      case MainGame_Chapter4_WaitOn57:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn57;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter4_WaitOn57;    
         }
         break;
      case MainGame_Chapter4_Dialogue58:
         MainGame_State = MainGame_Chapter4_WaitOff58;
         break;      
      case MainGame_Chapter4_WaitOff58:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1){
            MainGame_State = MainGame_Chapter4_WaitOff58;    
         }
         else if(A0 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_Chapter4_WaitOn58;
         }
         break;
      case MainGame_Chapter4_WaitOn58:
         if(A0 == 0){
            MainGame_State = MainGame_Chapter4_WaitOn58;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter1_Dialogue0;    
         }
         break;
      case MainGame_GameOver_Init:
         MainGame_State = MainGame_GameOver;
         break;
      case MainGame_GameOver:
         MainGame_State = MainGame_GameOver_WaitOff;
         break;      
      case MainGame_GameOver_WaitOff:
         //display_lives = 0;
         //trigger_life_loss = 0;
         //display_lives = 1;
         if(A0 == 1 || A1 == 1 || A2 == 1){
            MainGame_State = MainGame_GameOver_WaitOff;    
         }
         else if(A0 == 0 && A1 == 0 && A2 == 0){
            //printf("Off\n");
            MainGame_State = MainGame_GameOver_WaitOn;
         }
         break;
      case MainGame_GameOver_WaitOn:
         if(A0 == 0){
            MainGame_State = MainGame_GameOver_WaitOn;     
         }
         else if(A0 == 1){
            //printf("On\n");
            MainGame_State = MainGame_Chapter1_Dialogue0;    
         }
         break;
      default:
         break;
   }
   
   switch(MainGame_State){ //State actions
      case MainGame_SMStart:
         break;
      case MainGame_Menu1:
         printf("Welcome to Jeff Dating Sim Part 2! :D\n\n");
         
         printf("In this game, every single choice matters\n");
         printf("If you make 3 wrong choices, the game will end\n");
         printf("and you must start over. Ready to play?\n\n");

         printf("Synopsis: You started dating your girlfriend Jeffrey McDaniel over a month ago and your relationship has been going well. However, you both got isekai'd into another world and lost each other's memories. You, Jeffrey, and many others now had to fight the Demon King along with his subordinates in order to escape the world you were transported to and find love once again. Will you be able to win? Find out today!\n\n");
         
         printf("Select an option to start the game\n\n");
         printf("A0 - Start game from beginning\n");
         printf("A3 - Select a chapter\n");
         break;
      case MainGame_Menu2:
         //printf("here2\n");
         break;
      case MainGame_Chapter1_Dialogue0:
         printf("\n\n");
         printf("Chapter 1 - Slice of life with your girlfriend Jeffrey McDaniel\n\n");
         printf("You are on the phone with your girlfriend.\n");
         printf("Jeff: \"Hey babe! I wanted to check up on you and see how you were doing!\"\n");
         break;
      case MainGame_Chapter1_WaitOff0:
         break;
      case MainGame_Chapter1_WaitOn0:
         break;
      case MainGame_Chapter1_Dialogue1:
         printf("\n\n");
         printf("You: \"Thanks for calling! I had a pretty stressful day to be honest.\"\n");
         break;
      case MainGame_Chapter1_WaitOff1:
         break;
      case MainGame_Chapter1_WaitOn1:
         break;
      case MainGame_Chapter1_Dialogue2:
         printf("\n\n");
         printf("Jeff: \"Aww I'm sorry to hear that! I wanna tell you how proud I am of you. You've been working very hard. You deserve a break.\"\n");
         break;
      case MainGame_Chapter1_WaitOff2:
         break;
      case MainGame_Chapter1_WaitOn2:
         break;
      case MainGame_Chapter1_Dialogue3:
         printf("\n\n");
         printf("Jeff: \"Why don't we go eat lunch on the school rooftop like people do in anime?\"\n");
         break;
      case MainGame_Chapter1_WaitOff3:
         break;
      case MainGame_Chapter1_WaitOn3:
         break;
      case MainGame_Chapter1_Dialogue4:
         printf("\n\n");
         printf("Select a dialogue choice below: \n\n");
         printf("A1: \"Lol you're desperate\"\n");
         printf("A2: \"Sure! I'll call you when I'm free\"\n");
         break;
      case MainGame_Chapter1_WaitOff4:
         break;
      case MainGame_Chapter1_WaitOn4:
         break;
      case MainGame_Chapter1_Dialogue5a:
         printf("\n\n");
         printf("You: \"Lol you're desperate\"");
         break;
      case MainGame_Chapter1_WaitOff5a:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn5a:
         break;
      case MainGame_Chapter1_Dialogue5b:
         printf("\n\n");
         printf("Jeff: \"Eh? What do you mean? :(\"");
         break;
      case MainGame_Chapter1_WaitOff5b:
         display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn5b:
         break;
      case MainGame_Chapter1_Dialogue5c:
         printf("\n\n");
         printf("You: \"You want me so bad that you just had to call me and ask for lunch out of the blue lol\"");
         break;
      case MainGame_Chapter1_WaitOff5c:
         break;
      case MainGame_Chapter1_WaitOn5c:
         break;
      case MainGame_Chapter1_Dialogue5d:
         printf("\n\n");
         printf("Jeff: \"Is there something wrong with that? :(\"");
         break;
      case MainGame_Chapter1_WaitOff5d:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn5d:
         break;
      case MainGame_Chapter1_Dialogue5e:
         printf("\n\n");
         printf("You: \"No I'm just teasing you lol\"");
         break;
      case MainGame_Chapter1_WaitOff5e:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn5e:
         break;
       case MainGame_Chapter1_Dialogue5f:
         printf("\n\n");
         printf("Jeff: \"Okay but that sounded really mean :(\"");
         break;
      case MainGame_Chapter1_WaitOff5f:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn5f:
         break; 
       case MainGame_Chapter1_Dialogue5g:
         printf("\n\n");
         printf("You: (Oops...)");
         break;
      case MainGame_Chapter1_WaitOff5g:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn5g:
         break;   
      case MainGame_Chapter1_Dialogue6a:
         printf("\n\n");
         printf("You: \"Sure! I'll call you when I'm free\"");
         break;
      case MainGame_Chapter1_WaitOff6a:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn6a:
         break;
      case MainGame_Chapter1_Dialogue6b:
         printf("\n\n");
         printf("Jeff: \"Awesome! Can't wait to see you later. I love you! :D\"");
         break;
      case MainGame_Chapter1_WaitOff6b:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn6b:
         break;
      case MainGame_Chapter1_Dialogue6c:
         printf("\n\n");
         printf("You: \"I love you too! :D\"");
         break;
      case MainGame_Chapter1_WaitOff6c:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn6c:
         break;
      case MainGame_Chapter1_Dialogue6d:
         printf("\n\n");
         printf("Jeff: \"Btw I have a surprise for you!\"");
         break;
      case MainGame_Chapter1_WaitOff6d:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn6d:
         break;
      case MainGame_Chapter1_Dialogue6e:
         printf("\n\n");
         printf("You: \"Really now? :o Well it's not gonna be a surprise if you tell me :p\"");
         break;
      case MainGame_Chapter1_WaitOff6e:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn6e:
         break;
      case MainGame_Chapter1_Dialogue6f:
         printf("\n\n");
         printf("Jeff: \"I'm not gonna tell you obviously :p\"");
         break;
      case MainGame_Chapter1_WaitOff6f:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn6f:
         break;
      case MainGame_Chapter1_Dialogue6g:
         printf("\n\n");
         printf("You: \"I know. I can't wait to see it! :D\"\n");
         printf("You and Jeff hang up after saying I love you again.");
         break;
      case MainGame_Chapter1_WaitOff6g:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn6g:
         break;
      case MainGame_Chapter1_Dialogue7:
         printf("\n\n");
         printf("After finishing up your work, you head towards the rooftop as promised.\n");
         break;
      case MainGame_Chapter1_WaitOff7:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn7:
         break;
      case MainGame_Chapter1_Dialogue8:
         printf("\n\n");
         printf("However, in the corner of your eye, it seemed like the sky was turning purple and going back to blue. \n");
         break;
      case MainGame_Chapter1_WaitOff8:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn8:
         break;
      case MainGame_Chapter1_Dialogue9:
         printf("\n\n");
         printf("You: (Wait what?... I'm probably just really exhausted lol)\n");
         break;
      case MainGame_Chapter1_WaitOff9:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn9:
         break;
      case MainGame_Chapter1_Dialogue10:
         printf("\n\n");
         printf("You reached the rooftop and see Jeffrey McDaniel, your lovely girlfriend, in all her glory and splendor. And also the wind is blowing her hair quite visibly for dramatic effect like in anime. Y'know what I'm sayin?\n");
         break;
      case MainGame_Chapter1_WaitOff10:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn10:
         break;
      case MainGame_Chapter1_Dialogue11:
         printf("\n\n");
         printf("You look at the bag of goodies your girlfriend is holding.\n");
         printf("You:\"Whatchu got there?\"\n");
         break;
      case MainGame_Chapter1_WaitOff11:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn11:
         break;
      case MainGame_Chapter1_Dialogue12:
         printf("\n\n");
         printf("Jeff:\"A smoothie :p\"\n");
         break;
      case MainGame_Chapter1_WaitOff12:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn12:
         break;
      case MainGame_Chapter1_Dialogue13:
         printf("\n\n");
         printf("You:\"Lol you're very funny :p but seriously what did you bring?\"\n");
         break;
      case MainGame_Chapter1_WaitOff13:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn13:
         break;
      case MainGame_Chapter1_Dialogue14:
         printf("\n\n");
         printf("Jeff:\"I made you your favorite meal that your grandma makes!\"\n");
         break;
      case MainGame_Chapter1_WaitOff14:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn14:
         break;
      case MainGame_Chapter1_Dialogue15:
         printf("\n\n");
         printf("Select a dialogue choice below: \n\n");
         printf("A1: \"Thank you! That's really sweet and thoughtful of you. :)\"\n");
         printf("A2: \"Lol no one can ever cook like grandma\"\n");
         break;
      case MainGame_Chapter1_WaitOff15:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn15:
         break;
      case MainGame_Chapter1_Dialogue16a:
         printf("\n\n");
         printf("You: \"Thank you! That's really sweet and thoughtful of you. :)\"");
         break;
      case MainGame_Chapter1_WaitOff16a:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn16a:
         break;
      case MainGame_Chapter1_Dialogue16b:
         printf("\n\n");
         printf("You: \"Thank you! That's really sweet and thoughtful of you. :)\"");
         break;
      case MainGame_Chapter1_WaitOff16b:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn16b:
         break;
      case MainGame_Chapter1_Dialogue16c:
         printf("\n\n");
         printf("Jeff: \"Of course! I'm really glad I met her. She's literally the sweetest person ever.\"");
         break;
      case MainGame_Chapter1_WaitOff16c:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn16c:
         break;
      case MainGame_Chapter1_Dialogue16d:
         printf("\n\n");
         printf("You: \"It means a lot to me hearing that from you. :) I'm glad we could spend our first month together here too. I hope for many more moments like this with my amazing girlfriend.\"");
         break;
      case MainGame_Chapter1_WaitOff16d:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn16d:
         break;
      case MainGame_Chapter1_Dialogue16e:
         printf("\n\n");
         printf("Jeff: \"Aww you're so sweet! :) You make me feel like the happiest girl alive.\"");
         break;
      case MainGame_Chapter1_WaitOff16e:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn16e:
         break;
      case MainGame_Chapter1_Dialogue16f:
         printf("\n\n");
         printf("You: \"Haha I know :p\"");
         break;
      case MainGame_Chapter1_WaitOff16f:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn16f:
         break;
      case MainGame_Chapter1_Dialogue17a:
         printf("\n\n");
         printf("You: \"Lol no one can ever cook like grandma\"");
         break;
      case MainGame_Chapter1_WaitOff17a:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn17a:
         break;
      case MainGame_Chapter1_Dialogue17b:
         printf("\n\n");
      
         printf("Jeff: \"I mean... I know that but I was hoping I could make you happy by reminding you of her in my own way. :(\"");
         break;
      case MainGame_Chapter1_WaitOff17b:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn17b:
         break;
      case MainGame_Chapter1_Dialogue17c:
         printf("\n\n");
      
         printf("You: \"Well I'm just stating the facts. It's not like I'm saying I don't appreciate what you did.\"");
         break;
      case MainGame_Chapter1_WaitOff17c:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn17c:
         break;
      case MainGame_Chapter1_Dialogue17d:
         printf("\n\n");
      
         printf("Jeff: \"Okay but still. What you're saying is really hurtful. :(\"");
         break;
      case MainGame_Chapter1_WaitOff17d:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn17d:
         break;
      case MainGame_Chapter1_Dialogue17e:
         printf("\n\n");
      
         printf("You: \"Oh... I'm sorry babe :(\"");
         break;
      case MainGame_Chapter1_WaitOff17e:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn17e:
         break;
      case MainGame_Chapter1_Dialogue17f:
         printf("\n\n");
      
         printf("Jeff only nods silently");
         break;
      case MainGame_Chapter1_WaitOff17f:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn17f:
         break;
      case MainGame_Chapter1_Dialogue18:
         printf("\n\n");
      
         printf("After eating your girlfriend's cooking, you notice that the sky has definitely turned purple. Even she notices too.");
         printf("You: (So I wasn't hallucinating!)");
         break;
      case MainGame_Chapter1_WaitOff18:
         //display_lives = 0;
         break;
      case MainGame_Chapter1_WaitOn18:
         break;
      case MainGame_Chapter1_Dialogue19:
         printf("\n\n");
      
         printf("Jeff:\"Eh?! What's going on?!\"");
         break;
      case MainGame_Chapter1_WaitOff19:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn19:
         break;
      case MainGame_Chapter1_Dialogue20:
         printf("\n\n");
      
         printf("You both look up and see a huge floating silhouette, arms outscretched. It was hard to tell if it was a ghost or a person.");
         break;
      case MainGame_Chapter1_WaitOff20:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn20:
         break;
      case MainGame_Chapter1_Dialogue21:
         printf("\n\n");
      
         printf("Floating silhouette: \"🥺😊😡😂😒\"");
         break;
      case MainGame_Chapter1_WaitOff21:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn21:
         break;
      case MainGame_Chapter1_Dialogue22:
         printf("\n\n");
      
         printf("You: \"I did not understand a word you just said bro.\"");
         break;
      case MainGame_Chapter1_WaitOff22:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn22:
         break;
      case MainGame_Chapter1_Dialogue23:
         printf("\n\n");
      
         printf("Suddenly you saw a bright flashing light and covered your eyes while instinctively hugging your girlfriend.\n");
         break;
      case MainGame_Chapter1_WaitOff23:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn23:
         break;
      case MainGame_Chapter1_Dialogue24:
         printf("\n\n");
      
         printf("When you opened your eyes again, you found yourself in another world. As in transported to another world. It was still UCR but everything looked darker and there was no one else.\n");
         break;
      case MainGame_Chapter1_WaitOff24:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn24:
         break;
      case MainGame_Chapter1_Dialogue25:
         printf("\n\n");
      
         printf("Even worse, it seemed like you remembered absolutely nothing except that you went to this school.");
         break;
      case MainGame_Chapter1_WaitOff25:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn25:
         break;
      case MainGame_Chapter1_Dialogue26:
         printf("\n\n");
      
         printf("You: \"What happened? Is anyone here?! I.. I need help!\"");
         break;
      case MainGame_Chapter1_WaitOff26:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn26:
         break;
      case MainGame_Chapter1_Dialogue27:
         printf("\n\n");
      
         printf("That was an understatement. You felt completely lost.");
         break;
      case MainGame_Chapter1_WaitOff27:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn27:
         break;
      case MainGame_Chapter1_Dialogue28:
         printf("\n\n");
      
         printf("Unknown voice:\"Boo!\"");
         break;
      case MainGame_Chapter1_WaitOff28:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn28:
         break;
      case MainGame_Chapter1_Dialogue29:
         printf("\n\n");
      
         printf("You:\"Gah! What was that for?\"");
         break;
      case MainGame_Chapter1_WaitOff29:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn29:
         break;
      case MainGame_Chapter1_Dialogue30:
         printf("\n\n");
      
         printf("Pai:\"Sorry I couldn't help it! xD Btw, my name is Pai. I'm here to help you navigate this world.\"");
         break;
      case MainGame_Chapter1_WaitOff30:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn30:
         break;
      case MainGame_Chapter1_Dialogue31:
         printf("\n\n");
      
         printf("You:\"Okay umm... where am I first of all?\"");
         break;
      case MainGame_Chapter1_WaitOff31:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn31:
         break;
      case MainGame_Chapter1_Dialogue32:
         printf("\n\n");
      
         printf("Pai:\"You're in the shadow realm of UCR! You've been transported here along with a couple other people to help defeat the Demon King\"");
         break;
      case MainGame_Chapter1_WaitOff32:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn32:
         break;
      case MainGame_Chapter1_Dialogue33:
         printf("\n\n");
      
         printf("You:\"Seriously?! This sounds like a very badly written isekai.\"");
         break;
      case MainGame_Chapter1_WaitOff33:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn33:
         break;
      case MainGame_Chapter1_Dialogue34:
         printf("\n\n");
      
         printf("Pai:\"Not really! You didn't get run over by a truck! :D\"");
         break;
      case MainGame_Chapter1_WaitOff34:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn34:
         break;
      case MainGame_Chapter1_Dialogue35:
         printf("\n\n");
      
         printf("You:\"Not the point... But anyways, how do I get out of here?\"");
         break;
      case MainGame_Chapter1_WaitOff35:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn35:
         break;
      case MainGame_Chapter1_Dialogue36:
         printf("\n\n");
      
         printf("Pai:\"You need to level up your magic powers by building an emotional connection with the people who got transported here. The more you improve your relationships with them, the stronger your magic becomes then you'll have the power you need to defeat the Demon King!\"");
         break;
      case MainGame_Chapter1_WaitOff36:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn36:
         break;
      case MainGame_Chapter1_Dialogue37:
         printf("\n\n");
      
         printf("You:\"Interesting. This isekai is built different...\"");
         break;
      case MainGame_Chapter1_WaitOff37:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn37:
         break;
      case MainGame_Chapter1_Dialogue38:
         printf("\n\n");
      
         printf("Pai:\"I have absolutely no idea what you mean by that but seems like you don't have any questions. Good luck btw! The Demon King won't show up until you've gathered enough magic power so you have plenty of time to train by defeating the Demon King's subordinates and by emotionally connecting with people here!\"");
         break;
      case MainGame_Chapter1_WaitOff38:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn38:
         break;
      case MainGame_Chapter1_Dialogue39:
         printf("\n\n");
      
         printf("You:\"Thanks emergency food!\"");
         break;
      case MainGame_Chapter1_WaitOff39:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn39:
         break;
      case MainGame_Chapter1_Dialogue40:
         printf("\n\n");
      
         printf("Pai:\"Hey you can't just make video game references like that!\"");
         break;
      case MainGame_Chapter1_WaitOff40:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn40:
         break;
      case MainGame_Chapter1_Dialogue41:
         printf("\n\n");
      
         printf("You: (What an interesting way to start my day. I got isekai'd into the shadow dimension of my university with no memories of the people I've met here. And I have a little creature who looks like she belongs in a popular video game to help me on this journey to defeat the Demon King or whatever. And the only way I can be powerful enough to defeat the Demon King is by emotionally connecting with people I meet in this world. So... romancing? Awesome. Absolutely awesome. I'm being sarcastic btw.)");
         break;
      case MainGame_Chapter1_WaitOff41:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn41:
         break;
      case MainGame_Chapter1_Dialogue42:
         printf("\n\n");
      
         printf("End of chapter 1");
         break;
      case MainGame_Chapter1_WaitOff42:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter1_WaitOn42:
         break;
      case MainGame_Chapter2_Dialogue0:
         printf("\n\n");
      
         printf("Chapter 2 - The power of love\n\n");
         printf("Unknown voice 2: \"You're finally awake!\"");
         break;
      case MainGame_Chapter2_WaitOff0:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn0:
         break;
      case MainGame_Chapter2_Dialogue1:
         printf("\n\n");
      
         printf("You: \"Wait a minute!!...\"\n");
         printf("You find yourself lying on a couch at the HUB\n");
         printf("You: \"Oh...\"");
         break;
      case MainGame_Chapter2_WaitOff1:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn1:
         break;
      case MainGame_Chapter2_Dialogue2:
         printf("\n\n");
      
         printf("Unknown voice 2: \"Apologies. I did not mean to startle you mate.\"");
         break;
      case MainGame_Chapter2_WaitOff2:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn2:
         break;
      case MainGame_Chapter2_Dialogue3:
         printf("\n\n");
      
         printf("Brian: \"I'm Brian Linard btw.\"");
         break;
      case MainGame_Chapter2_WaitOff3:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn3:
         break;
      case MainGame_Chapter2_Dialogue4:
         printf("\n\n");
      
         printf("You: \"Nice to meet you!\"");
         break;
      case MainGame_Chapter2_WaitOff4:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn4:
         break;
      case MainGame_Chapter2_Dialogue5:
         printf("\n\n");
      
         printf("Brian: \"Likewise!\"");
         break;
      case MainGame_Chapter2_WaitOff5:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn5:
         break; 
      case MainGame_Chapter2_Dialogue6:
         printf("\n\n");
      
         printf("You: \"So I got transported to the shadow realm a few hours ago. All I know is that we're supposed to defeat the Demon King using magic so that we can get out of here, along with whoever is stuck here presumably. Any luck finding him?\"");
         break;
      case MainGame_Chapter2_WaitOff6:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn6:
         break;  
      case MainGame_Chapter2_Dialogue7:
         printf("\n\n");
      
         printf("Brian: \"We're getting somewhere I suppose... I've met the Demon King a couple of times after dealing a great number on his subordinates. It seems that we attract the Demon King whenever we defeat some of his army.\"");
         break;
      case MainGame_Chapter2_WaitOff7:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn7:
         break;
      case MainGame_Chapter2_Dialogue8:
         printf("\n\n");
      
         printf("Brian: \"Now of course we can't face too many at once since our magic wouldn't be strong enough and there's no way we can level it up.\"");
         break;
      case MainGame_Chapter2_WaitOff8:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn8:
         break;
      case MainGame_Chapter2_Dialogue9:
         printf("\n\n");
      
         printf("You: \"Wait! Actually there is a way to level up our magic! Someone told me! What we have to do is- Agh!\"\n");
         printf("You felt someone gripping your heart really hard.\n");
         printf("You: (What?! I can't tell her what Pai told me?! Great... This is an anime reference I was hoping wouldn't be true in this isekai.)");
         break;
      case MainGame_Chapter2_WaitOff9:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn9:
         break;
      case MainGame_Chapter2_Dialogue10:
         printf("\n\n");
      
         printf("Brian: \"You good mate?\"");
         break;
      case MainGame_Chapter2_WaitOff10:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn10:
         break;
      case MainGame_Chapter2_Dialogue11:
         printf("\n\n");
      
         printf("Brian got interrupted by the Demon King's subordinates. They all materialized outside the HUB and are now breaking in.");
         break;
      case MainGame_Chapter2_WaitOff11:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn11:
         break;
      case MainGame_Chapter2_Dialogue12:
         printf("\n\n");
      
         printf("Brian chugged fireballs onto them, frying them so well that it reminded you of the steak you had at the Outback Steakhouse. Ah yes steak...");
         break;
      case MainGame_Chapter2_WaitOff12:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn12:
         break;
      case MainGame_Chapter2_Dialogue13:
         printf("\n\n");
      
         printf("You: (Sweet! I wonder what kind of magic I have.)");
         break;
      case MainGame_Chapter2_WaitOff13:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn13:
         break;
      case MainGame_Chapter2_Dialogue14:
         printf("\n\n");
      
         printf("Since you didn't know what your magic was, you played around with your hands, making physics hand signs, gang signs, anything..");
         break;
      case MainGame_Chapter2_WaitOff14:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn14:
         break;
      case MainGame_Chapter2_Dialogue15:
         printf("\n\n");
      
         printf("Then after that, you shot electricity towards the Demon King's subordinates after pointing two fingers at them");
         break;
      case MainGame_Chapter2_WaitOff15:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn15:
         break;
      case MainGame_Chapter2_Dialogue16:
         printf("\n\n");
      
         printf("After fighting for a couple more minutes, you and Brian finally got rid of them all");
         break;
      case MainGame_Chapter2_WaitOff16:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn16:
         break;
      case MainGame_Chapter2_Dialogue17:
         printf("\n\n");
      
         printf("After that, you sat on the ground and looked up towards the ceiling");
         break;
      case MainGame_Chapter2_WaitOff17:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn17:
         break;
      case MainGame_Chapter2_Dialogue18:
         printf("\n\n");
      
         printf("Brian: \"Hey there. Are you feeling alright?\"");
         break;
      case MainGame_Chapter2_WaitOff18:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn18:
         break;
      case MainGame_Chapter2_Dialogue19:
         printf("\n\n");
      
         printf("Select a dialogue choice below: \n\n");
         printf("A1: (Keep your feelings to yourself)\n");
         printf("A2: (Show her how you're feeling)\n");
         break;
      case MainGame_Chapter2_WaitOff19:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn19:
         break;
      case MainGame_Chapter2_Dialogue20a:
         printf("\n\n");
      
         printf("You:\"It's nothing. I mean I've never used magic before so it's kind of a workout you know what I mean?\"");
         break;
      case MainGame_Chapter2_WaitOff20a:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn20a:
         break;
      case MainGame_Chapter2_Dialogue20b:
         printf("\n\n");
      
         printf("Brian:\"Oh. Alright. I suppose it can be hard to adjust since it seems like you've only been here today.\"");
         break;
      case MainGame_Chapter2_WaitOff20b:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn20b:
         break;
      case MainGame_Chapter2_Dialogue20c:
         printf("\n\n");
      
         printf("You:\"Yeah that sounds about right. So there's nothing to worry about. I'm fine.\"");
         break;
      case MainGame_Chapter2_WaitOff20c:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn20c:
         break;
      case MainGame_Chapter2_Dialogue20d:
         printf("\n\n");
      
         printf("Brian:\"Mmm... Well okay that's good to hear\"");
         break;
      case MainGame_Chapter2_WaitOff20d:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn20d:
         break;
      case MainGame_Chapter2_Dialogue20e:
         printf("\n\n");
      
         printf("Brian:\"Now I need you to get up. Who knows when more of his subordinates will be back?\"");
         break;
      case MainGame_Chapter2_WaitOff20e:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn20e:
         break;
      case MainGame_Chapter2_Dialogue20f:
         printf("\n\n");
      
         printf("You:\"Aight. I'll get up\"");
         break;
      case MainGame_Chapter2_WaitOff20f:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn20f:
         break;
      case MainGame_Chapter2_Dialogue21a:
         printf("\n\n");
      
         printf("You:\"To be honest I'm feeling kind of overwhelmed right now. I've lost a lot of my memories and all I remember for sure is this school. I feel like I lost someone important to me but I don't know who. And now we're suddenly in a life or death scenario with powers and circumstances I'm barely beginning to understand. It kinda feels overwhelming y'know? Makes me wanna cry.\"");
         break;
      case MainGame_Chapter2_WaitOff21a:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn21a:
         break;
      case MainGame_Chapter2_Dialogue21b:
         printf("\n\n");
      
         printf("Brian:\"Yeah I know it's a lot to take in. I'll be here to support you along the way though. We'll find a way to get out of this world and get through this together!\"");
         break;
      case MainGame_Chapter2_WaitOff21b:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn21b:
         break;
      case MainGame_Chapter2_Dialogue21c:
         printf("\n\n");
      
         printf("You:\"Thank you I really needed to hear that :). I think I feel much better now thanks to you.\"");
         break;
      case MainGame_Chapter2_WaitOff21c:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn21c:
         break;
      case MainGame_Chapter2_Dialogue21d:
         printf("\n\n");
      
         printf("Brian: \"Of course. :)\"");
         break;
      case MainGame_Chapter2_WaitOff21d:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn21d:
         break;  
      case MainGame_Chapter2_Dialogue21e:
         printf("\n\n");
         printf("Brian offers her hand.\n");     
         printf("Brian: \"Are you ready to get up?\"");
         break;
      case MainGame_Chapter2_WaitOff21e:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn21e:
         break;  
      case MainGame_Chapter2_Dialogue21f:
         printf("\n\n");
         printf("Brian offers her hand.\n");     
         printf("You: \"Yup :) I am\"");
         break;
      case MainGame_Chapter2_WaitOff21f:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn21f:
         break;  
      case MainGame_Chapter2_Dialogue22:
         printf("\n\n");
      
         printf("Brian lifts you up on your feet then she starts thinking about her next course of action.");
         break;
      case MainGame_Chapter2_WaitOff22:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn22:
         break; 
      case MainGame_Chapter2_Dialogue23:
         printf("\n\n");
      
         printf("Brian: \"Alright mate. Listen up. So I'm going to take you to my group's hideout. It's a safe place where the Demon King's soldiers never show up. And it's stacked with supplies. Then I'll head to Orbach and pick up something I'm 3D printing that'll significantly increase our chances of surviving.\"");
         break;
      case MainGame_Chapter2_WaitOff23:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn23:
         break;  
      case MainGame_Chapter2_Dialogue24:
         printf("\n\n");
      
         printf("You: \"Will you be okay?\"");
         break;
      case MainGame_Chapter2_WaitOff24:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn24:
         break; 
      case MainGame_Chapter2_Dialogue25:
         printf("\n\n");
      
         printf("Brian: \"That's a dumb question. You should know the answer already. We've talked about this in cs10.\"");
         break;
      case MainGame_Chapter2_WaitOff25:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn25:
         break; 
      case MainGame_Chapter2_Dialogue26:
         printf("\n\n");
      
         printf("You: \"What?\"");
         break;
      case MainGame_Chapter2_WaitOff26:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn26:
         break;  
      case MainGame_Chapter2_Dialogue27:
         printf("\n\n");
      
         printf("Brian: \"I'm just messing with you lol I'll be fine! Been stuck here for a month already so I'm used to fighting off the Demon King's subordinates.\"");
         break;
      case MainGame_Chapter2_WaitOff27:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn27:
         break; 
      case MainGame_Chapter2_Dialogue28:
         printf("\n\n");
      
         printf("You follow her to Coffee Bean.");
         break;
      case MainGame_Chapter2_WaitOff28:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn28:
         break; 
      case MainGame_Chapter2_Dialogue29:
         printf("\n\n");
      
         printf("You: \"Interesting hide out!\"");
         break;
      case MainGame_Chapter2_WaitOff29:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn29:
         break; 
      case MainGame_Chapter2_Dialogue30:
         printf("\n\n");
      
         printf("Brian: \"Keeps us awake when we need it! :)\"");
         break;
      case MainGame_Chapter2_WaitOff30:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn30:
         break;
      case MainGame_Chapter2_Dialogue31:
         printf("\n\n");
      
         printf("Unknown voice 3: \"Hey gang! :D Welcome back!\"");
         break;
      case MainGame_Chapter2_WaitOff31:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn31:
         break; 
      case MainGame_Chapter2_Dialogue32:
         printf("\n\n");
      
         printf("Brian: \"Hey Frank! I'll be off to Orbach to pick up a spicy invention I'm 3D printing\"");
         break;
      case MainGame_Chapter2_WaitOff32:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn32:
         break; 
      case MainGame_Chapter2_Dialogue33:
         printf("\n\n");
      
         printf("Frank: \"Alright take care!\"");
         break;
      case MainGame_Chapter2_WaitOff33:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn33:
         break; 
      case MainGame_Chapter2_Dialogue34:
         printf("\n\n");
      
         printf("You and Frank were left alone at Coffee Bean");
         break;
      case MainGame_Chapter2_WaitOff34:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn34:
         break; 
      case MainGame_Chapter2_Dialogue35:
         printf("\n\n");
      
         printf("Frank: \"I haven't seen you around before. How long have you been stuck in the shadow realm state?\"");
         break;
      case MainGame_Chapter2_WaitOff35:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn35:
         break; 
      case MainGame_Chapter2_Dialogue36:
         printf("\n\n");
      
         printf("You explain your situation with Frank and she sees that you're definitely still at a loss since it's only been less than a day.");
         break;
      case MainGame_Chapter2_WaitOff36:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn36:
         break; 
      case MainGame_Chapter2_Dialogue37:
         printf("\n\n");
      
         printf("Frank:\"I hope you'll be able to get your memories back too!\"");
         break;
      case MainGame_Chapter2_WaitOff37:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn37:
         break; 
      case MainGame_Chapter2_Dialogue38:
         printf("\n\n");
      
         printf("You:\"I hope so too...\"");
         break;
      case MainGame_Chapter2_WaitOff38:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn38:
         break; 
      case MainGame_Chapter2_Dialogue39:
         printf("\n\n");
      
         printf("You stare off into the distance.");
         break;
      case MainGame_Chapter2_WaitOff39:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn39:
         break; 
      case MainGame_Chapter2_Dialogue40:
         printf("\n\n");
      
         printf("Frank:\"I remember back when I co-founded zyBooks with a friend of mine. The work was tough but the process was definitely fun. When we finally got it to work, we were ecstatic. :)\"");
         break;
      case MainGame_Chapter2_WaitOff40:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn40:
         break; 
      case MainGame_Chapter2_Dialogue41:
         printf("\n\n");
      
         printf("Select a dialogue choice below: \n\n");
         printf("A1: \"What made you passionate about zyBooks?\"\n");
         printf("A2: \"Oh okay. That's cool.\"\n");
         break;
      case MainGame_Chapter2_WaitOff41:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn41:
         break; 
      case MainGame_Chapter2_Dialogue42a:
         printf("\n\n");
      
         printf("You: \"What made you passionate about zyBooks?\"");
         break;
      case MainGame_Chapter2_WaitOff42a:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn42a:
         break; 
      case MainGame_Chapter2_Dialogue42b:
         printf("\n\n");
         
         printf("Frank seems very delighted that you asked that question.");      
         printf("Frank: \"I had a dream to create something that made education more engaging and interactive.\"");
         break;
      case MainGame_Chapter2_WaitOff42b:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn42b:
         break; 
      case MainGame_Chapter2_Dialogue42c:
         printf("\n\n");
   
         printf("Frank: \"I thought to myself that instead of having outdated, boring material in expensive textbooks, why not create a STEM material native for the web which uses less text and more action?\"");
         break;
      case MainGame_Chapter2_WaitOff42c:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn42c:
         break; 
      case MainGame_Chapter2_Dialogue42d:
         printf("\n\n");
   
         printf("You: \"That's really amazing! And how did it feel having zyBooks popularized for STEM majors?\"");
         break;
      case MainGame_Chapter2_WaitOff42d:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn42d:
         break; 
      case MainGame_Chapter2_Dialogue42e:
         printf("\n\n");
   
         printf("Frank: \"I felt like I did something completely amazing and seeing how on average it raised students' letter grades by 2/3, it was heartwarming.\"");
         break;
      case MainGame_Chapter2_WaitOff42e:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn42e:
         break; 
      case MainGame_Chapter2_Dialogue42f:
         printf("\n\n");
   
         printf("You couldn't help but smile at her words.");
         break;
      case MainGame_Chapter2_WaitOff42f:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn42f:
         break; 
      case MainGame_Chapter2_Dialogue43a:
         printf("\n\n");
      
         printf("You: \"Oh okay. That's cool.\"");
         break;
      case MainGame_Chapter2_WaitOff43a:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn43a:
         break; 
      case MainGame_Chapter2_Dialogue43b:
         printf("\n\n");
      
         printf("Frank: \"Yeah.\"");
         break;
      case MainGame_Chapter2_WaitOff43b:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn43b:
         break; 
      case MainGame_Chapter2_Dialogue43c:
         printf("\n\n");
      
         printf("Frank: \"It went pretty well too.\"");
         break;
      case MainGame_Chapter2_WaitOff43c:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn43c:
         break; 
      case MainGame_Chapter2_Dialogue43d:
         printf("\n\n");
      
         printf("You: \"Seems like it did.\"");
         break;
      case MainGame_Chapter2_WaitOff43d:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn43d:
         break; 
      case MainGame_Chapter2_Dialogue43e:
         printf("\n\n");
      
         printf("Frank: \"It definitely did.\"");
         break;
      case MainGame_Chapter2_WaitOff43e:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn43e:
         break; 
      case MainGame_Chapter2_Dialogue43f:
         printf("\n\n");
      
         printf("You nodded and then remained silent after.");
         break;
      case MainGame_Chapter2_WaitOff43f:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn43f:
         break; 
      case MainGame_Chapter2_Dialogue44:
         printf("\n\n");
      
         printf("Since Coffee Bean was a safe hideout, you used this time to relax and continue making conversation with Frank. You got to know her more and felt a connection as you decided to open up about yourself and your personal experience at UCR. You did the same thing as well with Brian after she came back with her new invention.");
         break;
      case MainGame_Chapter2_WaitOff44:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn44:
         break; 
      case MainGame_Chapter2_Dialogue45:
         printf("\n\n");
      
         printf("Since Coffee Bean was a safe hideout, you used this time to relax and continue making conversation with Frank. You got to know her more and felt a connection as you decided to open up about yourself and your personal experience at UCR. You did the same thing as well with Brian after she came back with her new invention.");
         break;
      case MainGame_Chapter2_WaitOff45:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn45:
         break; 
      case MainGame_Chapter2_Dialogue46:
         printf("\n\n");
      
         printf("You: \"So how does this thing work?\"");
         break;
      case MainGame_Chapter2_WaitOff46:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn46:
         break; 
      case MainGame_Chapter2_Dialogue47:
         printf("\n\n");
      
         printf("Brian: \"It uses special registers in lc3 to track people who are registered at UCR, even in different dimensions.\"");
         break;
      case MainGame_Chapter2_WaitOff47:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn47:
         break; 
      case MainGame_Chapter2_Dialogue48:
         printf("\n\n");
      
         printf("You: (Wait what?)\n");
         printf("You: \"Huh...\"");
         break;
      case MainGame_Chapter2_WaitOff48:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn48:
         break; 
      case MainGame_Chapter2_Dialogue49:
         printf("\n\n");
      
         printf("Frank: \"So who's the closest person in our vicinity?\"");
         break;
      case MainGame_Chapter2_WaitOff49:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn49:
         break; 
      case MainGame_Chapter2_Dialogue50:
         printf("\n\n");
      
         printf("Brian: \"It seems that we have a heat signature down under- I mean, the basement of Rivera library\"");
         break;
      case MainGame_Chapter2_WaitOff50:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn50:
         break; 
      case MainGame_Chapter2_Dialogue51:
         printf("\n\n");
      
         printf("You: \"Alright. Why don't we head there now? If we're all ready at least.\"");
         break;
      case MainGame_Chapter2_WaitOff51:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn51:
         break; 
      case MainGame_Chapter2_Dialogue52:
         printf("\n\n");
      
         printf("Frank: \"Sure! Alright gang! Let's head out! :D\"");
         break;
      case MainGame_Chapter2_WaitOff52:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn52:
         break; 
      case MainGame_Chapter2_Dialogue53:
         printf("\n\n");
      
         printf("But before you guys could head out, the Demon King's subordinates materialized themselves inside Coffee Bean, much to everyone's horror.");
         break;
      case MainGame_Chapter2_WaitOff53:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn53:
         break; 
      case MainGame_Chapter2_Dialogue54:
         printf("\n\n");
      
         printf("Brian: \"God save the queen!\"");
         break;
      case MainGame_Chapter2_WaitOff54:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn54:
         break; 
      case MainGame_Chapter2_Dialogue55:
         printf("\n\n");
      
         printf("Frank and Brian chugged fire balls at them. It seemed stronger than ever before and even turned their spells into flamethrowers. You shoot lightning at them and the sparks that came out of your fingers were even more intense than before. Then you all ran outside Coffee Bean and continued fighting by the tables.");
         break;
      case MainGame_Chapter2_WaitOff55:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn55:
         break; 
      case MainGame_Chapter2_Dialogue56:
         printf("\n\n");
      
         printf("You were amazed at this newfound magic power surging in your veins. Then you remembered what Pai told you about how your magic gets more powerful as you build emotional connections with people in the shadow realm. You also think about the hours you spent getting to know Frank and Brian while also opening up about yourself.");
         break;
      case MainGame_Chapter2_WaitOff56:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn56:
         break; 
      case MainGame_Chapter2_Dialogue57:
         printf("\n\n");
      
         printf("You:\"Oohh I get it now...\"");
         break;
      case MainGame_Chapter2_WaitOff57:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn57:
         break; 
      case MainGame_Chapter2_Dialogue58:
         printf("\n\n");
      
         printf("You: (Oohh I get it now...)");
         break;
      case MainGame_Chapter2_WaitOff58:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn58:
         break; 
      case MainGame_Chapter2_Dialogue59:
         printf("\n\n");
      
         printf("You kept channeling huge amounts of lightning at your foes and they all collapsed to the ground.");
         break;
      case MainGame_Chapter2_WaitOff59:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn59:
         break; 
      case MainGame_Chapter2_Dialogue60:
         printf("\n\n");
      
         printf("But instead of dematerializing, their bodies seemed to merge together until it formed into one giant demon-like mage, much to everyone's horror.");
         break;
      case MainGame_Chapter2_WaitOff60:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn60:
         break; 
      case MainGame_Chapter2_Dialogue61:
         printf("\n\n");
      
         printf("Brian: \"Even with all this new power, we still couldn't defeat it.\"");
         break;
      case MainGame_Chapter2_WaitOff61:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn61:
         break; 
      case MainGame_Chapter2_Dialogue62:
         printf("\n\n");
      
         printf("You: \"Then we'll just have to give it our all!\"");
         break;
      case MainGame_Chapter2_WaitOff62:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn62:
         break; 
      case MainGame_Chapter2_Dialogue63:
         printf("\n\n");
      
         printf("Everyone was completely focused. After putting every single ounce of strength into your magic, you attacked the demon-like mage.");
         break;
      case MainGame_Chapter2_WaitOff63:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn63:
         break; 
      case MainGame_Chapter2_Dialogue64:
         printf("\n\n");
      
         printf("And yet he still deflected it!");
         break;
      case MainGame_Chapter2_WaitOff64:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn64:
         break; 
      case MainGame_Chapter2_Dialogue65:
         printf("\n\n");
      
         printf("Frank: \"Even after all that?!\"");
         break;
      case MainGame_Chapter2_WaitOff65:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn65:
         break; 
      case MainGame_Chapter2_Dialogue66:
         printf("\n\n");
      
         printf("Then the mage shot an ice beam and froze all of you at once. And began charging up another spell as you were all frozen.");
         break;
      case MainGame_Chapter2_WaitOff66:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn66:
         break; 
      case MainGame_Chapter2_Dialogue67:
         printf("\n\n");
      
         printf("You: (This can't be it... I got isekai'd and was given magic to defeat the Demon King. We're all about to die..)");
         break;
      case MainGame_Chapter2_WaitOff67:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn67:
         break; 
      case MainGame_Chapter2_Dialogue68:
         printf("\n\n");
      
         printf("You: (But I refuse... Brian and Frank. They're amazing people. Perhaps I've grown attached to them... I don't want to lose them... I don't want to lose hope...)");
         break;
      case MainGame_Chapter2_WaitOff68:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn68:
         break; 
      case MainGame_Chapter2_Dialogue69:
         printf("\n\n");
      
         printf("You: (I want to BELIEVE!!!!)");
         break;
      case MainGame_Chapter2_WaitOff69:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn69:
         break; 
      case MainGame_Chapter2_Dialogue70:
         printf("\n\n");
      
         printf("You broke out of your ice cage and charged at the demon mage, with a huge amount of electricity glowing brightly in your fist.");
         break;
      case MainGame_Chapter2_WaitOff70:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn70:
         break; 
      case MainGame_Chapter2_Dialogue71:
         printf("\n\n");
      
         printf("You: \"HAAAAAAHHHH!!!!\"");
         break;
      case MainGame_Chapter2_WaitOff71:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn71:
         break; 
      case MainGame_Chapter2_Dialogue72:
         printf("\n\n");
      
         printf("After your fist connected to the mage's rib cage, there was a huge explosion.");
         break;
      case MainGame_Chapter2_WaitOff72:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn72:
         break; 
      case MainGame_Chapter2_Dialogue73:
         printf("\n\n");
      
         printf("Brian: \"Bruh...\"");
         break;
      case MainGame_Chapter2_WaitOff73:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn73:
         break; 
      case MainGame_Chapter2_Dialogue74:
         printf("\n\n");
      
         printf("You were panting heavily, tired but satisfied, after seeing that the demon mage was no more...");
         break;
      case MainGame_Chapter2_WaitOff74:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn74:
         break; 
      case MainGame_Chapter2_Dialogue75:
         printf("\n\n");
      
         printf("The magic seemed to take a toll on your body and you fainted...");
         break;
      case MainGame_Chapter2_WaitOff75:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn75:
         break; 
      case MainGame_Chapter2_Dialogue76:
         printf("\n\n");
      
         printf("End of chapter 2");
         break;
      case MainGame_Chapter2_WaitOff76:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter2_WaitOn76:
         break; 
      case MainGame_Chapter3_Dialogue0:
         printf("\n\n");
      
         printf("Chapter 3 - What happens when we believe?\n\n");
         printf("You look around what seems like a white room.\n");
         printf("You: (What happened?)");
         break;
      case MainGame_Chapter3_WaitOff0:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn0:
         break; 
      case MainGame_Chapter3_Dialogue1:
         printf("\n\n");
      
         printf("Pai: \"Hey there!\"");
         break;
      case MainGame_Chapter3_WaitOff1:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn1:
         break; 
      case MainGame_Chapter3_Dialogue2:
         printf("\n\n");
      
         printf("You: \"Huh?! What happened? Where am I?\"");
         break;
      case MainGame_Chapter3_WaitOff2:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn2:
         break; 
      case MainGame_Chapter3_Dialogue3:
         printf("\n\n");
      
         printf("Pai: \"Calm down! You're asleep and dreaming right now. I'm talking to you in your dreams.\"");
         break;
      case MainGame_Chapter3_WaitOff3:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn3:
         break; 
      case MainGame_Chapter3_Dialogue4:
         printf("\n\n");
      
         printf("You: \"But this feels so real...\"");
         break;
      case MainGame_Chapter3_WaitOff4:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn4:
         break; 
      case MainGame_Chapter3_Dialogue5:
         printf("\n\n");
      
         printf("Pai: \"I know! Anyways, I wanted to comment on your magic earlier since you're an intriguing type of person... By that I mean, I haven't run into many people who are like you... Your power to BELIEVE in yourself and channel it to your already existing magic, making it even more powerful than before.\"");
         break;
      case MainGame_Chapter3_WaitOff5:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn5:
         break; 
      case MainGame_Chapter3_Dialogue6:
         printf("\n\n");
      
         printf("You: \"I really want to get back to my world. And as long as I'm alive and I can move, there's always hope. That's why I always BELIEVE even when my chances are slim.\"");
         break;
      case MainGame_Chapter3_WaitOff6:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn6:
         break;
      case MainGame_Chapter3_Dialogue7:
         printf("\n\n");
      
         printf("Pai stares off into the distance.");
         break;
      case MainGame_Chapter3_WaitOff7:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn7:
         break;
      case MainGame_Chapter3_Dialogue8:
         printf("\n\n");
      
         printf("Pai:\"Humans are really interesting... They're physically weak and can die in many ways easily.\"");
         break;
      case MainGame_Chapter3_WaitOff8:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn8:
         break;
      case MainGame_Chapter3_Dialogue9:
         printf("\n\n");
      
         printf("Pai:\"And yet they still choose to believe in themselves...\"");
         break;
      case MainGame_Chapter3_WaitOff9:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn9:
         break;
      case MainGame_Chapter3_Dialogue10:
         printf("\n\n");
      
         printf("You stared at Pai, not sure where she is going with this.");
         break;
      case MainGame_Chapter3_WaitOff10:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn10:
         break;
      case MainGame_Chapter3_Dialogue11:
         printf("\n\n");
      
         printf("Pai: \"Never mind I've been talking to myself too much. Anyways, you're definitely going to face harder opponents now since the Demon King despises people who BELIEVE in themselves.\"");
         break;
      case MainGame_Chapter3_WaitOff11:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn11:
         break;
      case MainGame_Chapter3_Dialogue12:
         printf("\n\n");
         printf("You thought about what Pai said.\n");      
         printf("You: \"Okay so when will the Demon King reveal himself?\"");
         break;
      case MainGame_Chapter3_WaitOff12:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn12:
         break;
      case MainGame_Chapter3_Dialogue13:
         printf("\n\n");
      
         printf("Pai did not say a word. Moments after, the whitespace around you began to fade and then you woke up in the basement of Rivera library.");
         break;
      case MainGame_Chapter3_WaitOff13:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn13:
         break;
      case MainGame_Chapter3_Dialogue14:
         printf("\n\n");
      
         printf("You: \"Strange dream...\"");
         break;
      case MainGame_Chapter3_WaitOff14:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn14:
         break;
      case MainGame_Chapter3_Dialogue15:
         printf("\n\n");
      
         printf("Unknown voice 3: \"Thank god you're okay. Brian told me that you passed out after your last fight and they carried you here.\"");
         break;
      case MainGame_Chapter3_WaitOff15:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn15:
         break;
      case MainGame_Chapter3_Dialogue16:
         printf("\n\n");
         printf("You: (Oh...)\n");      
         printf("You: \"Thanks for looking out for me! Who are you btw?\"");
         break;
      case MainGame_Chapter3_WaitOff16:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn16:
         break;
      case MainGame_Chapter3_Dialogue17:
         printf("\n\n");
      
         printf("Elena: \"I'm Elena.\"");
         break;
      case MainGame_Chapter3_WaitOff17:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn17:
         break;
      case MainGame_Chapter3_Dialogue18:
         printf("\n\n");
      
         printf("And then for some odd reason, she began to blush? And then looked away from you.");
         break;
      case MainGame_Chapter3_WaitOff18:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn18:
         break;
      case MainGame_Chapter3_Dialogue19:
         printf("\n\n");
      
         printf("Elena: \"It's not like I looked out for you because I like you for anything! Idiot.\"");
         break;
      case MainGame_Chapter3_WaitOff19:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn19:
         break;
      case MainGame_Chapter3_Dialogue20:
         printf("\n\n");
      
         printf("You: (Oh it's another overused anime trope.)");
         break;
      case MainGame_Chapter3_WaitOff20:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn20:
         break;
      case MainGame_Chapter3_Dialogue21:
         printf("\n\n");
      
         printf("You:\"I get you. Anyways, where's Brian and Frank?\"");
         break;
      case MainGame_Chapter3_WaitOff21:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn21:
         break;
      case MainGame_Chapter3_Dialogue22:
         printf("\n\n");
      
         printf("Elena:\"They're off fighting demons somewhere on the 2nd or 3rd floor of Rivera.\"");
         break;
      case MainGame_Chapter3_WaitOff22:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn22:
         break;
      case MainGame_Chapter3_Dialogue23:
         printf("\n\n");
      
         printf("You:\"We should go help them out.\"");
         break;
      case MainGame_Chapter3_WaitOff23:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn23:
         break;
      case MainGame_Chapter3_Dialogue24:
         printf("\n\n");

         printf("Elena narrowed her eyes.\n");
         printf("Elena: \"Don't tell me what to do.\"");
         break;
      case MainGame_Chapter3_WaitOff24:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn24:
         break;
      case MainGame_Chapter3_Dialogue25:
         printf("\n\n");

         printf("You: \"Sorry I meant-\"\n");
         printf("You were interrupted by demons showing up in front of you and Elena");   
         break;
      case MainGame_Chapter3_WaitOff25:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn25:
         break;
      case MainGame_Chapter3_Dialogue26:
         printf("\n\n");

         printf("Elena: \"This will be quick.\""); 
         break;
      case MainGame_Chapter3_WaitOff26:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn26:
         break;
      case MainGame_Chapter3_Dialogue27:
         printf("\n\n");

         printf("You and Elena fought off the demons with ease. She also had electric powers like you so you were able to synergize well.");   
         break;
      case MainGame_Chapter3_WaitOff27:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn27:
         break; 
      case MainGame_Chapter3_Dialogue28:
         printf("\n\n");

         printf("Elena seemed very surprised at how much powerful your magic was compared to hers. She stared at you after the fight was over.");   
         break;
      case MainGame_Chapter3_WaitOff28:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn28:
         break;  
      case MainGame_Chapter3_Dialogue29:
         printf("\n\n");

         printf("Elena: \"How long have you been in the shadow realm?\"");   
         break;
      case MainGame_Chapter3_WaitOff29:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn29:
         break;  
      case MainGame_Chapter3_Dialogue30:
         printf("\n\n");

         printf("You: \"I think yesterday? I don't know...\"");   
         break;
      case MainGame_Chapter3_WaitOff30:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn30:
         break; 
      case MainGame_Chapter3_Dialogue31:
         printf("\n\n");

         printf("Elena: \"Only yesterday?\"");   
         break;
      case MainGame_Chapter3_WaitOff31:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn31:
         break; 
      case MainGame_Chapter3_Dialogue32:
         printf("\n\n");

         printf("Elena: \"I've been here for 6 months and I still haven't gotten a clue on how to get out of here. I've faced the Demon King a couple of times but every time I try to fight him, he effortlessly blocks my attack and then flees. It's almost as if he thinks I'm not worthy enough to fight him yet so that's why he doesn't even bother.\"");   
         break;
      case MainGame_Chapter3_WaitOff32:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn32:
         break;
      case MainGame_Chapter3_Dialogue33:
         printf("\n\n");

         printf("You kept listening to her intently.");   
         break;
      case MainGame_Chapter3_WaitOff33:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn33:
         break;
      case MainGame_Chapter3_Dialogue34:
         printf("\n\n");

         printf("Elena: \"It's really frustrating you know? Being trapped here for so long and feeling like you've made so much effort yet it still feels like you're really far away from your goal.\"");   
         break;
      case MainGame_Chapter3_WaitOff34:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn34:
         break;
      case MainGame_Chapter3_Dialogue35:
         printf("\n\n");
         printf("Select a dialogue choice below: \n\n");
         printf("A1: (Give her space)\n");
         printf("A2: (Comfort her)\n");
         break;
      case MainGame_Chapter3_WaitOff35:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn35:
         break;
      case MainGame_Chapter3_Dialogue36a:
         printf("\n\n");
         printf("You decided to walk away and give her space for a while.");
         break;
      case MainGame_Chapter3_WaitOff36a:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn36a:
         break;
      case MainGame_Chapter3_Dialogue36b:
         printf("\n\n");
         printf("You: (She'll be alright. She needs time to collect her own thoughts that's all)");
         break;
      case MainGame_Chapter3_WaitOff36b:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn36b:
         break;
      case MainGame_Chapter3_Dialogue36c:
         printf("\n\n");
         printf("You stare at a dead cockroach on the bathroom floor of Rivera.");
         break;
      case MainGame_Chapter3_WaitOff36c:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn36c:
         break;
      case MainGame_Chapter3_Dialogue36d:
         printf("\n\n");
         printf("You: (I've been feeling down a lot ever since I got transported into the shadow realm a day ago. What more 6 months?)");
         break;
      case MainGame_Chapter3_WaitOff36d:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn36d:
         break;
      case MainGame_Chapter3_Dialogue36e:
         printf("\n\n");
         printf("You: (I can't imagine what it must feel like.)");
         break;
      case MainGame_Chapter3_WaitOff36e:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn36e:
         break;
      case MainGame_Chapter3_Dialogue36f:
         printf("\n\n");
         printf("You hear Elena walking up behind you.\n");
         printf("Elena: \"I'm feeling better now. Let's go.\"");
         break;
      case MainGame_Chapter3_WaitOff36f:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn36f:
         break;
      case MainGame_Chapter3_Dialogue37a:
         printf("\n\n");

         printf("You: \"I'm really sorry you're feeling that way. I can't imagine what it must feel like to be stuck here for 6 months but I'll be here to support you along the way.\"");
         break;
      case MainGame_Chapter3_WaitOff37a:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn37a:
         break;
      case MainGame_Chapter3_Dialogue37b:
         printf("\n\n");

         printf("Elena looked at you with a sparkle in her eyes.");
         break;
      case MainGame_Chapter3_WaitOff37b:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn37b:
         break;
      case MainGame_Chapter3_Dialogue37c:
         printf("\n\n");

         printf("You: \"And you're a strong person. You've survived all by yourself for six months and fought these demons all on your own. I know you'll be able to make your magic stronger and face the Demon King head on.\"");
         break;
      case MainGame_Chapter3_WaitOff37c:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn37c:
         break;
      case MainGame_Chapter3_Dialogue37d:
         printf("\n\n");

         printf("Elena: \"Thanks I really needed to hear that. :)\"");
         break;
      case MainGame_Chapter3_WaitOff37d:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn37d:
         break;
      case MainGame_Chapter3_Dialogue37e:
         printf("\n\n");

         printf("You smiled at her in return.");
         break;
      case MainGame_Chapter3_WaitOff37e:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn37e:
         break;
      case MainGame_Chapter3_Dialogue37f:
         printf("\n\n");

         printf("Elena: \"I'm feeling much better now thanks to you. Why don't we head upstairs and check out on them?\"");
         break;
      case MainGame_Chapter3_WaitOff37f:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn37f:
         break;
      case MainGame_Chapter3_Dialogue38:
         printf("\n\n");

         printf("You head upstairs with Elena to check up on them.");
         break;
      case MainGame_Chapter3_WaitOff38:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn38:
         break;
      case MainGame_Chapter3_Dialogue39:
         printf("\n\n");

         printf("By the time you got there, all the Demon King's subordinates that Brian and Frank were supposedly fighting were already gone. All that stood was one mage who looked even more sinister than the demon mage you fought a few hours ago. He looked like the Black Mage from Maplestory. Bruh.");
         break;
      case MainGame_Chapter3_WaitOff39:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn39:
         break;
      case MainGame_Chapter3_Dialogue40:
         printf("\n\n");

         printf("You: \"Wha-\"");
         break;
      case MainGame_Chapter3_WaitOff40:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn40:
         break;
      case MainGame_Chapter3_Dialogue41:
         printf("\n\n");

         printf("Frank: \"It's the Demon King!\"");
         break;
      case MainGame_Chapter3_WaitOff41:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn41:
         break;
      case MainGame_Chapter3_Dialogue42:
         printf("\n\n");

         printf("Brian and Frank were panting. It seemed like they've been fighting him for a while now.");
         break;
      case MainGame_Chapter3_WaitOff42:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn42:
         break;
      case MainGame_Chapter3_Dialogue43:
         printf("\n\n");

         printf("Demon King: \"Not yet strong enough.\"");
         break;
      case MainGame_Chapter3_WaitOff43:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn43:
         break;
      case MainGame_Chapter3_Dialogue45:
         printf("\n\n");

         printf("The Demon King looked and pointed a finger at you.");
         break;
      case MainGame_Chapter3_WaitOff45:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn45:
         break;
      case MainGame_Chapter3_Dialogue46:
         printf("\n\n");

         printf("Demon King: \"Next time I come back, I'm fighting all 5 of you. You better be strong enough by then!\"");
         break;
      case MainGame_Chapter3_WaitOff46:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn46:
         break;
      case MainGame_Chapter3_Dialogue47:
         printf("\n\n");

         printf("You: (You mean all 4 of us?)");
         break;
      case MainGame_Chapter3_WaitOff47:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn47:
         break;
      case MainGame_Chapter3_Dialogue48:
         printf("\n\n");

         printf("Before the Demon King was about to leave though, you were charging up your electric magic with the intent of firing it at him.");
         break;
      case MainGame_Chapter3_WaitOff48:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn48:
         break;
      case MainGame_Chapter3_Dialogue49:
         printf("\n\n");

         printf("You: \"I'm not letting you get away!! You think we're weak? We're all going to get out of the shadow realm right now and go back to our normal lives! Right now!!\"\n");
         printf("You finished up charging your attack and shot millions of volts of lightning at the Demon King.");
                  
         break;
      case MainGame_Chapter3_WaitOff49:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn49:
         break;
      case MainGame_Chapter3_Dialogue50:
         printf("\n\n");

         printf("You: (As long as I BELIEVE in myself, I CAN be strong enough to get everyone out of here!)");
         break;
      case MainGame_Chapter3_WaitOff50:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn50:
         break;
      case MainGame_Chapter3_Dialogue51:
         printf("\n\n");

         printf("When your attack landed on the Demon King, he seemed to cry out in pain before disappearing.");
         break;
      case MainGame_Chapter3_WaitOff51:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn51:
         break;
      case MainGame_Chapter3_Dialogue52:
         printf("\n\n");

         printf("Frank: \"Did you defeat him? :o\"");
         break;
      case MainGame_Chapter3_WaitOff52:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn52:
         break;
      case MainGame_Chapter3_Dialogue53:
         printf("\n\n");
         
         printf("You paused for a while and looked around you.\n");
         printf("You: \"I don't think so. We would've been transported back to the real world by now if I did.\"");
         break;
      case MainGame_Chapter3_WaitOff53:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn53:
         break;
      case MainGame_Chapter3_Dialogue54:
         printf("\n\n");
         
         printf("The room fell silent for a while.");
         break;
      case MainGame_Chapter3_WaitOff54:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn54:
         break;
      case MainGame_Chapter3_Dialogue55:
         printf("\n\n");
         
         printf("Brian: \"But he seemed to have done some damage on him. This is a major step forward!\"");
         break;
      case MainGame_Chapter3_WaitOff55:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn55:
         break;
      case MainGame_Chapter3_Dialogue56:
         printf("\n\n");
         
         printf("Everyone was smiling and a glimmer of hope appeared in all their eyes.");
         break;
      case MainGame_Chapter3_WaitOff56:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn56:
         break;
      case MainGame_Chapter3_Dialogue58:
         printf("\n\n");
         
         printf("You:\"As long as we BELIEVE in ourselves, we'll be able to get out of here and go home in no time!\"");
         break;
      case MainGame_Chapter3_WaitOff58:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn58:
         break;
      case MainGame_Chapter3_Dialogue59:
         printf("\n\n");
         
         printf("Everyone was screaming triumphantly.");
         break;
      case MainGame_Chapter3_WaitOff59:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn59:
         break;
      case MainGame_Chapter3_Dialogue60:
         printf("\n\n");
         
         printf("Elena: \"So where do we find the next person?\"");
         break;
      case MainGame_Chapter3_WaitOff60:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn60:
         break;
      case MainGame_Chapter3_Dialogue61:
         printf("\n\n");
         
         printf("Brian: \"I have a heat signature at the SRC (school gym) mate! We should head there ASAP.\"");
         break;
      case MainGame_Chapter3_WaitOff61:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn61:
         break;
      case MainGame_Chapter3_Dialogue62:
         printf("\n\n");
         
         printf("Everyone nods and begins heading towards the SRC. Since there were no demons along the way, everyone made casual conversation about themselves and their personal lives in the real world ranging from hobbies, interests, likes/dislikes, hopes and dreams, childhood memories, everything. And it also turned out that Elena had a really soft side, like pretty much all tsunderes do btw lol xd");
         break;
      case MainGame_Chapter3_WaitOff62:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn62:
         break;
      case MainGame_Chapter3_Dialogue63:
         printf("\n\n");
         
         printf("Your already existing emotional connection with Frank and Brian improved and your new connection with Elena strengthened your already powerful magic. You could feel the electricity coarsing through your veins, like Spiderman Morales.");
         break;
      case MainGame_Chapter3_WaitOff63:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn63:
         break;
      case MainGame_Chapter3_Dialogue64:
         printf("\n\n");
         
         printf("As you entered the gym, you were all surprised to see who was there, training her ice magic powers by freezing the dumbells and sliding on them.");
         break;
      case MainGame_Chapter3_WaitOff64:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn64:
         break;
      case MainGame_Chapter3_Dialogue65:
         printf("\n\n");
         
         printf("Frank: \"Jeff? :D\"");
         break;
      case MainGame_Chapter3_WaitOff65:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn65:
         break;
      case MainGame_Chapter3_Dialogue66:
         printf("\n\n");
         
         printf("Jeff: \"Jeff who? :p\"");
         break;
      case MainGame_Chapter3_WaitOff66:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn66:
         break;
      case MainGame_Chapter3_Dialogue67:
         printf("\n\n");
         
         printf("Frank: \"Still the same jokester I know xD\"");
         break;
      case MainGame_Chapter3_WaitOff67:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn67:
         break;
      case MainGame_Chapter3_Dialogue68:
         printf("\n\n");
         
         printf("Brian: \"How long have you been stuck here mate?\"");
         break;
      case MainGame_Chapter3_WaitOff68:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn68:
         break;
      case MainGame_Chapter3_Dialogue69:
         printf("\n\n");
         
         printf("Jeff: \"Since yesterday.\"");
         break;
      case MainGame_Chapter3_WaitOff69:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn69:
         break;
      case MainGame_Chapter3_Dialogue70:
         printf("\n\n");
         
         printf("You: \"!...\"\n");
         printf("You: (For some reason, you felt some kind of familiarity but you weren't sure exactly how to put it into words.)");
         break;
      case MainGame_Chapter3_WaitOff70:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn70:
         break;
      case MainGame_Chapter3_Dialogue71:
         printf("\n\n");
         
         printf("Elena: \"Btw I have to use the restroom.\"");
         break;
      case MainGame_Chapter3_WaitOff71:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn71:
         break;
      case MainGame_Chapter3_Dialogue72:
         printf("\n\n");
         
         printf("Brian: \"Me too.\"");
         break;
      case MainGame_Chapter3_WaitOff72:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn72:
         break;
      case MainGame_Chapter3_Dialogue73:
         printf("\n\n");
         
         printf("Frank: \"Me three.\"");
         break;
      case MainGame_Chapter3_WaitOff73:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn73:
         break;
      case MainGame_Chapter3_Dialogue74:
         printf("\n\n");
         
         printf("You: (How very convenient.)\n");
         printf("You look at Jeff who has already gone back to practicing her magic.");
         break;
      case MainGame_Chapter3_WaitOff74:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn74:
         break;
      case MainGame_Chapter3_Dialogue75:
         printf("\n\n");
         
         printf("Select a dialogue choice below: \n\n");
         printf("A1: (Compliment Jeff for her dedication)\n");
         printf("A2: (Leave Jeff alone and practice alone)\n");
         break;
      case MainGame_Chapter3_WaitOff75:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn75:
         break;
      case MainGame_Chapter3_Dialogue76a:
         printf("\n\n");
         
         printf("You: \"I really admire how dedicated you are at refining your magic skills\"\n");
         break;
      case MainGame_Chapter3_WaitOff76a:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn76a:
         break;
      case MainGame_Chapter3_Dialogue76b:
         printf("\n\n");
         
         printf("Jeff picked up a marker and then dropped it on the ground.");
         break;
      case MainGame_Chapter3_WaitOff76b:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn76b:
         break;
      case MainGame_Chapter3_Dialogue76c:
         printf("\n\n");
         
         printf("Jeff: \"Of course! :D Because hard work pays after all. Literally. Get it? :p\"");
         break;
      case MainGame_Chapter3_WaitOff76c:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn76c:
         break;
      case MainGame_Chapter3_Dialogue76d:
         printf("\n\n");
         
         printf("You: \"Nice boomer joke lol\"");
         break;
      case MainGame_Chapter3_WaitOff76d:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn76d:
         break;
      case MainGame_Chapter3_Dialogue76e:
         printf("\n\n");
         
         printf("Jeff: \"xD\"");
         break;
      case MainGame_Chapter3_WaitOff76e:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn76e:
         break;
      case MainGame_Chapter3_Dialogue76f:
         printf("\n\n");
         
         printf("You decide to join Jeff in his practice and synchronize with each others' powers.");
         break;
      case MainGame_Chapter3_WaitOff76f:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn76f:
         break;
      case MainGame_Chapter3_Dialogue77a:
         printf("\n\n");
         
         printf("You: (She's busy anyways. I don't want to disturb her.)");
         break;
      case MainGame_Chapter3_WaitOff77a:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn77a:
         break;
      case MainGame_Chapter3_Dialogue77b:
         printf("\n\n");
         
         printf("You head to the 2nd floor of the gym and practice there.");
         break;
      case MainGame_Chapter3_WaitOff77b:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn77b:
         break;
      case MainGame_Chapter3_Dialogue77c:
         printf("\n\n");
         
         printf("While you were practicing alone, you were wondering how the things happening physically in the shadow realm were affecting the real world.");
         break;
      case MainGame_Chapter3_WaitOff77c:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn77c:
         break;
      case MainGame_Chapter3_Dialogue77d:
         printf("\n\n");
         
         printf("You: (I don't want to overthink this. Things are probably fine honestly.)");
         break;
      case MainGame_Chapter3_WaitOff77d:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn77d:
         break;
      case MainGame_Chapter3_Dialogue77e:
         printf("\n\n");
         
         printf("You headed back downstairs.");
         break;
      case MainGame_Chapter3_WaitOff77e:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn77e:
         break;
      case MainGame_Chapter3_Dialogue77f:
         printf("\n\n");
         
         printf("Jeff was still practicing and her stamina and focus seem to have improved.");
         break;
      case MainGame_Chapter3_WaitOff77f:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn77f:
         break;
      case MainGame_Chapter3_Dialogue78:
         printf("\n\n");
         
         printf("Brian, Frank, and Elena came out of the restroom. Why were they gone for so long anyways?");
         break;
      case MainGame_Chapter3_WaitOff78:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn78:
         break;
      case MainGame_Chapter3_Dialogue79:
         printf("\n\n");
         
         printf("Frank: \"I can feel it gang. The final boss battle is about to happen soon. >:D\"");
         break;
      case MainGame_Chapter3_WaitOff79:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn79:
         break;
      case MainGame_Chapter3_Dialogue80:
         printf("\n\n");
         
         printf("Everyone: \"I'm ready!\"");
         break;
      case MainGame_Chapter3_WaitOff80:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn80:
         break;
      case MainGame_Chapter3_Dialogue81:
         printf("\n\n");
         
         printf("And as if we summoned the demons working for the Demon King, ten seemingly very powerful demon mages spawned right outside the SRC.");
         break;
      case MainGame_Chapter3_WaitOff81:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn81:
         break;
      case MainGame_Chapter3_Dialogue82:
         printf("\n\n");
         
         printf("However, instead of everyone being scared like before, everyone was determined to face them head on. Perhaps having fought the Demon King before, everyone realized just how much more capable they were.");
         break;
      case MainGame_Chapter3_WaitOff82:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn82:
         break;
      case MainGame_Chapter3_Dialogue83:
         printf("\n\n");
         
         printf("But somehow, you were way ahead of them.");
         break;
      case MainGame_Chapter3_WaitOff83:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn83:
         break;
      case MainGame_Chapter3_Dialogue85:
         printf("\n\n");
         
         printf("You thought about the emotional connections you've formed with Brian, Frank, and Elena, along with a familiar but unexplainable feeling when you met Jeff.");
         break;
      case MainGame_Chapter3_WaitOff85:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn85:
         break;
      case MainGame_Chapter3_Dialogue86:
         printf("\n\n");
         
         printf("You: (They all mean so much to me and I don't want to lose any of them. Once we get out of here alive, I'm going to ask out one of them to be my girlfriend and make her the happiest girl alive.)");
         break;
      case MainGame_Chapter3_WaitOff86:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn86:
         break;
      case MainGame_Chapter3_Dialogue87:
         printf("\n\n");
         
         printf("You: (That's why I choose to BELIEVE!!)");
         break;
      case MainGame_Chapter3_WaitOff87:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn87:
         break;
      case MainGame_Chapter3_Dialogue88:
         printf("\n\n");
         
         printf("A blinding laser came out of your hand and vaporized all ten demon mages in one shot.");
         break;
      case MainGame_Chapter3_WaitOff88:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn88:
         break;
      case MainGame_Chapter3_Dialogue89:
         printf("\n\n");
         
         printf("A blinding laser came out of your hand and vaporized all ten demon mages in one shot.");
         break;
      case MainGame_Chapter3_WaitOff89:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn89:
         break;
      case MainGame_Chapter3_Dialogue90:
         printf("\n\n");
         printf("Everyone was shocked.");         
         printf("Everyone: \"What?!\"");
         break;
      case MainGame_Chapter3_WaitOff90:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn90:
         break;
      case MainGame_Chapter3_Dialogue91:
         printf("\n\n");
         
         printf("You had a wide grin and clenched your first.");         
         break;
      case MainGame_Chapter3_WaitOff91:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn91:
         break;
      case MainGame_Chapter3_Dialogue92:
         printf("\n\n");
         
         printf("Pai: \"How very interesting.\"");         
         break;
      case MainGame_Chapter3_WaitOff92:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn92:
         break;
      case MainGame_Chapter3_Dialogue93:
         printf("\n\n");
         
         printf("You swiveled around.\n");           
         printf("You: \"Where did you come from? :o\"");         
         break;
      case MainGame_Chapter3_WaitOff93:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn93:
         break;
      case MainGame_Chapter3_Dialogue94:
         printf("\n\n");
                  
         printf("Pai: \"You believed in yourself so much that your magic evolved into light magic.\"");         
         break;
      case MainGame_Chapter3_WaitOff94:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn94:
         break;
      case MainGame_Chapter3_Dialogue95:
         printf("\n\n");
                  
         printf("Everyone was confused since they had no idea who you were talking to, even though they could see Pai in front of them.");         
         break;
      case MainGame_Chapter3_WaitOff95:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn95:
         break;
      case MainGame_Chapter3_Dialogue96:
         printf("\n\n");
                  
         printf("Pai: \"I'll admit the power to BELIEVE definitely was what made you come this far.\"");         
         break;
      case MainGame_Chapter3_WaitOff96:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn96:
         break;
      case MainGame_Chapter3_Dialogue97:
         printf("\n\n");
                  
         printf("Pai: \"But...\"");         
         break;
      case MainGame_Chapter3_WaitOff97:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn97:
         break;
      case MainGame_Chapter3_Dialogue98:
         printf("\n\n");
                  
         printf("Pai: \"The will and determination to BELIEVE and push yourself forward... WILL BE YOUR BIGGEST DOWNFALL!\"");         
         break;
      case MainGame_Chapter3_WaitOff98:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn98:
         break;
      case MainGame_Chapter3_Dialogue99:
         printf("\n\n");
                  
         printf("Pai shape shifted into... the Demon King himself?!");         
         break;
      case MainGame_Chapter3_WaitOff99:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn99:
         break;
      case MainGame_Chapter3_Dialogue100:
         printf("\n\n");
                  
         printf("Demon King: \"I know what you're thinking and you're right. I am the true Demon King. I've been watching you this whole time... Asriel.\"");         
         break;
      case MainGame_Chapter3_WaitOff100:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn100:
         break;
      case MainGame_Chapter3_Dialogue101:
         printf("\n\n");
                  
         printf("You quiver as he calls out your real name.");         
         break;
      case MainGame_Chapter3_WaitOff101:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn101:
         break;
      case MainGame_Chapter3_Dialogue102:
         printf("\n\n");
                  
         printf("Asriel: (How does he know?)");         
         break;
      case MainGame_Chapter3_WaitOff102:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn102:
         break;
      case MainGame_Chapter3_Dialogue103:
         printf("\n\n");
                  
         printf("Demon King: \"Now time for me to take away your will to BELIEVE and convert it into utter hopelessness and despair!\"");         
         break;
      case MainGame_Chapter3_WaitOff103:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn103:
         break;
      case MainGame_Chapter3_Dialogue104:
         printf("\n\n");
                  
         printf("End of chapter 3");         
         break;
      case MainGame_Chapter3_WaitOff104:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter3_WaitOn104:
         break;
      case MainGame_Chapter4_Dialogue0:
         printf("\n\n");
                  
         printf("Chapter 4 - Facing the Demon King\n\n");  
         printf("Asriel: \"You're not going to take our will to BELIEVE!\"");   
         break;
      case MainGame_Chapter4_WaitOff0:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn0:
         break;
      case MainGame_Chapter4_Dialogue1:
         printf("\n\n");
                   
         printf("Frank: \"Yeah! We've come so far!\"");   
         break;
      case MainGame_Chapter4_WaitOff1:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn1:
         break;
      case MainGame_Chapter4_Dialogue2:
         printf("\n\n");
                  
         printf("Demon King: \"Humans are really foolish and naive\"");   
         break;
      case MainGame_Chapter4_WaitOff2:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn2:
         break;
      case MainGame_Chapter4_Dialogue3:
         printf("\n\n");
                  
         printf("Demon King: \"Let me teach you all a lesson...\"");   
         break;
      case MainGame_Chapter4_WaitOff3:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn3:
         break;
      case MainGame_Chapter4_Dialogue4:
         printf("\n\n");
                  
         printf("Demon King: \"Hopelessness is strongest when you've held so dearly to your hopes and dreams yet still utterly failed.\"");   
         break;
      case MainGame_Chapter4_WaitOff4:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn4:
         break;
      case MainGame_Chapter4_Dialogue5:
         printf("\n\n");
          printf("The Demon King was charging up his power during his short little monologue.\n");                 
         printf("Demon King: \"Observe!!\"");   
         break;
      case MainGame_Chapter4_WaitOff5:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn5:
         break;
      case MainGame_Chapter4_Dialogue6:
         printf("\n\n");
          printf("The Demon King fired a beam of dark, negative energy towards all of you while everyone tried to fire back a beam of light towards the Demon King.");                   
         break;
      case MainGame_Chapter4_WaitOff6:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn6:
         break;
      case MainGame_Chapter4_Dialogue7:
         printf("\n\n");
          printf("Asriel: (Hopelessness.. Despair.. I know what it feels like. And I'm feeling it right now. It's numbing really..)");                   
         break;
      case MainGame_Chapter4_WaitOff7:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn7:
         break;
      case MainGame_Chapter4_Dialogue8:
         printf("\n\n");
          printf("Asriel: (But letting those negative emotions sink in and completely change my view of the world.)");                   
         break;
      case MainGame_Chapter4_WaitOff8:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn8:
         break;
      case MainGame_Chapter4_Dialogue9:
         printf("\n\n");
          printf("Asriel: (Doesn't sit right with me at all!!)");                   
         break;
      case MainGame_Chapter4_WaitOff9:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn9:
         break;
      case MainGame_Chapter4_Dialogue10:
         printf("\n\n");
          printf("You get up and shoot your most powerful beam of light against the Demon King. Much to your surprise, he seemed to have deflected it with ease, despite damaging his hand a bit.");                   
         break;
      case MainGame_Chapter4_WaitOff10:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn10:
         break;
      case MainGame_Chapter4_Dialogue11:
         printf("\n\n");
          printf("Demon King: \"That beam of light you just fired at me was enough to disintegrate twenty powerful demon mages at once.\"");                   
         break;
      case MainGame_Chapter4_WaitOff11:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn11:
         break;
      case MainGame_Chapter4_Dialogue12:
         printf("\n\n");
         printf("You widened your eyes.\n"); 
         printf("Asriel: \"Pai- I mean, Demon King. If you're so powerful, why didn't you kill us the very moment you ran into us?\""); 
         break;
      case MainGame_Chapter4_WaitOff12:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn12:
         break;
      case MainGame_Chapter4_Dialogue13:
         printf("\n\n");
         printf("The Demon King laughed.\n"); 
         printf("Demon King: \"I think I've kind of told you already! Hopelessness is strongest when it's powered by fallen hopes and dreams. So I waited until you BELIEVED in yourself more so that when I crush you, I would be able to convert all your big hopes and dreams into an ever expanding pool of hopelessness in my magic.\"\n"); 
         break;
      case MainGame_Chapter4_WaitOff13:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn13:
         break;
      case MainGame_Chapter4_Dialogue14:
         printf("\n\n");
         printf("You felt disgusted.\n"); 
         printf("Asriel: \"You're sadistic you know that!\""); 
         break;
      case MainGame_Chapter4_WaitOff14:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn14:
         break;
      case MainGame_Chapter4_Dialogue15:
         printf("\n\n");
         printf("Jeff: \"You're not going to crush our hopes and dreams!\""); 
         break;
      case MainGame_Chapter4_WaitOff15:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn15:
         break;
      case MainGame_Chapter4_Dialogue16:
         printf("\n\n");
         printf("Elena: \"We're gonna continue to BELIEVE!\""); 
         break;
      case MainGame_Chapter4_WaitOff16:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn16:
         break;
      case MainGame_Chapter4_Dialogue17:
         printf("\n\n");
         printf("Everyone fired an even more powerful beam of light against the Demon King"); 
         break;
      case MainGame_Chapter4_WaitOff17:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn17:
         break;
      case MainGame_Chapter4_Dialogue18:
         printf("\n\n");
         printf("It was so powerful that the Demon King launched back several hundreds of feet even after blocking it."); 
         break;
      case MainGame_Chapter4_WaitOff18:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn18:
         break;
      case MainGame_Chapter4_Dialogue19:
         printf("\n\n");
         printf("Demon King: \"The source of your magic in which you BELIEVE in. It's flawed. Don't you know that?\""); 
         break;
      case MainGame_Chapter4_WaitOff19:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn19:
         break;
      case MainGame_Chapter4_Dialogue20:
         printf("\n\n");
         printf("Brian: \"What do you mean?\""); 
         break;
      case MainGame_Chapter4_WaitOff20:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn20:
         break;
      case MainGame_Chapter4_Dialogue21:
         printf("\n\n");
         printf("Demon King: \"Here's the reality. This man, Asriel. He has 4 girls he can choose from after this. He may reject you and you will be heartbroken.\""); 
         break;
      case MainGame_Chapter4_WaitOff21:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn21:
         break;
      case MainGame_Chapter4_Dialogue22:
         printf("\n\n");
         printf("Demon King: \"Even after knowing that, you still choose to BELIEVE in yourselves?\""); 
         break;
      case MainGame_Chapter4_WaitOff22:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn22:
         break;
      case MainGame_Chapter4_Dialogue23:
         printf("\n\n");
         printf("Elena: \"Of course we do!\""); 
         break;
      case MainGame_Chapter4_WaitOff23:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn23:
         break;
      case MainGame_Chapter4_Dialogue24:
         printf("\n\n");
         printf("Frank: \"We know what the odds are!\""); 
         break;
      case MainGame_Chapter4_WaitOff24:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn24:
         break;
      case MainGame_Chapter4_Dialogue25:
         printf("\n\n");
         printf("Brian: \"Yet even then...\""); 
         break;
      case MainGame_Chapter4_WaitOff25:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn25:
         break;
      case MainGame_Chapter4_Dialogue26:
         printf("\n\n");
         printf("Jeff: \"We still BELIEVE!\""); 
         break;
      case MainGame_Chapter4_WaitOff26:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn26:
         break;
      case MainGame_Chapter4_Dialogue27:
         printf("\n\n");
         printf("An even more powerful beam of light fired against the Demon King"); 
         break;
      case MainGame_Chapter4_WaitOff27:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn27:
         break;  
      case MainGame_Chapter4_Dialogue28:
         printf("\n\n");
         printf("It was so powerful that the Demon King could not block it. He flew all the way back to Bourns Hall from SRC and slammed through the building."); 
         break;
      case MainGame_Chapter4_WaitOff28:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn28:
         break;  
      case MainGame_Chapter4_Dialogue29:
         printf("\n\n");
         printf("Even then, he was still putting up a fight."); 
         break;
      case MainGame_Chapter4_WaitOff29:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn29:
         break;  
      case MainGame_Chapter4_Dialogue30:
         printf("\n\n");
         printf("Demon King: \"Why do you BELIEVE in such a flawed concept?!\""); 
         break;
      case MainGame_Chapter4_WaitOff30:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn30:
         break;  
      case MainGame_Chapter4_Dialogue31:
         printf("\n\n");
         printf("Demon King: \"At least with absolute hopelessness and despair, there is only one answer.\""); 
         break;
      case MainGame_Chapter4_WaitOff31:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn31:
         break;  
      case MainGame_Chapter4_Dialogue32:
         printf("\n\n");
         printf("Demon King: \"But if you BELIEVE in your hopes and dreams, you don't even know where you'll end up!\""); 
         break;
      case MainGame_Chapter4_WaitOff32:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn32:
         break;  
      case MainGame_Chapter4_Dialogue33:
         printf("\n\n");
         printf("Everyone: \"Exactly!\""); 
         break;
      case MainGame_Chapter4_WaitOff33:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn33:
         break;  
      case MainGame_Chapter4_Dialogue34:
         printf("\n\n");
         printf("Before everyone launched another powerful beam of light, the Demon King buffed himself until he was glowing in absolute darkness. Then he quickly fired another beam of darkness towards you."); 
         break;
      case MainGame_Chapter4_WaitOff34:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn34:
         break; 
      case MainGame_Chapter4_Dialogue35:
         printf("\n\n");
         printf("There was a huge explosion that followed right after which sent everyone flying back, though no one was damaged."); 
         break;
      case MainGame_Chapter4_WaitOff35:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn35:
         break; 
      case MainGame_Chapter4_Dialogue36:
         printf("\n\n");
         printf("Demon King: \"You've chosen to BELIEVE in such a flawed, imperfect source for your magic and have rejected the perfection of absolute despair.\""); 
         break;
      case MainGame_Chapter4_WaitOff36:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn36:
         break; 
      case MainGame_Chapter4_Dialogue37:
         printf("\n\n");
         printf("Asriel: \"We'll never fall to darkness! We'll continue to BELIEVE in the light within us!\""); 
         break;
      case MainGame_Chapter4_WaitOff37:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn37:
         break; 
      case MainGame_Chapter4_Dialogue38:
         printf("\n\n");
         printf("Demon King: \"You may be the strongest 5 people I've ever faced. But millions have come before you and have said pretty much the same thing. They've fought, they lost, and I turned their will to BELIEVE into absolute despair.\""); 
         break;
      case MainGame_Chapter4_WaitOff38:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn38:
         break; 
      case MainGame_Chapter4_Dialogue39:
         printf("\n\n");
         printf("Asriel: (That means those people... they're still alive! They've merely been absorbed into the Demon King's body and have been powering him with broken hopes and dreams. That's the source of his darkness! Millions of broken hopes and dreams combined!)"); 
         break;
      case MainGame_Chapter4_WaitOff39:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn39:
         break; 
      case MainGame_Chapter4_Dialogue40:
         printf("\n\n");
         printf("Asriel: \"We're gonna free those people too!\""); 
         break;
      case MainGame_Chapter4_WaitOff40:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn40:
         break; 
      case MainGame_Chapter4_Dialogue41:
         printf("\n\n");
         printf("Once again, you all launched a very powerful beam of light towards the Demon King."); 
         break;
      case MainGame_Chapter4_WaitOff41:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn41:
         break; 
      case MainGame_Chapter4_Dialogue42:
         printf("\n\n");
         printf("The Demon King launched a very powerful beam of darkness in return and once the beams collided, they refused to move, equalling each other out in a tug of war."); 
         break;
      case MainGame_Chapter4_WaitOff42:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn42:
         break;
      case MainGame_Chapter4_Dialogue43:
         printf("\n\n");
         printf("The Demon King was astonished by everyone's power."); 
         break;
      case MainGame_Chapter4_WaitOff43:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn43:
         break;
      case MainGame_Chapter4_Dialogue44:
         printf("\n\n");
         printf("Demon King: \"To deny perfect despair and to venture into the unknown of hopes and dreams. You're all insane! Naive! This power in which you BELIEVE in is responsible for the destruction of your world! Why can't you accept the truth and embrace perfect absolute despair?!\""); 
         break;
      case MainGame_Chapter4_WaitOff44:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn44:
         break;
      case MainGame_Chapter4_Dialogue45:
         printf("\n\n");
         printf("Everyone: \"Because even if the road that lies ahead of us is unclear, we still want to BELIEVE!\""); 
         break;
      case MainGame_Chapter4_WaitOff45:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn45:
         break;
      case MainGame_Chapter4_Dialogue46:
         printf("\n\n");
         printf("Demon King: \"Even if you'll face many struggles and disappointments along the way?\""); 
         break;
      case MainGame_Chapter4_WaitOff46:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn46:
         break;
      case MainGame_Chapter4_Dialogue47:
         printf("\n\n");
         printf("Everyone: \"We still BELIEVE!\""); 
         break;
      case MainGame_Chapter4_WaitOff47:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn47:
         break;
      case MainGame_Chapter4_Dialogue48:
         printf("\n\n");
         printf("Demon King: \"Even if you may have many heartbreaks and have sleepless nights crying over them?\""); 
         break;
      case MainGame_Chapter4_WaitOff48:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn48:
         break;
      case MainGame_Chapter4_Dialogue49:
         printf("\n\n");
         printf("Everyone: \"We still BELIEVE!\""); 
         break;
      case MainGame_Chapter4_WaitOff49:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn49:
         break;
      case MainGame_Chapter4_Dialogue50:
         printf("\n\n");
         printf("Demon King: \"Even if you may have lost or risk losing everything you've worked hard for?\""); 
         break;
      case MainGame_Chapter4_WaitOff50:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn50:
         break;
      case MainGame_Chapter4_Dialogue51:
         printf("\n\n");
         printf("Everyone: \"We still BELIEVE!!!!!\""); 
         break;
      case MainGame_Chapter4_WaitOff51:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn51:
         break;
      case MainGame_Chapter4_Dialogue52:
         printf("\n\n");
         printf("In the light magic/dark magic beam tug of war, the light prevailed and disintegrated the dark beam, landing on the Demon King and severely damaging him. He cried out in agony loudly."); 
         break;
      case MainGame_Chapter4_WaitOff52:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn52:
         break;
      case MainGame_Chapter4_Dialogue53:
         printf("\n\n");
         printf("Demon King: \"...if your light is so strong that I cannot defeat you... Then... I'll take you down with me!\""); 
         break;
      case MainGame_Chapter4_WaitOff53:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn53:
         break;
      case MainGame_Chapter4_Dialogue54:
         printf("\n\n");
         printf("The Demon King was charging up and getting ready to self-destruct. In about a split of a second, he exploded and a shockwave of darkness decimated the entire area and everyone was immediately engulfed in it."); 
         break;
      case MainGame_Chapter4_WaitOff54:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn54:
         break;
      case MainGame_Chapter4_Dialogue55:
         printf("\n\n");
         printf("You were all screaming as you were collided with millions of fallen hopes and dreams point blank."); 
         break;
      case MainGame_Chapter4_WaitOff55:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn55:
         break;
      case MainGame_Chapter4_Dialogue56:
         printf("\n\n");
         printf("However, all of you were still holding on to dear hope and light."); 
         break;
      case MainGame_Chapter4_WaitOff56:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn56:
         break;
      case MainGame_Chapter4_Dialogue57:
         printf("\n\n");
         printf("Asriel: \"There's one very important thing you forgot Demon King! If the strength of your hopelessness comes from fallen hopes and dreams, then the same thing must be true the other way around!\"\n"); 
         //printf("\nINPUT BUFFER LIMIT REACHED!\n");
         break;
      case MainGame_Chapter4_WaitOff57:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn57:
         break;
      case MainGame_Chapter4_Dialogue58:
         break;
      case MainGame_Chapter4_WaitOff58:
         //display_lives = 0;
  
         break;
      case MainGame_Chapter4_WaitOn58:
         break;
      case MainGame_GameOver_Init:
         break;
      case MainGame_GameOver:
         printf("\n\n");

         printf("Game over. Ouch guess you weren't smooth enough. :( Don't take it personally though! Whether you're in a relationship or not, we're all trying our best to understand and connect with women better. And besides, some of my choices may even be wrong! So there's that. :)\n\n");
         printf("Total score earned: %d", score); 
         score = 0;
         printf("\n\n");
         printf("Press A0 to restart the story from chapter 1");
         break;
      case MainGame_GameOver_WaitOff:
         //display_lives = 0;
  
         break;
      case MainGame_GameOver_WaitOn:
         break;
      default:
         break;
   }
}

enum ChapterSelection_States {ChapterSelection_SMStart, ChapterSelection_Inactive, ChapterSelection_Menu1, ChapterSelection_Menu2, ChapterSelection_WaitOff} ChapterSelection_State;

void TickFct_ChapterSelection(){
   switch(ChapterSelection_State){ //Transitions
      case ChapterSelection_SMStart:
         ChapterSelection_State = ChapterSelection_Inactive;
         break;
      case ChapterSelection_Inactive:
         if(A3 == 0){
            ChapterSelection_State = ChapterSelection_Inactive;    
         }
         else if(A3 == 1){
            ChapterSelection_State = ChapterSelection_Menu1;    
         }
         break;
      case ChapterSelection_Menu1:
         ChapterSelection_State = ChapterSelection_Menu2;
         break;
      case ChapterSelection_Menu2:
         ChapterSelection_State = ChapterSelection_Menu2;
         //use global variable here
         if(A4 == 1 && A5 == 0 && A6 == 0 && A7 == 0){
            printf("\nChapter 1 selected! Turn off A3 and A4 then turn on A0 to start the chapter. :)");
            MainGame_State = MainGame_Chapter4_Dialogue58;    
            ChapterSelection_State = ChapterSelection_WaitOff;
         }
         else if(A4 == 0 && A5 == 1 && A6 == 0 && A7 == 0){
            printf("\nChapter 2 selected! Turn off A3 and A5 then turn on A0 to start the chapter. :)");
            MainGame_State = MainGame_Chapter1_Dialogue42;   
            ChapterSelection_State = ChapterSelection_WaitOff;
         }
         else if(A4 == 0 && A5 == 0 && A6 == 1 && A7 == 0){
            printf("\nChapter 3 selected! Turn off A3 and A6 then turn on A0 to start the chapter. :)");
            MainGame_State = MainGame_Chapter2_Dialogue76;    
            ChapterSelection_State = ChapterSelection_WaitOff;
         }
         else if(A4 == 0 && A5 == 0 && A6 == 0 && A7 == 1){
            printf("\nChapter 4 selected! Turn off A3 and A7 then turn on A0 to start the chapter. :)");
            MainGame_State = MainGame_Chapter3_Dialogue104; 
            //MainGame_State = MainGame_Chapter4_Dialogue56; //to debug
            ChapterSelection_State = ChapterSelection_WaitOff; 
         }
         break;
      case ChapterSelection_WaitOff:
         if(A3 == 1){
            ChapterSelection_State = ChapterSelection_WaitOff;    
         }
         else if(A3 == 0){
            ChapterSelection_State = ChapterSelection_Inactive;    
         }
         break;
      default:
         ChapterSelection_State = ChapterSelection_Inactive;
         break;
   }
   
   switch(ChapterSelection_State){ //State actions
      case ChapterSelection_SMStart:
         break;
      case ChapterSelection_Inactive:
         break;
      case ChapterSelection_Menu1:
         printf("\n\n");
         printf("Select what chapter you would like to read! :D\n");
         printf("A4 - Chapter 1\n");
         printf("A5 - Chapter 2\n");
         printf("A6 - Chapter 3\n");
         printf("A7 - Chapter 4\n");
         score = 0; //but dont reset lives. this is to prevent cheating
         break;
      case ChapterSelection_Menu2:
         break;
      case ChapterSelection_WaitOff:
         break;
      default:
         break;
   }
}

void main(){
   TimerSet(1000);
   TimerOn();
   while (1) { 
      TickFct_LifeDisplay();
      TickFct_MainGame();
      TickFct_MainGame2();
      TickFct_ChapterSelection();
      
      while(!TimerFlag);
      TimerFlag=0;
   }
}
