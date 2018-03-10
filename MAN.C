#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<math.h>

#define PI 3.141
int dist = 10;
/* represents the no of pixels to be used as one unit for the human*/
 /* since i'm translating the gimp co ordinates to turboc
 grid size in gimp is 10, i've set default value of dist as 10
 if need be, we can just change the value of dist
 to resize the human proportionately
 */

const int LEN_NECK      = 2;
const int LEN_UP_ARM    = 2;
const int LEN_FOREARM   = 3;
const int LEN_MID       = 5;
const int LEN_THIGH     = 3;
const int LEN_CALF      = 4;

/*
FUNCTIONS:
initPerson();
    Initializes the co ordinates of the person variable

*/

typedef struct{
  int x;
  int y;
} Point;

typedef struct{
 int r;
 int t;
} Polar;


/* Converts cartesian Point to Polar*/
Polar cart_to_polar(Point p){
Polar a;
a.r = sqrt(  p.x * p.x + p.y * p.y);
a.t = atan( p.y/(float)p.x) * 180/PI;//converting radians to degrees

return a;
}// cart_to_polar

/* Converts Polar to cartesian Point*/
Point polar_to_cart(Polar a){
Point p;
p.x = a.r * cos(a.t * PI/180.0 ); //converting degrees to radians
p.y = a.r * sin(a.t * PI/180.0 );

return p;
}// polar_to_cart


typedef struct{

 Point head;
 int head_r;
 /* co ordinates of the centre of the circle which represents the head*/

 Point neck_head;
 //Point neck_body;
 /* Co-ordinates of the line that is neck
  neck_head - midSecTop = This is the neck
  */

 Point midSecTop;
 Point midSecBot;
 /* Co ordinates of the mid section line */

 Point l_elbow, r_elbow;
 Point l_hand, r_hand;
 /* Co ordinates corresponding to 4 lines such that
 midSecTop - l_elbow;
 midSecTop - r_elbow;
 l_elbow   - l_hand;
 r_elbow   - r_hand;

       |     midSecTop
      /|\    The lines that are described above
    /  |  \

 */


 Point l_knee, r_knee;
 Point l_foot, r_foot;
 /* Co ordinates of the legs
 Lines to be made as
 midSecBot - l_knee
 midSecBot - r_knee
 l_knee    - l_foot
 r_knee    - r_foot

	|    midSecBot
       / \
     /     \


 */

} Person;


Person initPerson(Person p){
p.head.x = 100;
p.head.y = 100;
p.head_r = 2 * dist;  /* upper end will always be at below point of circle*/

// neck_head
p.neck_head.x = p.head.x;
p.neck_head.y = p.head.y + p.head_r;

// midSecTop
p.midSecTop.x = p.head.x;
p.midSecTop.y = p.neck_head.y + dist;

// midSecBot
p.midSecBot.x = p.head.x;
p.midSecBot.y = p.midSecTop.y + 5 * dist;

// l_elbow
p.l_elbow.x = p.midSecTop.x - 2 * dist;
p.l_elbow.y = p.midSecTop.y + dist;

// r_elbow
p.r_elbow.x = p.midSecTop.x + 2 * dist;
p.r_elbow.y = p.midSecTop.y + dist;

// l_hand
p.l_hand.x = p.l_elbow.x;
p.l_hand.y = p.l_elbow.y + 3 * dist;

// r_hand
p.r_hand.x = p.r_elbow.x;
p.r_hand.y = p.r_elbow.y + 3 * dist;

// l_knee
p.l_knee.x = p.midSecBot.x - 2 * dist;
p.l_knee.y = p.midSecBot.y + 3 * dist;

// r_knee
p.r_knee.x = p.midSecBot.x + 2 * dist;
p.r_knee.y = p.midSecBot.y + 3 * dist;

// l_foot
p.l_foot.x = p.l_knee.x;
p.l_foot.y = p.l_knee.y + 4 * dist;

// r_foot
p.r_foot.x = p.r_knee.x;
p.r_foot.y = p.r_knee.y + 4 * dist;

return p;
}

void printPerson(Person p){

printf("Person details:\n");
printf("Head:      x= %3d, y= %3d, r= %3d\n", p.head.x, p.head.y, p.head_r);
printf("Neck_head: x= %3d, y= %3d\n", p.neck_head.x, p.neck_head.y);
printf("MidSecTop: x= %3d, y= %3d\n", p.midSecTop.x, p.midSecTop.y);
printf("MidSecBot: x= %3d, y= %3d\n", p.midSecBot.x, p.midSecBot.y);

printf("L_Elbow  : x= %3d, y= %3d  ", p.l_elbow.x,   p.l_elbow.y  );
printf("R_Eblow  : x= %3d, y= %3d\n", p.r_elbow.x,   p.r_elbow.y  );

printf("L_Hand   : x= %3d, y= %3d  ", p.l_hand.x,    p.l_hand.y   );
printf("R_Hand   : x= %3d, y= %3d\n", p.r_hand.x,    p.r_hand.y   );

printf("L_Knee   : x= %3d, y= %3d  ", p.l_knee.x,    p.l_knee.y   );
printf("R_Knee   : x= %3d, y= %3d\n", p.r_knee.x,    p.r_knee.y   );

printf("L_Foot   : x= %3d, y= %3d  ", p.l_foot.x,    p.l_foot.y   );
printf("R_Foot   : x= %3d, y= %3d\n", p.r_foot.x,    p.r_foot.y   );
}//print Person



void drawPerson(Person p){
  // draw Head
  circle( p.head.x, p.head.y, p.head_r);

  // draw neck
  line( p.neck_head.x, p.neck_head.y ,
	p.midSecTop.x, p.midSecTop.y );

  // draw midSection
  line( p.midSecTop.x, p.midSecTop.y ,
	p.midSecBot.x, p.midSecBot.y );

  // shoulder to left elbow
  line( p.midSecTop.x, p.midSecTop.y ,
	p.l_elbow.x  , p.l_elbow.y   );

  // left elbow to left hand
  line( p.l_elbow.x  , p.l_elbow.y   ,
	p.l_hand.x   , p.l_hand.y    );

  // right elbow to right hand
  line( p.r_elbow.x  , p.r_elbow.y   ,
	p.r_hand.x   , p.r_hand.y    );

  // shoulder to right elbow
  line( p.midSecTop.x, p.midSecTop.y,
	p.r_elbow.x  , p.r_elbow.y   );

  // midSecBot to left knee
  line( p.midSecBot.x, p.midSecBot.y,
	p.l_knee.x   , p.l_knee.y    );

  // midSecBot to right knee
  line( p.midSecBot.x, p.midSecBot.y,
	p.r_knee.x   , p.r_knee.y    );

  // left knee to left foot
  line( p.l_knee.x   , p.l_knee.y   ,
	p.l_foot.x   , p.l_foot.y   );

  // right knee to right foot
  line( p.r_knee.x   , p.r_knee.y   ,
	p.r_foot.x   , p.r_foot.y   );

}// drawPerson

int main(){

/* request auto detection */
int gdriver = DETECT, gmode, errorcode;
int xmax, ymax;
Point ap;
Polar ar;


Person pp;

clrscr();
pp.head_r = 100;
//printf("Before init : %d\n",pp.head_r);
printPerson(pp);

pp = initPerson(pp);
//printf("After  init : %d\n",pp.head_r);
printPerson(pp);

//END MAIN
getch();
//return 12;

//test polar/cart conversion

ap.x = 12;
ap.y = 5;
ar = cart_to_polar(ap);
printf("ar.r = %3d; ar.t = %3d\n", ar.r, ar.t);

ap = polar_to_cart(ar);
printf("ap.x = %3d; ap.y = %3d\n", ap.x, ap.y);

getch();

/* initialize graphics and local variables */
initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

//line(0,0,200,200);


drawPerson(pp);


getch();
closegraph();
return 0;
}//main