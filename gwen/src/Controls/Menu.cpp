/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/


#include "Gwen/Gwen.h"
#include "Gwen/Controls/Menu.h"
#include "Gwen/Skin.h"
#include "Gwen/Utility.h"

using namespace Gwen;
using namespace Gwen::Controls;




GWEN_CONTROL_CONSTRUCTOR( Menu )
{
	SetBounds( 0, 0, 10, 10 );
	SetPadding( Padding( 2, 2, 2, 2 ) );
	SetDisableIconMargin( false );
	SetAutoHideBars( true );
	SetScroll( false, true );
	SetDeleteOnClose( false );
}


void Menu::Render( Skin::Base* skin )
{
	skin->DrawMenu( this, IconMarginDisabled() );
}

void Menu::RenderUnder( Skin::Base* skin )
{
	BaseClass::RenderUnder( skin );
	skin->DrawShadow( this );
}

void Menu::Layout( Skin::Base* skin )
{
	int childrenHeight = 0;

	int w = 0;
	for ( Base::List::iterator it = m_InnerPanel->Children.begin(); it != m_InnerPanel->Children.end(); ++it )
	{
		Base* pChild = ( *it );

		if ( !pChild )
		{ continue; }
		
		w = std::max(w, pChild->GetMinimumSize().x + 10 + 32);
		
		pChild->SetHeight(pChild->GetMinimumSize().y);

		childrenHeight += pChild->Height();
	}

	if ( Y() + childrenHeight > GetCanvas()->Height() )
	{ childrenHeight = GetCanvas()->Height() - Y(); }

	SetSize( w, childrenHeight );
	BaseClass::Layout( skin );
}

MenuItem* Menu::AddItem( const TextObject & strName, const TextObject & strIconName, const TextObject & strAccelerator )
{
	MenuItem* pItem = new MenuItem( this );
	pItem->SetPadding( Padding( 2, 4, 4, 4 ) );
	pItem->SetText( strName );
	pItem->SetImage( strIconName );
	pItem->SetAccelerator( strAccelerator );
	OnAddItem( pItem );
	return pItem;
}

void Menu::OnAddItem( MenuItem* item )
{
	item->SetTextPadding( Padding( IconMarginDisabled() ? 0 : 24, 0, 16, 0 ) );
	item->Dock( Pos::Top );
	item->SizeToContents();
	item->SetAlignment( Pos::CenterV | Pos::Left );
	item->onHoverEnter.Add( this, &Menu::OnHoverItem );
	// Do this here - after Top Docking these values mean nothing in layout
	int w = item->GetMinimumSize().y + 10 + 32;

	if ( w < Width() ) { w = Width(); }

	SetSize( w, Height() );
}

void Menu::ClearItems()
{
	for ( Base::List::iterator it = m_InnerPanel->Children.begin(); it != m_InnerPanel->Children.end(); ++it )
	{
		Base* pChild = *it;

		if ( !pChild ) { continue; }

		pChild->DelayedDelete();
	}
}

void Menu::CloseAll()
{
	for ( Base::List::iterator it = m_InnerPanel->Children.begin(); it != m_InnerPanel->Children.end(); ++it )
	{
		Base* pChild = *it;
		MenuItem* pItem = gwen_cast<MenuItem> ( pChild );

		if ( !pItem ) { continue; }

		pItem->CloseMenu();
	}
}

bool Menu::IsMenuOpen()
{
	for ( Base::List::iterator it = m_InnerPanel->Children.begin(); it != m_InnerPanel->Children.end(); ++it )
	{
		Base* pChild = *it;
		MenuItem* pItem = gwen_cast<MenuItem> ( pChild );

		if ( !pItem ) { continue; }

		if ( pItem->IsMenuOpen() )
		{ return true; }
	}

	return false;
}

void Menu::OnHoverItem( Gwen::Controls::Base* pControl )
{
	if ( !ShouldHoverOpenMenu() ) { return; }

	MenuItem* pItem = gwen_cast<MenuItem> ( pControl );

	if ( !pItem ) { return; }

	if ( pItem->IsMenuOpen() ) { return; }

	CloseAll();
	pItem->OpenMenu();
}

void Menu::Open( unsigned int iPos )
{
	SetHidden( false );
	BringToFront();
	Gwen::Point MousePos = Input::GetMousePosition();
	MousePos -= GetCanvas()->WindowPosition();
	SetPos( MousePos.x, MousePos.y );
}

void Menu::Close()
{
	SetHidden( true );

	if ( DeleteOnClose() )
	{
		DelayedDelete();
	}
}

void Menu::CloseMenus()
{
	BaseClass::CloseMenus();
	CloseAll();
	Close();
	onMenuClosed.Call(this);
}

void Menu::AddDivider()
{
	MenuDivider* divider = new MenuDivider( this );
	divider->Dock( Pos::Top );
	divider->SetMargin( Margin( IconMarginDisabled() ? 0 : 24, 0, 4, 0 ) );
}

void MenuDivider::Render( Gwen::Skin::Base* skin )
{
	skin->DrawMenuDivider( this );
}
