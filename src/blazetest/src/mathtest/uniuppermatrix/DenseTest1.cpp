//=================================================================================================
/*!
//  \file src/mathtest/uniuppermatrix/DenseTest1.cpp
//  \brief Source file for the UniUpperMatrix dense test (part 1)
//
//  Copyright (C) 2012-2020 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <cstdlib>
#include <iostream>
#include <memory>
#include <blaze/math/CompressedMatrix.h>
#include <blaze/math/CustomMatrix.h>
#include <blaze/math/HybridMatrix.h>
#include <blaze/math/StaticMatrix.h>
#include <blaze/util/policies/ArrayDelete.h>
#include <blazetest/mathtest/uniuppermatrix/DenseTest.h>

#ifdef BLAZE_USE_HPX_THREADS
#  include <hpx/hpx_main.hpp>
#endif


namespace blazetest {

namespace mathtest {

namespace uniuppermatrix {

//=================================================================================================
//
//  CONSTRUCTORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Constructor for the UniUpperMatrix dense test.
//
// \exception std::runtime_error Operation error detected.
*/
DenseTest::DenseTest()
{
   testConstructors();
   testAssignment();
   testAddAssign();
   testSubAssign();
   testSchurAssign();
   testMultAssign();
}
//*************************************************************************************************




//=================================================================================================
//
//  TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Test of the UniUpperMatrix constructors.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all constructors of the UniUpperMatrix specialization.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testConstructors()
{
   //=====================================================================================
   // Row-major default constructor
   //=====================================================================================

   // Default constructor (StaticMatrix)
   {
      test_ = "Row-major UniUpperMatrix default constructor (StaticMatrix)";

      const blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > upper;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
   }

   // Default constructor (HybridMatrix)
   {
      test_ = "Row-major UniUpperMatrix default constructor (HybridMatrix)";

      const blaze::UniUpperMatrix< blaze::HybridMatrix<int,3UL,3UL,blaze::rowMajor> > upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Default constructor (DynamicMatrix)
   {
      test_ = "Row-major UniUpperMatrix default constructor (DynamicMatrix)";

      const UT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }


   //=====================================================================================
   // Row-major single argument constructor
   //=====================================================================================

   // Single argument constructor (StaticMatrix)
   {
      test_ = "Row-major UniUpperMatrix single argument constructor (StaticMatrix)";

      const blaze::UniUpperMatrix< blaze::StaticMatrix<int,2UL,2UL,blaze::rowMajor> > upper( 5 );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 5 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 5 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (HybridMatrix)
   {
      test_ = "Row-major UniUpperMatrix single argument constructor (HybridMatrix)";

      const blaze::UniUpperMatrix< blaze::HybridMatrix<int,3UL,3UL,blaze::rowMajor> > upper( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (DynamicMatrix)
   {
      test_ = "Row-major UniUpperMatrix single argument constructor (DynamicMatrix)";

      const UT upper( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (0x0)
   {
      test_ = "Row-major UniUpperMatrix single argument constructor (0x0)";

      const blaze::DynamicMatrix<int,blaze::rowMajor> mat;
      const UT upper( mat );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Single argument constructor (uniupper)
   {
      test_ = "Row-major UniUpperMatrix single argument constructor (uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;

      const UT upper( mat );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (non-uniupper)
   {
      test_ = "Row-major UniUpperMatrix single argument constructor (non-uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         const UT upper( mat );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of non-uniupper UniUpperMatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Single argument constructor (UniUpperMatrix)
   {
      test_ = "Row-major UniUpperMatrix single argument constructor (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      const UT upper2( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major two argument constructor
   //=====================================================================================

   // Two argument constructor (HybridMatrix)
   {
      test_ = "Row-major UniUpperMatrix two argument constructor (HybridMatrix)";

      const blaze::UniUpperMatrix< blaze::HybridMatrix<int,3UL,3UL,blaze::rowMajor> > upper( 2UL, 5 );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 5 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 5 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Two argument constructor (DynamicMatrix)
   {
      test_ = "Row-major UniUpperMatrix two argument constructor (DynamicMatrix)";

      const UT upper( 2UL, 5 );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 5 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 5 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major list initialization
   //=====================================================================================

   // Complete initializer list
   {
      test_ = "Row-major UniUpperMatrix initializer list constructor (complete list)";

      const UT upper{ { 1, 2, 3 }, { 0, 1, 5 }, { 0, 0, 1 } };

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Incomplete initializer list
   {
      test_ = "Row-major UniUpperMatrix initializer list constructor (incomplete list)";

      const UT upper{ { 1, 2 }, { 0, 1 }, { 0, 0, 1 } };

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 4UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 1 0 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major array initialization
   //=====================================================================================

   // Dynamic array initialization constructor
   {
      test_ = "Row-major UniUpperMatrix dynamic array initialization constructor";

      std::unique_ptr<int[]> array( new int[9] );
      array[0] = 1;
      array[1] = 2;
      array[2] = 3;
      array[3] = 0;
      array[4] = 1;
      array[5] = 5;
      array[6] = 0;
      array[7] = 0;
      array[8] = 1;
      const UT upper( 3UL, array.get() );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Static array initialization constructor
   {
      test_ = "Row-major UniUpperMatrix static array initialization constructor";

      const int array[3][3] = { { 1, 2, 3 }, { 0, 1, 5 }, { 0, 0, 1 } };
      const UT upper( array );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major custom matrix constructors
   //=====================================================================================

   // Custom matrix constructor (ElementType*, size_t)
   {
      test_ = "Row-major UniUpperMatrix custom matrix constructor (ElementType*, size_t)";

      using blaze::unaligned;
      using blaze::unpadded;
      using blaze::rowMajor;

      using UnalignedUnpadded = blaze::CustomMatrix<int,unaligned,unpadded,rowMajor>;
      std::unique_ptr<int[]> memory( new int[5UL] );
      memory[1] = 1;
      memory[2] = 2;
      memory[3] = 0;
      memory[4] = 1;
      const blaze::UniUpperMatrix<UnalignedUnpadded> upper( memory.get()+1UL, 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Custom matrix constructor (ElementType*, size_t, size_t)
   {
      test_ = "Row-major UniUpperMatrix custom matrix constructor (ElementType*, size_t, size_t)";

      using blaze::unaligned;
      using blaze::unpadded;
      using blaze::rowMajor;

      using UnalignedUnpadded = blaze::CustomMatrix<int,unaligned,unpadded,rowMajor>;
      std::unique_ptr<int[]> memory( new int[11UL] );
      memory[1] = 1;
      memory[2] = 2;
      memory[6] = 0;
      memory[7] = 1;
      const blaze::UniUpperMatrix<UnalignedUnpadded> upper( memory.get()+1UL, 2UL, 5UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major copy constructor
   //=====================================================================================

   // Copy constructor (0x0)
   {
      test_ = "Row-major UniUpperMatrix copy constructor (0x0)";

      const UT upper1;
      const UT upper2( upper1 );

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Copy constructor (3x3)
   {
      test_ = "Row-major UniUpperMatrix copy constructor (3x3)";

      UT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      const UT upper2( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major move constructor
   //=====================================================================================

   // Move constructor (0x0)
   {
      test_ = "Row-major UniUpperMatrix move constructor (0x0)";

      UT upper1;
      UT upper2( std::move( upper1 ) );

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Move constructor (3x3)
   {
      test_ = "Row-major UniUpperMatrix move constructor (3x3)";

      UT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      UT upper2( std::move( upper1 ) );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major default constructor
   //=====================================================================================

   // Default constructor (StaticMatrix)
   {
      test_ = "Column-major UniUpperMatrix default constructor (StaticMatrix)";

      const blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> > upper;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
   }

   // Default constructor (HybridMatrix)
   {
      test_ = "Column-major UniUpperMatrix default constructor (HybridMatrix)";

      const blaze::UniUpperMatrix< blaze::HybridMatrix<int,3UL,3UL,blaze::columnMajor> > upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Default constructor (DynamicMatrix)
   {
      test_ = "Column-major UniUpperMatrix default constructor (DynamicMatrix)";

      const OUT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }


   //=====================================================================================
   // Column-major single argument constructor
   //=====================================================================================

   // Single argument constructor (StaticMatrix)
   {
      test_ = "Column-major UniUpperMatrix single argument constructor (StaticMatrix)";

      const blaze::UniUpperMatrix< blaze::StaticMatrix<int,2UL,2UL,blaze::columnMajor> > upper( 5 );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != 5 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 5 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (HybridMatrix)
   {
      test_ = "Column-major UniUpperMatrix single argument constructor (HybridMatrix)";

      const blaze::UniUpperMatrix< blaze::HybridMatrix<int,3UL,3UL,blaze::columnMajor> > upper( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (DynamicMatrix)
   {
      test_ = "Column-major UniUpperMatrix single argument constructor (DynamicMatrix)";

      const OUT upper( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (0x0)
   {
      test_ = "Column-major UniUpperMatrix single argument constructor (0x0)";

      const blaze::DynamicMatrix<int,blaze::columnMajor> mat;
      const OUT upper( mat );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Single argument constructor (uniupper)
   {
      test_ = "Column-major UniUpperMatrix single argument constructor (uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;

      const OUT upper( mat );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (non-uniupper)
   {
      test_ = "Column-major UniUpperMatrix single argument constructor (non-uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         const OUT upper( mat );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of non-uniupper UniUpperMatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Single argument constructor (UniUpperMatrix)
   {
      test_ = "Column-major UniUpperMatrix single argument constructor (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      const OUT upper2( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major two argument constructor
   //=====================================================================================

   // Two argument constructor (HybridMatrix)
   {
      test_ = "Column-major UniUpperMatrix two argument constructor (HybridMatrix)";

      const blaze::UniUpperMatrix< blaze::HybridMatrix<int,3UL,3UL,blaze::columnMajor> > upper( 2UL, 5 );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != 5 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 5 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Two argument constructor (DynamicMatrix)
   {
      test_ = "Column-major UniUpperMatrix two argument constructor (DynamicMatrix)";

      const OUT upper( 2UL, 5 );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != 5 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 5 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major list initialization
   //=====================================================================================

   // Complete initializer list
   {
      test_ = "Column-major UniUpperMatrix initializer list constructor (complete list)";

      const OUT upper{ { 1, 2, 3 }, { 0, 1, 5 }, { 0, 0, 1 } };

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Incomplete initializer list
   {
      test_ = "Column-major UniUpperMatrix initializer list constructor (incomplete list)";

      const OUT upper{ { 1, 2 }, { 0, 1 }, { 0, 0, 1 } };

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 4UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 1 0 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major array initialization
   //=====================================================================================

   // Dynamic array initialization constructor
   {
      test_ = "Column-major UniUpperMatrix dynamic array initialization constructor";

      std::unique_ptr<int[]> array( new int[9] );
      array[0] = 1;
      array[1] = 0;
      array[2] = 0;
      array[3] = 2;
      array[4] = 1;
      array[5] = 0;
      array[6] = 3;
      array[7] = 5;
      array[8] = 1;
      const OUT upper( 3UL, array.get() );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Static array initialization constructor
   {
      test_ = "Column-major UpperMatrix static array initialization constructor";

      const int array[3][3] = { { 1, 2, 3 }, { 0, 1, 5 }, { 0, 0, 1 } };
      const OUT upper( array );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major custom matrix constructors
   //=====================================================================================

   // Custom matrix constructor (ElementType*, size_t)
   {
      test_ = "Column-major UniUpperMatrix custom matrix constructor (ElementType*, size_t)";

      using blaze::unaligned;
      using blaze::unpadded;
      using blaze::columnMajor;

      using UnalignedUnpadded = blaze::CustomMatrix<int,unaligned,unpadded,columnMajor>;
      std::unique_ptr<int[]> memory( new int[5UL] );
      memory[1] = 1;
      memory[2] = 0;
      memory[3] = 2;
      memory[4] = 1;
      const blaze::UniUpperMatrix<UnalignedUnpadded> upper( memory.get()+1UL, 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Custom matrix constructor (ElementType*, size_t, size_t)
   {
      test_ = "Column-major UniUpperMatrix custom matrix constructor (ElementType*, size_t, size_t)";

      using blaze::unaligned;
      using blaze::unpadded;
      using blaze::columnMajor;

      using UnalignedUnpadded = blaze::CustomMatrix<int,unaligned,unpadded,columnMajor>;
      std::unique_ptr<int[]> memory( new int[11UL] );
      memory[1] = 1;
      memory[2] = 0;
      memory[6] = 2;
      memory[7] = 1;
      const blaze::UniUpperMatrix<UnalignedUnpadded> upper( memory.get()+1UL, 2UL, 5UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major copy constructor
   //=====================================================================================

   // Copy constructor (0x0)
   {
      test_ = "Column-major UniUpperMatrix copy constructor (0x0)";

      const OUT upper1;
      const OUT upper2( upper1 );

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Copy constructor (3x3)
   {
      test_ = "Column-major UniUpperMatrix copy constructor (3x3)";

      OUT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      const OUT upper2( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major move constructor
   //=====================================================================================

   // Move constructor (0x0)
   {
      test_ = "Column-major UniUpperMatrix move constructor (0x0)";

      OUT upper1;
      OUT upper2( std::move( upper1 ) );

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Move constructor (3x3)
   {
      test_ = "Column-major UniUpperMatrix move constructor (3x3)";

      OUT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      OUT upper2( std::move( upper1 ) );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the UniUpperMatrix assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all assignment operators of the UniUpperMatrix specialization.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testAssignment()
{
   //=====================================================================================
   // Row-major homogeneous assignment
   //=====================================================================================

   // Homogeneous assignment (3x3)
   {
      test_ = "Row-major UniUpperMatrix homogeneous assignment (3x3)";

      UT upper( 3UL );
      upper = 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 2 )\n( 0 1 2 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major list assignment
   //=====================================================================================

   // Complete initializer list
   {
      test_ = "Row-major UniUpperMatrix initializer list assignment (complete list)";

      UT upper;
      upper = { { 1, 2, 3 }, { 0, 1, 5 }, { 0, 0, 1 } };

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Incomplete initializer list
   {
      test_ = "Row-major UniUpperMatrix initializer list assignment (incomplete list)";

      UT upper;
      upper = { { 1, 2 }, { 0, 1 }, { 0, 0, 1 } };

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 1 0 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major array assignment
   //=====================================================================================

   // Array assignment
   {
      test_ = "Row-major UniUpperMatrix array assignment";

      const int array[3][3] = { { 1, 2, 3 }, { 0, 1, 5 }, { 0, 0, 1 } };
      UT upper;
      upper = array;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major copy assignment
   //=====================================================================================

   // Copy assignment (0x0)
   {
      test_ = "Row-major UniUpperMatrix copy assignment (0x0)";

      UT upper1, upper2;

      upper2 = upper1;

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Copy assignment (3x3)
   {
      test_ = "Row-major UniUpperMatrix copy assignment (3x3)";

      UT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;
      upper1(1,2) =  0;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major move assignment
   //=====================================================================================

   // Move assignment (0x0)
   {
      test_ = "Row-major UniUpperMatrix move assignment (0x0)";

      UT upper1, upper2;

      upper2 = std::move( upper1 );

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Move assignment (3x3)
   {
      test_ = "Row-major UniUpperMatrix move assignment (3x3)";

      UT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;
      upper1(1,2) =  0;

      UT upper2;
      upper2 = std::move( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense matrix assignment
   //=====================================================================================

   // Conversion assignment (0x0)
   {
      test_ = "Row-major UniUpperMatrix dense matrix assignment (0x0)";

      const blaze::DynamicMatrix<int,blaze::rowMajor> mat;

      UT upper;
      upper = mat;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Row-major/row-major dense matrix assignment (uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix assignment (uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;

      UT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix assignment (uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix assignment (uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;

      UT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix assignment (non-uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix assignment (non-uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         UT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix assignment (non-uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix assignment (non-uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         UT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major dense matrix assignment (UniUpperMatrix)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix assignment (UniUpperMatrix)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix assignment
   //=====================================================================================

   // Conversion assignment (0x0)
   {
      test_ = "Row-major UniUpperMatrix sparse matrix assignment (0x0)";

      const blaze::CompressedMatrix<int,blaze::rowMajor> mat;

      UT upper;
      upper = mat;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Row-major/row-major sparse matrix assignment (uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;
      mat.insert( 1UL, 0UL, 0 );

      UT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix assignment (uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;
      mat.insert( 1UL, 0UL, 0 );

      UT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix assignment (non-uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         UT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix assignment (non-uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         UT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major sparse matrix assignment (UniUpperMatrix)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 5UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix assignment (UniUpperMatrix)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 5UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major homogeneous assignment
   //=====================================================================================

   // Homogeneous assignment (3x3)
   {
      test_ = "Column-major UniUpperMatrix homogeneous assignment (3x3)";

      OUT upper( 3UL );
      upper = 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 2 )\n( 0 1 2 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Complete-major list assignment
   //=====================================================================================

   // Complete initializer list
   {
      test_ = "Column-major UniUpperMatrix initializer list assignment (complete list)";

      OUT upper;
      upper = { { 1, 2, 3 }, { 0, 1, 5 }, { 0, 0, 1 } };

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Incomplete initializer list
   {
      test_ = "Column-major UniUpperMatrix initializer list assignment (incomplete list)";

      OUT upper;
      upper = { { 1, 2 }, { 0, 1 }, { 0, 0, 1 } };

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 1 0 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major array assignment
   //=====================================================================================

   // Array assignment
   {
      test_ = "Column-major UniUpperMatrix array assignment";

      const int array[3][3] = { { 1, 2, 3 }, { 0, 1, 5 }, { 0, 0, 1 } };
      OUT upper;
      upper = array;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major copy assignment
   //=====================================================================================

   // Copy assignment (0x0)
   {
      test_ = "Column-major UniUpperMatrix copy assignment (0x0)";

      OUT upper1, upper2;

      upper2 = upper1;

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Copy assignment (3x3)
   {
      test_ = "Column-major UniUpperMatrix copy assignment (3x3)";

      OUT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;
      upper1(1,2) =  0;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major move assignment
   //=====================================================================================

   // Move assignment (0x0)
   {
      test_ = "Column-major UniUpperMatrix move assignment (0x0)";

      OUT upper1, upper2;

      upper2 = std::move( upper1 );

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Move assignment (3x3)
   {
      test_ = "Column-major UniUpperMatrix move assignment (3x3)";

      OUT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;
      upper1(1,2) =  0;

      OUT upper2;
      upper2 = std::move( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix assignment
   //=====================================================================================

   // Conversion assignment (0x0)
   {
      test_ = "Column-major UniUpperMatrix dense matrix assignment (0x0)";

      const blaze::DynamicMatrix<int,blaze::columnMajor> mat;

      OUT upper;
      upper = mat;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Column-major/row-major dense matrix assignment (uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix assignment (uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;

      OUT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix assignment (uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix assignment (uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;

      OUT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix assignment (non-uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix assignment (non-uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         OUT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix assignment (non-uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix assignment (non-uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         OUT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major dense matrix assignment (UniUpperMatrix)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix assignment (UniUpperMatrix)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix assignment
   //=====================================================================================

   // Conversion assignment (0x0)
   {
      test_ = "Column-major UniUpperMatrix sparse matrix assignment (0x0)";

      const blaze::CompressedMatrix<int,blaze::rowMajor> mat;

      OUT upper;
      upper = mat;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Column-major/row-major sparse matrix assignment (uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;
      mat.insert( 1UL, 0UL, 0 );

      OUT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix assignment (uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;
      mat.insert( 1UL, 0UL, 0 );

      OUT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix assignment (non-uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         OUT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix assignment (non-uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         OUT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major sparse matrix assignment (UniUpperMatrix)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 5UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix assignment (UniUpperMatrix)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 5UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the UniUpperMatrix addition assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the addition assignment operators of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testAddAssign()
{
   //=====================================================================================
   // Row-major dense matrix addition assignment
   //=====================================================================================

   // Row-major/row-major dense matrix addition assignment (strictly upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix addition assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix addition assignment (strictly upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix addition assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix addition assignment (non-upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix addition assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix addition assignment (non-upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix addition assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Row-major sparse matrix addition assignment
   //=====================================================================================

   // Row-major/row-major sparse matrix addition assignment (strictly upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix addition assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix addition assignment (strictly upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix addition assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix addition assignment (non-upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix addition assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix addition assignment (non-upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix addition assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major dense matrix addition assignment
   //=====================================================================================

   // Column-major/row-major dense matrix addition assignment (strictly upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix addition assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix addition assignment (strictly upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix addition assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix addition assignment (non-upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix addition assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix addition assignment (non-upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix addition assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major sparse matrix addition assignment
   //=====================================================================================

   // Column-major/row-major sparse matrix addition assignment (strictly upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix addition assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix addition assignment (strictly upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix addition assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix addition assignment (non-upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix addition assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix addition assignment (non-upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix addition assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the UniUpperMatrix subtraction assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the subtraction assignment operators of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testSubAssign()
{
   //=====================================================================================
   // Row-major dense matrix subtraction assignment
   //=====================================================================================

   // Row-major/row-major dense matrix subtraction assignment (strictly upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix subtraction assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix subtraction assignment (strictly upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix subtraction assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix subtraction assignment (non-upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix subtraction assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix subtraction assignment (non-upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix subtraction assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Row-major sparse matrix subtraction assignment
   //=====================================================================================

   // Row-major/row-major sparse matrix subtraction assignment (strictly upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix subtraction assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix subtraction assignment (strictly upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix subtraction assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix subtraction assignment (non-upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix subtraction assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix subtraction assignment (non-upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix subtraction assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major dense matrix subtraction assignment
   //=====================================================================================

   // Column-major/row-major dense matrix subtraction assignment (strictly upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix subtraction assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix subtraction assignment (strictly upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix subtraction assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix subtraction assignment (non-upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix subtraction assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix subtraction assignment (non-upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix subtraction assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major sparse matrix subtraction assignment
   //=====================================================================================

   // Column-major/row-major sparse matrix subtraction assignment (strictly upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix subtraction assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix subtraction assignment (strictly upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix subtraction assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix subtraction assignment (non-upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix subtraction assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix subtraction assignment (non-upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix subtraction assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the UniUpperMatrix Schur product assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the Schur product assignment operators of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testSchurAssign()
{
   //=====================================================================================
   // Row-major dense matrix Schur product assignment
   //=====================================================================================

   // Row-major/row-major dense matrix Schur product assignment (uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix Schur product assignment (uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,1) =  2;
      mat(1,1) =  1;
      mat(1,2) = 99;
      mat(2,0) = 99;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper %= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -8 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix Schur product assignment (uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix Schur product assignment (uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,1) =  2;
      mat(1,1) =  1;
      mat(1,2) = 99;
      mat(2,0) = 99;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper %= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -8 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix Schur product assignment (non-uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix Schur product assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) = 1;
      mat(1,1) = 1;
      mat(2,2) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper %= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix Schur product assignment (non-uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix Schur product assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) = 1;
      mat(1,1) = 1;
      mat(2,2) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper %= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major dense matrix Schur product assignment (UniUpperMatrix)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix Schur product assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > upper1;
      upper1(0,1) =  2;
      upper1(1,2) = 99;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 %= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 4UL );
      checkNonZeros( upper2, 0UL, 2UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -8 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix Schur product assignment (UniUpperMatrix)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix Schur product assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> > upper1;
      upper1(0,1) =  2;
      upper1(1,2) = 99;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 %= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 4UL );
      checkNonZeros( upper2, 0UL, 2UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -8 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix Schur product assignment
   //=====================================================================================

   // Row-major/row-major sparse matrix Schur product assignment (uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix Schur product assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 7UL );
      mat(0,0) =  1;
      mat(0,1) =  2;
      mat(1,1) =  1;
      mat(1,2) = 99;
      mat(2,0) = 99;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper %= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -8 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix Schur product assignment (uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix Schur product assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 7UL );
      mat(0,0) =  1;
      mat(0,1) =  2;
      mat(1,1) =  1;
      mat(1,2) = 99;
      mat(2,0) = 99;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper %= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -8 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix Schur product assignment (non-uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix Schur product assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 3UL );
      mat(0,0) = 1;
      mat(1,1) = 1;
      mat(2,2) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper %= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix Schur product assignment (non-uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix Schur product assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 3UL );
      mat(0,0) = 1;
      mat(1,1) = 1;
      mat(2,2) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper %= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major sparse matrix Schur product assignment (UniUpperMatrix)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix Schur product assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 5UL );
      upper1(0,1) =  2;
      upper1(1,2) = 99;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 %= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 4UL );
      checkNonZeros( upper2, 0UL, 2UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -8 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix Schur product assignment (UniUpperMatrix)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix Schur product assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 5UL );
      upper1(0,1) =  2;
      upper1(1,2) = 99;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 %= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 4UL );
      checkNonZeros( upper2, 0UL, 2UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -8 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix Schur product assignment
   //=====================================================================================

   // Column-major/row-major dense matrix Schur product assignment (uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix Schur product assignment (uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,1) =  2;
      mat(1,1) =  1;
      mat(1,2) = 99;
      mat(2,0) = 99;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper %= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -8 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix Schur product assignment (uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix Schur product assignment (uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,1) =  2;
      mat(1,1) =  1;
      mat(1,2) = 99;
      mat(2,0) = 99;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper %= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -8 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix Schur product assignment (non-uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix Schur product assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) = 1;
      mat(1,1) = 1;
      mat(2,2) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper %= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix Schur product assignment (non-uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix Schur product assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) = 1;
      mat(1,1) = 1;
      mat(2,2) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper %= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major dense matrix Schur product assignment (UniUpperMatrix)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix Schur product assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > upper1;
      upper1(0,1) =  2;
      upper1(1,2) = 99;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 %= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 4UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -8 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix Schur product assignment (UniUpperMatrix)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix Schur product assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> > upper1;
      upper1(0,1) =  2;
      upper1(1,2) = 99;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 %= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 4UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -8 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix Schur product assignment
   //=====================================================================================

   // Column-major/row-major sparse matrix Schur product assignment (uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix Schur product assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 7UL );
      mat(0,0) =  1;
      mat(0,1) =  2;
      mat(1,1) =  1;
      mat(1,2) = 99;
      mat(2,0) = 99;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper %= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -8 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix Schur product assignment (uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix Schur product assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 7UL );
      mat(0,0) =  1;
      mat(0,1) =  2;
      mat(1,1) =  1;
      mat(1,2) = 99;
      mat(2,0) = 99;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper %= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -8 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix Schur product assignment (non-uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix Schur product assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 3UL );
      mat(0,0) = 1;
      mat(1,1) = 1;
      mat(2,2) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper %= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix Schur product assignment (non-uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix Schur product assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 3UL );
      mat(0,0) = 1;
      mat(1,1) = 1;
      mat(2,2) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper %= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major sparse matrix Schur product assignment (UniUpperMatrix)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix Schur product assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 5UL );
      upper1(0,1) =  2;
      upper1(1,2) = 99;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 %= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 4UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -8 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix Schur product assignment (UniUpperMatrix)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix Schur product assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 5UL );
      upper1(0,1) =  2;
      upper1(1,2) = 99;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 %= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 4UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -8 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Schur product assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -8  0 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the UniUpperMatrix multiplication assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the multiplication assignment operators of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testMultAssign()
{
   //=====================================================================================
   // Row-major dense matrix multiplication assignment
   //=====================================================================================

   // Row-major/row-major dense matrix multiplication assignment (uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix multiplication assignment (uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix multiplication assignment (uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix multiplication assignment (uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix multiplication assignment (non-uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix multiplication assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix multiplication assignment (non-uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix multiplication assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major dense matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix multiplication assignment (UniUpperMatrix)";

      UT upper1( 3UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix multiplication assignment (UniUpperMatrix)";

      OUT upper1( 3UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix multiplication assignment
   //=====================================================================================

   // Row-major/row-major sparse matrix multiplication assignment (uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix multiplication assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix multiplication assignment (uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix multiplication assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix multiplication assignment (non-uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix multiplication assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 5UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix multiplication assignment (non-uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix multiplication assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 5UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major sparse matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix multiplication assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 5UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix multiplication assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 5UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix multiplication assignment
   //=====================================================================================

   // Column-major/row-major dense matrix multiplication assignment (uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix multiplication assignment (uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix multiplication assignment (uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix multiplication assignment (uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix multiplication assignment (non-uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix multiplication assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix multiplication assignment (non-uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix multiplication assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major dense matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix multiplication assignment (UniUpperMatrix)";

      UT upper1( 3UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 3UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix multiplication assignment (UniUpperMatrix)";

      OUT upper1( 3UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 3UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix multiplication assignment
   //=====================================================================================

   // Column-major/row-major sparse matrix multiplication assignment (uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix multiplication assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix multiplication assignment (uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix multiplication assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix multiplication assignment (non-uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix multiplication assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 5UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix multiplication assignment (non-uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix multiplication assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 5UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major sparse matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix multiplication assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 5UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 3UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix multiplication assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 5UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 3UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************

} // namespace uniuppermatrix

} // namespace mathtest

} // namespace blazetest




//=================================================================================================
//
//  MAIN FUNCTION
//
//=================================================================================================

//*************************************************************************************************
int main()
{
   std::cout << "   Running UniUpperMatrix dense test (part 1)..." << std::endl;

   try
   {
      RUN_UNIUPPERMATRIX_DENSE_TEST;
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during UniUpperMatrix dense test (part 1):\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************
