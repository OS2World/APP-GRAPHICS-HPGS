/***********************************************************************
 *                                                                     *
 * $Id: font_test.c 308 2006-03-07 15:24:01Z softadm $
 *                                                                     *
 * hpgs - HPGl Script, a hpgl/2 interpreter, which uses a Postscript   *
 *        API for rendering a scene and thus renders to a variety of   *
 *        devices and fileformats.                                     *
 *                                                                     *
 * (C) 2004-2006 ev-i Informationstechnologie GmbH  http://www.ev-i.at *
 *                                                                     *
 * Author: Wolfgang Glas                                               *
 *                                                                     *
 *  hpgs is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU Lesser General Public          *
 * License as published by the Free Software Foundation; either        *
 * version 2.1 of the License, or (at your option) any later version.  *
 *                                                                     *
 * hpgs is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of      *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   *
 * Lesser General Public License for more details.                     *
 *                                                                     *
 * You should have received a copy of the GNU Lesser General Public    *
 * License along with this library; if not, write to the               *
 * Free Software  Foundation, Inc., 59 Temple Place, Suite 330,        *
 * Boston, MA  02111-1307  USA                                         *
 *                                                                     *
 ***********************************************************************
 *                                                                     *
 * Test program for hpgs_font.                                         *
 *                                                                     *
 ***********************************************************************/

#undef NDEBUG

#include <hpgs.h>
#include <math.h>
#include <assert.h>

#define DO_TEST(a) printf("Running test <%s>.\n",HPGS_STRINGIFY(a));a

static int moveto_func(void * ctxt, const hpgs_point *p)
{
  printf(" moveto: (%lg,%lg).\n",p->x,p->y);
  return 0;
}

static int lineto_func(void * ctxt, const hpgs_point *p)
{
  printf(" lineto: (%lg,%lg).\n",p->x,p->y);
  return 0;
}

static int curveto_func(void * ctxt, const hpgs_point *p1, const hpgs_point *p2, const hpgs_point *p3)
{
  printf(" curveto: (%lg,%lg),(%lg,%lg),(%lg,%lg).\n",p1->x,p1->y,p2->x,p2->y,p3->x,p3->y);
  return 0;
}

static int fill_func(void * ctxt, hpgs_bool winding)
{
  printf(" fill: %d.\n",(int)winding);
  return 0;
}

static void print_err()
{
  printf("hpgs error: %s.\n",hpgs_get_error());
}

void test_font(hpgs_font *f, const int *widths)
{
  hpgs_point m;
  hpgs_bbox bb;
  hpgs_matrix matrix;
  int ret;

  hpgs_matrix_set_identity(&matrix);
  matrix.mxx = 2048.0;
  matrix.myy = 2048.0;

  printf("hpgs_font_get_glyph_name(f,'~') = %s.\n",hpgs_font_get_glyph_name(f,hpgs_font_get_glyph_id(f,'~')));
  printf("hpgs_font_get_glyph_id(f,'A') = %u.\n",hpgs_font_get_glyph_id(f,'A'));
  printf("hpgs_font_get_glyph_name(f,'A') = %s.\n",hpgs_font_get_glyph_name(f,hpgs_font_get_glyph_id(f,'A')));

  DO_TEST(ret=hpgs_font_get_glyph_metrics(f,&m,hpgs_font_get_glyph_id(f,'A')));
  if (ret) print_err();
  assert(ret == 0 && m.x == widths[0]/2048.0 && m.y == 0.0);
  printf("m=(%lg,%lg).\n",m.x,m.y);

  printf("hpgs_font_get_glyph_name(f,'r') = %s.\n",hpgs_font_get_glyph_name(f,hpgs_font_get_glyph_id(f,'r')));

  DO_TEST(ret=hpgs_font_get_glyph_metrics(f,&m,hpgs_font_get_glyph_id(f,'r')));
  if (ret) print_err();
  assert(ret == 0 && m.x == widths[1]/2048.0 && m.y == 0.0);
  printf("m=(%lg,%lg).\n",m.x,m.y);

  printf("hpgs_font_get_glyph_name(f,'i') = %s.\n",hpgs_font_get_glyph_name(f,hpgs_font_get_glyph_id(f,'i')));

  DO_TEST(ret=hpgs_font_get_glyph_metrics(f,&m,hpgs_font_get_glyph_id(f,'i')));
  if (ret) print_err();
  assert(ret == 0 && m.x == widths[2]/2048.0 && m.y == 0.0);
  printf("m=(%lg,%lg).\n",m.x,m.y);

  printf("hpgs_font_get_glyph_name(f,'a') = %s.\n",hpgs_font_get_glyph_name(f,hpgs_font_get_glyph_id(f,'a')));

  DO_TEST(ret=hpgs_font_get_glyph_metrics(f,&m,hpgs_font_get_glyph_id(f,'a')));
  if (ret) print_err();
  assert(ret == 0 && m.x == widths[3]/2048.0 && m.y == 0.0);
  printf("m=(%lg,%lg).\n",m.x,m.y);

  printf("hpgs_font_get_glyph_name(f,'l') = %s.\n",hpgs_font_get_glyph_name(f,hpgs_font_get_glyph_id(f,'l')));

  DO_TEST(ret=hpgs_font_get_glyph_metrics(f,&m,hpgs_font_get_glyph_id(f,'l')));
  if (ret) print_err();
  assert(ret == 0 && m.x == widths[4]/2048.0 && m.y == 0.0);
  printf("m=(%lg,%lg).\n",m.x,m.y);

  printf("hpgs_font_get_glyph_name(f,0x20AC) = %s.\n",hpgs_font_get_glyph_name(f,hpgs_font_get_glyph_id(f,0x20AC)));

  DO_TEST(ret=hpgs_font_get_glyph_metrics(f,&m,hpgs_font_get_glyph_id(f,0x20AC)));
  if (ret) print_err();
  assert(ret == 0 && m.x == widths[5]/2048.0 && m.y == 0.0);
  printf("m=(%lg,%lg).\n",m.x,m.y);

  printf("hpgs_font_get_glyph_name(f,'V') = %s.\n",hpgs_font_get_glyph_name(f,hpgs_font_get_glyph_id(f,'V')));

  DO_TEST(ret=hpgs_font_get_glyph_metrics(f,&m,hpgs_font_get_glyph_id(f,'V')));
  if (ret) print_err();
  assert(ret == 0 && m.x == widths[6]/2048.0 && m.y == 0.0);
  printf("m=(%lg,%lg).\n",m.x,m.y);

  DO_TEST(ret=hpgs_font_get_utf8_metrics(f,&m,"AV",-1));
  if (ret) print_err();
  assert(ret == 0);
  printf("m=(%lg,%lg).\n",m.x,m.y);

  DO_TEST(ret=hpgs_font_get_kern_metrics(f,&m,hpgs_font_get_glyph_id(f,'A'),hpgs_font_get_glyph_id(f,'V')));
  if (ret) print_err();
  assert(ret == 0);
  printf("m=(%lg,%lg).\n",m.x,m.y);

  DO_TEST(ret=hpgs_font_decompose_glyph(f,NULL,moveto_func,lineto_func,curveto_func,&matrix,hpgs_font_get_glyph_id(f,0xe4)));
  if (ret<0) print_err();
  assert(ret >= 0);
  DO_TEST(ret=hpgs_font_decompose_glyph(f,NULL,moveto_func,lineto_func,curveto_func,&matrix,hpgs_font_get_glyph_id(f,'a')));
  if (ret<0) print_err();
  assert(ret >= 0);

  DO_TEST(ret=hpgs_font_decompose_utf8(f,NULL,moveto_func,lineto_func,curveto_func,fill_func,&matrix,"AV",-1));
  if (ret) print_err();
  assert(ret == 0);

  DO_TEST(ret=hpgs_font_get_glyph_bbox(f,&bb,hpgs_font_get_glyph_id(f,'a')));
  if (ret) print_err();
  assert(ret == 0);
  printf("bb=(%lg,%lg,%lg,%lg).\n",bb.llx,bb.lly,bb.urx,bb.ury);
}

int main()
{
  hpgs_font *f;

  int arial_widths[7] =        {1366,682,455,1139,455,1139,1366};
  int arial_bold_widths[7] =   {1479,797,569,1139,569,1139,1366};

  hpgs_init("/usr/local");

  puts("***** Running font_test.");

  DO_TEST(f=hpgs_find_font("Arial"));
  if (f==0) print_err();
  assert(f!=0);
  test_font(f,arial_widths);
  DO_TEST(hpgs_destroy_font(f));
  
  DO_TEST(f=hpgs_find_font("Arial Bold"));
  if (f==0) print_err();
  assert(f!=0);
  test_font(f,arial_bold_widths);
  DO_TEST(hpgs_destroy_font(f));
  
  DO_TEST(f=hpgs_find_font("Arial Italic"));
  if (f==0) print_err();
  assert(f!=0);
  test_font(f,arial_widths);
  DO_TEST(hpgs_destroy_font(f));
  
  DO_TEST(f=hpgs_find_font("Arial Bold Italic"));
  if (f==0) print_err();
  assert(f!=0);
  test_font(f,arial_bold_widths);
  DO_TEST(hpgs_destroy_font(f));

  puts("***** font_test successful.");
  hpgs_cleanup();
  return 0;
}
