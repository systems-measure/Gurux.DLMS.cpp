//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#include "../include/GXDLMSLimits.h"

const unsigned char DEFAULT_MAX_INFO_RX = 128;
const unsigned char DEFAULT_MAX_INFO_TX = 128;
const unsigned char DEFAULT_WINDOWS_SIZE_RX = 1;
const unsigned char DEFAULT_WINDOWS_SIZE_TX = 1;

const unsigned char CGXDLMSLimits::defLimits[4] = { DEFAULT_MAX_INFO_RX, DEFAULT_MAX_INFO_TX, DEFAULT_WINDOWS_SIZE_RX, DEFAULT_WINDOWS_SIZE_TX };

CGXDLMSLimits::CGXDLMSLimits()
{
	SetDefaultLimits();
}

unsigned short CGXDLMSLimits::GetMaxInfoTX()
{
    return m_MaxInfoTX;
}

void CGXDLMSLimits::SetMaxInfoTX(unsigned short value)
{
    m_MaxInfoTX = value;
}

void CGXDLMSLimits::DefaultInfoTX() 
{
	m_MaxInfoTX = DEFAULT_MAX_INFO_TX;
}

unsigned short CGXDLMSLimits::GetMaxInfoRX()
{
    return m_MaxInfoRX;
}

void CGXDLMSLimits::SetMaxInfoRX(unsigned short value)
{
    m_MaxInfoRX = value;
}

void CGXDLMSLimits::DefaultInfoRX() 
{
	m_MaxInfoRX = DEFAULT_MAX_INFO_RX;
}

unsigned char CGXDLMSLimits::GetWindowSizeTX()
{
    return m_WindowSizeRX;
}

void CGXDLMSLimits::SetWindowSizeTX(unsigned char value)
{
    m_WindowSizeRX = value;
}

void CGXDLMSLimits::DefaultWindowSizeTX() 
{
	m_WindowSizeRX = DEFAULT_WINDOWS_SIZE_TX;
}

unsigned char CGXDLMSLimits::GetWindowSizeRX()
{
    return m_WindowSizeTX;
}

void CGXDLMSLimits::SetWindowSizeRX(unsigned char value)
{
    m_WindowSizeTX = value;
}

void CGXDLMSLimits::DefaultWindowSizeRX() 
{
	m_WindowSizeTX = DEFAULT_WINDOWS_SIZE_RX;
}

void CGXDLMSLimits::SetDefaultLimits() {
	m_MaxInfoTX = DEFAULT_MAX_INFO_TX;
	m_MaxInfoRX = DEFAULT_MAX_INFO_RX;
	m_WindowSizeTX = DEFAULT_WINDOWS_SIZE_TX;
	m_WindowSizeRX = DEFAULT_WINDOWS_SIZE_RX;
}


