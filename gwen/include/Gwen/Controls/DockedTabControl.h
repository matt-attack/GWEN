/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_DOCKEDTABCONTROL_H
#define GWEN_CONTROLS_DOCKEDTABCONTROL_H

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/TabControl.h"
#include "Gwen/Controls/TabTitleBar.h"

namespace Gwen
{
	namespace Controls
	{
		class GWEN_EXPORT DockedTabControl : public TabControl
		{
			friend class TabButton;
			friend class TabTitleBar;
			public:

				GWEN_CONTROL( DockedTabControl, TabControl );

				void SetShowTitlebar( bool bShow ) { m_pTitleBar->SetHidden( !bShow ); }
				void SetAlwaysShowStrip( bool bShow ) { if (bShow != m_bAlwaysShowStrip) { m_bAlwaysShowStrip = bShow; Invalidate(); } }

				void Layout( Skin::Base* skin ) override;
				void UpdateTitleBar();

				virtual void DragAndDrop_StartDragging( Gwen::DragAndDrop::Package* pPackage, int x, int y ) override;
				virtual void DragAndDrop_EndDragging( bool bSuccess, int x, int y ) override;

				void MoveTabsTo( DockedTabControl* pTarget );

				TabTitleBar* GetTitleBar()
				{
					return this->m_pTitleBar;
				}

			private:

				bool            m_bAlwaysShowStrip;
				TabTitleBar*	m_pTitleBar;
				Base*			m_WindowControl;

		};
	}
}
#endif
