/*
	GWEN
	Copyright (c) 2011 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_TREENODE_H
#define GWEN_CONTROLS_TREENODE_H

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Button.h"
#include "Gwen/Controls/ScrollControl.h"


namespace Gwen
{
	namespace Controls
	{
		class TreeControl;

		class GWEN_EXPORT TreeNode : public Base
		{
			public:

				GWEN_CONTROL( TreeNode, Base );

				virtual TreeNode* AddNode( const TextObject & strLabel );

				virtual void SetText( const TextObject & text );
				virtual const TextObject & GetText();
				virtual void SetImage( const TextObject & text );

				virtual void Open();
				virtual void Close();

				virtual void CollapseAll();
				virtual void ExpandAll();

				virtual Button* GetButton();
				virtual Button* GetToggleButton();

				virtual void Render( Skin::Base* skin ) override;
				virtual void Layout( Skin::Base* skin ) override;
				virtual void PostLayout( Skin::Base* skin ) override;

				virtual void SetRoot( bool b ) { m_bRoot = b; }
				virtual void SetTreeControl( TreeControl* pCtrl ) { m_TreeControl = pCtrl; }

				virtual void SetSelectable( bool b ) { m_bSelectable = b; }
				virtual bool IsSelected() { return m_bSelected; }
				virtual void SetSelected( bool b, bool FireEvents = true );

				virtual void DeselectAll();

				virtual Controls::Base::List & GetChildNodes();
				virtual Controls::Base::List GetSelectedChildNodes();

				Event::Caller	onNamePress;
				Event::Caller   onDoubleClick;
				Event::Caller	onRightPress;
				Event::Caller	onSelectChange;
				Event::Caller	onSelect;
				Event::Caller	onUnselect;

			protected:

				void OnToggleButtonPress( Base* control );
				void OnDoubleClickName( Base* control );
				void OnRightPress( Base* control );
				void OnClickName( Base* control );

				TreeControl*	m_TreeControl;
				Button*			m_ToggleButton;
				Button*			m_Title;

				bool			m_bRoot;
				bool			m_bSelected;
				bool			m_bSelectable;
		};

	}
}
#endif
