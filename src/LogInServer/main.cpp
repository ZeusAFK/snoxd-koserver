#include "stdafx.h"

LoginServer * g_pMain;
static Condition s_hEvent;

#ifdef WIN32
BOOL WINAPI _ConsoleHandler(DWORD dwCtrlType);
#endif

int main()
{
	LoginServer pMain;

	SetConsoleTitle("Login server for Knight Online v" STRINGIFY(__VERSION));

#ifdef WIN32
	// Override the console handler
	SetConsoleCtrlHandler(_ConsoleHandler, TRUE);
#else
	/* TO-DO: Signals */
#endif

	g_pMain = &pMain;

	// Startup server
	if (g_pMain->Startup())
	{
		printf("\nServer started up successfully!\n");

		// Wait until console's signaled as closing
		s_hEvent.Wait();
	}
	else
	{
#ifdef WIN32
		system("pause");
#endif
	}
	printf("Server shutting down, please wait...\n");

	return 0;
}

#ifdef WIN32
BOOL WINAPI _ConsoleHandler(DWORD dwCtrlType)
{
	s_hEvent.BeginSynchronized();
	s_hEvent.Signal();
	s_hEvent.EndSynchronized();
	sleep(10000); // Win7 onwards allows 10 seconds before it'll forcibly terminate
	return TRUE;
}
#endif