/*
 *    This file is part of ACADO Toolkit.
 *
 *    ACADO Toolkit -- A Toolkit for Automatic Control and Dynamic Optimization.
 *    Copyright (C) 2008-2009 by Boris Houska and Hans Joachim Ferreau, K.U.Leuven.
 *    Developed within the Optimization in Engineering Center (OPTEC) under
 *    supervision of Moritz Diehl. All rights reserved.
 *
 *    ACADO Toolkit is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    ACADO Toolkit is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with ACADO Toolkit; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */



 /**
 *    \file examples/function/matrix_vector_expressions.cpp
 *    \author Boris Houska, Hans Joachim Ferreau
 *    \date 2008
 */

#include <time.h>

#include <acado/utils/acado_utils.hpp>
#include <acado/user_interaction/user_interaction.hpp>
#include <acado/symbolic_expression/symbolic_expression.hpp>
#include <acado/function/function.hpp>


/* >>> start tutorial code >>> */
int main( ){

    USING_NAMESPACE_ACADO

    // DEFINE VALRIABLES:
    // ---------------------------
    Matrix                 A(3,3);
    Vector                 b(3)  ;
    DifferentialState      x(3)  ;
    Function               f     ;


    // DEFINE THE VECTOR AND MATRIX ENTRIES:
    // -------------------------------------
    A.setZero() ;
    A(0,0) = 1.0;  A(1,1) = 2.0;  A(2,2) = 3.0;
    b(0)   = 1.0;  b(1)   = 1.0;  b(2)   = 1.0;


    // DEFINE A TEST FUNCTION:
    // -----------------------
    f << A*x + b;
    f << ( A*x(0) ).getRow( 1 );
    f << ( A*x(0) ).getCol( 0 );

    // TEST THE FUNCTION f:
    // --------------------
    EvaluationPoint zz(f);

    Vector xx(3);
    xx(0) = 1.0;
    xx(1) = 2.0;
    xx(2) = 3.0;

    zz.setX( xx );

    Vector result = f.evaluate( zz );

    result.print("result: \n");

    return 0;
}
/* <<< end tutorial code <<< */


