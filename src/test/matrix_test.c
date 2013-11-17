/***********************************************************************
 *                                                                     *
 * $Id: matrix_test.c 282 2006-02-26 09:28:10Z softadm $
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
 * Test program for hpgs_matrix.                                       *
 *                                                                     *
 ***********************************************************************/

#undef NDEBUG

#include <hpgs.h>
#include <math.h>
#include <assert.h>

#define DO_TEST(a) printf("Running test <%s>.\n",HPGS_STRINGIFY(a));a

int main()
{
  hpgs_matrix a;
  hpgs_matrix b = { 0.234523, 12.2435134, -2345.9752, -93475.4532, 2.461, -234.253  };

  hpgs_point p = { 0.3425, -2.3451 }; 
  hpgs_point q1,q2; 

  hpgs_init("/usr/local");

  puts("***** Running matrix_test.");

  DO_TEST(hpgs_matrix_set_identity(&a));
  
  assert(a.dx == 0.0 && a.dy == 0.0 && a.mxx == 1.0 && a.mxy == 0.0 && a.myx == 0.0 && a.myy == 1.0);

  DO_TEST(hpgs_matrix_invert(&a,&a));

  assert(a.dx == 0.0 && a.dy == 0.0 && a.mxx == 1.0 && a.mxy == 0.0 && a.myx == 0.0 && a.myy == 1.0);

  DO_TEST(hpgs_matrix_invert(&a,&a));

  assert(a.dx == 0.0 && a.dy == 0.0 && a.mxx == 1.0 && a.mxy == 0.0 && a.myx == 0.0 && a.myy == 1.0);

  DO_TEST(hpgs_matrix_invert(&a,&b));

  printf(" a =\n (%24.16le,%24.16le,%24.16le)\n (%24.16le,%24.16le,%24.16le)\n",
         a.dx,a.mxx,a.mxy,a.dy,a.myx,a.myy);
  printf(" b =\n (%24.16le,%24.16le,%24.16le)\n (%24.16le,%24.16le,%24.16le)\n",
         b.dx,b.mxx,b.mxy,b.dy,b.myx,b.myy);

  DO_TEST(hpgs_matrix_xform(&q1,&b,&p));
  DO_TEST(hpgs_matrix_ixform(&q2,&p,&a));

  printf(" q1 = (%24.16le,%24.16le)\n",q1.x,q1.y);
  printf(" q2 = (%24.16le,%24.16le)\n",q2.x,q2.y);

  assert(q1.x == q2.x && q1.y == q2.y);

  DO_TEST(hpgs_matrix_concat(&a,&a,&b));

  printf(" a =\n (%24.16le,%24.16le,%24.16le)\n (%24.16le,%24.16le,%24.16le)\n",
         a.dx,a.mxx,a.mxy,a.dy,a.myx,a.myy);

  assert(fabs(a.dx)<1.0e-15 && fabs(a.dy)<1.0e-15 && a.mxx == 1.0 && fabs(a.mxy)<1.0e-15 && fabs(a.myx)<1.0e-15 && a.myy == 1.0);
  DO_TEST(hpgs_matrix_invert(&a,&b));
  DO_TEST(hpgs_matrix_invert(&b,&b));

  assert(a.dx == b.dx && a.dy == b.dy && a.mxx == b.mxx && a.mxy == b.mxy && a.myx == b.myx && a.myy == b.myy);

  puts("***** matrix_test successful.");
  hpgs_cleanup();
  return 0;
}
