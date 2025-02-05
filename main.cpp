#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <ws2bth.h>
#include <Windows.h>
#include <iostream>
#include <cstdio>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
    //WSADATA data;
    //memset(&data, 0, sizeof(data));
    //int error = WSAStartup(MAKEWORD(2, 2), &data);

    //if (error != 0) {
    //    std::cerr << "WSAStartup() failed, error: " << error;
    //    return -1;
    //}
   

    //WSAQUERYSET queryset;
    //memset(&queryset, 0, sizeof(WSAQUERYSET));
    //queryset.dwSize = sizeof(WSAQUERYSET);
    //queryset.dwNameSpace = NS_BTH;
    //HANDLE hLookup;
    //error = WSALookupServiceBegin(&queryset, LUP_CONTAINERS, &hLookup);
    //if (error != 0)
    //{
    //    std::cout << "error in initialising look up service\n";
    //    exit(error);
    //}

    //BYTE buffer[4096];
    //memset(buffer, 0, sizeof(buffer));
    //DWORD bufferLength = sizeof(buffer);
    //WSAQUERYSET* pResults = (WSAQUERYSET*)&buffer;

    //while (error == 0)
    //{
    //    error = WSALookupServiceNext(hLookup, LUP_RETURN_NAME | LUP_CONTAINERS | LUP_RETURN_ADDR | LUP_FLUSHCACHE | LUP_RETURN_TYPE | LUP_RETURN_BLOB | LUP_RES_SERVICE, &bufferLength, pResults);
    //    if (error == 0)
    //    {
    //        //DEVICE FOUND
    //        LPTSTR s = pResults->lpszServiceInstanceName;
    //        BTH_ADDR b = ((SOCKADDR_BTH*)pResults->lpcsaBuffer->RemoteAddr.lpSockaddr)->btAddr;
    //        unsigned long l = pResults->lpServiceClassId->Data1;
    //       
    //        std::wcout << s << std::endl;
    //        std::cout << std::hex << b << std::endl;

    //        std::wcout << l << std::endl;
    //        Sleep(1000);
    //    }
    //}
    //
   
    //WSALookupServiceEnd(hLookup);
    //return 0;

    //----------------------------------------------------------------------------------------
    WSADATA wsa;
    memset(&wsa, 0, sizeof(wsa));

    int error = WSAStartup(MAKEWORD(2, 2), &wsa);

    if (error != 0) {
        std::cerr << "WSAStartup() failed, error: " << error;
        return -1;
    }
    
   
    SOCKET btSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);

    if (btSocket == INVALID_SOCKET) {
        error = WSAGetLastError();
        std::cerr << "socket() failed, error: " << error;
        WSACleanup();
        return -1;
    }
    std::cout << "WINSOCK: 'btSocket' Return Code: " << WSAGetLastError() << "\r\n";

    SOCKADDR_BTH sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.addressFamily = AF_BTH;
    sockAddr.serviceClassId = RFCOMM_PROTOCOL_UUID;
    sockAddr.port = BT_PORT_ANY;
    sockAddr.btAddr = BTH_ADDR(0x4f34e0e74079);
   
    ////str2ba("90:CB:A3:96:0E:F2", &sockAddr.btAddr);

    if (connect(btSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR) {
        error = WSAGetLastError();
        std::cerr << "connect() failed, error: " << error;
        closesocket(btSocket);
        WSACleanup();
        return -1;
    }

    closesocket(btSocket);

    return 0;
}

//int str2ba(const char* straddr, BTH_ADDR* btaddr)
//{
//    int i;
//    unsigned int aaddr[6];
//    BTH_ADDR tmpaddr = 0;

//    if (std::sscanf(straddr, "%02x:%02x:%02x:%02x:%02x:%02x",
//        &aaddr[0], &aaddr[1], &aaddr[2],
//        &aaddr[3], &aaddr[4], &aaddr[5]) != 6)
//        return 1;
//    *btaddr = 0;
//    for (i = 0; i < 6; i++) {
//        tmpaddr = (BTH_ADDR)(aaddr[i] & 0xff);
//        *btaddr = ((*btaddr) << 8) + tmpaddr;
//    }
//    return 0;
//}
