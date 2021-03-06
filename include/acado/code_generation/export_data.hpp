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
 *    \file include/acado/code_generation/export_data.hpp
 *    \author Hans Joachim Ferreau, Boris Houska, Milan Vukov
 */


#ifndef ACADO_TOOLKIT_EXPORT_DATA_HPP
#define ACADO_TOOLKIT_EXPORT_DATA_HPP

#include <acado/utils/acado_utils.hpp>
#include <casadi/symbolic/shared_object.hpp>

BEGIN_NAMESPACE_ACADO

// Forward declaration
class ExportDataInternal;

/** 
 *	\brief Abstract base class to define variables to be used for exporting code
 *
 *	\ingroup AuxiliaryFunctionality
 *
 *	The class ExportData serves as an abstract base class to define variables
 *	to be used for exporting code.
 *
 *	\author Hans Joachim Ferreau, Boris Houska, Milan Vukov
 */
class ExportData : public CasADi::SharedObject
{
    //
    // PUBLIC MEMBER FUNCTIONS:
    //
    public:
		/** Default constructor. 
		 */
        ExportData( );

        /** Destructor.
		 */
        virtual ~ExportData( );

        /** An operator for access to functions and  members of the node
         */
        ExportDataInternal* operator->();

        /** An operator for const access to functions and  members of the node
         */
        const ExportDataInternal* operator->() const;

		/** Sets the name of the data object.
		 *
		 *	@param[in] _name			New name of the data object.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		returnValue	setName(	const String& _name
								);

		/** Sets the data type of the data object.
		 *
		 *	@param[in] _type			New data type of the data object.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		returnValue	setType(	ExportType _type
								);
								
		/** Sets the global data struct to which the data object belongs to.
		 *
		 *	@param[in] _dataStruct		New global data struct to which the data object belongs to.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		returnValue	setDataStruct(	ExportStruct _dataStruct
									);
		/** Sets the prefix which is placed before the structure name.
		 *
		 *  @param[in] _prefix Prefix name.
		 *
		 *  \return SUCCESSFUL_RETURN
		 */
		returnValue setPrefix(	const String& _prefix
								);
		/** Returns the name of the data object.
		 *
		 *	\return Name of the data object
		 */
		String getName( ) const;

		/** Returns the data type of the data object.
		 *
		 *	\return Data type of the data object
		 */
		ExportType getType( ) const;

		/** Returns a string containing the data type of the data object.
		 *
		 *	@param[in] _realString		String to be used to declare real variables.
		 *	@param[in] _intString		String to be used to declare integer variables.
		 *
		 *	\return String containing the data type of the data object.
		 */
		String getTypeString(	const String& _realString = "real_t",
								const String& _intString = "int"
								) const;

		/** Returns the global data struct to which the data object belongs to.
		 *
		 *	\return Global data struct to which the data object belongs to
		 */
		ExportStruct getDataStruct( ) const;

		/** Returns a string containing the global data struct to which the data object belongs to.
		 *
		 *	\return String containing the global data struct to which the data object belongs to.
		 */
		String getDataStructString( ) const;
		
		/** Returns a string which contains a prefix name.
		 *
		 *  \return Prefix name
		 */
		String getPrefix( ) const;

		/** Returns the full name of the data object including the possible prefix 
		 *	of the global data struct.
		 *
		 *	\return Full name of the data object
		 */
		String getFullName( ) const;


		/** Exports declaration of the index variable. Its appearance can 
		 *  can be adjusted by various options.
		 *
		 *	@param[in] file				Name of file to be used to export function.
		 *	@param[in] _realString		String to be used to declare real variables.
		 *	@param[in] _intString		String to be used to declare integer variables.
		 *	@param[in] _precision		Number of digits to be used for exporting real values.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue exportDataDeclaration(	FILE* file,
													const String& _realString = "real_t",
													const String& _intString = "int",
													int _precision = 16
													) const;


		/** Returns whether the index is set to a given value.
		 *
		 *	\return BT_TRUE  iff index is set to a given value, \n
		 *	        BT_FALSE otherwise
		 */
		virtual BooleanType isGiven( );

		virtual returnValue setDoc(const String& _doc);

		virtual String getDoc() const;
};

CLOSE_NAMESPACE_ACADO


#endif  // ACADO_TOOLKIT_EXPORT_DATA_HPP

// end of file.
