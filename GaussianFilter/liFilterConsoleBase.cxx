/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    liFilterConsoleBase.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/


#include <liFilterConsoleBase.h>
#include <itkMetaImageIOFactory.h>



/************************************
 *
 *  Constructor
 *
 ***********************************/
liFilterConsoleBase 
::liFilterConsoleBase()
{

  m_ImageLoaded = false;

  m_Reader     = VolumeReaderType::New();
  
  m_Hx   = InputGaussianFilterType::New();
  m_Hy   = InputGaussianFilterType::New();
  m_Hz   = InputGaussianFilterType::New();

  m_Hx->SetDirection( 0 );
  m_Hy->SetDirection( 1 );
  m_Hz->SetDirection( 2 );

  m_Hxy  = GaussianFilterType::New();
  m_Hyz  = GaussianFilterType::New();
  m_Hzx  = GaussianFilterType::New();

  m_Hxy->SetDirection( 1 );
  m_Hyz->SetDirection( 2 );
  m_Hzx->SetDirection( 0 );

  m_H1x  = GaussianFirstDerivativeFilterType::New();
  m_H1y  = GaussianFirstDerivativeFilterType::New();
  m_H1z  = GaussianFirstDerivativeFilterType::New();

  m_H1x->SetDirection( 0 );
  m_H1y->SetDirection( 1 );
  m_H1z->SetDirection( 2 );

  m_H2x  = GaussianSecondDerivativeFilterType::New();
  m_H2y  = GaussianSecondDerivativeFilterType::New();
  m_H2z  = GaussianSecondDerivativeFilterType::New();

  m_H2x->SetDirection( 0 );
  m_H2y->SetDirection( 1 );
  m_H2z->SetDirection( 2 );


  m_Hx->SetInputImage( m_Reader->GetOutput() );
  m_Hy->SetInputImage( m_Reader->GetOutput() );
  m_Hz->SetInputImage( m_Reader->GetOutput() );

  m_Hxy->SetInputImage( m_Hx->GetOutput() );
  m_Hyz->SetInputImage( m_Hy->GetOutput() );
  m_Hzx->SetInputImage( m_Hz->GetOutput() );

  m_H1x->SetInputImage( m_Hyz->GetOutput() );
  m_H1y->SetInputImage( m_Hzx->GetOutput() );
  m_H1z->SetInputImage( m_Hxy->GetOutput() );

  m_H2x->SetInputImage( m_Hyz->GetOutput() );
  m_H2y->SetInputImage( m_Hzx->GetOutput() );
  m_H2z->SetInputImage( m_Hxy->GetOutput() );

  m_Add = AddFilterType::New();

  m_Add->SetInput1( m_H2x->GetOutput() );
  m_Add->SetInput2( m_H2y->GetOutput() );
  m_Add->SetInput3( m_H2z->GetOutput() );

  m_Modulus = ModulusFilterType::New();

  m_Modulus->SetInput1( m_H1x->GetOutput() );
  m_Modulus->SetInput2( m_H1y->GetOutput() );
  m_Modulus->SetInput3( m_H1z->GetOutput() );


  /*
  m_Writer_Gradient_Modulus = VolumeWriterType::New();
  m_Writer_Gradient_X      = VolumeWriterType::New();
  m_Writer_Gradient_Y      = VolumeWriterType::New();
  m_Writer_Gradient_Z      = VolumeWriterType::New();
  m_Writer_Laplacian       = VolumeWriterType::New();

  m_Writer_Gradient_X->SetInput( m_H1x->GetOutput() );
  m_Writer_Gradient_Y->SetInput( m_H1y->GetOutput() );
  m_Writer_Gradient_Z->SetInput( m_H1z->GetOutput() );

  m_Writer_Gradient_Modulus->SetInput( m_Modulus->GetOutput() );

  m_Writer_Laplacian->SetInput( m_Add->GetOutput() );
  */
  
  // Register a producer of MetaImage readers
  itk::MetaImageIOFactory::RegisterOneFactory();

}




/************************************
 *
 *  Destructor
 *
 ***********************************/
liFilterConsoleBase 
::~liFilterConsoleBase()
{

}



 
/************************************
 *
 *  Load
 *
 ***********************************/
void
liFilterConsoleBase 
::Load( const char * filename )
{
  if( !filename )
  {
    return;
  }

  m_Reader->SetFileName( filename );
  m_Reader->Update();

  m_ImageLoaded = true;

}


 
/************************************
 *
 *  Show Progress
 *
 ***********************************/
void
liFilterConsoleBase 
::ShowProgress( float )
{

}


 
/************************************
 *
 *  Show Status
 *
 ***********************************/
void
liFilterConsoleBase 
::ShowStatus( const char * )
{

}




 
/************************************
 *
 *  Set Sigma
 *
 ***********************************/
void
liFilterConsoleBase 
::SetSigma( ComputationType value )
{
  
  m_Hx->SetSigma( value );
  m_Hy->SetSigma( value );
  m_Hz->SetSigma( value );

  m_Hxy->SetSigma( value );
  m_Hyz->SetSigma( value );
  m_Hzx->SetSigma( value );

  m_H1x->SetSigma( value );
  m_H1y->SetSigma( value );
  m_H1z->SetSigma( value );

  m_H2x->SetSigma( value );
  m_H2y->SetSigma( value );
  m_H2z->SetSigma( value );

}




 
/************************************
 *
 *  Execute
 *
 ***********************************/
void
liFilterConsoleBase 
::Execute( void )
{

  if( ! (m_ImageLoaded) ) 
  {
    ShowStatus("Please load an image first");
    return;
  }
  
  m_H1x->Update();
  m_H1y->Update();
  m_H1z->Update();

  m_H2x->Update();
  m_H2y->Update();
  m_H2z->Update();

  m_Add->Update();

  m_Modulus->Update();

}





 
/************************************
 *
 *  Write Gradient X
 *
 ***********************************/
void
liFilterConsoleBase 
::WriteGradientX( const char * filename )
{
//  m_Writer_Gradient_X->SetInput( m_H1x->GetOutput() );
//  m_Writer_Gradient_X->SetFileName( filename );
//  m_Writer_Gradient_X->Write();
}


   
/************************************
 *
 *  Write Gradient Y
 *
 ***********************************/
void
liFilterConsoleBase 
::WriteGradientY( const char * filename )
{
//  m_Writer_Gradient_Y->SetFileName( filename );
//  m_Writer_Gradient_Y->Write();
}



/************************************
 *
 *  Write Gradient Z
 *
 ***********************************/
void
liFilterConsoleBase 
::WriteGradientZ( const char * filename )
{
//  m_Writer_Gradient_Z->SetFileName( filename );
//  m_Writer_Gradient_Z->Write();
}



/************************************
 *
 *  Write Gradient Modulus
 *
 ***********************************/
void
liFilterConsoleBase 
::WriteGradientModulus( const char * filename )
{
//  m_Writer_Gradient_Modulus->SetFileName( filename );
//  m_Writer_Gradient_Modulus->Write();
}



/************************************
 *
 *  Write Laplacian
 *
 ***********************************/
void
liFilterConsoleBase 
::WriteLaplacian( const char * filename )
{
//  m_Writer_Laplacian->SetFileName( filename );
//  m_Writer_Laplacian->Write();
}



