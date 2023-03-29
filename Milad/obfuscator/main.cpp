#include "headers/require.h"

BASE g_CallGate = { 0 };

int main(int argc, char* argv[])
{
	obfuscation::load();
	g_CallGate._MessageBoxW(NULL, L"I am an anonymous call.", L"Obfuscated Runtime", MB_OKCANCEL);

	return 0;
}