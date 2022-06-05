#include "ConsoleEngine.h"


void main()
{
	CCEngine *CCE = new CCEngine(false);
	CCE->Prepare(150, 40);

	CCE->Start();

	CCE->Complete();

}