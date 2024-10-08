/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_BASERENDER_H
#define GWEN_BASERENDER_H

#include "Gwen/Structures.h"
#include "Gwen/TextObject.h"

namespace Gwen
{
	struct Font;
	struct Texture;
	class WindowProvider;

	namespace Renderer
	{
		class Base;

		class ICacheToTexture
		{
			public:

				virtual ~ICacheToTexture() {}
				virtual void Initialize() = 0;
				virtual void ShutDown() = 0;
				virtual void SetupCacheTexture( Gwen::Controls::Base* control ) = 0;
				virtual void FinishCacheTexture( Gwen::Controls::Base* control ) = 0;
				virtual void DrawCachedControlTexture( Gwen::Controls::Base* control ) = 0;
				virtual void CreateControlCacheTexture( Gwen::Controls::Base* control ) = 0;
				virtual void UpdateControlCacheTexture( Gwen::Controls::Base* control ) = 0;
				virtual void SetRenderer( Gwen::Renderer::Base* renderer ) = 0;

		};

		class GWEN_EXPORT Base
		{
			public:

				Base();
				virtual ~Base();

				virtual void Init() = 0;

				virtual void Begin() = 0;
				virtual void End() = 0;

				virtual void EnableVSync(bool yn) {};

				virtual void SetDrawColor( Color color ) = 0;

				virtual void DrawFilledRect( Gwen::Rect rect ) = 0;

				virtual void StartClip() = 0;
				virtual void EndClip() = 0;

				virtual void LoadTexture( Gwen::Texture* pTexture ) {};
				virtual void FreeTexture( Gwen::Texture* pTexture ) {};
				virtual void DrawTexturedRect( Gwen::Texture* pTexture, Gwen::Rect pTargetRect, float u1 = 0.0f, float v1 = 0.0f, float u2 = 1.0f, float v2 = 1.0f ) = 0;
				virtual void DrawMissingImage( Gwen::Rect pTargetRect );
				virtual Gwen::Color PixelColour( Gwen::Texture* pTexture, unsigned int x, unsigned int y, const Gwen::Color & col_default = Gwen::Color( 255, 255, 255, 255 ) ) { return col_default; }

				virtual ICacheToTexture* GetCTT() { return NULL; }

				virtual void LoadFont( Gwen::Font* pFont ) {};
				virtual void FreeFont( Gwen::Font* pFont ) {};
				virtual void RenderText( Gwen::Font* pFont, Gwen::PointF pos, const Gwen::UnicodeString & text );
				virtual Gwen::PointF MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString & text );

				//
				// No need to implement these functions in your derived class, but if
				// you can do them faster than the default implementation it's a good idea to.
				//
				virtual void DrawLinedRect( Gwen::Rect rect );
				virtual void DrawPixel( int x, int y );
				virtual void DrawShavedCornerRect( Gwen::Rect rect, bool bSlight = false );
				virtual Gwen::PointF MeasureText( Gwen::Font* pFont, const Gwen::String & text );
				virtual void RenderText( Gwen::Font* pFont, Gwen::PointF pos, const Gwen::String & text );
				virtual Gwen::PointF MeasureText( Gwen::Font* pFont, const Gwen::TextObject & text );
				virtual void RenderText( Gwen::Font* pFont, Gwen::PointF pos, const Gwen::TextObject & text );

			public:

				//
				// Translate a panel's local drawing coordinate
				//  into view space, taking Offset's into account.
				//
				void Translate( int & x, int & y );
				void Translate( Gwen::Rect & rect );

				//
				// Set the rendering offset. You shouldn't have to
				// touch these, ever.
				//
				void SetRenderOffset( const Gwen::Point & offset ) { m_RenderOffset = offset; }
				void AddRenderOffset( const Gwen::Rect & offset ) { m_RenderOffset.x += offset.x; m_RenderOffset.y += offset.y; }
				const Gwen::Point & GetRenderOffset() const { return m_RenderOffset; }

			private:
			public:
				Gwen::Point m_RenderOffset;

			public:

				void SetClipRegion( Gwen::Rect rect );
				void AddClipRegion( Gwen::Rect rect );
				bool ClipRegionVisible();
				const Gwen::Rect & ClipRegion() const;

			private:

				Gwen::Rect m_rectClipRegion;
				ICacheToTexture* m_RTT;
				Gwen::PointF m_dpi = Gwen::PointF(96, 96);

			public:

				void SetScale( float fScale ) { m_fScale = fScale; }
				float Scale() const { return m_fScale; }
				
				void SetFontScale( float fScale ) { m_fFontScale = fScale; }
				float FontScale() const { return m_fFontScale; }

				float m_fScale;
				float m_fFontScale;


			public:

				//
				// Self Initialization, shutdown
				//

				virtual bool InitializeContext( Gwen::WindowProvider* pWindow ) { return false; }
				virtual bool ShutdownContext( Gwen::WindowProvider* pWindow ) { return false; }
				virtual bool ResizedContext( Gwen::WindowProvider* pWindow, int w, int h ) { return false; }

				virtual bool BeginContext( Gwen::WindowProvider* pWindow ) { return false; }
				virtual bool EndContext( Gwen::WindowProvider* pWindow ) { return false; }
				virtual bool PresentContext( Gwen::WindowProvider* pWindow ) { return false; }



		};
	}
}
#endif
