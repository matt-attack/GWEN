#include "Gwen/UnitTest/UnitTest.h"
#include "Gwen/Controls/NumericUpDown.h"
#include "Gwen/Controls/Button.h"
#include "Gwen/Controls/Layout/Form.h"

using namespace Gwen;

class FormLayout : public GUnit
{
	public:

		GWEN_CONTROL_INLINE( FormLayout, GUnit )
		{	
			this->Dock(Gwen::Pos::Fill);
			auto layout = new Controls::Layout::Form(this);
			layout->Dock(Gwen::Pos::Fill);
			Controls::NumericUpDown* pCtrl = new Controls::NumericUpDown( layout );
			pCtrl->SetBounds( 10, 10, 50, 20 );
			pCtrl->SetValue( 50 );
			pCtrl->SetMax( 1000 );
			pCtrl->SetMin( -1000 );
			layout->AddRow(L"Test", pCtrl);

			pCtrl = new Controls::NumericUpDown( layout );
			pCtrl->SetBounds( 10, 10, 50, 20 );
			pCtrl->SetValue( 50 );
			pCtrl->SetMax( 1000 );
			pCtrl->SetMin( -1000 );
			layout->AddRow(L"Test Longer", pCtrl);

			pCtrl = new Controls::NumericUpDown( layout );
			pCtrl->SetBounds( 10, 10, 50, 20 );
			pCtrl->SetValue( 50 );
			pCtrl->SetMax( 1000 );
			pCtrl->SetMin( -1000 );
			layout->AddRow(L"Test 2", pCtrl);

			Controls::Button* pButtonA = new Controls::Button( this );
			pButtonA->SetText( L"Button Tester" );
			layout->AddRow(pButtonA);
		}

};



DEFINE_UNIT_TEST( FormLayout, L"FormLayout" );
