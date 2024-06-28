/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_LAYOUT_FORM_H
#define GWEN_CONTROLS_LAYOUT_FORM_H

#include "Gwen/Controls/Label.h"
#include "Gwen/Utility.h"


namespace Gwen
{
	namespace Controls
	{
		namespace Layout
		{
			class GWEN_EXPORT Form : public Base
			{
				std::vector<std::pair<Label*, Base*>> m_Rows;
				public:

					GWEN_CONTROL_INLINE( Form, Base )
					{
					}

					void Layout( Skin::Base* skin ) override
					{
						// determine label width
						int w = 0;
						for ( auto& r: m_Rows )
						{
							if (!r.first) continue;
							r.first->SizeToContents();
							w = std::max(r.first->Width(), w);
						}
						// layout the rows
						int h = 0;
						for ( auto& r: m_Rows )
						{
							r.second->SetPos(w + 3, h);
							r.second->SetWidth(Width() - (w + 3));
							int nh = r.second->Height();
							nh = std::max(nh, r.second->GetMinimumSize().y);
							r.second->SetHeight(nh);
							if (r.first)
							{
								r.first->SetPos(0, h);
								nh = std::max(nh, r.first->Height());
							}
							//printf("w %i h %i\n", w, h);
							h += nh + 3;// todo variable padding
						}
						SetHeight(std::max(Height(), h));
					}

					void AddRow(const Gwen::UnicodeString& label, Base* control)
					{
						Gwen::Controls::Label* l = new Gwen::Controls::Label( this );
						l->SetText( label );
						l->SizeToContents();
						m_Rows.push_back({l, control});
						Invalidate();
					}

					void AddRow(Base* control)
					{
						m_Rows.push_back({0, control});
						Invalidate();
					}

				private:

			};
		}
	}
}
#endif
