/*
 *    This file is part of ACADO Toolkit.
 *
 *    ACADO Toolkit -- A Toolkit for Automatic Control and Dynamic Optimization.
 *    Copyright (C) 2008-2009 by Boris Houska and Hans Joachim Ferreau.
 *    All rights reserved.
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
  *    \file   examples/multi_objective/fed_batch_bioreactor_ws.cpp
  *    \author Filip Logist, Boris Houska, Hans Joachim Ferreau
  *    \date   2009
  *
  *    \  Weighted Sum method for a fed-batch bioreactor with yield-productivity conflict
  *    \  J = (1-W)*J1+W*J2		Weighted Sum
  *    \  J1 = -x3/tf		Productivity
  *    \  J2 = -x3/(Csin*x4-x2) Yield
  *
  *	References:
  *	D. Sarkar, and J.M. Modak 2005.
  *     Pareto optimal solutions for multi-objective optimization of fed-batch bioreactors using nondominated sorting genetic algorithm.
  *     Chemical Engineering Science, 60, 481-492.
  * 
  * 	F. Logist, P.M. Van Erdeghem, and J.F. Van Impe 2009. 
  *	Efficient deterministic multiple objective optimal control of (bio)chemical processes. 
  *	Chemical Engineering Science, 64, 2527-2538.
  *
  */

#include "acado_optimal_control.hpp"
#include "../../external_packages/include/acado_gnuplot/gnuplot_window.hpp"


int main( ){

    USING_NAMESPACE_ACADO

    // INTRODUCE FIXED PARAMETERS:
    // ---------------------------
    #define  Csin	2.8


    // INTRODUCE THE VARIABLES:
    // -------------------------
    DifferentialState     x1,x2,x3,x4,x5;
    IntermediateState     mu,sigma,pif;
    Control               u           ;
    Parameter             tf          ;
    DifferentialEquation  f(0.0,tf)   ;


    // DEFINE A DIFFERENTIAL EQUATION:
    // -------------------------------
    mu    = 0.125*x2/x4;
    sigma = mu/0.135;
    pif   = (-384.0*mu*mu + 134.0*mu);

    f << dot(x1) ==  mu*x1;
    f << dot(x2) == -sigma*x1 + u*Csin;
    f << dot(x3) ==  pif*x1;
    f << dot(x4) ==  u;
    f << dot(x5) ==  0.001*(u*u + 0.01*tf*tf);

    // DEFINE AN OPTIMAL CONTROL PROBLEM:
    // ----------------------------------
    OCP ocp( 0.0, tf, 50 );
    ocp.minimizeMayerTerm(0, -x3/tf          ); // Solve productivity optimal problem (Note: - due to maximization, small regularisation term)
    ocp.minimizeMayerTerm(1, -x3/(Csin*x4-x2)); // Solve yield optimal problem (Note: Csin = x2(t=0)/x4(t=0); - due to maximization, small regularisation term)

    ocp.subjectTo( f );

    ocp.subjectTo( AT_START, x1 ==   0.1           );
    ocp.subjectTo( AT_START, x2 ==  14.0           );
    ocp.subjectTo( AT_START, x3 ==   0.0           );
    ocp.subjectTo( AT_START, x4 ==   5.0           );
    ocp.subjectTo( AT_START, x5 ==   0.0           );

    ocp.subjectTo(  0.0 <= x1 <=   15.0  );
    ocp.subjectTo(  0.0 <= x2 <=   30.0  );
    ocp.subjectTo( -0.1 <= x3 <= 1000.0  );
    ocp.subjectTo(  5.0 <= x4 <=   20.0  );
    ocp.subjectTo( 20.0 <= tf <=   40.0  );
    ocp.subjectTo(  0.0 <= u  <=    2.0  );


    // DEFINE A MULTI-OBJECTIVE ALGORITHM AND SOLVE THE OCP:
    // -----------------------------------------------------
    MultiObjectiveAlgorithm algorithm(ocp);

    algorithm.set( PARETO_FRONT_GENERATION    , PFG_WEIGHTED_SUM );
    algorithm.set( PARETO_FRONT_DISCRETIZATION, 21               );
    algorithm.set( HESSIAN_APPROXIMATION, EXACT_HESSIAN );
    algorithm.set( KKT_TOLERANCE, 1e-7 );

    // Generate Pareto set
    algorithm.solve();

    algorithm.getWeights("fed_batch_bioreactor_ws_weights.txt");
    algorithm.getAllDifferentialStates("fed_batch_bioreactor_ws_states.txt");
    algorithm.getAllControls("fed_batch_bioreactor_ws_controls.txt");
    algorithm.getAllParameters("fed_batch_bioreactor_ws_parameters.txt");

    // VISUALIZE THE RESULTS IN A GNUPLOT WINDOW:
    // ------------------------------------------
    VariablesGrid paretoFront;
    algorithm.getParetoFront( paretoFront );

    GnuplotWindow window1;
    window1.addSubplot( paretoFront, "Pareto Front (yield versus productivity)", "-PRODUCTIVTY", "-YIELD", PM_POINTS );
    window1.plot( );


    // PRINT INFORMATION ABOUT THE ALGORITHM:
    // --------------------------------------
    algorithm.printInfo();


    // SAVE INFORMATION:
    // -----------------
    FILE *file = fopen("fed_batch_bioreactor_ws_pareto.txt","w");
    paretoFront.print();
    file << paretoFront;
    fclose(file);

    return 0;
}

