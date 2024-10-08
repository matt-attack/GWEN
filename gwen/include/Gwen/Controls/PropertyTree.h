/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_PROPERTYTREE_H
#define GWEN_CONTROLS_PROPERTYTREE_H

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Gwen.h"
#include "Gwen/Skin.h"
#include "Gwen/Controls/TreeControl.h"
#include "Gwen/Controls/Properties.h"


namespace Gwen
{
	namespace Controls
	{
		class PropertyTreeNode : public TreeNode
		{
			public:

				GWEN_CONTROL_INLINE( PropertyTreeNode, TreeNode )
				{
					m_Title->SetTextColorOverride( GetSkin()->Colors.Properties.Title );
				}

				virtual void Render( Skin::Base* skin ) override
				{
					skin->DrawPropertyTreeNode( this, m_InnerPanel->X(), m_InnerPanel->Y() );
				}

		};

		class PropertyTree : public TreeControl
		{
			public:

				GWEN_CONTROL_INLINE( PropertyTree, TreeControl )
				{
				}

				Properties* Add( const TextObject & text );
				Properties* Find( const TextObject & text );
		};

	}
}
#endif
