/*
 *	This file is part of ACADO Toolkit.
 *
 *	ACADO Toolkit -- A Toolkit for Automatic Control and Dynamic Optimization.
 *	Copyright (C) 2008-2009 by Boris Houska and Hans Joachim Ferreau, K.U.Leuven.
 *	Developed within the Optimization in Engineering Center (OPTEC) under
 *	supervision of Moritz Diehl. All rights reserved.
 *
 *	ACADO Toolkit is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU Lesser General Public
 *	License as published by the Free Software Foundation; either
 *	version 3 of the License, or (at your option) any later version.
 *
 *	ACADO Toolkit is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *	Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with ACADO Toolkit; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


/**
 *	\file include/acado/code_generation/export_statement_block.hpp
 *	\author Hans Joachim Ferreau, Boris Houska
 *	\date 2010-2011
 */



#ifndef ACADO_TOOLKIT_EXPORT_STATEMENT_BLOCK_HPP
#define ACADO_TOOLKIT_EXPORT_STATEMENT_BLOCK_HPP


#include <acado/utils/acado_utils.hpp>
#include <acado/code_generation/export_statement.hpp>
#include <acado/code_generation/export_variable.hpp>
#include <acado/code_generation/export_index.hpp>
#include <acado/code_generation/export_data_declaration.hpp>

#include <vector>

BEGIN_NAMESPACE_ACADO


class ExportFunction;
class ExportODEfunction;
class ExportFunctionDeclaration;


/** 
 *	\brief Allows to export code for a block of statements.
 *
 *	\ingroup AuxiliaryFunctionality
 *
 *	The class ExportStatementBlock allows to export code for a block of statements.
 *
 *	\author Hans Joachim Ferreau, Boris Houska
 */
class ExportStatementBlock : public ExportStatement
{
	//
	// PUBLIC MEMBER FUNCTIONS:
	//
	public:

		/**< Default Constructor.
		 */
		ExportStatementBlock( );

		/** Copy constructor (deep copy).
		 *
		 *	@param[in] arg	Right-hand side object.
		 */
		ExportStatementBlock(	const ExportStatementBlock& arg
								);

		/** Destructor.
		 */
		virtual ~ExportStatementBlock( );

		/** Assignment operator (deep copy).
		 *
		 *	@param[in] arg	Right-hand side object.
		 */
		ExportStatementBlock& operator=(	const ExportStatementBlock& rhs
											);

		/** Clone constructor (deep copy).
		 *
		 *	\return Pointer to cloned object.
		 */
		virtual ExportStatement* clone( ) const;


		/** Adds a statement to the statement block.
		 *
		 *	@param[in] _statement		Statement to be added.
		 *
		 *  \return SUCCESSFUL_RETURN
		 */
		returnValue addStatement(	const ExportStatement& _statement
									);

		/** Adds a string statement to the statement block.
		 *
		 *	@param[in] _statementString		String statement to be added.
		 *
		 *  \return SUCCESSFUL_RETURN
		 */
		returnValue addStatement(	const String& _statementString
									);


		/** Adds a function to the statement block.
		 *
		 *	@param[in] _function		Function to be added.
		 *
		 *  \return SUCCESSFUL_RETURN
		 */
		returnValue addFunction(	const ExportFunction& _function
									);


		/** Adds a function call to the statement block.
		 *
		 *	@param[in] _fName			Name of function to be called.
		 *
		 *  \return SUCCESSFUL_RETURN
		 */
		returnValue addFunctionCall(	const String& _fName,
										const ExportArgument& _argument1 = emptyConstExportArgument,
										const ExportArgument& _argument2 = emptyConstExportArgument,
										const ExportArgument& _argument3 = emptyConstExportArgument,
										const ExportArgument& _argument4 = emptyConstExportArgument,
										const ExportArgument& _argument5 = emptyConstExportArgument,
										const ExportArgument& _argument6 = emptyConstExportArgument,
										const ExportArgument& _argument7 = emptyConstExportArgument,
										const ExportArgument& _argument8 = emptyConstExportArgument,
										const ExportArgument& _argument9 = emptyConstExportArgument
										);

		/** Adds a function call to the statement block.
		 *
		 *	@param[in] _f				Function to be called.
		 *
		 *  \return SUCCESSFUL_RETURN
		 */
		returnValue addFunctionCall(	const ExportFunction& _f,
										const ExportArgument& _argument1 = emptyConstExportArgument,
										const ExportArgument& _argument2 = emptyConstExportArgument,
										const ExportArgument& _argument3 = emptyConstExportArgument,
										const ExportArgument& _argument4 = emptyConstExportArgument,
										const ExportArgument& _argument5 = emptyConstExportArgument,
										const ExportArgument& _argument6 = emptyConstExportArgument,
										const ExportArgument& _argument7 = emptyConstExportArgument,
										const ExportArgument& _argument8 = emptyConstExportArgument,
										const ExportArgument& _argument9 = emptyConstExportArgument
										);


		/** Adds a variable declaration to the statement block.
		 *
		 *	@param[in] _data		Variable declaration to be added.
		 *
		 *  \return SUCCESSFUL_RETURN
		 */
		returnValue addDeclaration(	const ExportVariable& _data,
									ExportStruct _dataStruct = ACADO_ANY
									);

		/** Adds an index declaration to the statement block.
		 *
		 *	@param[in] _data		Index declaration to be added.
		 *
		 *  \return SUCCESSFUL_RETURN
		 */
		returnValue addDeclaration(	const ExportIndex& _data,
									ExportStruct _dataStruct = ACADO_ANY
									);

		/** Adds a function forward declaration to the statement block.
		 *
		 *	@param[in] _f			function forward declaration to be added.
		 *
		 *  \return SUCCESSFUL_RETURN
		 */
		returnValue addDeclaration(	const ExportFunction& _f
									);

		/** Adds a forward declaration of an ODE function to the statement block.
		 *
		 *	@param[in] _f			ODE function whose forward declaration is to be added.
		 *
		 *  \return SUCCESSFUL_RETURN
		 */
		returnValue addDeclaration(	const ExportODEfunction& _f
									);


		/** Adds a line break to the statement block.
		 *
		 *	@param[in] num			Number of line breaks to be added.
		 *
		 *  \return SUCCESSFUL_RETURN
		 */
		returnValue addLinebreak(	uint num = 1
									);

		/** Adds a comment to the statement block.
		 *
		 *	@param[in] _comment		Comment to be added.
		 *
		 *  \return SUCCESSFUL_RETURN
		 */
		returnValue addComment(	const String& _comment
								);

		/** Adds a comment preceded by a given number of blanks to the statement block.
		 *
		 *	@param[in] _nBlanks		Number of blanks.
		 *	@param[in] _comment		Comment to be added.
		 *
		 *  \return SUCCESSFUL_RETURN
		 */
		returnValue addComment(	uint _nBlanks,
								const String& _comment
								);


		/** Returns number of statement within statement block.
		 *
		 *  \return Number of statement within statement block
		 */
		uint getNumStatements( ) const;


		/** Exports data declaration of the statement block into given file. Its appearance can 
		 *  can be adjusted by various options.
		 *
		 *	@param[in] file				Name of file to be used to export statement block.
		 *	@param[in] _realString		String to be used to declare real variables.
		 *	@param[in] _intString		String to be used to declare integer variables.
		 *	@param[in] _precision		Number of digits to be used for exporting real values.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue exportDataDeclaration(	FILE *file,
													const String& _realString = "real_t",
													const String& _intString = "int",
													int _precision = 16
													) const;

		/** Exports source code of the statement block into given file. Its appearance can 
		 *  can be adjusted by various options.
		 *
		 *	@param[in] file				Name of file to be used to export statement block.
		 *	@param[in] _realString		String to be used to declare real variables.
		 *	@param[in] _intString		String to be used to declare integer variables.
		 *	@param[in] _precision		Number of digits to be used for exporting real values.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		virtual returnValue exportCode(	FILE* file,
										const String& _realString = "real_t",
										const String& _intString = "int",
										int _precision = 16
										) const;


		/** Removes all statements to yield an empty statement block.
		 *
		 *	\return SUCCESSFUL_RETURN
		 */
		returnValue clear( );


	//
	// PROTECTED MEMBER FUNCTIONS:
	//
	protected:


	//
	// DATA MEMBERS:
	//
	protected:
		typedef std::vector< statementPtr > statementPtrArray;

		/** Array containing all statements of the statement block. */
		statementPtrArray statements;
};


CLOSE_NAMESPACE_ACADO



#endif	// ACADO_TOOLKIT_EXPORT_STATEMENT_BLOCK_HPP


/*
 *	end of file
 */
