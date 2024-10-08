/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/


#include <math.h>
#include "Gwen/Controls/Slider.h"

using namespace Gwen;
using namespace Gwen::Controls;
using namespace Gwen::ControlsInternal;

GWEN_CONTROL_CONSTRUCTOR( SliderBar )
{
	SetTarget( this );
	RestrictToParent( true );
}

void SliderBar::Render( Skin::Base* skin )
{
	skin->DrawSlideButton( this, IsDepressed(), IsHorizontal(), IsHovered() );
}


GWEN_CONTROL_CONSTRUCTOR( Slider )
{
	SetBounds( Gwen::Rect( 0, 0, 32, 128 ) );
	m_SliderBar = new SliderBar( this );
	m_SliderBar->onDragged.Add( this, &Slider::OnMoved );
	m_fMin = 0.0f;
	m_fMax = 1.0f;
	m_bClampToNotches = false;
	m_iNumNotches = 5;
	m_fValue = 0.0f;
	SetTabable( true );
}

void Slider::OnMoved( Controls::Base* /*control*/ )
{
	SetValueInternal( CalculateValue() );
}

void Slider::Layout( Skin::Base* skin )
{
	BaseClass::Layout( skin );
}

double Slider::CalculateValue()
{
	return 0;
}

void Slider::SetFloatValue( double val, bool /*forceUpdate*/ )
{
	if ( val < m_fMin ) { val = m_fMin; }

	if ( val > m_fMax ) { val = m_fMax; }

	// Normalize Value
	val = ( val - m_fMin ) / ( m_fMax - m_fMin );
	SetValueInternal( val );
	Redraw();
}

void Slider::SetValueInternal( double val )
{
	if ( m_bClampToNotches )
	{
		val = floorf( ( val * ( double ) m_iNumNotches ) + 0.5f );
		val /= ( double ) m_iNumNotches;
	}

	if ( m_fValue != val )
	{
		m_fValue = val;
		onValueChanged.Call( this );
	}

	UpdateBarFromValue();
}

double Slider::GetFloatValue()
{
	return m_fMin + ( m_fValue * ( m_fMax - m_fMin ) );
}

void Slider::SetRange( double fMin, double fMax )
{
	m_fMin = fMin;
	m_fMax = fMax;
}

void Slider::RenderFocus( Gwen::Skin::Base* skin )
{
	if ( Gwen::KeyboardFocus != this ) { return; }

	if ( !IsTabable() ) { return; }

	skin->DrawKeyboardHighlight( this, GetRenderBounds(), 0 );
}

void Slider::OnBoundsChanged(Gwen::Rect oldBounds)
{
	BaseClass::OnBoundsChanged( oldBounds );
	UpdateBarFromValue();
}
