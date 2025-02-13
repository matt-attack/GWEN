/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/


#include "Gwen/Gwen.h"
#include "Gwen/Skin.h"
#include "Gwen/Controls/DockedTabControl.h"
#include "Gwen/Controls/Highlight.h"
#include "Gwen/DragAndDrop.h"
#include "Gwen/Controls/WindowControl.h"

using namespace Gwen;
using namespace Gwen::Controls;

GWEN_CONTROL_CONSTRUCTOR( DockedTabControl )
{
	m_WindowControl = NULL;
	m_bAlwaysShowStrip = false;
	Dock( Pos::Fill );
	m_pTitleBar = new TabTitleBar( this );
	m_pTitleBar->Dock( Pos::Top );
	m_pTitleBar->SetHidden( true );
	SetAllowReorder( true );
}

void DockedTabControl::Layout( Skin::Base* skin )
{
	GetTabStrip()->SetHidden(m_bAlwaysShowStrip ? false : TabCount() <= 1 );
	UpdateTitleBar();
	BaseClass::Layout( skin );
}

void DockedTabControl::UpdateTitleBar()
{
	if ( !GetCurrentButton() ) { return; }

	m_pTitleBar->UpdateFromTab( GetCurrentButton(), m_WindowControl != 0);
}

void DockedTabControl::DragAndDrop_StartDragging( Gwen::DragAndDrop::Package* pPackage, int x, int y )
{
	BaseClass::DragAndDrop_StartDragging( pPackage, x, y );
	SetHidden( true );
	// This hiding our parent thing is kind of lousy.
	GetParent()->SetHidden( true );
}

void DockedTabControl::DragAndDrop_EndDragging( bool bSuccess, int x, int y )
{
	SetHidden( false );

	if ( !bSuccess )
	{
		GetParent()->SetHidden( false );
	}
	
	// On failure, pop out into a new window if we havent already been popped out
	// also only pop out popoutable windows
	if ( !bSuccess && !m_WindowControl )
	{
		// Pop out our tabs into a new window
		DockedTabControl* control = 0;
		Base::List Children = GetTabStrip()->Children;
		TabReturnButtonData return_data;
		for ( Base::List::iterator iter = Children.begin(); iter != Children.end(); ++iter )
		{
			TabButton* pButton = gwen_cast<TabButton> ( *iter );

			if ( !pButton ) { continue; }
			
			if (!pButton->IsPopoutable()) { continue; }
			
			if (!control)
			{
				Gwen::Point p = GetCanvas()->WindowPosition();
				control = pButton->PopOut(p.x + x - Gwen::DragAndDrop::CurrentPackage->holdoffset.x,
				                          p.y + y - Gwen::DragAndDrop::CurrentPackage->holdoffset.y, &return_data);
			}
			else
			{
				control->AddPage( pButton );
				
				TabReturnButtonData* data = new TabReturnButtonData;
				*data = return_data;
				pButton->UserData.Set<TabReturnButtonData*>("return_data", data);
			}
		}
		Invalidate();
	}
	
	// Delete our window if we were moved out of it
	if ( bSuccess && m_WindowControl && TabCount() == 0 )
	{
		auto wc = dynamic_cast<WindowCanvas*>(m_WindowControl);
		if (wc)
		{
			wc->InputQuit();
		}
		DelayedDelete();
	}
}

void DockedTabControl::MoveTabsTo( DockedTabControl* pTarget )
{
	Base::List Children = GetTabStrip()->Children;

	for ( Base::List::iterator iter = Children.begin(); iter != Children.end(); ++iter )
	{
		TabButton* pButton = gwen_cast<TabButton> ( *iter );

		if ( !pButton ) { continue; }

		pTarget->AddPage( pButton );
	}

	Invalidate();
}
