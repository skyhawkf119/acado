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
 *    \file include/acado/transfer_device/actuator.ipp
 *    \author Hans Joachim Ferreau, Boris Houska
 *    \date 24.08.2008
 */



BEGIN_NAMESPACE_ACADO



//
// PUBLIC MEMBER FUNCTIONS:
//



inline uint Actuator::getNU( ) const
{
	return nU;
}


inline uint Actuator::getNP( ) const
{
	return nP;
}



inline Noise* Actuator::getControlNoise(	uint idx
											) const
{
	if ( ( idx >= getNU( ) ) || ( additiveNoise == 0 ) || ( additiveNoise[idx] == 0 ) )
		return 0;
	else
		return additiveNoise[ idx ]->clone( );
}


inline Noise* Actuator::getParameterNoise(	uint idx
											) const
{
	if ( ( idx >= getNP( ) ) || ( additiveNoise == 0 ) || ( additiveNoise[idx] == 0 ) )
		return 0;
	else
		return additiveNoise[ getNU()+idx ]->clone( );
}



inline double Actuator::getControlDeadTime(	uint idx
											) const
{
	if ( ( idx >= getNU( ) ) || ( idx >= deadTimes.getDim() ) )
		return 0.0;
	else
		return deadTimes( idx );
}


inline Vector Actuator::getControlDeadTimes( ) const
{
	Vector tmp( getNU( ) );

	for( uint i=0; i<getNU( ); ++i )
		tmp( i ) = deadTimes( i );

	return tmp;
}



inline double Actuator::getParameterDeadTime(	uint idx
												) const
{
	if ( ( idx >= getNP( ) ) || ( idx >= deadTimes.getDim() ) )
		return 0.0;
	else
		return deadTimes( getNU()+idx );
}


inline Vector Actuator::getParameterDeadTimes( ) const
{
	Vector tmp( getNP( ) );

	for( uint i=0; i<getNP( ); ++i )
		tmp( i ) = deadTimes( getNU()+i );

	return tmp;
}



CLOSE_NAMESPACE_ACADO

/*
 *	end of file
 */
